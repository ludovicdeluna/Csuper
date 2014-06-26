/*!
 * \file    utils.h
 * \brief   The new file assistant function
 * \author  Remi BERTHO
 * \date    26/06/14
 * \version 4.0.0
 */

 /*
 * utils.h
 *
 * Copyright 2014 Remi BERTHO <remi.bertho@gmail.com>
 *
 * This file is part of Csuper-gui.
 *
 * Csuper-gui is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Csuper-gui is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "csuper-gui.h"

void setGtkLabelAttributes(GtkLabel *label, int text_size, gboolean use_foreground,guint16 foreground_red, guint16 foreground_green, guint16 foreground_blue, gboolean use_background,guint16 background_red, guint16 background_green, guint16 background_blue);
GtkLabel *createGtkLabelWithAttributes(gchar *text, int text_size, gboolean use_foreground,guint16 foreground_red, guint16 foreground_green, guint16 foreground_blue, gboolean use_background,guint16 background_red, guint16 background_green, guint16 background_blue);
#endif // UTILS_H_INCLUDED
