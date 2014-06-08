/*!
 * \file    csuper-gui.h
 * \brief   Inclusion of csuper-gui
 * \author  Remi BERTHO
 * \date    02/05/14
 * \version 3.0.0
 */

 /*
 * csuper-gui.h
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

#ifndef CSUPER_GUI_H_INCLUDED
#define CSUPER_GUI_H_INCLUDED

/*!
 * \def CSUPER_GUI
 * Define that we compile csuper-gui.
 */
#define CSUPER_GUI

/*!
 * \def PORTABLE
 * Define that we compile csuper-gui portable
 */
//#define PORTABLE

#include <gtk/gtk.h>
#include <stdlib.h>
#include <glib/gi18n.h>
#include <locale.h>
#include "../libcsuper/libcsuper.h"

/*!
 * \struct globalData
 * Represent the global data which is passed into all signal
 */
typedef struct
{
    GtkBuilder *ptr_builder;                /*!< A pointer to a GTK builder. */
    csuStruct *ptr_csu_struct;              /*!< A pointer to a csuStruct */
    GtkWidget *ptr_main_window;                 /*! The main window */
    GtkWidget *ptr_new_csu_file_assistant;     /*! The new csu file assistant window */
    game_config config;                     /*!< A game configuration */
    csuStruct *ptr_csu_struct_tmp;              /*!< A pointer to a temporary csuStruct */
    gchar csu_filename[SIZE_MAX_FILE_NAME];   /*!< The filename of the csu file*/
    GtkClipboard *ptr_clipboard;                /*!< A pointer to the main clipboard */
    GtkClipboard *ptr_clipboard_selected;       /*!< A pointer to the selected clipboard */
}globalData;



#endif // CSUPER-GUI_H_INCLUDED
