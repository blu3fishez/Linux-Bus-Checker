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
    /*
    if(c != EOF && sleepmode){
        // show the menu and wake up
        
        sleepmode = 0;
        set_ticker(10000);
    }
    */
    int pid;
    if(c == 'q'){
        done = 1;
        enable_kbd_signals(0);
    }
    else if(c == 't'){
        set_ticker(0);
        pid = fork();
        if(pid == 0){
            execl("./client", "./client", "localhost", "5500", NULL);
        }
        else wait(&pid);
        set_ticker(10000);
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
        pid = fork();
        if(pid == 0){
            execl("./execute", "./execute", "reserve", NULL);
        }
        else wait(&pid);
        set_ticker(10000);
    }
}

void on_timer(int signum){
    // set_ticker(0);
    // if the program receives timer signal,
    // the program discards all of the data and
    // turn the sleep mode on
    // sleepmode? clear all of screen and wait for the input.
}

void enable_kbd_signals(int mode){
    static int orig_flags;
    static int stored = 0;
    int fd_flags;
    if(mode == 1){ // 1 : set
        fcntl(0, F_SETOWN, getpid());
        fd_flags = fcntl(0, F_GETFL);
        orig_flags = fd_flags;
        fd_flags |= O_ASYNC;
        fd_flags |= O_NDELAY;
        fcntl(0, F_SETFL, fd_flags);
        stored = 1;
    }
    if(mode == 0 && stored){ // 0 : restore
        fcntl(0, F_SETFL, orig_flags);
    }
}