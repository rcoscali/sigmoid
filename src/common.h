#ifndef COMMON_H
#define COMMON_H

#include <glib.h>
#include <glib/gi18n.h>
#include <gio/gio.h>

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

void cb_action_new_activate(GSimpleAction *, GVariant *, gpointer);
void cb_action_open_activate(GSimpleAction *, GVariant *, gpointer);
void cb_action_save_activate(GSimpleAction *, GVariant *, gpointer);
void cb_action_save_changed_state(GSimpleAction *, GVariant *, gpointer);
void cb_action_saveas_activate(GSimpleAction *, GVariant *, gpointer);
void cb_action_saveas_changed_state(GSimpleAction *, GVariant *, gpointer);
void cb_action_quit_activate(GSimpleAction *, GVariant *, gpointer);
void cb_action_about_activate(GSimpleAction *, GVariant *, gpointer);

void myfunc();

#endif /* COMMON_H */
