#include <gtk/gtk.h>
#include "toolbar.h"
#include "ui/icons.h"

GtkWidget *build_toolbar(void)
{
    GtkWidget *toolbar = gtk_box_new(
        GTK_ORIENTATION_HORIZONTAL,
        3
    );

    gtk_widget_set_name(toolbar, "explorer-toolbar");

    // botões de navegação
    GtkWidget *backButton = edens_icon_button_new(
        EDENS_ICON_GO_PREVIOUS,
        EDENS_ICON_GO_PREVIOUS_FALLBACK
    );
    GtkWidget *forwardButton = edens_icon_button_new(
        EDENS_ICON_GO_NEXT,
        EDENS_ICON_GO_NEXT_FALLBACK
    );

    gtk_box_pack_start(GTK_BOX(toolbar),backButton,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(toolbar),forwardButton,FALSE,FALSE,0);


    GtkWidget *pathEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(pathEntry), "Procurar...");

    gtk_widget_set_halign(pathEntry, GTK_ALIGN_FILL);
    gtk_box_pack_start(GTK_BOX(toolbar),pathEntry,TRUE,TRUE,0);
    
    GtkWidget *btn_hidden = edens_icon_button_new(
        EDENS_ICON_EYE_HIDDEN,
        EDENS_ICON_EYE_HIDDEN_FALLBACK
    );
    gtk_widget_set_tooltip_text(btn_hidden, "Mostrar/Ocultar arquivos ocultos (Ctrl+H)");

    gtk_box_pack_start(GTK_BOX(toolbar),btn_hidden,FALSE,FALSE,0);
    return toolbar;
}
