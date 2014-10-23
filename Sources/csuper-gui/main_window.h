/*!
 * \file    main_window.h
 * \brief   Main window
 * \author  Remi BERTHO
 * \date    26/04/14
 * \version 4.0.0
 */

 /*
 * main_window.h
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

#ifndef MAIN_WINDOW_H_INCLUDED
#define MAIN_WINDOW_H_INCLUDED

#include "csuper-gui.h"
#include "utils.h"
#include "main_menu.h"

void noCsuFileRanking(globalData *data);
void deleteRanking(globalData *data);
void createRanking(globalData *data);
void updateMainWindow(globalData *data,bool editable);
void updateDistributorLabel(globalData *data);
G_MODULE_EXPORT void updateTotalPointsInTurnLabelSignal(GtkWidget *widget, gpointer data);
void updateTotalPointsInTurnLabel(globalData *data,bool updatable_points);
void noCsuFilePoints(globalData *data);
void deletePoints(globalData *data);
void createPointsGrid(globalData *data,bool spin_button);
G_MODULE_EXPORT void endOfTurn(GtkWidget *widget, gpointer data);
void gameOver(globalData *data);
void setButtonMainWindow(globalData *data);
G_MODULE_EXPORT gboolean setButtonMainWindowClipboardSensitive(gpointer data);
void readMainWindowSize(globalData *data);
G_MODULE_EXPORT gboolean saveMainWindowSize(GtkWidget *widget,GdkEvent *event,gpointer user_data);
G_MODULE_EXPORT void changeDistributorButton(GtkWidget *widget, gpointer data);

#endif // MAIN_WINDOW_H_INCLUDED
