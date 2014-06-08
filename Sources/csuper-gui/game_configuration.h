/*!
 * \file    game_configuration.h
 * \brief   Game configuration
 * \author  Remi BERTHO
 * \date    03/05/14
 * \version 3.0.0
 */

 /*
 * game_configuration.h
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
#include "main_window.h"

G_MODULE_EXPORT void openGameConfigurationPreferences(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void closeGameConfigurationPreferences(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT gboolean closeGameConfigurationPreferencesQuit(GtkWidget *widget, GdkEvent  *event, gpointer user_data);
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
void newGameConfigurationError(globalData *data, GtkWindow *parent_window);
G_MODULE_EXPORT void noMaxMinNewGameConfiguration(GtkWidget *widget, gpointer data);
void changeNewGameConfigurationDialog(globalData *data,game_config config);

#endif // GAME_CONFIGURATION_H_INCLUDED
