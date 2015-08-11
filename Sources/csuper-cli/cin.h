/*!
 * \file    cin.h
 * \author  Remi BERTHO
 * \date    18/07/15
 * \version 4.3.0
 */

/*
 * cin.h
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

#ifndef CIN_H_INCLUDED
#define CIN_H_INCLUDED

#include "share.h"
#include <glibmm.h>

/*! \class Cin
*   \brief This class is for Cin
*/
class Cin
{
public:
    /*!
     *  Do a keyboarding of a string
     * \return the ustring
     */
    static Glib::ustring getUstring();

    /*!
     *  Do a keyboarding of a int
     * \return the int
     */
    static int getInt();

    /*!
     *  Do a keyboarding of a unsigned int
     * \return the unsigned int
     */
    static unsigned int getUnsignedInt();

    /*!
     *  Do a keyboarding of a double
     * \return the double
     */
    static double getDouble();

    /*!
     *  Do a keyboarding of a char
     * \return the char
     */
    static char getChar();

    /*!
     *  Do a keyboarding to see if the user type yes
     * \return true if the type 'Y' or 'y', false otherwise
     */
    static bool getYes();

    /*!
     *  Do a keyboarding to see if the user type no
     * \return true if the type 'N' or 'n', false otherwise
     */
    static bool getNo();

private:
    /*!
     *  Clean the buffer of stdin.
     */
    static void clean();
};



#endif // CIN_H_INCLUDED
