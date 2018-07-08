/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * sigmoid.c
 * Copyright (C) 2018 R??mi Cohen-Scali <remi@cohenscali.net>
 * 
 * sigmoid is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * sigmoid is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <strings.h>
#include "common.h"
#include "sigmoid.h"

#include <glib/gi18n.h>
#include <glib-object.h>
#include <gtk/gtk.h>

/* For testing propose use the local (not installed) ui file */
#define UI_FILE_INSTALLED PACKAGE_DATA_DIR"/ui/sigmoid.ui"
#define UI_FILE_SRC_LOCAL "src/sigmoid.ui"
#define UI_FILE_LOCAL     "sigmoid.ui"

#define TOP_WINDOW "window1"

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };

G_DEFINE_TYPE (Sigmoid, sigmoid, GTK_TYPE_APPLICATION);


/* ANJUTA: Macro SIGMOID_APPLICATION gets Sigmoid - DO NOT REMOVE */
struct _SigmoidPrivate
{
	GString *filename;
	
	/* ANJUTA: Private declaration for sigmoid - DO NOT REMOVE */
	GtkBuilder *builder;
	GtkApplication *app;
	GtkWidget *widget;
	GtkWidget *about;

	/* ANJUTA: Widgets declaration for sigmoid.glade - DO NOT REMOVE */
	GtkWidget *window;
	GtkMenuBar *menubar;
	GtkMenuItem *menufichier;
	GtkMenuItem *menuedition;
	GtkMenuItem *menuaffichage;
	GtkMenuItem *menuaide;
	GtkToolbar *toolbar;
	GtkScrolledWindow *scrolledwindow;
	GtkViewport *viewport;
	GtkLabel *framelabel;
	GtkInfoBar *infobar;
	GtkAboutDialog *aboutdialog;

	/* Actions */
	GActionGroup *actions;
};

static void
sigmoid_init_priv (Sigmoid *object)
{
	object->priv->window = GTK_WIDGET(gtk_builder_get_object(object->priv->builder, "window1"));
	object->priv->window = GTK_WIDGET(g_object_ref(G_OBJECT(object->priv->window)));
	g_debug("sigmoid_init_priv(): Window = %p", object->priv->window);
	object->priv->menubar = GTK_MENU_BAR(gtk_builder_get_object(object->priv->builder, "menubar"));
	g_debug("sigmoid_init_priv(): Menubar = %p", object->priv->menubar);
	object->priv->menufichier = GTK_MENU_ITEM(gtk_builder_get_object(object->priv->builder, "menufichier"));
	g_debug("sigmoid_init_priv(): Menufichier = %p", object->priv->menufichier);
	object->priv->menuedition = GTK_MENU_ITEM(gtk_builder_get_object(object->priv->builder, "menuedition"));
	g_debug("sigmoid_init_priv(): Menuedition = %p", object->priv->menuedition);
	object->priv->menuaffichage = GTK_MENU_ITEM(gtk_builder_get_object(object->priv->builder, "menuaffichage"));
	g_debug("sigmoid_init_priv(): Menuaffichage = %p", object->priv->menuaffichage);
	object->priv->menuaide = GTK_MENU_ITEM(gtk_builder_get_object(object->priv->builder, "menuaide"));
	g_debug("sigmoid_init_priv(): Menuaide = %p", object->priv->menuaide);
	object->priv->toolbar = GTK_TOOLBAR(gtk_builder_get_object(object->priv->builder, "toolbar"));
	g_debug("sigmoid_init_priv(): Toolbar = %p", object->priv->toolbar);
	object->priv->scrolledwindow = GTK_SCROLLED_WINDOW(gtk_builder_get_object(object->priv->builder, "scrolledwindow"));
	g_debug("sigmoid_init_priv(): ScrolledWindow = %p", object->priv->scrolledwindow);
	object->priv->viewport = GTK_VIEWPORT(gtk_builder_get_object(object->priv->builder, "viewport"));
	g_debug("sigmoid_init_priv(): Viewport = %p", object->priv->viewport);
	object->priv->framelabel = GTK_LABEL(gtk_builder_get_object(object->priv->builder, "framelabel"));
	g_debug("sigmoid_init_priv(): Framelabel = %p", object->priv->framelabel);
	object->priv->infobar = GTK_INFO_BAR(gtk_builder_get_object(object->priv->builder, "infobar"));
	g_debug("sigmoid_init_priv(): Infobar = %p", object->priv->infobar);
	object->priv->aboutdialog = GTK_ABOUT_DIALOG(gtk_builder_get_object(object->priv->builder, "aboutdialog"));
	g_debug("sigmoid_init_priv(): AboutDialog = %p", object->priv->aboutdialog);

	g_debug("sigmoid_init_priv(): EXIT");
}

