/*!
 * \file    main.h
 * \brief   Main
 * \author  Remi BERTHO
 * \date    02/05/14
 * \version 3.0.0
 */

 /*
 * main.h
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

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "csuper-gui.h"
#include "main_menu.h"
#include "main_window.h"
#include "preferences.h"
#include "new_file_assistant.h"
#include "utils.h"

int main (int   argc, char *argv[]);
void openFileWithMainArgument(globalData *data,int argc, char *argv[]);

#endif // MAIN_H_INCLUDED
