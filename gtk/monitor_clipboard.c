/*
 * How to use Gtk monitor system clipboard
 * gcc `pkg-config --cflags --libs gtk+-2.0` monitor_clipboard.c
 * yurenjimi@gmail.com
 */
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <string.h>

void on_owner_change(void *data)
{
	GtkClipboard *clip = (GtkClipboard *) data;
	gchar *text = gtk_clipboard_wait_for_text(clip);
	g_printf("%s", text);
    g_printf("\n\n\n");
}

void usage(const char *cmd)
{
    g_printf("Usage: %s \"clipboard\"|\"primary\"|\"secondary\"\n", cmd);
}

int main (int argc, char **argv) 
{
    if (argc != 2) {
        usage(argv[0]);
        return 0;
    }

    /* initialize GTK */
    gtk_init (&argc, &argv);

    /* deal with cmd argv */
    GdkAtom type;
    if (!strcmp(argv[1], "primary")) {
        type = GDK_SELECTION_PRIMARY;
    } else if (!strcmp(argv[1], "clipboard")) {
        type = GDK_SELECTION_CLIPBOARD;
    } else if (!strcmp(argv[1], "secondary")) {
        type = GDK_SELECTION_SECONDARY;
    } else {
        usage(argv[0]);
        return 0;
    }
#if 0
    clipboard = gtk_clipboard_get(//GDK_SELECTION_CLIPBOARD  /* Ctrl-C */
                                  GDK_SELECTION_PRIMARY      /* */
                                  //GDK_SELECTION_SECONDARY  /* ? */
                                  );
#endif
    /* get system clipboard */
    GtkClipboard *clipboard = gtk_clipboard_get(type);
    g_signal_connect(clipboard, "owner-change", G_CALLBACK(on_owner_change), clipboard);

    /* event loop */
    gtk_main();
    return 0;
}