/* Create a new window loading a file */
static void
sigmoid_new_window (GApplication *app,
					GFile        *file)
{
	GError* error = NULL;
	SigmoidPrivate *priv = SIGMOID_APPLICATION(app)->priv;

	g_debug("sigmoid_new_window(): builder = %p, ENTRY", priv->builder);

	/* Load UI from file */
	priv->builder = gtk_builder_new();
	
#define TRY_LOAD_UI_FILE(ui_file) 								\
	if (gtk_builder_add_from_file (priv->builder, ui_file, &error))	\
		break;
	
	do
		{
			TRY_LOAD_UI_FILE(UI_FILE_LOCAL);
			g_error ("Couldn't load builder file: %s", error->message);
			TRY_LOAD_UI_FILE(UI_FILE_SRC_LOCAL);
			g_error ("Couldn't load builder file: %s", error->message);
			TRY_LOAD_UI_FILE(UI_FILE_INSTALLED);
			
			g_critical ("Couldn't load builder file: %s", error->message);
			g_error_free (error);
		}
	while (0);
#undef TRY_LOAD_UI_FILE

	/* Set app property */
	g_debug("sigmoid_new_window(): app = %p", app);
	priv->app = GTK_APPLICATION(app);

	/* load all widgets */
	sigmoid_init_priv(SIGMOID_APPLICATION(app));
	priv->widget = GTK_WIDGET(priv->window);
	
	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (priv->builder, app);

	/* ANJUTA: Widgets initialization for sigmoid.glade - DO NOT REMOVE */

	gtk_window_set_application (GTK_WINDOW (priv->window), GTK_APPLICATION (app));
	if (file != NULL)
		{
			/* TODO: Add code here to open the file in the new window */
			g_debug("TODO: open new window: app = %p", app);
		}

	GSimpleActionGroup *action_group = g_simple_action_group_new();
	
	const GActionEntry entries[] = {
		{ "sigmoid.file.new",    cb_action_new_activate,    NULL,   NULL,                        NULL    },
		{ "sigmoid.file.open",   cb_action_open_activate,   NULL,   NULL,                        NULL    },
		{ "sigmoid.file.save",   cb_action_save_activate,   NULL, "TRUE", cb_action_save_changed_state   },
		{ "sigmoid.file.saveas", cb_action_saveas_activate,  "s", "TRUE", cb_action_saveas_changed_state },
		{ "sigmoid.file.quit",   cb_action_quit_activate,   NULL,   NULL,                        NULL    },
		{ "sigmoid.help.about",  cb_action_about_activate,  NULL,   NULL,                        NULL    }
	};
	g_action_map_add_action_entries(G_ACTION_MAP(action_group), entries,  G_N_ELEMENTS (entries), NULL);
	priv->actions = G_ACTION_GROUP(action_group);

	gtk_widget_show_all (GTK_WIDGET (priv->window));
	
	g_debug("sigmoid_new_window(): EXIT");
}


/* GApplication implementation */
static void
sigmoid_activate (GApplication *application)
{
	g_debug("sigmoid_activate(): ENTRY");
	sigmoid_new_window (application, NULL);
	g_debug("sigmoid_activate(): EXIT");
}

static void
sigmoid_open (GApplication  *application,
			  GFile        **files,
			  gint           n_files,
			  const gchar   *hint)
{
	gint i;
	
	g_debug("sigmoid_open(): ENTRY");
	for (i = 0; i < n_files; i++)
		sigmoid_new_window (application, files[i]);
	g_debug("sigmoid_open(): EXIT");
}

static void
sigmoid_set_property (GObject      *object,
					  guint         property_id,
					  const GValue *value,
					  GParamSpec   *pspec)
{
	//Sigmoid *self = SIGMOID_APPLICATION (object);

	g_debug("sigmoid_set_property(): ENTRY");
	switch (property_id)
		{
		default:
			/* We don't have any other property... */
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
		}
	g_debug("sigmoid_set_property(): EXIT");
}

