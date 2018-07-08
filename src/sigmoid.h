/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * sigmoid.h
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

#ifndef _SIGMOID_
#define _SIGMOID_

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define SIGMOID_TYPE_APPLICATION             (sigmoid_get_type ())
#define SIGMOID_APPLICATION(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), SIGMOID_TYPE_APPLICATION, Sigmoid))
#define SIGMOID_APPLICATION_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), SIGMOID_TYPE_APPLICATION, SigmoidClass))
#define SIGMOID_IS_APPLICATION(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SIGMOID_TYPE_APPLICATION))
#define SIGMOID_IS_APPLICATION_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), SIGMOID_TYPE_APPLICATION))
#define SIGMOID_APPLICATION_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), SIGMOID_TYPE_APPLICATION, SigmoidClass))

typedef struct _SigmoidClass SigmoidClass;
typedef struct _Sigmoid Sigmoid;
typedef struct _SigmoidPrivate SigmoidPrivate;

struct _SigmoidClass
{
	GtkApplicationClass parent_class;
};

enum SigmoidProperties
{
  PROP_APPLICATION = 1,
  PROP_BUILDER,
  PROP_WINDOW,
  PROP_ABOUT,
  PROP_ACTION_GROUP,
  N_PROPERTIES
};

struct _Sigmoid
{
	GtkApplication parent_instance;

	SigmoidPrivate *priv;

};

GType sigmoid_get_type (void) G_GNUC_CONST;
Sigmoid *sigmoid_new (void);

/* Callbacks */

G_END_DECLS

#endif /* _APPLICATION_H_ */

