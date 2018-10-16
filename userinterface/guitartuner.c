#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h> // the library fo the tui


char* identifytune(int freq){
    // read tune from
    return NULL;
}

void pitchtune(double freq){
    double input;
    while (input <= freq - 0.1 || input >= freq + 0.1){
        printf("input : ");
        scanf("%lf", &input); // read input received from the fpga, later will be replaced
        if (input <= freq - 0.1){
            printf("too low\n");
        } else if (input >= freq + 0.1){
            printf("too high\n");
        }
    }
}

void automatictune(){
    // to be implemented

}

void manualtune(){
    int tuning;
    printf("-------------------------\n");
    printf("Which tuning do you want to do?\n");
    printf("1. Standard E (E2-A2-D3-G3-B3-E4)\n");
    printf("2. Drop D     (D2-A2-D3-G3-B3-E4)\n");
    printf("3. Standard D (D2-G2-C3-F3-A3-D4)\n");
    printf("4. Drop C     (C2-G2-C3-F3-A3-D4)\n");
    printf("Your choice : ");
    scanf("%d", &tuning);
    if (tuning == 1){
        printf("Tuning standard E\n");
        printf("Tuning String 1\n");
        pitchtune(82.4);
        printf("Tuning String 2\n");
        pitchtune(110.0);
        printf("Tuning String 3\n");
        pitchtune(146.8);
        printf("Tuning String 4\n");
        pitchtune(196.0);
        printf("Tuning String 5\n");
        pitchtune(246.9);
        printf("Tuning String 6\n");
        pitchtune(329.6);
        printf("We are done!\n");
    } else {
        printf("features coming soon");
        manualtune();
    }
}

void tuneguitar(){
    int method;
    printf("Which method would you like to use?\n");
    printf("1. Automatic\n");
    printf("2. Manual\n");
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
    printf("Guitar Tuner by group 30\n");
    printf("-------------------------\n");
}

int main() {
    welcometext();
    while (0==0){
        int act = 0;
        printf("Menu :\n");
        printf("1. Tune Guitar\n");
        printf("2. Scan tabs\n");
        printf("3. Exit\n");
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

    return 0;
}

