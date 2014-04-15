/*!
 * \file    main_argument.c
 * \brief   Lancement du programme
 * \author  Remi BERTHO
 * \date    21/03/14
 * \version 2.1.0
 */

/*
 * main_argument.c
 *
 * Copyright 2014 Remi BERTHO <remi.bertho@gmail.com>
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
 * aint with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include "main_argument.h"

/*!
 * \fn int searchArgument(int argc, char *argv[], int *fonction, int *file_place)
 *  Lance le programme
 * \param[in] argc le nombre d 'argument
 * \param[in] argv le tableau des arguments
 * \param[in] fonction entier determinant quelle fonction lancer
 * \param[in] file_place entier donnant l'emplacment du fichier a ouvrir
 * \return TRUE si la fonction a trouve un argument, FALSE sinon
 */
int searchArgument(int argc, char *argv[], int *fonction, int *file_place)
{
    int i;

    for (i=1 ; i< argc ; i++)
    {
        if (strcmp(argv[i],STRING_READ_FILE)==0 || strcmp(argv[i],STRING_READ_FILE_RED)==0)
        {
            *fonction = READ_FILE;
            *file_place = 1+i;
            break;
        }
        if (strcmp(argv[i],STRING_OPEN_FILE)==0 || strcmp(argv[i],STRING_OPEN_FILE_RED)==0)
        {
            *fonction = OPEN_FILE;
            *file_place = 1+i;
            break;
        }
        if (strcmp(argv[i],STRING_HELP)==0 || strcmp(argv[i],STRING_HELP_RED)==0)
        {
            displayHelp();
            *fonction=HELP;
            *file_place = i;
            break;
        }
    }

    if (i == argc || *file_place >= argc)
        return FALSE;
    else
        return TRUE;
}

void displayHelp()
{
    libcsuper_initialize();

    printf(_("\nCsuper - Universal points counter allowing reflexion exemption\nHere is the syntax to use it.\n"));
    printf(_("\t- Do not use argument to launch the main menu.\n"));
    printf(_("\t- Use the argument '%s' or '%s' followed by the file name to launch directly the program on this file.\n"),STRING_OPEN_FILE,STRING_OPEN_FILE_RED);
    printf(_("\t- Use the argument '%s' or '%s' followed by the file name to display directly the content of the file.\n"),STRING_READ_FILE,STRING_READ_FILE_RED);
}
