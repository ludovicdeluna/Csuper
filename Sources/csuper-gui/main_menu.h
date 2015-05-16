/*!
 * \file    main_menu.h
 * \brief   Main menu
 * \author  Remi BERTHO
 * \date    31/08/14
 * \version 4.2.0
 */

 /*
 * main_menu.h
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

#ifndef MAIN_MENU_H_INCLUDED
#define MAIN_MENU_H_INCLUDED

#include "csuper-gui.h"
#include "main_window.h"

G_MODULE_EXPORT void displayAbout(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void chooseCsuFileOpen(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void recentCsuFileOpen(GtkRecentChooser *chooser, gpointer data);
void openFileError(globalData *data);
G_MODULE_EXPORT void chooseCsuFileSave(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void chooseExportFile(GtkWidget *widget, gpointer data);
void saveFileError(globalData *data);
void exportFileError(globalData *data);
G_MODULE_EXPORT void copyToCliboard(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void pastFromClipboard(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void deleteSelectedText(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void cutToClipboard(GtkWidget *widget, gpointer data);
void updateCsuInfo(globalData *data);
G_MODULE_EXPORT void showPropertiesDialogBox(GtkWidget *widget, gpointer data);
void addLastCsuStruct(globalData *data);
void deleteAllLastCsuStruct(globalData *data);
G_MODULE_EXPORT void undoCsuStruct(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void redoCsuStruct(GtkWidget *widget, gpointer data);
void updateToolbarButton(globalData *data);
G_MODULE_EXPORT void deleteFileButton(GtkWidget *widget, gpointer data);
void deleteFileError(globalData *data);
G_MODULE_EXPORT void displayPodium(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void changeDisplayDifferencePoints(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void changeDisplayPointsGrid(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void updateCalculatorMainWindow(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void changeDisplayMainWindowSide(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void displayStatistics(GtkWidget *widget, gpointer data);

#endif // MAIN_MENU_H_INCLUDED
