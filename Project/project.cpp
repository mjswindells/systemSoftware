#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <locale.h>
#include <ncurses.h>
#include <pwd.h>
#include <stack>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

using namespace std;

void myError(const char *msg);
string get_fileInfo(const char *pathname);
void printFile();
void fillCurdir();
void KeyEnter();

WINDOW *wcurdir, *wfile, *whelp, *wfileInfo;

vector<string> CurDir;
stack<string> frontDir, backDir;
int y = 0;
char pathname[256];

int main() {

    // curses모드를 시작
    initscr();
    // color모드 시작 색 넣기위함
    start_color();
    // 사용자에게 입력받은 문자 출력 x
    noecho();
    // 특수한 키들 사용 가능 ( 방향키 같은 거 )
    keypad(stdscr, TRUE);
    nonl();
    // setlocale(LC_ALL, "ko_KR.utf8");
    // setlocale(LC_CTYPE, "ko_KR.utf8");

    getcwd(pathname, 256);

    fillCurdir();

    // 검은 배경에 흰 글씨
    init_pair(1, 7, 0);
    // 파란 배경에 흰 글씨
    init_pair(2, 7, 4);

    wcurdir = newwin(1, 300, 0, 0);
    wfile = newwin(10, 300, 1, 0);
    whelp = newwin(1, 300, 11, 0);
    wfileInfo = newwin(50, 300, 12, 0);

    wbkgd(wcurdir, COLOR_PAIR(2));
    wbkgd(wfile, COLOR_PAIR(1));
    wbkgd(whelp, COLOR_PAIR(2));
    wbkgd(wfileInfo, COLOR_PAIR(1));

    wprintw(wcurdir, pathname);
    wprintw(whelp, "QUIT: Q   UP: k(PgUp)  DOWN: j(PgDn) Move Dir: Enter");

    refresh();
    printFile();
    wmove(wfile, 0, 0);

    wrefresh(wcurdir);
    wrefresh(whelp);
    wrefresh(wfileInfo);
    wrefresh(wfile);

    while (true) {
        int press = getch();
        if (press == 'q' | press == 'Q') {
            break;
        } else if (press == 'k' || press == 'K' || press == KEY_UP) {
            if (y > 0) {
                y--;
            } else {
                if (frontDir.empty())
                    continue;
                string tmp = frontDir.top();
                frontDir.pop();
                CurDir.insert(CurDir.begin(), tmp);
                tmp = CurDir.back();
                CurDir.pop_back();
                backDir.push(tmp);
            }
        } else if (press == 'j' || press == 'J' || press == KEY_DOWN) {
            if (y < 9 && CurDir.size() - 1 > y) {
                y++;
            } else {
                if (backDir.empty())
                    continue;
                string tmp = backDir.top();
                CurDir.push_back(tmp);
                backDir.pop();
                tmp = CurDir.front();
                CurDir.erase(CurDir.begin());
                frontDir.push(tmp);
            }
        } else if (press == '\r' || press == 'e') {
            KeyEnter();
        } else {
            continue;
        }

        wclear(wfile);
        printFile();
        wmove(wfile, y, 0);
        wrefresh(wcurdir);
        wrefresh(wfileInfo);
        wrefresh(wfile);
    }
    endwin();

    return 0;
}

void myError(const char *msg) {
    endwin();
    perror(msg);
    exit(-1);
}

