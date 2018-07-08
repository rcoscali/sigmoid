#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include <assert.h>
#include <libintl.h>
#include <glib.h>
#include <glib/gi18n.h>
#include <gio/gio.h>
#include <gtk/gtk.h>

#include "common.h"
#include "sigmoid.h"

static Sigmoid *g_sigmoid;

/*
 * cb_quit
 *
 * Callback for quit button: this will exit the application
 */
void
cb_quit(void)
{
  g_debug("cb_quit(): ENTRY");
  g_application_quit(G_APPLICATION(g_sigmoid));
  g_debug("cb_quit(): EXIT");
}

GtkWidget *
get_window_widget(Sigmoid *sigmoid)
{
  g_debug("get_window_widget(): ENTRY");
  static GtkWidget *window = NULL;
  if (!window)
    {
      GValue *window_value = (GValue *)g_new0(GtkWidget *, 1);
      g_value_init (window_value, GTK_TYPE_WIDGET);
      g_object_get_property(G_OBJECT(g_sigmoid), "window", window_value);
      window = GTK_WIDGET(g_value_get_object(window_value));
    }
  window = GTK_WIDGET(g_object_ref(window));
  g_debug("get_window_widget(): RETURN(%p)", window);
  return (window);
}

GtkWidget *
get_about_dialog_widget(Sigmoid *sigmoid)
{
  g_debug("get_about_dialog_widget(): ENTRY");
  static GtkWidget *about_dialog = NULL;
  if (!about_dialog)
    {
      GValue *about_dialog_value = (GValue *)g_new0(GtkWidget *, 1);
      g_value_init (about_dialog_value, GTK_TYPE_WIDGET);
      g_object_get_property(G_OBJECT(g_sigmoid), "about-dialog", about_dialog_value);
      about_dialog = GTK_WIDGET(g_value_get_object(about_dialog_value));
    }
  about_dialog = GTK_WIDGET(g_object_ref(about_dialog));
  g_debug("get_about_dialog_widget(): RETURN(%p)", about_dialog);
  return (about_dialog);
}

GSimpleAction *
get_sigmoid_action(Sigmoid *sigmoid, gchar *action_name)
{
  g_debug("get_sigmoid_action(): ENTRY");

  GValue *action_group_value = (GValue *)g_new0(GtkWidget *, 1);
  g_value_init (action_group_value, G_TYPE_ACTION_MAP);
  g_object_get_property(G_OBJECT(g_sigmoid), "action-group", action_group_value);
  GActionGroup *action_group = (GActionGroup *)g_value_get_object(action_group_value);

  GAction *action = g_action_map_lookup_action(G_ACTION_MAP(action_group), action_name);

  g_debug("get_sigmoid_action(): RETURN(%p)", action);
  return (G_SIMPLE_ACTION(action));
}

/*
 * cb_quit_activate
 *
 * Callback for quit menu item: this will exit the application
 */
void
cb_quit_activate(void)
{
  g_debug("cb_quit_activate(): ENTRY");
  GtkWidget *window = get_window_widget(g_sigmoid);
  gtk_widget_hide(window);
  gtk_widget_destroy(window);
  g_object_unref(window);
  g_debug("cb_quit_activate(): EXIT");
}

/*
 * cb_menu_fichier_nouveau
 *
 *
 */
void
cb_menu_fichier_nouveau(void)
{
  g_debug("cb_menu_fichier_nouveau(): ENTRY");
  GtkWidget *window = get_window_widget(g_sigmoid);

  g_object_unref(window);
  g_debug("cb_menu_fichier_nouveau(): EXIT");
}

/*
 * cb_menu_fichier_ouvrir
 *
 *
 */
void
cb_menu_fichier_ouvrir(void)
{
  g_debug("cb_menu_fichier_ouvrir(): ENTRY");
  GtkWidget *window = get_window_widget(g_sigmoid);

  g_object_unref(window);
  g_debug("cb_menu_fichier_ouvrir(): EXIT");
}

