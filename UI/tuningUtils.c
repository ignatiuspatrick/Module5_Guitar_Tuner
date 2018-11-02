#include <zconf.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TUIview.c"
pthread_t gui_thread;
#include "GUIview.c"

int GUIBool = 1;
int ComBool = 1;

char *pstandarde[6] = {"E2","A2","D3","G3","B3","E4"};
char *pdropd[6]     = {"D2","A2","D3","G3","B3","E4"};
char *pstandardd[6] = {"D2","G2","C3","F3","A3","D4"};
char *pdropc[6]     = {"C2","G2","C3","F3","A3","D4"};
char *allpitch[]    = {"C2","D2","E2","G2","A2","C3","D3","F3","G3","A3","B3","D4","E4"}; //0-12
char *alltuning[]   = {"StE", "DrD", "StD", "DrC"};
float frstandarde[] = {82.4, 110.0, 146.8, 196.0, 246.9, 329.6};
float frdropd[]     = {73.4, 110.0, 146.8, 196.0, 246.9, 329.6};
float frstandardd[] = {73.4, 98.0, 130.8, 174.6, 220.0, 293.7};
float frdropc[]     = {65.4, 98.0, 130.8, 174.6, 220.0, 293.7};
float allfreq[]     = {65.4, 73.4, 82.4, 98.0, 110.0, 130.8, 146.8, 174.6, 196.0, 220.0, 246.9, 293.7, 329.6};

float tolerance = 1;

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
    char* cinput = "";
    float input;
    while (1) {
        //if (!ComBool){
        cinput = ptAutoTuneMenu();
        //}
        // identify the pitch
        if (!strcmp(cinput, "q") || buttonOutputNumber == 1) {
            throwMessage("Quitting program.....\n");
            break;
        } else {
            if (ComBool){
                while (1){
                    if (clockPin){
                        input = readGPIO();
                        break;
                    }
                }
            } else {
                input = (float) myatof(cinput);
            }
            float smallest = floorf((allfreq[0] - tolerance) * 10);
            float biggest = floorf((allfreq[12] + tolerance) * 10);
            //printf("smallest = %f , biggest = %f , input = %f\n",smallest, biggest,input);
            if (input * 10 >= smallest && input * 10 <= biggest) {
                // search for the closest key
                float upperb;
                float lowerb;
                for (int i = 0; i < 12; i++) {
                    if (i == 0) { // if it is the first
                        lowerb = floorf(((allfreq[i]) - tolerance - ((allfreq[i+1] - allfreq[i])/2)) * 10);
                        upperb = floorf(((allfreq[i] + allfreq[i + 1]) / 2 + tolerance) * 10);
                    } else if (i == 12) { // if it is the last
                        lowerb = floorf(((allfreq[i - 1] + allfreq[i]) / 2 - tolerance) * 10);
                        upperb = floorf(((allfreq[i]) + tolerance + ((allfreq[i] - allfreq[i-1])/2)) * 10);
                    } else { // if it is in between the first n' last
                        lowerb = floorf(((allfreq[i - 1] + allfreq[i]) / 2 - tolerance) * 10);
                        upperb = floorf(((allfreq[i] + allfreq[i + 1]) / 2 + tolerance) * 10);
                    }
                    if (input * 10 >= lowerb && input * 10 <= upperb) {
                        if (GUIBool){
                            char str1[50];
                            snprintf(str1, 50, "we received a %s (%f)\n", allpitch[i], input);
                            char* str = str1;
                            setFreqText(str);
                        } else {
                            printf("we received a %s (%f)\n", allpitch[i], input);
                        }
                        printf("%s\n", allpitch[i]);
                        pitchTuneAuto(allfreq[i], input);
                        break;
                    }
                }
            } else if (input * 10 < floorf((allfreq[0] - tolerance) * 10)) {
                throwMessage("Input is too low\n");
            } else if (input * 10 > floorf((allfreq[12] + tolerance) * 10)) {
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

    char* tunechar[6];
    if (!strcmp("StE",tuning)){
        memcpy(&tunechar, &pstandarde, sizeof tunechar);
    } else  if (!strcmp("DrD",tuning)){
        memcpy(&tunechar, &pdropd, sizeof tunechar);
    } else  if (!strcmp("StD",tuning)){
        memcpy(&tunechar, &pstandardd, sizeof tunechar);
    } else  if (!strcmp("DrC",tuning)){
        memcpy(&tunechar, &pdropc, sizeof tunechar);
    }

    for (int a = 0 ; a < 6 ; a++) {
        if (GUIBool) {
            GUImanTuning(tunechar[a]);
        }
        float freq = tuneprop[a];
        float input;
        float lowerbound = floorf((freq - tolerance)*10);
        float upperbound = floorf((freq + tolerance)*10);
        while (buttonOutputNumber == -1){
            if (ComBool){
                while (1){
                    if (clockPin){
                        input = readGPIO();
                        break;
                    }
                }
            } else {
                input = ptGetInput();
            }
            input = input*10;
            if (input >= lowerbound && input <= upperbound){
                ptPitchPerfect();
                //break;
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
        //Doing nothing is what we want here
    } else {
        throwMessage("Please enter a valid input!\n");
        manualTune();
    }
    //returning to previous tab
    //TODO: implement
}

void scanTabs(){
    // to be implemented
}

int tuningMenuScan() {
    if (GUIBool){
        return GUItuningMenuScan();
    } else {
        return TUItuningMenuScan();
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
        //Doing nothing is what we want here
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

int startBool = 0;

void startProgram(){
    startBool = 1;
}

void runProgram(){
    welcomeText();
    while (!startBool){
        sched_yield();
    }
    while (1){
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
}

void *runGUI(void *iets){
    runProgram();
}

GdkPixbuf *create_pixbuf(const gchar * filename) {

   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);

   if (!pixbuf) {

      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }

   return pixbuf;
}

int runUI( int argc, char* argv[] ) {
    if (argc > 1)
    {
        GUIBool = 1;
    } else {
        GUIBool = 0;
    }
    if (GUIBool){
        gdk_threads_init();
        gtk_init (&argc, &argv);
        window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW (window), "Our Application");
        GdkPixbuf *icon;
	    icon = create_pixbuf("music.png");
	    gtk_window_set_icon(GTK_WINDOW(window), icon);
	    gtk_window_set_default_size(GTK_WINDOW (window), 500, 750);

        displayText = gtk_label_new(NULL);
        errorText = gtk_label_new(NULL);
        freqText = gtk_label_new(NULL);
        fixed = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER (window), GTK_WIDGET (fixed));
        gtk_fixed_put(GTK_FIXED (fixed), GTK_WIDGET (displayText), 100, 50);
        gtk_fixed_put(GTK_FIXED (fixed), GTK_WIDGET (errorText), 100, 100);
        gtk_fixed_put(GTK_FIXED (fixed), GTK_WIDGET (freqText), 100, 150);

        gtk_widget_show_all  (GTK_WIDGET (window));

        char *str2 = "Guitar Tuner by Group 30";
        setDisplayText(str2);
        setErrorText("");

        setButton(startProgram, "start");

        g_signal_connect (window, "destroy", G_CALLBACK (destroy), NULL);
        pthread_create(&gui_thread, NULL, *runGUI, NULL);
        gdk_threads_enter();
        gtk_main();
        gdk_threads_leave();
    } else {
        startProgram();
        runProgram();
    }
    if (GUIBool){
        pthread_join(gui_thread, NULL);
    }
    return 0;
}