string get_fileInfo(const char *pathname) {
    struct stat fileInfo;
    struct passwd *userInfo;
    if (stat(pathname, &fileInfo) == -1) {
        myError("stat_get() error! ");
    }
    userInfo = getpwuid(fileInfo.st_uid);

    string rtn = "";

    char str[256];
    strcpy(str, pathname);
    char *temp = strtok(str, "/");
    char *path;
    while (temp != NULL) {
        path = temp;
        temp = strtok(NULL, "/");
    }

    rtn += " [ ";
    // file type
    if (S_ISREG(fileInfo.st_mode)) {
        rtn += "-";
    } else if (S_ISDIR(fileInfo.st_mode)) {
        rtn += "d";
    } else if (S_ISLNK(fileInfo.st_mode)) {
        rtn += "l";
    } else if (S_ISFIFO(fileInfo.st_mode)) {
        rtn += "p";
    } else if (S_ISCHR(fileInfo.st_mode)) {
        rtn += "c";
    } else if (S_ISBLK(fileInfo.st_mode)) {
        rtn += "b";
    }
    // User
    if (S_IRUSR & fileInfo.st_mode) {
        rtn += "r";
    } else {
        rtn += "-";
    }
    if (S_IWUSR & fileInfo.st_mode) {
        rtn += "w";
    } else {
        rtn += "-";
    }
    if (S_IXUSR & fileInfo.st_mode) {
        rtn += "x";
    } else {
        rtn += "-";
    }
    // Group
    if (S_IRGRP & fileInfo.st_mode) {
        rtn += "r";
    } else {
        rtn += "-";
    }
    if (S_IWGRP & fileInfo.st_mode) {
        rtn += "w";
    } else {
        rtn += "-";
    }
    if (S_IXGRP & fileInfo.st_mode) {
        rtn += "x";
    } else {
        rtn += "-";
    }
    // Others
    if (S_IROTH & fileInfo.st_mode) {
        rtn += "r";
    } else {
        rtn += "-";
    }
    if (S_IWOTH & fileInfo.st_mode) {
        rtn += "w";
    } else {
        rtn += "-";
    }
    if (S_IXOTH & fileInfo.st_mode) {
        rtn += "x";
    } else {
        rtn += "-";
    }
    rtn += " ";

    // 소유자
    rtn += userInfo->pw_name;
    // file size
    double size = fileInfo.st_size;
    if (size < 1000) {
        rtn += "  ";
        string tmp = to_string(size).substr(0, 5);
        rtn += tmp;
        rtn += " ]  ";
    } else {
        double ssize = size;
        ssize /= 1000;
        rtn += " ";
        string tmp = to_string(ssize).substr(0, 5);
        rtn += tmp;
        rtn += "K ]  ";
    }
    // 파일 이름
    rtn += path;

    return rtn;
}

void fillCurdir() {
    CurDir.clear();
    while (!frontDir.empty())
        frontDir.pop();
    while (!backDir.empty())
        backDir.pop();

    DIR *dirp = opendir(pathname);
    struct dirent **dirs;
    int count;
    if ((count = scandir(pathname, &dirs, NULL, alphasort)) == -1) {
        myError("scandir() Error :");
        return;
    }
    int i;
    for (i = 0; i < count; i++) {
        char full_path[256] = "";
        strcpy(full_path, pathname);
        strcat(full_path, "/");
        strcat(full_path, dirs[i]->d_name);
        if (i > 9) {
            backDir.push(full_path);
        } else {
            CurDir.push_back(full_path);
        }
    }
    for (int i = 0; i < count; i++)
        free(dirs[i]);
    free(dirs);
    closedir(dirp);
}

void printFile() {
    for (int i = 0; i < CurDir.size(); i++) {
        string tmp = get_fileInfo(CurDir[i].c_str());
        mvwprintw(wfile, i, 0, tmp.c_str());
    }
}

void KeyEnter() {
    string path_ = CurDir[y];
    struct stat fileInfo;
    if (stat(path_.c_str(), &fileInfo) == -1) {
        myError("stat error! ");
    }
    if (S_ISDIR(fileInfo.st_mode)) {
        vector<string> spl;
        char tmp[256];
        strcpy(tmp, CurDir[y].c_str());
        char *tok = strtok(tmp, "/");
        while (tok != NULL) {
            spl.push_back(tok);
            tok = strtok(NULL, "/");
        }
        string path;
        if ((!strcmp(spl.back().c_str(), "."))) {
            return;
        } else if (!strcmp(spl.back().c_str(), "..")) {
            path += "/";
            for (int i = 0; i < spl.size() - 2; i++) {
                path += spl[i];
                path += "/";
            }
            path = path.substr(0, path.length() - 1);
            strcpy(pathname, path.c_str());
        } else {
            path += "/";
            for (int i = 0; i < spl.size(); i++) {
                path += spl[i];
                path += "/";
            }
            path = path.substr(0, path.length() - 1);
            strcpy(pathname, path.c_str());
        }
        wclear(wcurdir);
        wprintw(wcurdir, pathname);
        fillCurdir();
        y = 0;
    } else {
        // 파일일 때 코드
        // 채워여함~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
        wclear(wfileInfo);
        wprintw(wfileInfo, CurDir[y].c_str());
        wprintw(wfileInfo, "\n");
    }
}
