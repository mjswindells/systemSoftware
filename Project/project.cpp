#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <locale.h>
#include <ncursesw/curses.h>
#include <pwd.h>
#include <queue>
#include <stack>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

using namespace std;

void myError(const char *msg);
string get_fileInfo(const char *ppathname);
bool isExist(const char *path);
void printFile();
void fillCurdir();
void KeyEnter();

WINDOW *wcurdir, *wfile, *whelp, *wfileInfo;

vector<string> CurDir;
stack<string> frontDir, backDir;
queue<string> tempDir;

pid_t pid = 0;
int status = 0;
int y = 0;
char pathname[256];
char temppath[256];

bool mv = false;
bool cp = false;

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
    setlocale(LC_ALL, "ko_KR.utf8");
    setlocale(LC_CTYPE, "ko_KR.utf8");

    getcwd(pathname, 256);

    fillCurdir();

    // 검은 배경에 흰 글씨
    init_pair(1, 7, 0);
    // 파란 배경에 흰 글씨
    init_pair(2, 7, 4);

    wcurdir = newwin(1, 300, 0, 0);
    wfile = newwin(10, 300, 1, 0);
    whelp = newwin(1, 300, 11, 0);
    wfileInfo = newwin(30, 300, 12, 0);

    wbkgd(wcurdir, COLOR_PAIR(2));
    wbkgd(wfile, COLOR_PAIR(1));
    wbkgd(whelp, COLOR_PAIR(2));
    wbkgd(wfileInfo, COLOR_PAIR(1));

    wprintw(wcurdir, pathname);
    wprintw(whelp, "HELP : H ");

    refresh();
    printFile();
    wmove(wfile, 0, 34);

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
                if (!backDir.empty()) {
                    string tmp = backDir.top();
                    CurDir.push_back(tmp);
                    backDir.pop();
                    tmp = CurDir.front();
                    CurDir.erase(CurDir.begin());
                    frontDir.push(tmp);
                } else if (!tempDir.empty()) {
                    string tmp = tempDir.front();
                    CurDir.push_back(tmp);
                    tempDir.pop();
                    tmp = CurDir.front();
                    CurDir.erase(CurDir.begin());
                    frontDir.push(tmp);
                }
            }
        } else if (press == '\r' || press == 'e' || press == 'E') {
            if (mv) {
                if (!strcmp(temppath, CurDir[y].c_str())) {
                } else {
                    KeyEnter();
                }
            } else {
                KeyEnter();
            }
        } else if (press == 'h' || press == 'H') {
            wclear(wfileInfo);
            wprintw(wfileInfo, "CHECK\t: Enter\nQUIT\t: Q\nUP\t: "
                               "k(PgUp)\nDOWN\t: j(PgDn)\nDELETE\t: D\n");
            wprintw(wfileInfo, "MOVE\t: M\nCOPY\t: C\n");
        } else if (press == 'd' || press == 'D') {
            wclear(whelp);
            wprintw(whelp, "delete? [y/n]");
            wrefresh(whelp);
            press = getchar();
            if (press == 'y' || press == 'Y') {
                pid = fork();
                if (pid == 0) {
                    execl("/bin/rm", "rm", "-rf", CurDir[y].c_str(),
                          (char *)NULL);
                    exit(0);
                } else {
                    wait(&status);
                    fillCurdir();
                    y = 0;
                }
            }
        } else if (press == 'm' || press == 'M') {
            if (mv) {
                if (isExist(temppath)) {
                    wclear(whelp);
                    wprintw(whelp, "Exist same name");
                    wrefresh(whelp);
                    continue;
                } else {
                    pid = fork();
                    if (pid == 0) {
                        execl("/bin/mv", "mv", temppath, pathname,
                              (char *)NULL);
                        exit(0);
                    } else {
                        wait(&status);
                        mv = false;
                        strcpy(temppath, "");
                        fillCurdir();
                        y = 0;
                    }
                }
            } else {
                strcpy(temppath, CurDir[y].c_str());
                mv = true;
            }
        } else if (press == 'c' || press == 'C') {
            if (cp) {
                if (isExist(temppath)) {
                    wclear(whelp);
                    wprintw(whelp, "Exist same name");
                    wrefresh(whelp);
                    continue;
                } else {
                    pid = fork();
                    if (pid == 0) {
                        execl("/bin/cp", "cp", "-r", temppath, pathname,
                              (char *)NULL);
                        exit(0);
                    } else {
                        wait(&status);
                        cp = false;
                        strcpy(temppath, "");
                        fillCurdir();
                        y = 0;
                    }
                }
            } else {
                strcpy(temppath, CurDir[y].c_str());
                cp = true;
            }
        }

        wclear(wfile);
        wclear(whelp);
        if (mv) {
            wprintw(whelp, "Move : ");
            wprintw(whelp, temppath);
        } else if (cp) {
            wprintw(whelp, "Copy : ");
            wprintw(whelp, temppath);
        } else {
            wprintw(whelp, "HELP : H ");
        }
        printFile();
        wmove(wfile, y, 34);

        wrefresh(wcurdir);
        wrefresh(whelp);
        wrefresh(whelp);
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

string get_fileInfo(const char *ppathname) {
    struct stat fileInfo;
    struct passwd *userInfo;
    if (stat(ppathname, &fileInfo) == -1) {
        myError("stat_get() error! ");
    }
    userInfo = getpwuid(fileInfo.st_uid);

    string rtn = "";

    char str[256];
    strcpy(str, ppathname);
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

bool isExist(const char *path) {
    char str[256];
    strcpy(str, path);
    char *temp = strtok(str, "/");
    char *path_;
    while (temp != NULL) {
        path_ = temp;
        temp = strtok(NULL, "/");
    }
    DIR *dirp = opendir(pathname);
    struct dirent *dirInfo;
    while ((dirInfo = readdir(dirp)) != NULL) {
        if (!strcmp(path_, dirInfo->d_name)) {
            closedir(dirp);
            return true;
        }
    }

    closedir(dirp);
    return false;
}

void fillCurdir() {
    CurDir.clear();
    while (!frontDir.empty())
        frontDir.pop();
    while (!backDir.empty())
        backDir.pop();
    while (!tempDir.empty()) {
        tempDir.pop();
    }

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
            tempDir.push(full_path);
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
        char buf[1025] = {
            '\0',
        };
        int fd = open(CurDir[y].c_str(), O_RDONLY);
        if (fd == -1) {
            myError("open() error!");
        }
        ssize_t rsize = 0;
        ssize_t tsize = 0;

        wclear(wfileInfo);
        wprintw(wfileInfo, CurDir[y].c_str());
        wprintw(wfileInfo, "\n");
        do {
            memset(buf, '\0', 1025);
            rsize = read(fd, buf, 1024);
            if (rsize == -1) {
                myError("read() error!");
            }
            wprintw(wfileInfo, buf);
            tsize += rsize;
        } while (rsize > 0);
        close(fd);
    }
}