static void
sigmoid_get_property (GObject    *object,
					  guint       property_id,
					  GValue     *value,
					  GParamSpec *pspec)
{
	Sigmoid *self = SIGMOID_APPLICATION (object);

	g_debug("sigmoid_get_property(): ENTRY");
	switch (property_id)
		{
		case PROP_APPLICATION:
			g_value_set_object (value, self->priv->app);
			break;
			
		case PROP_BUILDER:
			g_value_set_object (value, self->priv->builder);
			break;
			
		case PROP_WINDOW:
			g_value_set_object (value, self->priv->widget);
			break;
			
		case PROP_ABOUT:
			g_value_set_object (value, self->priv->about);
			break;
			
		case PROP_ACTION_GROUP:
			g_value_set_object (value, self->priv->actions);
			break;
			
		default:
			/* We don't have any other property... */
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
		}
	g_debug("sigmoid_get_property(): EXIT");
}

static void
sigmoid_init (Sigmoid *object)
{
	g_debug("sigmoid_init(): ENTRY");
	object->priv = G_TYPE_INSTANCE_GET_PRIVATE (object, SIGMOID_TYPE_APPLICATION, SigmoidPrivate);
	bzero(object->priv, sizeof(struct _SigmoidPrivate));
	g_debug("sigmoid_init(): EXIT");
}

static void
sigmoid_finalize (GObject *object)
{
	g_debug("sigmoid_finalize(): ENTRY");
	SigmoidPrivate *priv = G_TYPE_INSTANCE_GET_PRIVATE (object, SIGMOID_TYPE_APPLICATION, SigmoidPrivate);
	g_object_unref(priv->builder);
	g_object_unref(priv->actions);
	G_OBJECT_CLASS (sigmoid_parent_class)->finalize (object);
	g_debug("sigmoid_finalize(): EXIT");
}

static void
sigmoid_class_init (SigmoidClass *klass)
{
	g_debug("sigmoid_class_init(): ENTRY");
	G_APPLICATION_CLASS (klass)->activate = sigmoid_activate;
	G_APPLICATION_CLASS (klass)->open = sigmoid_open;

	g_type_class_add_private (klass, sizeof (SigmoidPrivate));

	G_OBJECT_CLASS (klass)->set_property = sigmoid_set_property;
	G_OBJECT_CLASS (klass)->get_property = sigmoid_get_property;
	G_OBJECT_CLASS (klass)->finalize = sigmoid_finalize;

	obj_properties[PROP_APPLICATION] =
		g_param_spec_object ("app",
							 "Application",
							 _("The Sigmoid GTK application object."),
							 GTK_TYPE_APPLICATION  /* type of object */,
							 G_PARAM_READABLE);

	obj_properties[PROP_BUILDER] =
		g_param_spec_object ("builder",
							 "Builder",
							 _("Name of the builder to load and display UI file."),
							 GTK_TYPE_BUILDER  /* type of object */,
							 G_PARAM_READABLE);
	
	obj_properties[PROP_WINDOW] =
		g_param_spec_object ("window",
							 "Window",
							 _("GTK window of the Sigmoid application."),
							 GTK_TYPE_WIDGET  /* type of object */,
							 G_PARAM_READABLE);
	
	obj_properties[PROP_ABOUT] =
		g_param_spec_object ("about-dialog",
							 "AboutDialog",
							 _("GTK window of the Sigmoid application about dialog."),
							 GTK_TYPE_WIDGET  /* type of object */,
							 G_PARAM_READABLE);
	
	obj_properties[PROP_ACTION_GROUP] =
		g_param_spec_object ("action-group",
							 "ActionGroup",
							 _("Action group for the Sigmoid application."),
							 G_TYPE_ACTION_MAP  /* type of object */,
							 G_PARAM_READABLE);
	
	g_object_class_install_properties (G_OBJECT_CLASS (klass),
									   N_PROPERTIES,
									   obj_properties);
	
	g_debug("sigmoid_class_init(): EXIT");
}

Sigmoid *
sigmoid_new (void)
{
	Sigmoid *ret = SIGMOID_APPLICATION(NULL);
	g_debug("sigmoid_new(): ENTRY");
	ret = g_object_new (sigmoid_get_type (),
						"application-id", "org.gnome.sigmoid",
						"flags", G_APPLICATION_HANDLES_OPEN,
						NULL);
	g_debug("sigmoid_new() = %p: EXIT", ret);
	return ret;
}

