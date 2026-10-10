#include "ui/theme.h"

#include <glib.h>
#include <glib/gstdio.h>

static char *resolve_css_path(void)
{
    const char *from_env = g_getenv("EDENS_DATA_DIR");

    if (from_env != NULL) {
        char *path = g_build_filename(from_env, "edens.css", NULL);
        if (g_file_test(path, G_FILE_TEST_EXISTS)) {
            return path;
        }
        g_free(path);
    }

    char *dev_path = g_build_filename("data", "edens.css", NULL);
    
    if (g_file_test(dev_path, G_FILE_TEST_EXISTS)) {
        return dev_path;
    }
    g_free(dev_path);

    char *exe = g_file_read_link("/proc/self/exe", NULL);
    if (exe != NULL) {
        char *dir = g_path_get_dirname(exe);
        char *path = g_build_filename(dir, "data", "edens.css", NULL);
        g_free(dir);
        g_free(exe);
        if (g_file_test(path, G_FILE_TEST_EXISTS)) {
            return path;
        }
        g_free(path);
    }

    return NULL;
}

static void add_provider_to_widget(GtkWidget *widget, GtkCssProvider *provider)
{
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(
        context,
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
}

static GtkCssProvider *load_css_provider(void)
{
    GtkCssProvider *provider = gtk_css_provider_new();
    GError *error = NULL;
    char *path = resolve_css_path();

    if (path != NULL && gtk_css_provider_load_from_path(provider, path, &error)) {
        g_free(path);
        return provider;
    }

    if (error != NULL) {
        g_warning("edens: failed to load theme from file: %s", error->message);
        g_clear_error(&error);
    } else {
        g_warning("edens: data/edens.css not found; using built-in fallback");
    }
    g_free(path);

    static const char fallback[] =
        "#explorer-toolbar button, #explorer-toolbar button image { color: #ffffff; }";
    gtk_css_provider_load_from_data(provider, fallback, -1, NULL);
    return provider;
}

void edens_apply_theme(GtkWidget *window)
{
    GtkCssProvider *provider = load_css_provider();

    add_provider_to_widget(window, provider);

    GtkWidget *titlebar = gtk_window_get_titlebar(GTK_WINDOW(window));
    
    if (titlebar != NULL) {
        add_provider_to_widget(titlebar, provider);
    }

    g_object_unref(provider);
}
