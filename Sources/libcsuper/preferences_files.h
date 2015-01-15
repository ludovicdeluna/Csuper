/*!
 * \file    preferences_files.h
 * \brief   Prototypes des fonctions qui l'emrankment des fichiers sauvegardes
 * \author  Remi BERTHO
 * \date    07/01/15
 * \version 4.2.0
 */

/*
* preferences_files.h
*
* Copyright 2014-2015 Remi BERTHO <remi.bertho@gmail.com>
*
* This file is part of LibCsuper.
*
* LibCsuper is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
* LibCsuper is distributed in the hope that it will be useful,
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

#ifndef FILE_SYSTEM_PATH_H_INCLUDED
#define FILE_SYSTEM_PATH_H_INCLUDED

#include "share.h"
#include "csu_struct.h"
#include "csu_files.h"
#include "filename.h"
#include "export.h"


/*!
 * \def FILENAME_SYSTEM_PATH
 * Define the filename of the file which contain the system path
 */
#define FILENAME_SYSTEM_PATH "system_path.txt"

/*!
 * \def FILENAME_TOOLBAR_BUTTON_PREFERENCES
 * Define the filename of the file which contain the toolbar button preferences
 */
#define FILENAME_TOOLBAR_BUTTON_PREFERENCES "toolbar_button_preferences.txt"

/*!
 * \def FILENAME_TOOLBAR_BUTTON_PREFERENCES
 * Define the filename of the file which contain the toolbar button preferences
 */
#define FILENAME_MAIN_WINDOW_SIZE "main_window_size.txt"

/*!
 * \def FILENAME_DIFFERENCE_BETWEEN_PLAYER
 * Define the filename of the file which contain the difference preference
 */
#define FILENAME_DIFFERENCE_BETWEEN_PLAYER "difference_beteween_player.txt"

/*!
 * \def FILENAME_PDF_PREFERENCES
 * Define the filename of the file which contain pdf preferences
 */
#define FILENAME_PDF_PREFERENCES "pdf_preferences.txt"

/*!
 * \def PREFERENCES_FOLDER_NAME
 * Define the folder name of the csuper preferences
 */
#define PREFERENCES_FOLDER_NAME ".csuper"

/*!
 * \struct toolbar_button_preferences_struct
 * Represent the toolbar button preferences
 */
typedef struct
{
    int new;              /*!< The new button */
    int open;              /*!< The open button */
    int save_as;              /*!< The save_as button */
    int export;              /*!< The export button */
    int separator_6;              /*!< The separator 6*/
    int delete_file;              /*!< The delete file button */
    int separator_1;              /*!< The separator 1*/
    int undo;              /*!< The undo button */
    int redo;              /*!< The redo button */
    int separator_2;              /*!< The separator 2 */
    int cut;              /*!< The cut button */
    int copy;              /*!< The copy button */
    int paste;              /*!< The paste button */
    int delete;              /*!< The delete button */
    int separator_3;              /*!< The separator 3 */
    int properties;              /*!< The properties button */
    int separator_4;              /*!< The separator 4 */
    int preferences;              /*!< The preferences button */
    int game_configuration_preferences;              /*!< The game configuration preferences button */
    int toolbar_button_preferences;              /*!< The toolbar button preferences button */
    int exportation_preferences;              /*!< The exportation preferences button */
    int separator_5;              /*!< The separator 5 */
    int about;              /*!< The about button */
} toolbar_button_preferences_struct;

/*!
 * \struct main_window_size
 * All component of the man window size
 */
typedef struct
{
    int width;              /*!< The width of the main window */
    int height;              /*!< The height of the main window */
    int is_maximize;              /*!< Said if the main window is maximize or not */
} main_window_size;

/*!
 * \struct difference_between_player
 * Indicate which difference between player will be displayed in the ranking
 */
typedef struct
{
    bool consecutive;   /*!< Between two player consecutive */
    bool first;         /*!< Between the player and the first */
    bool last;          /*!< Between the player and the last one */
} difference_between_player;


void createPreferencesFolder(char *home_path);
bool createFileToolbarButtonPreferences(char *home_path, toolbar_button_preferences_struct toolbar);
bool readFileToolbarButtonPreferences(char *home_path, toolbar_button_preferences_struct *toolbar);
bool differentsToolbarButtonPreferencesStruct(toolbar_button_preferences_struct toolbar1, toolbar_button_preferences_struct toolbar2);
bool createFileMainWidowSize(char *home_path, main_window_size size);
bool readFileMainWidowSize(char *home_path, main_window_size *size);
bool createFileSystemPath();
bool readFileSystemPath(char *file_name);
bool readSystemPath(char *file_name);
bool changeSystemPath(char *new_path);
bool createFileDifferenceBetweenPlayer(char *home_path, difference_between_player diff);
bool readFileDifferenceBetweenPlayer(char *home_path, difference_between_player *diff);
bool createFilePdfPreferences(char *home_path, export_pdf_preferences *ptr_pref);
bool readFilePdfPreferences(char *home_path, export_pdf_preferences *ptr_pref);
bool differentsTExportPdfPreferencesStruct(export_pdf_preferences pdf_1, export_pdf_preferences pdf_2);

#endif
