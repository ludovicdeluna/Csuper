/*!
 * \file    game_config_preferences.h
 * \brief   The preferences of csuper
 * \author  Remi BERTHO
 * \date    10/01/15
 * \version 4.2.0
 */

 /*
 * game_config_preferences.h
 *
 * Copyright 2014-2015 Remi BERTHO <remi.bertho@gmail.com>
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

#ifndef GAME_CONFIGURATION_PREFERENCES_H_INCLUDED
#define GAME_CONFIGURATION_PREFERENCES_H_INCLUDED

#include "csuper-gui.h"
#include "utils.h"


G_MODULE_EXPORT void chooseExportedFileDialogSelect(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void chooseExportedFileDialogDeselect(GtkWidget *widget, gpointer data);
bool dialogMenuImportExportGameConfig(globalData *data,list_game_config *ptr_list_config,int **id,int *nb_id);
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

#endif // GAME_CONFIGURATION_PREFERENCES_H_INCLUDED
