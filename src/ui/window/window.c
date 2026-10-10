#include <gtk/gtk.h>
#include "header_bar.c"
#include "window.h"
#include "menu.h"
#include "ui/theme.h"
#include "ui/app_icon.h"

static void on_window_realize(GtkWidget *window, gpointer user_data)
{
    (void)user_data;
    edens_window_set_icon(window);
}

static void set_window_properties(GtkWidget *window)
{
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_window_unmaximize(GTK_WINDOW(window));
    edens_window_set_icon(window);
    g_signal_connect(window, "realize", G_CALLBACK(on_window_realize), NULL);
}

GtkWidget *build_window(GtkApplication *app)
{
    GtkWidget *window = gtk_application_window_new(app);
    set_window_properties(window);


    GtkWidget *header_bar = create_header_bar();
    gtk_window_set_titlebar(GTK_WINDOW(window), header_bar);

    register_actions(app);

    GMenu *menu = create_menu();
    gtk_application_set_menubar(GTK_APPLICATION(app), G_MENU_MODEL(menu));
    g_object_unref(menu);
    
    gtk_application_window_set_show_menubar(GTK_APPLICATION_WINDOW(window), TRUE);

    edens_apply_theme(window);

    return window;
}
