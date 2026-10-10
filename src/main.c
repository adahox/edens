#include <gtk/gtk.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "processors/directories.h"

#include "ui/window/window.h"
#include "ui/mainbox.h"
#include "ui/toolbar.h"
#include "ui/actionBar.h"
#include "ui/filearea.h"
#include "ui/scrolledwindow.h"


static void activate(GtkApplication *app, gpointer user_data)
{
    (void)user_data;

    GtkWidget *window = build_window(app);
    GtkWidget *main_box = build_main_box();
    GtkWidget *toolbar = build_toolbar();
    GtkWidget *file_area = build_file_area();
    GtkWidget *scrolled_window = build_scrolled_window();
    GtkWidget *actionBar = build_action_bar();

    gtk_container_add(
        GTK_CONTAINER(scrolled_window),
        file_area
    );

    gtk_box_pack_start(
        GTK_BOX(main_box),
        toolbar,
        FALSE,
        FALSE,
        0
    );

    gtk_box_pack_start(
        GTK_BOX(main_box),
        scrolled_window,
        TRUE,
        TRUE,
        0
    );

    gtk_box_pack_start(GTK_BOX(main_box), actionBar, FALSE, FALSE, 0);

    gtk_container_add(
        GTK_CONTAINER(window),
        main_box
    );

    const char *home = getenv("HOME");
    const char *start_path = home != NULL ? home : ".";

    EdensDirectoryEntries entries;

    int error = read_directory(start_path, &entries);

    if (error != 0) {
        fprintf(
            stderr,
            "Erro ao ler diretório: %d\n",
            error
        );

        gtk_widget_show_all(window);
        return;
    }

    populate_file_area(file_area, &entries);
    free_directory_entries(&entries);

    gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{
    GtkApplication *app = gtk_application_new(
        "com.edens.FileManager",
        G_APPLICATION_DEFAULT_FLAGS
    );

    g_signal_connect(
        app,
        "activate",
        G_CALLBACK(activate),
        NULL
    );

    int status = g_application_run(
        G_APPLICATION(app),
        argc,
        argv
    );

    g_object_unref(app);

    return status;
}
