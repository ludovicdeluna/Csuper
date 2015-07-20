/*!
 * \file    cin.cpp
 * \author  Remi BERTHO
 * \date    18/07/15
 * \version 4.3.0
 */

/*
 * cin.cpp
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
 #include <glibmm/i18n.h>
 #include "../libcsuper/libcsuper.h"

 using namespace std;
 using namespace Glib;
 using namespace csuper;

ustring Cin::getUstring()
{
    ustring res;
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
    ustring tmp;
    cin >> tmp;
    clean();
    return ustringToDouble(tmp);
}

char Cin::getChar()
{
    char res;
    res = getchar();
    if (res != '\n')
        clean();
    return res;
}

bool Cin::getYes()
{
    char tmp = getChar();
    //TRANSLATORS:First letter of YES
    ustring yes_upper(_("Y"));
    //TRANSLATORS:First letter of yes
    ustring yes_lower(_("y"));
    return ((ustring(1,tmp) == yes_upper) || (ustring(1,tmp) == yes_lower));
}

bool Cin::getNo()
{
    char tmp = getChar();
    //TRANSLATORS:First letter of NO
    ustring yes_upper(_("N"));
    //TRANSLATORS:First letter of no
    ustring yes_lower(_("n"));
    return ((ustring(1,tmp) == yes_upper) || (ustring(1,tmp) == yes_lower));
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
