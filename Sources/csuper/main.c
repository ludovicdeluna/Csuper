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
    int function;
    int file_place;
    setlocale(LC_ALL,"");
    bindtextdomain("csuper","Locales");
    textdomain("csuper");
    #ifdef PORTABLE
    printLicense();
    systemPause();
    #endif
    if (argc >= 2 && searchArgument(argc,argv,&function,&file_place))
    {
        switch (function)
        {
            case READ_FILE    :   displayFileLocale(argv[file_place]);
                                        break;
            case OPEN_FILE  :   loadGameLocale(argv[file_place]);
                                        break;
            case HELP               :   systemPause();
                                        break;
        }
    }
    else
        mainMenu();
    return EXIT_SUCCESS;
}

