/*!
 * \file    main_argument.c
 * \brief   Begin csuper
 * \author  Remi BERTHO
 * \date    16/04/14
 * \version 2.2.0
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
 * \fn int searchArgument(int argc, char *argv[], int *function, int *file_place)
 *  Search the argument passed to the main function
 * \param[in] argc the number of argument
 * \param[in] argv the array of argument
 * \param[in] function integer which determine which function run
 * \param[in] file_place integer which determine the index of the filename
 * \return MY_TRUE if the function founded an argument, MY_FALSE otherwise
 */
int searchArgument(int argc, char *argv[], int *function, int *file_place)
{
    int i;

    for (i=1 ; i< argc ; i++)
    {
        if (strcmp(argv[i],STRING_READ_FILE)==0 || strcmp(argv[i],STRING_READ_FILE_RED)==0)
        {
            *function = READ_FILE;
            *file_place = 1+i;
            break;
        }
        if (strcmp(argv[i],STRING_OPEN_FILE)==0 || strcmp(argv[i],STRING_OPEN_FILE_RED)==0)
        {
            *function = OPEN_FILE;
            *file_place = 1+i;
            break;
        }
        if (strcmp(argv[i],STRING_HELP)==0 || strcmp(argv[i],STRING_HELP_RED)==0)
        {
            displayHelp();
            *function=HELP;
            *file_place = i;
            break;
        }
    }

    if (i == argc || *file_place >= argc)
        return MY_FALSE;
    else
        return MY_TRUE;
}


/*!
 * \fn void displayHelp()
 *  Display the help
 */
void displayHelp()
{
    libcsuper_initialize();

    printf(_("\nCsuper - Universal points counter allowing reflexion exemption\nHere is the syntax to use it.\n"));
    printf(_("\t- Do not use argument to launch the main menu.\n"));
    printf(_("\t- Use the argument '%s' or '%s' followed by the file name to launch directly the program on this file.\n"),STRING_OPEN_FILE,STRING_OPEN_FILE_RED);
    printf(_("\t- Use the argument '%s' or '%s' followed by the file name to display directly the content of the file.\n"),STRING_READ_FILE,STRING_READ_FILE_RED);
}
