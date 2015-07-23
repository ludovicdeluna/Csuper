/*!
 * \file    preferences.h
 * \brief   The preferences of csuper
 * \author  Remi BERTHO
 * \date    10/01/15
 * \version 4.2.0
 */

 /*
 * preferences.h
 *
 * Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
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

#ifndef PREFERENCES_H_INCLUDED
#define PREFERENCES_H_INCLUDED

#include "csuper-gui.h"
#include "game_config_preferences.h"
#include "toolbar_button_preferences.h"
#include "exportation_preferences.h"

G_MODULE_EXPORT void openPreferences(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void openGameConfigurationPreferences(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void openToolbarButtonPreferences(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void openExporationPreferences(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void closePreferences(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT gboolean closePreferencesQuit(GtkWidget *widget, GdkEvent  *event, gpointer user_data);

#endif // PREFERENCES_H_INCLUDED
