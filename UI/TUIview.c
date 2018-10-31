int TUImainScan() {
    int choice;
    printf(" ___________________________________ \n");
    printf("| Menu :                            |\n");
    printf("|1. Tune Guitar                     |\n");
    printf("|2. Scan tabs                       |\n");
    printf("|3. Exit                            |\n");
    printf("|___________________________________|\n\n");
    printf("Your choice : ");
    scanf("%d", &choice);
    return choice;
}

void TUIwelcomeText() {
    printf(" ____________________________________\n");
    printf("|      Guitar Tuner by Group 30      |\n");
    printf("|____________________________________|\n");
    printf("\n");
}
int TUItuningMenuScan(){
    int choice;
    printf(" ___________________________________ \n");
    printf("|Which method would you like to use?|\n");
    printf("|1. Automatic                       |\n");
    printf("|2. Manual                          |\n");
    printf("|3. Back                            |\n");
    printf("|___________________________________|\n\n");
    printf("Your choice : ");
    scanf("%d", &choice);
    return choice;
}

int TUIptManualTuneMenu(){
    int tuning;
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
    return tuning;
}

char* TUIptAutoTuneMenu(){
    char cinput2[5];
    printf("Enter q to quit\n");
    printf("Input : ");
    scanf("%s", cinput2);
    char* cinput = cinput2;
    return cinput;
}

float TUIptGetInput(){
    float ret_input;
    printf("Input : ");
    scanf("%f", &ret_input); // read input received from the fpga, later will be replaced
    return ret_input;
}

void TUIptHigh(){
    printf("its too high\n");
}

void TUIptLow(){
    printf("its too low\n");
}

void TUIptPitchPerfect(){
    printf("pitch perfect\n");
}

void TUIThrowMessage(char *message){
    printf("%s\n", message);
}

int TUIscanTabsMenuScan(){
    int input;
    printf("Enter 1 to start scanning the tabs : ");
    scanf("%d", &input);
    return input;
}

int TUIdisplayScanTabsGuide() {
    int input;
    printf(" _________________________________________________________________\n");
    printf("|------------------THE GUIDE TO THE TABS SCANNER-------------------|\n");
    printf("|1. Pick the correct simple beat for the song                      |\n");
    printf("|2. Enter 1 to start recording the tabs                            |\n");
    printf("|3. Prepare to strum a different tab every time there is a counter |\n");
    printf("|4. Switch the chord at the count of 3 or keep playing the same    |\n");
    printf("|5. When you are done, press 1 again                               |\n");
    printf("|6. Wait for your result to be displayed                           |\n");
    printf("|__________________________________________________________________|\n\n");
    printf(" ________________________________\n");
    printf("|Pick your choice :              |\n");
    printf("|1. Duple (2/4)                  |\n");
    printf("|2. Triple (3/4)                 |\n");
    printf("|3. Quadruple (4/4)              |\n");
    printf("|4. Exit                         |\n");
    printf("|________________________________|\n\n");
    printf("Your choice : ");
    scanf("%d", &input);
    return input;
}

float TUIscGetInput() {
    float input;
    printf("Input = ");
    scanf("%f", &input);
    return input;
}