#include <dirent.h>
#include <iostream>
#include <ncurses.h>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#define MAX_PATH_LEN 1024
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

using namespace std;

// 프로그램을 실행한 위치의 디렉토리의 주소를 알아냄
stack<string> currentDir();

// 디렉토리 스택 표시용
string showDir(stack<string> stc);

// 디렉토리 내 파일 확인용
vector<dirent> searchFile(string dirString);

// 디렉토리 내 파일 표시용
void showFile(WINDOW *win, vector<dirent> fileList, int y);

stack<string> changeDir(stack<string> dirLocation, vector<dirent> fileList,
                        int y);

int main() {
    // dirLocal : 현재 디렉토리 위치
    // fileIn : 파일 탐색기
    // command : 명령어 및 현재 상태 안내바
    // fileShow : 파일 미리 보기
    WINDOW *dirLocal, *fileIn, *command, *fileShow;

    int press;

    // 디렉토리 저장용 스택
    stack<string> dirLocation;
    // 파일 목록 저장용 큐
    vector<dirent> fileList;
    // 파일 정보 탐색용
    struct stat buf;

    dirLocation = currentDir();

    int x = 1, y = 1;

    initscr();

    if (has_colors() == FALSE) {
        puts("Terminal does not support colors!");
        endwin();
        return 1;
    } else {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_BLACK, COLOR_WHITE);
        init_pair(3, COLOR_GREEN, COLOR_BLACK);
    }

    refresh();

    dirLocal = newwin(1, 100, 0, 0);
    fileIn = newwin(30, 100, 1, 0);
    command = newwin(1, 100, 31, 0);

    wborder(fileIn, '|', '|', '-', '-', '+', '+', '+', '+');

    wbkgd(dirLocal, COLOR_PAIR(2));
    wbkgd(fileIn, COLOR_PAIR(1));
    wbkgd(command, COLOR_PAIR(2));

    wprintw(dirLocal, showDir(dirLocation).c_str());
    fileList = searchFile(showDir(dirLocation));
    wprintw(command, "UP: i DOWN: k Move Dir: e");

    wmove(fileIn, y, x);

    noecho();

    showFile(fileIn, fileList, y);

    wrefresh(dirLocal);
    wrefresh(fileIn);
    wrefresh(command);

    while (true) {
        press = getch();
        if (press == 'q') {
            break;
        } else {
            switch (press) {
            case 'i':
                if (y <= 1)
                    break;
                y--;
                break;
            case 'k':
                if (y >= 28)
                    break;
                y++;
                break;
            case 'e':
                dirLocation = changeDir(dirLocation, fileList, y);
                fileList = searchFile(showDir(dirLocation));
                y = 1;
                break;
            default:
                continue;
            }
        }

        wclear(fileIn);
        wborder(fileIn, '|', '|', '-', '-', '+', '+', '+', '+');
        showFile(fileIn, fileList, y);
        wmove(fileIn, y, x);
        wrefresh(fileIn);
    }
    endwin();

    return 0;
}

stack<string> currentDir() {
    stack<string> stc;

    char dirChar[MAX_PATH_LEN + 1] = {
        '\0',
    };

    if (getcwd(dirChar, MAX_PATH_LEN) == NULL) {
        perror("getcwd error!");
        exit(-1);
    }

    string dirStr(dirChar);

    while (true) {
        int cursor = 0;

        if (dirStr.empty())
            break;

        cursor = dirStr.find("/", 1);
        // cout << cursor << endl;

        stc.push(dirStr.substr(1, cursor - 1));
        stc.top();

        dirStr.erase(0, cursor);
        // cout << dirStr << endl;
    }

    return stc;
}

string showDir(stack<string> stc) {
    stack<string> tmpStr = stc;
    string dirStr;

    while (true) {
        if (tmpStr.empty())
            break;

        dirStr.insert(0, tmpStr.top());
        dirStr.insert(0, "/");
        tmpStr.pop();
    }

    return dirStr;
}

vector<dirent> searchFile(string dirString) {
    DIR *dirp;
    struct dirent *dirInfo;
    vector<dirent> fileList;

    int i = 1;

    dirp = opendir(dirString.c_str());
    while ((dirInfo = readdir(dirp)) != NULL) {
        fileList.push_back(*dirInfo);
    }

    return fileList;
}

void showFile(WINDOW *win, vector<dirent> fileList, int y) {
    for (int i = 1; i < fileList.size(); i++) {
        mvwprintw(win, i, 1, fileList[i].d_name);
    }
}

stack<string> changeDir(stack<string> dirLocation, vector<dirent> fileList,
                        int y) {
    string targetDir(fileList[y].d_name);
    stack<string> tmpLocation = dirLocation;

    tmpLocation.push(targetDir);
    if (opendir(showDir(tmpLocation).c_str()) == NULL) {
        return dirLocation;
    }
    return tmpLocation;
}
