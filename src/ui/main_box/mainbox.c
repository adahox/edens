#include <gtk/gtk.h>
#include "ui/main_box/mainbox.h"

GtkWidget *build_main_box(void)
{
    GtkWidget *main_box = gtk_box_new(
        GTK_ORIENTATION_VERTICAL,
        0
    );

    gtk_widget_set_name(main_box, "main_box");

    return main_box;
}
