#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <gtk/gtk.h>

GtkWidget *window;
GtkWidget *displayText;
GtkWidget *flabel;
GtkWidget *entry;
GtkWidget *buttons[4];
int buttonNumber = 0;

void setDisplayText(char* str){
    gtk_label_set_text(GTK_LABEL (displayText), str);
}

void setButton(void*, char*);
void removeButtons();

void nextEvent(){
    removeButtons();
    char *but2 = "doe";
    setButton(nextEvent, but2);
}

void removeButtons(){
    for(int i = 0; i < buttonNumber; i++){
        gtk_widget_destroy(buttons[i]);
    }
    buttonNumber = 0;
}

void setButton(void* function, char* str){
    GtkWidget *button;
    button = gtk_button_new_with_label(str);
    gtk_fixed_put(GTK_FIXED (flabel), button, 200, 100 + buttonNumber*50);
    g_signal_connect (button, "clicked",
                      G_CALLBACK (function), NULL);
    buttons[buttonNumber] = button;
    buttonNumber++;
    gtk_widget_show  (button);
}

float GUIptGetInput(){
    return -1.0;
}

static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    gtk_main_quit ();
}

void *runGUI(void *iets){
    gtk_main();
}

int main( int   argc,
          char *argv[] )
{
    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW (window), "Our Application");
    gtk_window_set_default_size(GTK_WINDOW (window), 500, 750);

    displayText = gtk_label_new(NULL);
    flabel = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER (window), flabel);
    gtk_fixed_put(GTK_FIXED (flabel), displayText, 100, 50);

    gtk_widget_show_all  (window);

    //pthread_t gui_thread;
    //pthread_create(&gui_thread, NULL, *runGUI, NULL);

    char *str2 = "pizza is echt super lekker";
    setDisplayText(str2);

    char *but1 = "hoi";
    setButton(nextEvent, but1);

    /*for(int i = 0; i <1000000000; i++){

    }

    char *but2 = "doe";
    setButton(but2);*/

    g_signal_connect (window, "destroy", G_CALLBACK (destroy), NULL);
    gtk_main();
    //pthread_join(gui_thread, NULL);
    return 0;
}