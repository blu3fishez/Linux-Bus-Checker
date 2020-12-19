// execution of showtime, reserve
// 
// date : 2020-12-19-3:00am
#include"basiclib.h"
#include"linecode.h"
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
int compare_time(busdata);

int main(int ac, char* av[]){
    busdata mybusdata[BUSBUF];
    char nowtime[26];
    int k;
    for(k = 0; k<BUSBUF; k++){
        mybusdata[k].bushead[0] = '\0';
        mybusdata[k].bustime[0] = '\0';
        mybusdata[k].maxticket = 0;
        mybusdata[k].reserved = 0; 
    }
    get_bus_data(mybusdata);
    if(!strcmp(av[1], "showlist")){
        //show list
        int i;
        printf("============= Today's Bus =============\n");
        for(i = 0; i<BUSBUF; i++){
            if(mybusdata[i].bustime[0] == '\0')
                break;
            printf("%d. Bus Time: %s | Heading To : %s | Left Seats : %d/%d\n", i+1, mybusdata[i].bustime, mybusdata[i].bushead, mybusdata[i].reserved, mybusdata[i].maxticket);
        }
        printf("%s", NEXTCMD);
        return 0;
    }
    else if(!strcmp(av[1], "reserve")){
        // ask what bus to 
        printf("type the destination you want to reserve (enter 'q' if you want to cancel) ");
        char resbuf[20];
        scanf("%s", resbuf);
        if(!strcmp(resbuf, "q")){
            printf("%s", NEXTCMD);
            return 0;
        }
        int i;
        int destination = 0;
        int found = 0;
        for(i = 0; i<BUSBUF; i++){
            if(!strcmp(mybusdata[i].bushead, resbuf) && compare_time(mybusdata[i])){
                if(mybusdata[i].maxticket > mybusdata[i].reserved){
                    found = 1;
                    destination = i;
                    break;
                }
            }
        }
        if(!found){
            printf("Bus not Available, Transaction Refused.\n");
            printf("%s", NEXTCMD);
            return 0;
        }
        mybusdata[i].reserved++;
        printf("Seat had been reserved\n");
        update_bus_data(mybusdata); //update file data
        printf("%s", NEXTCMD);
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
        if(feof(busfileinfo)) break;
        fscanf(busfileinfo, "%[^\n]", data[i].bustime);
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
    int i;
    char nowtime[26];
    time_t timeval = time(NULL);
    strcpy(nowtime, ctime(&timeval));
    // start comparing nowtime & dest
    // if dest is more furtherer (that means available bus), then return 1
    // else return 0
    // year : use 19~22
    int destyear;
    int nowyear;
    sscanf(dest.bustime, "%*s %*s %*d %*d:%*d:%*d %d", &destyear);
    sscanf(nowtime, "%*s %*s %*d %*d:%*d:%*d %d", &nowyear);
    if(destyear > nowyear) return 1;
    else if(destyear < nowyear) return 0;
    // month : use c_month made by own
    char _destmonth[5];
    char _nowmonth[5];
    for(i = 4; i<7; i++){
        _destmonth[i - 4] = dest.bustime[i];
        _nowmonth[i - 4] = nowtime[i];
    }
    if(c_month(_destmonth) < c_month(_nowmonth)) return 0;
    else if(c_month(_destmonth) > c_month(_nowmonth)) return 1;
    // date : use sscanf
    int destdate;
    int nowdate;
    sscanf(dest.bustime, "%*s %*s %d", &destdate);
    sscanf(nowtime, "%*s %*s %d", &nowdate);
    if(destdate > nowdate){
        return 1;
    }
    else if(destdate < nowdate) return 0;
    // time : you can reserve 
    int desthour;
    int nowhour;
    sscanf(dest.bustime, "%*s %*s %*d %d:%*d:%*d", &desthour);
    sscanf(nowtime, "%*s %*s %*d %d:%*d:%*d", &nowhour);
    if(desthour > nowhour) return 1;
    else return 0;
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