/*
 * cb_menu_fichier_sauver
 *
 *
 */
void
cb_menu_fichier_sauver(void)
{
  g_debug("cb_menu_fichier_sauver(): ENTRY");
  GtkWidget *window = get_window_widget(g_sigmoid);

  g_object_unref(window);
  g_debug("cb_menu_fichier_sauver(): EXIT");
}

/*
 * cb_menu_fichier_sauver_comme
 *
 *
 */
void
cb_menu_fichier_sauver_comme(GString *filename)
{
  g_debug("cb_menu_fichier_sauver_comme(filename = %s): ENTRY", filename->str);
  GtkWidget *window = get_window_widget(g_sigmoid);

  g_object_unref(window);
  g_debug("cb_menu_fichier_sauver_comme(): EXIT");
}

/*
 * cb_menu_edition_couper
 *
 *
 */
void
cb_menu_edition_couper(void)
{
  g_debug("cb_menu_edition_couper(): ENTRY");
  GtkWidget *window = get_window_widget(g_sigmoid);

  g_object_unref(window);
  g_debug("cb_menu_edition_couper(): EXIT");
}

/*
 * cb_menu_edition_copier
 *
 *
 */
void
cb_menu_edition_copier(void)
{
  g_debug("cb_menu_edition_copier(): ENTRY");
  GtkWidget *window = get_window_widget(g_sigmoid);

  g_object_unref(window);
  g_debug("cb_menu_edition_copier(): EXIT");
}

/*
 * cb_menu_edition_coller
 *
 *
 */
void
cb_menu_edition_coller(void)
{
  g_debug("cb_menu_edition_coller(): ENTRY");
  GtkWidget *window = get_window_widget(g_sigmoid);

  g_object_unref(window);
  g_debug("cb_menu_edition_coller(): EXIT");
}

/*
 * cb_menu_edition_supprimer
 *
 *
 */
void
cb_menu_edition_supprimer(void)
{
  g_debug("cb_menu_edition_supprimer(): ENTRY");
  GtkWidget *window = get_window_widget(g_sigmoid);

  g_object_unref(window);
  g_debug("cb_menu_edition_supprimer(): EXIT");
}

/*
 * cb_menu_aide_apropos
 *
 *
 */
void
cb_menu_aide_apropos(void)
{
  g_debug("cb_menu_aide_apropos(): ENTRY");
  GtkWidget *window = get_window_widget(g_sigmoid);
  GtkWidget *about = get_about_dialog_widget(g_sigmoid);

  gtk_show_about_dialog(GTK_WINDOW(window),
                        "program-name", "Sigmoid",
                        "title", _("About Aigmoid"),
                        NULL);

  g_object_unref(about);
  g_debug("cb_menu_aide_apropos(): EXIT");
}

/*
 * cb_apropos_accel_activate
 */
void
cb_apropos_accel_activate(void)
{
  g_debug("cb_apropos_accel_activate(): ENTRY");
  cb_menu_aide_apropos();
  g_debug("cb_apropos_accel_activate(): EXIT");
}

/*
 * cb_action_new_activate
 */
void
cb_action_new_activate(GSimpleAction *simple,
                       GVariant      *parameter,
                       gpointer       user_data)
{
  g_debug("cb_action_new_activate(): ENTRY");

  GSimpleAction *action_save = get_sigmoid_action(g_sigmoid, "sigmoid.file.save");
  GSimpleAction *action_saveas = get_sigmoid_action(g_sigmoid, "sigmoid.file.saveas");

  cb_menu_fichier_nouveau();

  g_action_change_state((GAction *)action_save, g_variant_new_string("TRUE"));
  g_action_change_state((GAction *)action_saveas, g_variant_new_string("TRUE"));

  g_debug("cb_action_new_activate(): EXIT");
}

/*
 * cb_action_open_activate
 */
