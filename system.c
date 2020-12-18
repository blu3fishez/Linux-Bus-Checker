// main procedure of system
// uses asynchronous input
// uses timer signal : set_ticker.c
// uses non-blocking input mode (need to be set to nodelay mode)
// date : 2020-12-19-3:00am

#include"basiclib.h"
#include"linecode.h"
#include<fcntl.h>
#include<termios.h>

int set_ticker(int);
void enable_kbd_signals();
void safequit();
int done = 0;

int main(){
    // set variables
    // set signals
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    // ignore quit signal
    // ignore interrupt signal
    // set timer signal handler
    set_ticker(10000);
    void on_timer(int);
    void on_input(int);
    // set terminals for async
    enable_kbd_signals();
    // set terminals for non-blocking input
    // set async signal handler
    signal(SIGIO, on_input);
    
    // set ticker
    //while(!done) pause
    while(!done)
        pause();
    // if async signal is q, call quit() procedure & quit.
    // if asynchronous input came, wait & fork with execl
}

void on_input(int signum){
    int c = getch();
    if(c == 'q')
        done = 1;
    else if(c == 'l'){
        safequit();
    }
    else if(c == 's'){
        
    }
    else if(c == 'r'){

    }
}

void on_timer(int signum){

}

void enable_kbd_signals(){
    int fd_flags;
    fcntl(0, F_SETOWN, getpid());
    fd_flags = fcntl(0, F_GETFL);
    fcntl(0, F_SETFL, (fd_flags|O_ASYNC));
}

void safequit(){

}