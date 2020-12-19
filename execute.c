// execution of showtime, reserve
// 
// date : 2020-12-19-3:00am
#include"basiclib.h"
#define BUSBUF 20

typedef struct _busdata{
    char bustime[26];
    char bushead[24];
    int reserved;
    int maxticket;
} busdata;

void get_bus_data(busdata*);
void update_bus_data(busdata*);
int c_month(char* month);

int main(int ac, char* av[]){
    busdata mybusdata[BUSBUF];
    char nowtime[26];
    get_bus_data(mybusdata);
    if(!strcmp(av[1], "showlist")){
        //show list
        
        return 0;
    }
    else if(!strcmp(av[1], "reserve")){
        // ask what bus to 
        printf("bus do you want to reserve (enter 'q' if you want to cancel) \n");
        char resbuf[20];
        scanf("%s", resbuf);
        if(!strcmp(resbuf, "q"))
            return 0;
        int i;
        for(i = 0; i<BUSBUF; i++){
            if(!strcmp(resbuf, mybusdata[i].bushead)){
                if(mybusdata[i].maxticket == mybusdata[i].reserved){
                    printf("The Bus is Full\n");
                    printf("Please Try Another Bus\n");
                }
                else{
                    mybusdata[i].reserved++;
                    printf("Seat had been reserved\n");
                }
            }
        }
        update_bus_data(mybusdata); //update file data
        return 0;
    }
    else{
        perror("invalid mode in execute.c");
        exit(1);
    }
}

void get_bus_data(busdata data[]){
    // get struct tm data and bus by mktime()
    time_t current = time(NULL);
    FILE* busfileinfo = fopen("bus_table", "r");
    if(busfileinfo == NULL){
        printf("invalid bus data\n");
        printf("please check the bus_table is available\n");
        exit(1);
    }
    int i;
    for(i = 0; i<BUSBUF; i++){
        fscanf(busfileinfo, "%s\n", data[i].bustime);
        fscanf(busfileinfo, "%s %d %d\n", data[i].bushead, &data[i].reserved, &data[i].maxticket);
    }
    fclose(busfileinfo);
}

void update_bus_data(busdata data[]){
    int i;
    FILE* writetable = fopen("bus_table", "w");
    for(i = 0; i<BUSBUF; i++){
        if(data[i].bustime[0] == '\0'){
            fclose(writetable);
            return;
        }
        fprintf(writetable, "%s\n", data[i].bustime);
        fprintf(writetable, "%s %d %d\n", data[i].bushead, data[i].reserved, data[i].maxticket);
    }
}

int compare_time(busdata dest){
    char nowtime[26];
    time_t timeval = time(NULL);
    strcpy(nowtime, ctime(&timeval));
}

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