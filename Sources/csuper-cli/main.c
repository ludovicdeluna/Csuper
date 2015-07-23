/*!
 * \file    main.c
 * \brief   Begin csuper
 * \author  Remi BERTHO
 * \date    17/04/14
 * \version 2.2.0
 */

/*
 * main.c
 *
 * Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
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
 * aint with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include "main.h"

/*!
 * \fn int main(int argc, char *argv[])
 *  Begin csuper.
 * \param[in] argc the number of argument.
 * \param[in] argv the array of argument.
 * \return EXIT_SUCCESS if everything is OK
 */
int main(int argc, char *argv[])
{
    main_argument_function function;
    int file_place;
    int new_argc=argc;

    setlocale(LC_ALL,"");
    bindtextdomain("csuper-cli","Locales");
    textdomain("csuper-cli");

    #ifdef PORTABLE
    printLicense();
    systemPause();
    #endif

    // Delete the empty arguments
    while (new_argc>0 && strcmp(argv[new_argc-1],"") == 0)
        new_argc--;

    if (new_argc >= 2)
    {
        searchArgument(new_argc,argv,&function,&file_place);
        switch (function)
        {
            case read_file    :   displayFileLocale(argv[file_place]);
                                        break;
            case open_file  :   loadGameLocale(argv[file_place]);
                                        break;
            case export_to_pdf  :   exportToPdfLocale(argv[file_place],argv[file_place+1]);
                                        break;
            case export_to_csv  :   exportToCsvLocale(argv[file_place],argv[file_place+1]);
                                        break;
            case export_to_gnuplot  :   exportToGnuplotLocale(argv[file_place],argv[file_place+1]);
                                        break;
            case export_to_m  :   exportToMLocale(argv[file_place],argv[file_place+1]);
                                        break;
            case help               :   systemPause();
                                        break;
        }
    }
    else
        mainMenu();
    return EXIT_SUCCESS;
}

