#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <gtk/gtk.h>

GtkWidget *window;
GtkWidget *displayText;
GtkWidget *errorText;
GtkWidget *fixed;
//GtkWidget *entry;
GtkWidget *buttons[4];
int buttonNumber = 0;

int buttonOutputNumber = -1;
void buttonSetValueMin1(){
    buttonOutputNumber = -1;
}
void buttonSetValue1(){
    buttonOutputNumber = 1;
}
void buttonSetValue2(){
    buttonOutputNumber = 2;
}
void buttonSetValue3(){
    buttonOutputNumber = 3;
}
void buttonSetValue4(){
    buttonOutputNumber = 4;
}
void buttonSetValue5(){
    buttonOutputNumber = 5;
}


void setDisplayText(char* str){
    gtk_label_set_text(GTK_LABEL (displayText), str);
}
void setErrorText(char* str){
    gtk_label_set_text(GTK_LABEL (errorText), str);
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
    gtk_fixed_put(GTK_FIXED (fixed), button, 200, 200 + buttonNumber*50);
    g_signal_connect (button, "clicked",
                      G_CALLBACK (function), NULL);
    buttons[buttonNumber] = button;
    buttonNumber++;
    gtk_widget_show  (button);
}

static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    gtk_main_quit ();
}