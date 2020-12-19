// main procedure of system
// uses asynchronous input
// uses timer signal : set_ticker.c
// uses non-blocking input mode (need to be set to nodelay mode)
// date : 2020-12-19-3:00am

#include"basiclib.h"
#include"linecode.h"

int set_ticker(int);
char getch(void);
void enable_kbd_signals(int);
int done = 0;
int sleepmode = 0;

int main(){
    // set variables
    // set signals
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    void on_timer(int);
    void on_input(int);
    enable_kbd_signals(1);
    signal(SIGIO, on_input);
    signal(SIGALRM, on_timer);
    set_ticker(10000);
    printf("%s", LINE1);
    printf("%s", LINE2);
    printf("%s", LINE3);
    printf("%s", LINE4);
    printf("%s", LINE5);
    printf("%s", LINE6);
    while(!done)
        pause();
    // if async signal is q, call quit() procedure & quit.
}

void on_input(int signum){
    int c = getch();
    if(c == EOF && sleepmode) fflush(stdout);
    if(c != EOF && sleepmode){
        void on_timer(int);
        // show the menu and wake up
        printf("%s", LINE1);
        printf("%s", LINE2);
        printf("%s", LINE3);
        printf("%s", LINE4);
        printf("%s", LINE5);
        printf("%s", LINE6);
        signal(SIGALRM, on_timer);
        sleepmode = 0;
        set_ticker(10000);
    }
    int pid;
    if(c == 'q'){
        done = 1;
        enable_kbd_signals(0);
    }
    else if(c == 't'){
        set_ticker(0);
        pid = fork();
        if(pid == 0){
            execl("./client", "./client", "127.0.1.1", "5500", NULL);
        }
        else wait(&pid);
        set_ticker(10000);
        printf("%s", NEXTCMD);
    }
    else if(c == 'l'){
        // fork, exelp 
        set_ticker(0);
        pid = fork();
        if(pid == 0){
            execl("./execute", "./execute", "showlist", NULL);
        }
        else wait(&pid);
        set_ticker(10000);
    }
    else if(c == 'r'){ // reserve
        set_ticker(0);
        enable_kbd_signals(0);
        pid = fork();
        if(pid == 0){
            execl("./execute", "./execute", "reserve", NULL);
        }
        else wait(&pid);
        set_ticker(10000);
        enable_kbd_signals(1);
    }
}

void on_timer(int signum){
    // if the program receives timer signal,
    // the program discards all of the data and
    // turn the sleep mode on
    // sleepmode? clear all of screen and wait for the input.
    signal(SIGALRM, SIG_IGN);
    set_ticker(0);
    sleepmode = 1;
    printf("\e[1;1H\e[2J");
    fflush(stdout);
}

void enable_kbd_signals(int mode){
    static int orig_flags;
    static struct termios orig_ttystate;
    static int stored = 0;
    int fd_flags;
    struct termios ttystate;
    if(mode == 1){ // 1 : set
        fcntl(0, F_SETOWN, getpid());
        fd_flags = fcntl(0, F_GETFL);
        orig_flags = fd_flags;
        fd_flags |= O_ASYNC;
        fd_flags |= O_NDELAY;
        fcntl(0, F_SETFL, fd_flags);

        // you should turn on in the reservation stage
        tcgetattr(0, &ttystate);
        tcgetattr(0, &orig_ttystate);
        ttystate.c_lflag &= ~ICANON;
        ttystate.c_lflag &= ~ECHO;
        ttystate.c_cc[VMIN] = 1; // per 1 char
        tcsetattr(0, TCSANOW, &ttystate);

        stored = 1;
    }
    if(mode == 0 && stored){ // 0 : restore
        fcntl(0, F_SETFL, orig_flags);
        tcsetattr(0, TCSANOW, &orig_ttystate);
    }
}