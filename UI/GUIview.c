#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <gtk/gtk.h>

float GUIptGetInput(){
    return -1.0;
}

static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    gtk_main_quit ();
}

void *test(void *iets){
    gtk_main();
}

int main( int   argc,
          char *argv[] )
{
    GtkWidget *window;
    GtkWidget *label;
    GtkWidget *entry;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    label = gtk_label_new(NULL);
    const char *str = "";
    gtk_label_set_text(label, str);

    gtk_container_add(GTK_CONTAINER (window), label);
    gtk_widget_show  (window);
    gtk_widget_show (label);

    pthread_t gui_thread;
    pthread_create(&gui_thread, NULL, *test, NULL);

    //gtk_main ();
    printf("doei");
    int i = 0;
    while (i <= 200000000){
        i = i + 1;
    }
    const char *str2 = "pizza is echt super lekker, waarom weet \nniet iedereen dit dafd adfa efadf eafea ef";
    gtk_label_set_text(label, str2);
    printf("hoi");

    g_signal_connect (window, "destroy", G_CALLBACK (destroy), NULL);


    i = 0;
    while (i <= 500000000){
        i = i + 1;
    }
    pthread_join(gui_thread, NULL);
    return 0;
}