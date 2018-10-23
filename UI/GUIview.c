#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

float GUIptGetInput(){
    return -1.0;
}

static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    gtk_main_quit ();
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
    const char *str = "pizza is echt super lekker, waarom weet niet iedereen dit dafd adfa efadf eafea ef";
    gtk_label_set_text(label, str);

    gtk_container_add(GTK_CONTAINER (window), label);
    gtk_widget_show  (window);
    gtk_widget_show (label);

    delay(10);
    const char *str2 = "";
    gtk_label_set_text(label, str2);

    g_signal_connect (window, "destroy", G_CALLBACK (destroy), NULL);

    gtk_main ();

    return 0;
}