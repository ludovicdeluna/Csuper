/*!
 * \file    preferences.h
 * \brief   The preferences of csuper
 * \author  Remi BERTHO
 * \date    26/06/14
 * \version 4.0.0
 */

 /*
 * preferences.h
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

#ifndef GAME_CONFIGURATION_H_INCLUDED
#define GAME_CONFIGURATION_H_INCLUDED

#include "csuper-gui.h"
#include "utils.h"
#include "main_window.h"

G_MODULE_EXPORT void openPreferences(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void openGameConfigurationPreferences(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void openToolbarButtonPreferences(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void closePreferences(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT gboolean closePreferencesQuit(GtkWidget *widget, GdkEvent  *event, gpointer user_data);
G_MODULE_EXPORT void chooseExportedFile(GtkWidget *widget, gpointer data);
void exportGameConfigurationError(globalData *data);
G_MODULE_EXPORT void chooseImportedFile(GtkWidget *widget, gpointer data);
void importGameConfigurationError(globalData *data);
void displayGameConfiguration(globalData *data);
void deleteDisplayGameConfiguration(globalData *data);
void updateDisplayGameConfiguration(globalData *data);
G_MODULE_EXPORT void deleteGameConfiguration(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void editGameConfiguration(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void viewGameConfiguration(GtkWidget *widget, gpointer data);
void updateDisplayCurrentGameConfiguration(globalData *data , gint index, gboolean clear);
G_MODULE_EXPORT void addGameConfiguration(GtkWidget *widget, gpointer data);
game_config *newGameConfiguration(globalData *data, GtkWindow *parent_window);
G_MODULE_EXPORT void checkGoodNewGameConfiguration(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void noMaxMinNewGameConfiguration(GtkWidget *widget, gpointer data);
void changeNewGameConfigurationDialog(globalData *data,game_config config);
void updateToolbarButtonPreferencesSwitch(globalData *data);
void readToolbarButtonPreferencesSwitch(globalData *data, toolbar_button_preferences_struct *toolbar_preferences);
G_MODULE_EXPORT void checkToolbarButtonPreferencesChanged(GtkWidget *widget, GParamSpec *pspec,gpointer data);
G_MODULE_EXPORT void validToolbarButtonPreferences(GtkWidget *widget, gpointer data);

#endif // GAME_CONFIGURATION_H_INCLUDED