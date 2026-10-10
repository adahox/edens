#include <gtk/gtk.h>
#include "ui/file_area/filearea.h"
#include "ui/file_item/fileitem.h"

GtkWidget *build_file_area(void)
{
    GtkWidget *file_area = gtk_flow_box_new();

    gtk_widget_set_name(file_area, "file-area");

    gtk_flow_box_set_row_spacing(
        GTK_FLOW_BOX(file_area),
        1
    );

    gtk_flow_box_set_column_spacing(
        GTK_FLOW_BOX(file_area),
        1
    );

    gtk_flow_box_set_selection_mode(
        GTK_FLOW_BOX(file_area),
        GTK_SELECTION_NONE
    );

    return file_area;
}

void populate_file_area(
    GtkWidget *file_area,
    EdensDirectoryEntries *entries
)
{
    for (size_t i = 0; i < entries->count; i++) {
        GtkWidget *item = build_file_item(
            &entries->entries[i]
        );

        gtk_flow_box_insert(
            GTK_FLOW_BOX(file_area),
            item,
            -1
        );
    }
}
