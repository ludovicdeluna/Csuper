/*!
 * \file    interface.h
 * \brief   Graphical interface
 * \author  Remi BERTHO
 * \date    17/06/14
 * \version 4.0.0
 */

 /*
 * interface.h
 *
 * Copyright 2014 Remi BERTHO <remi.bertho@gmail.com>
 *
 * This file is part of Csuper-cli.
 *
 * Csuper is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Csuper is distributed in the hope that it will be useful,
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

#ifndef INTERFACE_INCLUDED
#define INTERFACE_INCLUDED

#include <dirent.h>

#include "menu.h"
#include "display.h"
#include "main.h"
#include "csuper.h"

typedef enum {newMatch=1 , loadMatch=2 , printFile=3 , deleteFiles=4 , listFile=5 , pref=6, quit=7 , easterEggs = 42} MainMenu;
#ifndef PORTABLE
typedef enum {newPath=1, readPath=2 , newGameConf=3, removeGameConf=4, printListGameConf=5 , printGameConf=6, exportGameConf=7, importGameConf=8 ,backMainMenu=9 , easterEggs2 = 42} PreferencesMenu;
#else
typedef enum {newGameConf=1,removeGameConf=2,printListGameConf=3 , printGameConf=4,exportGameConf=5, importGameConf=6  ,backMainMenu=7, easterEggs2 = 42} PreferencesMenu;
#endif


void displayFile();
void deleteCsuFileNom();
void listCsuFiles();
void play(csuStruct *ptr_csu_struct, char *file_name);
void newGame();
void loadGame();
void mainMenu();
void preferencesMenu();
void changeFilePath();
void readFilePath();
void loadGameLocale(char *file_name);
void displayFileLocale(char *file_name);
void newGameConfig();
void removeGameConfig();
void printListGameConfig();
void printGameConfigFile();
void exportListGameConfig();
void importListGameConfig();

#endif
