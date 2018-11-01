#include <zconf.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "TUIview.c"
pthread_t gui_thread;
#include "GUIview.c"
#include "ourUtilFunctions.c"

int GUIBool = 1;
int exflag = 0; // turns on when set to 1

char *pstandarde[6]   = {"E2","A2","D3","G3","B3","E4"};
char *pdropd[6]       = {"D2","A2","D3","G3","B3","E4"};
char *pstandardd[6]   = {"D2","G2","C3","F3","A3","D4"};
char *pdropc[6]       = {"C2","G2","C3","F3","A3","D4"};
char *allpitch[]      = {"C2","D2","E2","G2","A2","C3","D3","F3","G3","A3","B3","D4","E4"}; //0-12
char *alltuning[]     = {"StE", "DrD", "StD", "DrC"};
float frstandarde[]   = {82.4, 110.0, 146.8, 196.0, 246.9, 329.6};
float frdropd[]       = {73.4, 110.0, 146.8, 196.0, 246.9, 329.6};
float frstandardd[]   = {73.4, 98.0, 130.8, 174.6, 220.0, 293.7};
float frdropc[]       = {65.4, 98.0, 130.8, 174.6, 220.0, 293.7};
float allfreq[]       = {65.4, 73.4, 82.4, 98.0, 110.0, 130.8, 146.8, 174.6, 196.0, 220.0, 246.9, 293.7, 329.6};
char *allstrumpitch[] = {"A","B","C","D","E","F","G"};
float allstrumfreq    = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
// make a strum array library here.


float tolerance = 0.1;

void throwMessage(char *message){
    if (GUIBool){
        GUIThrowMessage(message);
    } else {
        TUIThrowMessage(message);
    }
}

void ptPitchPerfect(){
    if (GUIBool){
        return GUIptPitchPerfect();
    } else {
        return TUIptPitchPerfect();
    }
}

void ptLow(){
    if (GUIBool){
        return GUIptLow();
    } else {
        return TUIptLow();
    }
}

void ptHigh(){
    if (GUIBool){
        return GUIptHigh();
    } else {
        return TUIptHigh();
    }
}

float ptGetInput(){
    if (GUIBool){
        return GUIptGetInput();
    } else {
        return TUIptGetInput();
    }
}

void pitchTuneAuto(float target, float input){
    float lowerbound = floorf((target - tolerance)*10);
    float upperbound = floorf((target + tolerance)*10);
    input = input*10;
    if (input < lowerbound) {
        //printf("hoi%f %f\n",target, input);
        throwMessage("its too low\n");
    } else if (input > upperbound) {
        //printf("hoi%f %f\n",target, input);
        throwMessage("its too high\n");
    } else {
        throwMessage("pitch perfect\n");
    }
}

char* ptAutoTuneMenu(){
    if (GUIBool){
        return GUIptAutoTuneMenu();
    } else {
        return TUIptAutoTuneMenu();
    }
}

void automaticTune(){
    // to be implemented
    char* cinput;
    float input;
    while (1) {
        cinput = ptAutoTuneMenu();
        // identify the pitch
        if (!strcmp(cinput, "q")) {
            throwMessage("Quitting program.....\n");
            break;
        } else {
            input = (float) myatof(cinput);
            // printf("we received %f", input*10);
            float smallest = floorf((allfreq[0] - tolerance) * 10);
            float biggest = floorf((allfreq[12] + tolerance) * 10);
            // printf("smallest = %f , biggest = %f",smallest, biggest);
            if (input * 10 >= smallest && input * 10 <= biggest) {
                // search for the closest key
                float upperb;
                float lowerb;
                for (int i = 0; i < 12; i++) {
                    if (i == 0) { // if it is the first
                        lowerb = floorf(((allfreq[i]) - tolerance) * 10);
                        upperb = floorf(((allfreq[i] + allfreq[i + 1]) / 2 + tolerance) * 10);
                    } else if (i == 12) { // if it is the last
                        lowerb = floorf(((allfreq[i - 1] + allfreq[i]) / 2 - tolerance) * 10);
                        upperb = floorf(((allfreq[i]) + tolerance) * 10);
                    } else { // if it is in between the first n' last
                        lowerb = floorf(((allfreq[i - 1] + allfreq[i]) / 2 - tolerance) * 10);
                        upperb = floorf(((allfreq[i] + allfreq[i + 1]) / 2 + tolerance) * 10);
                    }
                    if (input * 10 >= lowerb && input * 10 <= upperb) {
                        printf("%s\n", allpitch[i]);
                        pitchTuneAuto(allfreq[i], input);
                        break;
                    }
                }
            } else if (input * 10 < floorf((allfreq[0] - tolerance) * 10)) {
                throwMessage("Input is too low\n");
            } else if (input * 10 > floorf((allfreq[12] - tolerance) * 10)) {
                throwMessage("Input is too high\n");
            } else {
                throwMessage("Please enter another input\n");
            }
        }
    }
}


