/*!
 * \file    share.cpp
 * \author  Remi BERTHO
 * \date    10/07/15
 * \version 4.3.0
 */

/*
 * share.cpp
 *
 * Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
 *
 * This file is part of Csuper-cli.
 *
 * Csuper-cli is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Csuper-cli is distributed in the hope that it will be useful,
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

#include "share.h"

#include <cstdio>
#include <iostream>
#include <glibmm.h>
#include <glibmm/i18n.h>
#include "cin.h"

#ifdef G_OS_UNIX
#include <unistd.h>
#include <term.h>
#endif // G_OS_UNIX

#ifdef G_OS_WIN32
#include <windows.h>
#endif // G_OS_WIN32

using namespace std;
using namespace Glib;


void systemPause()
{
    cout << ustring(_("Press ENTER to continue"));
    Cin::getChar();
}


void clearScreen()
{
    #ifdef G_OS_UNIX
    if (!cur_term)
    {
        int result;
        setupterm( NULL, STDOUT_FILENO, &result);
        if (result <= 0)
            return;
    }
    putp(tigetstr((char*)"clear"));
    #else
    #ifdef G_OS_WIN32
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE)
        return;

    // Get the number of cells in the current buffer
    if (!GetConsoleScreenBufferInfo( hStdOut, &csbi ))
        return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    // Fill the entire buffer with spaces
    if (!FillConsoleOutputCharacter(hStdOut,(TCHAR) ' ',cellCount,homeCoords,&count))
        return;

    // Fill the entire buffer with the current colors and attributes
    if (!FillConsoleOutputAttribute(hStdOut,csbi.wAttributes,cellCount,homeCoords,&count))
        return;

    // Move the cursor home
    SetConsoleCursorPosition( hStdOut, homeCoords );
    #else
    cerr << ustring(_("Your environment cannot permit to clear the screen.")) << endl;
    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    #endif // G_OS_WIN32
    #endif // G_OS_UNIX
}
