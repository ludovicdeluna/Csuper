/*!
 * \file    new_file_assistant.h
 * \brief   The new file assistant function
 * \author  Remi BERTHO
 * \date    26/06/14
 * \version 4.0.0
 */

 /*
 * new_file_assistant.h
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

#ifndef NEW_FILE_ASSISTANT_H_INCLUDED
#define NEW_FILE_ASSISTANT_H_INCLUDED

#include "csuper-gui.h"
#include "main_window.h"
#include "main_menu.h"
#include "game_config_preferences.h"
#include "utils.h"

G_MODULE_EXPORT void openAssistantNewCsu(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void deleteEventAssistantNewCsu(GtkWidget *widget,GdkEvent  *event, gpointer data);
G_MODULE_EXPORT void deleteAssistantNewCsu(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void validAssistantNewCsuOne(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void chooseGameConfigurationNewAssistant(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void preparePageAssistantNewCsu(GtkAssistant *assistant,GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void validAssistantNewCsuTwo(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void validAssistantNewCsuThree(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void endAssistantNewCsu(GtkWidget *widget, gpointer data);
void cleanAssistantNewCsu(globalData *data);

#endif // NEW_FILE_ASSISTANT_H_INCLUDED
