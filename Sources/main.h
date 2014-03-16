/*!
 * \file    main.h
 * \brief   Lancement du programme
 * \author  Remi BERTHO
 * \date    09/03/14
 * \version 2.1.0
 */

/*
 * main.h
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
 * aint with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "interface.h"

/*!
 * \def LECTURE_FICHIER
 * Definit l'appel a la lecture du fichier a "--read"
 */
#define LECTURE_FICHIER "--read"

/*!
 * \def OUVERTURE_FICHIER
 * Definit l'appel a l'ouverture du fichier a "--open"
 */
#define OUVERTURE_FICHIER "--open"

int main(int argc, char *argv[]);

#endif
