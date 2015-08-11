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
 * along with this program; if not, write to the Free Software
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
    double res = 0.0;
    cin >> tmp;
    clean();
    try
    {
        res = Calculator::calculate(tmp);
    }
    catch (Glib::Exception& e)
    {
        cout << e.what() << endl;
    }
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

bool Cin::getYes()
{
    char tmp = getChar();
    //TRANSLATORS:First letter of YES
    const ustring yes_upper(_("Y"));
    //TRANSLATORS:First letter of yes
    const ustring yes_lower(_("y"));
    return ((ustring(1,tmp) == yes_upper) || (ustring(1,tmp) == yes_lower));
}

bool Cin::getNo()
{
    char tmp = getChar();
    //TRANSLATORS:First letter of NO
    const ustring no_upper(_("N"));
    //TRANSLATORS:First letter of no
    const ustring no_lower(_("n"));
    return ((ustring(1,tmp) == no_upper) || (ustring(1,tmp) == no_lower));
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
