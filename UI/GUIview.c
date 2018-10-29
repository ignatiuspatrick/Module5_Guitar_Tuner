#include "GUIutils.c"

int GUImainScan() {
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

void GUIwelcomeText() {
    printf(" ____________________________________\n");
    printf("|      Guitar Tuner by Group 30      |\n");
    printf("|____________________________________|\n");
    printf("\n");
}
int GUItuningMenuScan(){
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

int GUIptManualTuneMenu(){
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

char* GUIptAutoTuneMenu(){
    char* cinput;
    printf("Enter q to quit\n");
    printf("Input : ");
    scanf("%s", cinput);
    return cinput;
}

float GUIptGetInput(){
    float ret_input;
    printf("Input : ");
    scanf("%f", &ret_input); // read input received from the fpga, later will be replaced
    return ret_input;
}

void GUIptHigh(){
    printf("its too high\n");
}

void GUIptLow(){
    printf("its too low\n");
}

void GUIptPitchPerfect(){
    printf("pitch perfect\n");
}

void GUIThrowMessage(char *message){
    printf("%s\n", message);
}

int runGUI( int argc, char* argv[] )
{
    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW (window), "Our Application");
    gtk_window_set_default_size(GTK_WINDOW (window), 500, 750);

    displayText = gtk_label_new(NULL);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER (window), fixed);
    gtk_fixed_put(GTK_FIXED (fixed), displayText, 100, 50);

    gtk_widget_show_all  (window);

    char *str2 = "pizza is echt super lekker";
    setDisplayText(str2);

    char *but1 = "hoi";
    setButton(nextEvent, but1);

    g_signal_connect (window, "destroy", G_CALLBACK (destroy), NULL);
    gtk_main();
    return 0;
}