void
cb_action_open_activate(GSimpleAction *simple,
                       GVariant      *parameter,
                       gpointer       user_data)
{
  g_debug("cb_action_open_activate(): ENTRY");

  GString *filename = (GString *)g_variant_get_type_string(parameter);

  g_debug("cb_action_open_activate(): filename = %s", filename->str);

  GSimpleAction *action_save = get_sigmoid_action(g_sigmoid, "sigmoid.file.save");
  GSimpleAction *action_saveas = get_sigmoid_action(g_sigmoid, "sigmoid.file.saveas");

  cb_menu_fichier_ouvrir();

  g_action_change_state((GAction *)action_save, g_variant_new_string("TRUE"));
  g_action_change_state((GAction *)action_saveas, g_variant_new_string("TRUE"));
  
  g_debug("cb_action_open_activate(): EXIT");
}


/*
 * cb_action_save_activate
 */
void
cb_action_save_activate(GSimpleAction *simple,
                       GVariant      *parameter,
                       gpointer       user_data)
{
  g_debug("cb_action_save_activate(): ENTRY");

  GSimpleAction *action_save = get_sigmoid_action(g_sigmoid, "sigmoid.file.save");

  cb_menu_fichier_sauver();

  g_action_change_state((GAction *)action_save, g_variant_new_string("TRUE"));
  
  g_debug("cb_action_save_activate(): EXIT");
}

/*
 * cb_action_save_changed_state
 */
void
cb_action_save_changed_state(GSimpleAction *simple,
                             GVariant      *parameter,
                             gpointer       user_data)
{
  g_debug("cb_action_save_changed_state(): ENTRY");

  
  g_debug("cb_action_save_changed_state(): EXIT");
}

/*
 * cb_action_saveas_activate
 */
void
cb_action_saveas_activate(GSimpleAction *simple,
                       GVariant      *parameter,
                       gpointer       user_data)
{
  g_debug("cb_action_saveas_activate(): ENTRY");

  GString *filename = (GString *)g_variant_get_type_string(parameter);

  g_debug("cb_action_saveas_activate(): filename = %s", filename->str);

  GSimpleAction *action_save = get_sigmoid_action(g_sigmoid, "sigmoid.file.save");
  GSimpleAction *action_saveas = get_sigmoid_action(g_sigmoid, "sigmoid.file.saveas");

  cb_menu_fichier_sauver_comme(filename);

  g_action_change_state((GAction *)action_save, g_variant_new_string(""));
  g_action_change_state((GAction *)action_saveas, g_variant_new_string(""));

  g_debug("cb_action_saveas_activate(): EXIT");
}

/*
 * cb_action_saveas_changed_state
 */
void
cb_action_saveas_changed_state(GSimpleAction *simple,
                               GVariant      *parameter,
                               gpointer       user_data)
{
  g_debug("cb_action_saveas_changed_state(): ENTRY");
  
  g_debug("cb_action_saveas_changed_state(): EXIT");
}

/*
 * cb_action_quit_activate
 */
void
cb_action_quit_activate(GSimpleAction *simple,
                        GVariant      *parameter,
                        gpointer       user_data)
{
  g_debug("cb_action_quit_activate(): ENTRY");
  cb_quit_activate();
  g_debug("cb_action_quit_activate(): EXIT");
}

/*
 * cb_action_about_activate
 */
void
cb_action_about_activate(GSimpleAction *simple,
                       GVariant      *parameter,
                       gpointer       user_data)
{
  g_debug("cb_action_about_activate(): ENTRY");
  cb_menu_aide_apropos();
  g_debug("cb_action_about_activate(): EXIT");
}

/*
 * main
 *
 * Main entry point for application
 *
 * @param[in] argc	number of arguments
 * @param[in] argv	table of arguments pointers
 *
 * @return exit code as an int
 */
int
main(int argc, char **argv)
{
  int ret = 0;
  g_debug("main(): ENTRY");
  gtk_init(&argc, &argv);
  g_sigmoid = sigmoid_new();
  ret = g_application_run(G_APPLICATION(g_sigmoid), argc, argv);
  g_debug("main(): EXIT = %d", ret);
  exit(ret);
}
