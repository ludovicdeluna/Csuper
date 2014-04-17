/*!
 * \file    display.h
 * \brief   Display the games
 * \author  Remi BERTHO
 * \date    17/04/14
 * \version 2.2.0
 */

 /*
 * display.h
 *
 * Copyright 2014 Remi BERTHO <remi.bertho@gmail.com>
 *
 * This file is part of Csuper.
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

#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED


#include <math.h>
#include <string.h>
#include "main.h"
#include "csuper.h"


void printNames(csuStruct *ptr_csu_struct, int *ptr_size_ligne);
void printLigne(int size_ligne);
void printTotalPoints(csuStruct *ptr_csu_struct);
void printDistributor(csuStruct *ptr_csu_struct);
void printHeader(csuStruct *ptr_csu_struct);
void printAllPoints(csuStruct *ptr_csu_struct);
void printRanking(csuStruct *ptr_csu_struct);
void printPoints(csuStruct *ptr_csu_struct);
void printCsuStruct(csuStruct *ptr_csu_struct);
void printGameOver(csuStruct *ptr_csu_struct);
void printStringThreeTabs(char *string);
void printLicense();
void printGameConfig(game_config config);

#endif
