#include <gtk/gtk.h>
#include "ui/header_bar/header_bar.h"

GtkWidget *create_header_bar(void)
{
    GtkWidget *header_bar = gtk_header_bar_new();
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), TRUE);
    gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), "Eden's Explorer");

    return header_bar;
}