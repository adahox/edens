#include "ui/icons/icons.h"

static const char *pick_icon_name(const char *primary, const char *fallback)
{
    GtkIconTheme *theme = gtk_icon_theme_get_default();

    if (gtk_icon_theme_has_icon(theme, primary)) {
        return primary;
    }
    if (fallback != NULL && gtk_icon_theme_has_icon(theme, fallback)) {
        return fallback;
    }
    return primary;
}

GtkWidget *edens_icon_button_new(const char *primary, const char *fallback)
{
    return gtk_button_new_from_icon_name(
        pick_icon_name(primary, fallback),
        GTK_ICON_SIZE_BUTTON
    );
}