void pitchTuneMan(char* tuning){
    float tuneprop[6];
    if (!strcmp("StE",tuning)){
        memcpy(&tuneprop, &frstandarde, sizeof tuneprop);
    } else  if (!strcmp("DrD",tuning)){
        memcpy(&tuneprop, &frdropd, sizeof tuneprop);
    } else  if (!strcmp("StD",tuning)){
        memcpy(&tuneprop, &frstandardd, sizeof tuneprop);
    } else  if (!strcmp("DrC",tuning)){
        memcpy(&tuneprop, &frdropc, sizeof tuneprop);
    }
    for (int a = 0 ; a < 6 ; a++) {
        float freq = tuneprop[a];
        float input;
        float lowerbound = floorf((freq - tolerance)*10);
        float upperbound = floorf((freq + tolerance)*10);
        while (1){
            input = ptGetInput();
            input = input*10;
            if (input >= lowerbound && input <= upperbound){
                ptPitchPerfect();
                break;
            } else {
                if (input < lowerbound) {
                    ptLow();
                } else if (input > upperbound) {
                    ptHigh();
                }
            }
        }
    }

}

int ptManualTuneMenu(){
    if (GUIBool) {
        return GUIptManualTuneMenu();
    } else {
        return TUIptManualTuneMenu();
    }
}

void manualTune(){
    int tuning = ptManualTuneMenu();
    if (tuning == 1){
        pitchTuneMan("StE");
    } else if (tuning == 2){
        pitchTuneMan("DrD");
    } else if (tuning == 3){
        pitchTuneMan("StD");
    } else if (tuning == 4){
        pitchTuneMan("DrC");
    } else if (tuning == 5){
        //TODO: return to previous
    } else {
        throwMessage("Please enter a valid input!\n");
        manualTune();
    }
}

int tuningMenuScan() {
    if (GUIBool){
        return GUItuningMenuScan();
    } else {
        return TUItuningMenuScan();
    }
}

int scanTabsMenuScan(){
    if(GUIBool){
        return GUIscanTabsMenuScan();
    } else {
        return TUIscanTabsMenuScan();
    }
}

int displayScanTabsGuide(){
    if (GUIBool) {
        return GUIdisplayScanTabsGuide();
    } else {
        return TUIdisplayScanTabsGuide();
    }
}

float scGetInput(){
    if (GUIBool){
        return GUIscGetInput();
    } else {
        return TUIscGetInput();
    }
}

// make the actual chord library first
char* translateChord(float input){
    char res;
    float smallest = floorf((allstrumfreq[0] - tolerance) * 10);
    float biggest = floorf((allstrumfreq[12] + tolerance) * 10);
    // printf("smallest = %f , biggest = %f",smallest, biggest);
    if (input * 10 >= smallest && input * 10 <= biggest) {
        // search for the closest key
        float upperb;
        float lowerb;
        for (int i = 0; i < 12; i++) {
            if (i == 0) { // if it is the first
                lowerb = floorf(((allfreq[i]) - tolerance) * 10);
                upperb = floorf(((allfreq[i] + allfreq[i + 1]) / 2 + tolerance) * 10);
            } else if (i == 12) { // if it is the last
                lowerb = floorf(((allfreq[i - 1] + allfreq[i]) / 2 - tolerance) * 10);
                upperb = floorf(((allfreq[i]) + tolerance) * 10);
            } else { // if it is in between the first n' last
                lowerb = floorf(((allfreq[i - 1] + allfreq[i]) / 2 - tolerance) * 10);
                upperb = floorf(((allfreq[i] + allfreq[i + 1]) / 2 + tolerance) * 10);
            }
            if (input * 10 >= lowerb && input * 10 <= upperb) {
                res = allpitch[i];
                break;
            }
        }
    }
    return res;
}

