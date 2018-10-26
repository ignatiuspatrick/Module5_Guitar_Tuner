#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <gtk/gtk.h>

GtkWidget *window;
GtkWidget *displayText;
GtkWidget *entry;
//GtkWidget*[] buttons;

void setDisplayText(char* str){
    gtk_label_set_text(GTK_LABEL (displayText), str);
}

void setButton(char* str){

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
    GtkWidget *flabel = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER (window), flabel);
    gtk_fixed_put(GTK_FIXED (flabel), displayText, 100, 50);

    gtk_widget_show_all  (window);

    pthread_t gui_thread;
    pthread_create(&gui_thread, NULL, *runGUI, NULL);

    char *str2 = "pizza is echt super lekker, waarom weet \nniet iedereen dit dafd adfa efadf eafea ef";
    setDisplayText(str2);

    g_signal_connect (window, "destroy", G_CALLBACK (destroy), NULL);

    pthread_join(gui_thread, NULL);
    return 0;
}