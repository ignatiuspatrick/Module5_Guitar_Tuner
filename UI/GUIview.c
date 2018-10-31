#include "GUIutils.c"

int GUImainScan() {
    buttonSetValueMin1();
    setDisplayText("Menu:");
    removeButtons();
    setButton(buttonSetValue1,"Tune guitar");
    setButton(buttonSetValue2,"Scan tabs");
    setButton(buttonSetValue3,"Exit");
    while(buttonOutputNumber == -1){
        sched_yield();
    }
    return buttonOutputNumber;
}

void GUIwelcomeText() {
    setDisplayText("Guitar Tuner by Group 30");
}

int GUItuningMenuScan(){
    buttonSetValueMin1();
    setDisplayText("Which method would you like to use:");
    removeButtons();
    setButton(buttonSetValue1,"Automatic");
    setButton(buttonSetValue2,"Manual");
    setButton(buttonSetValue3,"back");
    while(buttonOutputNumber == -1){
        sched_yield();
    }
    return buttonOutputNumber;
}

int GUIptManualTuneMenu(){
    buttonSetValueMin1();
    setDisplayText("Which tuning do you want to do?");
    removeButtons();
    setButton(buttonSetValue1,"Standard_E_(E2-A2-D3-G3-B3-E4)");
    setButton(buttonSetValue2,"Drop_D_____(D2-A2-D3-G3-B3-E4)");
    setButton(buttonSetValue3,"Standard_D_(D2-G2-C3-F3-A3-D4)");
    setButton(buttonSetValue4,"Drop_C_____(C2-G2-C3-F3-A3-D4)");
    //back option is removed because gtk is weird i guess
    //setButton(buttonSetValue5,"Back__________________________");
    while(buttonOutputNumber == -1){
        sched_yield();
    }
    return buttonOutputNumber;
    /*int tuning;
    printf(" __________________________________\n");
    printf("|Which tuning do you want to do?   |\n");
    printf("|1. Standard E (E2-A2-D3-G3-B3-E4) |\n");
    printf("|2. Drop D     (D2-A2-D3-G3-B3-E4) |\n");
    printf("|3. Standard D (D2-G2-C3-F3-A3-D4) |\n");
    printf("|4. Drop C     (C2-G2-C3-F3-A3-D4) |\n");
    printf("|5. Back                           |\n");
    printf("|__________________________________|\n\n");
    printf("Your choice : ");
    scanf("%d", &tuning);
    return tuning;*/
}

char* GUIptAutoTuneMenu(){
    char cinput2[5];
    printf("Enter q to quit\n");
    printf("Input : ");
    scanf("%s", cinput2);
    char* cinput = cinput2;
    return cinput;
}

float GUIptGetInput(){
    char cinput2[5];
    printf("Input : ");
    scanf("%s", cinput2); // read input received from the fpga, later will be replaced
    char* cinput = cinput2;
    float ret_input = myatof(cinput);
    return ret_input;
    /*float ret_input;
    printf("Input : ");
    scanf("%f", &ret_input); // read input received from the fpga, later will be replaced
    return ret_input;*/
}

void GUIptHigh(){
    setErrorText("its too high");
}

void GUIptLow(){
    setErrorText("its too low");
}

void GUIptPitchPerfect(){
    setErrorText("pitch perfect");
}

void GUIThrowMessage(char *message){
    setErrorText(message);
}