#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <math.h>
//#include <gtk/gtk.h>

char *pstandarde[6] = {"E2","A2","D3","G3","B3","E4"};
char *pdropd[6] = {"D2","A2","D3","G3","B3","E4"};
char *pstandardd[6] = {"D2","G2","C3","F3","A3","D4"};
char *pdropc[6] = {"C2","G2","C3","F3","A3","D4"};
char *allpitch[] = {"C2","D2","E2","G2","A2","C3","D3","F3","G3","A3","B3","D4","E4"};
float frstandarde[] = {82.4, 110.0, 146.8, 196.0, 246.9, 329.6};
float frdropd[] = {73.4, 110.0, 146.8, 196.0, 246.9, 329.6};
float frstandardd[] = {73.4, 98.0, 130.8, 174.6, 220.0, 293.7};
float frdropc[] = {65.4, 98.0, 130.8, 174.6, 220.0, 293.7};
float allfreq[] =  {65.4,73.4,82.4,98.0,110.0,130.8,146.8,174.6,196.0,220.0,246.9,293.7,329.6};

void pitchtune(float freq){
    float input;
    float tolerance = 0.1;
    float lowerbound = floorf((freq - tolerance)*10);
    float upperbound = floorf((freq + tolerance)*10);
    while (0==0){
        printf("input : ");
        scanf("%f", &input); // read input received from the fpga, later will be replaced
        input = input*10;
        if (input >= lowerbound && input <= upperbound){
            printf("pitch perfect\n");
            break;
        } else {
            if (input < lowerbound) {
                printf("its too low\n");
            } else if (input > upperbound) {
                printf("its too high\n");
            }
        }
    }
    printf("============================\n");
}

void automatictune(){
    // to be implemented
    float input;
    printf("Doing automatic tuning.....\n");
    scanf("%f", &input);
    // identify the pitch

    // suggest something
}

void manualtune(){
    int tuning;
    printf(" __________________________________\n");
    printf("|Which tuning do you want to do?   |\n");
    printf("|1. Standard E (E2-A2-D3-G3-B3-E4) |\n");
    printf("|2. Drop D     (D2-A2-D3-G3-B3-E4) |\n");
    printf("|3. Standard D (D2-G2-C3-F3-A3-D4) |\n");
    printf("|4. Drop C     (C2-G2-C3-F3-A3-D4) |\n");
    printf("|__________________________________|\n\n");
    printf("Your choice : ");
    scanf("%d", &tuning);
    if (tuning == 1){
        printf("Tuning Standard E\n");
        for (int i = 0; i < 6; i++){
            printf("Tuning String %d\n", i+1);
            pitchtune(frstandarde[i]);
        }
        printf("We are done!\n");
    } else if (tuning == 2){
        printf("Tuning Drop D\n");
        for (int i = 0; i < 6; i++){
            printf("Tuning String %d\n", i+1);
            pitchtune(frdropd[i]);
        }
        printf("We are done!\n");
    } else if (tuning == 3){
        printf("Tuning standard D\n");
        for (int i = 0; i < 6; i++){
            printf("Tuning String %d\n", i+1);
            pitchtune(frstandardd[i]);
        }
        printf("We are done!\n");
    } else if (tuning == 4){
        printf("Tuning drop C\n");
        for (int i = 0; i < 6; i++){
            printf("Tuning String %d\n", i+1);
            pitchtune(frdropc[i]);
        }
        printf("We are done!\n");
    } else {
        printf("Please choose a valid tuning.\n");
        manualtune();
    }
}

void tuneguitar(){
    int method;
    printf(" ___________________________________ \n");
    printf("|Which method would you like to use?|\n");
    printf("|1. Automatic                       |\n");
    printf("|2. Manual                          |\n");
    printf("|___________________________________|\n\n");
    printf("Your choice : ");
    scanf("%d", &method);
    int pitch;
    if (method == 1){
        automatictune();
    } else if (method == 2){
        manualtune();
    }
}

void scantabs(){
    // to be implemented
}

void welcometext(){
    printf(" ____________________________________\n");
    printf("|      Guitar Tuner by Group 30      |\n");
    printf("|____________________________________|\n");
    printf("\n");
}

int main() {
    printf("%s", pstandarde[0]);
    /*
    welcometext();
    while (0==0){
        int act = 0;
        printf("Menu :\n");
        printf("1. Tune Guitar\n");
        printf("2. Scan tabs\n");
        printf("3. Exit\n\n");
        printf("Your choice : ");
        scanf("%d", &act);
        if (act == 1){
            tuneguitar();
        } else if (act == 2){
            scantabs();
        } else if (act == 3){
            break;
        }
    }
     */
    return 0;
}


