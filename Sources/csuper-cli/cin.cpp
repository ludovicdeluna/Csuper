/*!
 * \file    Cin.cpp
 * \author  Remi BERTHO
 * \date    18/07/15
 * \version 4.3.0
 */

/*
 * Cin.cpp
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
 * aint with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

 #include "cin.h"
 #include <iostream>

 using namespace std;
 using namespace Glib;

ustring Cin::getUstring()
{
    Glib::ustring res;
    cin >> res;
    clean();
    return res;
}

int Cin::getInt()
{
    int res;
    cin >> res;
    clean();
    return res;
}

unsigned int Cin::getUnsignedInt()
{
    unsigned int res;
    cin >> res;
    clean();
    return res;
}

double Cin::getDouble()
{
    double res;
    cin >> res;
    clean();
    return res;
}

char Cin::getChar()
{
    char res;
    res = getchar();
    if (res != '\n')
        clean();
    return res;
}

void Cin::clean()
{
    char c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
    if (cin.fail())
    {
        cin.ignore(numeric_limits<streamsize>::max());
        cin.clear();
    }
}
