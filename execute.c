// execution of showtime, reserve
// 
// date : 2020-12-19-3:00am
#include"basiclib.h"
#include<string.h>
#define BUSBUF 20

int c_month(char* month){
    if(!strcmp("Jan", month)) return 1;
    else if(!strcmp("Feb", month)) return 2;
    else if(!strcmp("Mar", month)) return 3;
    else if(!strcmp("Apr", month)) return 4;
    else if(!strcmp("May", month)) return 5;
    else if(!strcmp("Jun", month)) return 6;
    else if(!strcmp("Jul", month)) return 7;
    else if(!strcmp("Aug", month)) return 8;
    else if(!strcmp("Sep", month)) return 9;
    else if(!strcmp("Oct", month)) return 10;
    else if(!strcmp("Nov", month)) return 11;
    else if(!strcmp("Dec", month)) return 12;
    else{
        perror("month change");
        exit(1);
    }
}

typedef struct _busdata{
    time_t bustime;
    char bushead[24];
    int reserved;
    int maxticket;
} busdata;

int main(int ac, char* av[]){
    busdata mybusdata[BUSBUF];
    get_bus_data(mybusdata);
    if(!strcmp(av[1], "showtime")){
        //compare and show


        return 0;
    }
    else if(!strcmp(av[1], "reserve")){
        // ask what bus to 
        printf("bus do you want to reserve :");
        char resbuf[20];
        scanf("%s", resbuf);
        int i;
        for(i = 0; i<BUSBUF; i++){
            if(!strcmp(resbuf, mybusdata[i].bushead)){

            }
        }

        //update file data


        return 0;
    }
    else{
        perror("forking in execute.c");
        exit(1);
    }
}

void get_bus_data(busdata data[]){
    // get struct tm data and bus by mktime()
    time_t current = time(NULL);
    
    FILE* busfileinfo = fopen("bus_table", "r");
    int i;
    for(i = 0; i<BUSBUF; i++){
        fscanf(busfileinfo, "%s", );
    }
}