void* turnExitFlag(void *arg){
    int fl;
    scanf("%d", fl);
    if (fl == 1){
        exflag = 1;
    }
}

void scanTabs(){
    int beat;
    while (1){
        while (1){
            beat = displayScanTabsGuide(); // display instructions & menus and get the input
            if (beat == 1) {
                beat = 2;
            } else if (beat == 2){
                beat = 3;
            } else if (beat == 3){
                beat = 4;
            } else if (beat == 4){
                break;
            } else {
                throwMessage("Please enter a valid input!");
            }
        }
        float intvls[960]; // for 1 minute, the 0th array is always empty
        int stflag = 0;
        // scan for start of the record
        while (!stflag == 1){
            strflag = scanTabsMenuScan();
        }
        // record the intervals while counting the beat
        pthread_t exit;
        while (!exflag == 1){
            float input;
            int count = 0; // array intvls pointer
            // loop for seconds
            for (int sec = 0; sec < 60; sec++) {
                // loop for intervals
                // run the turnExitFlag to scan if the user enters 1 to stop
                pthread_create(&exit, NULL, &turnExitFlag, NULL);
                for (int val = 0; val < 16; val++){
                    input = scGetInput(); // later input should be replaced
                    intvls[val*(sec+1)] = input;
                    count++;
                }
                throwMessage("Change chord!"); // change chord every second
            }
            exflag = 1; // exit recording
            intvls[count] = -1.0; // to indicate the end of the array
        }
        pthread_join(exit, NULL);
        // determine the length of a chord
        int chordc = 0;
        char* result[960];
        for (int val = 0; val < 960; val++) {
            if (intvls[val] == -1.0){
                break;
            }
            char now[] = translateChord(intvls[val]); // translate current freq to interval
            char temp[2];
            if (val == 0){
                chordc++;
                strcpy(temp, now);
            } else {
                if (strcmp(now,bef) == 0){ // if its the same as before
                    chordc++;
                } else { // if its different than before
                    // write result
                    snprintf(result,3,"%d%s", chordc, temp);
                    throwMessage(result); // display the result
                    // reset counter
                    chordc = 0;
                    strcpy(temp,now);
                }

            }
        }
    }

}

void tuneGuitar(){
    int method;
    method = tuningMenuScan();
    if (method == 1){
        automaticTune();
    } else if (method == 2){
        manualTune();
    } else if (method == 3){
        throwMessage("not implemented");
        //TODO: return to previous
    } else {
        throwMessage("Please enter a valid input!\n");
    }
}

int mainMenuScan(){
    if (GUIBool){
        return GUImainScan();
    } else {
        return TUImainScan();
    }
}

void welcomeText(){
    if (GUIBool){
        GUIwelcomeText();
    } else {
        TUIwelcomeText();
    }
}

int main( int argc, char* argv[] ) {
    if (argc > 1)
    {
        GUIBool = 1;
    } else {
        GUIBool = 0;
    }
    if (GUIBool){
        gtk_init (&argc, &argv);
        window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW (window), "Our Application");
        gtk_window_set_default_size(GTK_WINDOW (window), 500, 750);

        displayText = gtk_label_new(NULL);
        errorText = gtk_label_new(NULL);
        fixed = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER (window), GTK_WIDGET (fixed));
        gtk_fixed_put(GTK_FIXED (fixed), GTK_WIDGET (displayText), 100, 50);
        gtk_fixed_put(GTK_FIXED (fixed), GTK_WIDGET (errorText), 100, 100);

        gtk_widget_show_all  (GTK_WIDGET (window));



        char *str2 = "pizza is echt super lekker";
        setDisplayText(str2);
        setErrorText("");

        setButton(GUIwelcomeText, "hoi");

        g_signal_connect (window, "destroy", G_CALLBACK (destroy), NULL);
        pthread_create(&gui_thread, NULL, *runGUI, NULL);
    }
    welcomeText();
    while (0==0){
        int act = 0;
        act = mainMenuScan();
        if (act == 1){
            tuneGuitar();
        } else if (act == 2){
            scanTabs();
            if (GUIBool){
                gtk_main_quit ();
            };
            break;
        } else if (act == 3){
            if (GUIBool){
                gtk_main_quit ();
            };
            break;
        } else {
            throwMessage("Please make a valid choice!");
        }
    }
    if (GUIBool){
        pthread_join(gui_thread, NULL);
    }
    return 0;
}
