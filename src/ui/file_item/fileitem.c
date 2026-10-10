#include <gtk/gtk.h>
#include "ui/file_item/fileitem.h"

enum { FILE_ICON_SIZE = 64 };

static int label_width_chars(GtkWidget *label)
{
    PangoLayout *layout = gtk_widget_create_pango_layout(label, "n");
    int char_width = 1;

    pango_layout_get_pixel_size(layout, &char_width, NULL);
    g_object_unref(layout);

    if (char_width < 1) {
        char_width = 1;
    }

    return FILE_ICON_SIZE / char_width;
}

static gboolean file_item_pointer_crossing(
    GtkWidget *widget,
    GdkEventCrossing *event,
    gpointer user_data)
{
    (void)event;
    gboolean entering = GPOINTER_TO_INT(user_data) != 0;

    if (entering) {
        gtk_widget_set_state_flags(widget, GTK_STATE_FLAG_PRELIGHT, FALSE);
    } else {
        gtk_widget_unset_state_flags(widget, GTK_STATE_FLAG_PRELIGHT);
    }

    return GDK_EVENT_PROPAGATE;
}

static gboolean file_item_button_press(
    GtkWidget *widget,
    GdkEventButton *event,
    gpointer user_data)
{
    (void)event;
    (void)user_data;

    printf("button press: %s\n", (char *)user_data);
}

GtkWidget *build_file_item(EdensDirectoryEntry *entry)
{
    GtkWidget *shell = gtk_event_box_new();
    gtk_widget_set_name(shell, "file-item");

    GtkWidget *item = gtk_box_new(
        GTK_ORIENTATION_VERTICAL,
        0
    );

    GtkWidget *file_icon;

    if (entry->type == EDENS_ENTRY_DIRECTORY) {
        file_icon = gtk_image_new_from_icon_name(
            "folder",
            GTK_ICON_SIZE_BUTTON
        );
    } else {
        file_icon = gtk_image_new_from_icon_name(
            "text-x-generic",
            GTK_ICON_SIZE_BUTTON
        );
    }

    gtk_image_set_pixel_size(GTK_IMAGE(file_icon), FILE_ICON_SIZE);

    GtkWidget *file_label = gtk_label_new(entry->name);

    gtk_widget_set_name(file_label, "file-item-label");

    int width_chars = label_width_chars(file_label);

    gtk_label_set_max_width_chars(GTK_LABEL(file_label), width_chars);
    gtk_label_set_ellipsize(GTK_LABEL(file_label), PANGO_ELLIPSIZE_END);
    gtk_label_set_xalign(GTK_LABEL(file_label), 0.5);
    gtk_widget_set_halign(file_label, GTK_ALIGN_CENTER);

    gtk_box_pack_start(
        GTK_BOX(item),
        file_icon,
        FALSE,
        FALSE,
        0
    );

    gtk_box_pack_start(
        GTK_BOX(item),
        file_label,
        FALSE,
        FALSE,
        0
    );

    gtk_container_add(GTK_CONTAINER(shell), item);

    gtk_widget_add_events(
        shell,
        GDK_ENTER_NOTIFY_MASK | GDK_LEAVE_NOTIFY_MASK
    );
    g_signal_connect(
        shell,
        "enter-notify-event",
        G_CALLBACK(file_item_pointer_crossing),
        GINT_TO_POINTER(1)
    );
    g_signal_connect(
        shell,
        "leave-notify-event",
        G_CALLBACK(file_item_pointer_crossing),
        GINT_TO_POINTER(0)
    );

    g_signal_connect(
        shell,
        "button-press-event",
        G_CALLBACK(file_item_button_press),
        g_strdup(gtk_widget_get_name(shell))
    );

    return shell;
}
