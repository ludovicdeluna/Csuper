/*!
 * \file    calculator.cpp
 * \brief   Header for the essential function of libcsuper
 * \author  Remi BERTHO
 * \date    26/08/15
 * \version 4.3.0
 */

/*
* calculator.cpp
*
* Copyright 2014-2015
 Remi BERTHO <remi.bertho@openmailbox.org>
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
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
* MA 02110-1301, USA.
*
*
*/

#include "calculator.h"
#include "config.h"
#include "exceptions.h"
#include <glibmm.h>

namespace csuper
{
    using namespace mu;
    using namespace std;
    using namespace Glib;

    Calculator::Calculator() : parser_()
    {
        parser_.SetArgSep(';');
    }

    Calculator::Calculator(const string& s) : parser_()
    {
        parser_.SetArgSep(';');
        parser_.SetExpr(s);
    }


    double Calculator::calculate(const string &s)
    {
        Calculator calc(s);

        return calc.calculate();
    }


    ostream& operator<<(ostream& os, const Calculator& calc)
    {
        os << calc.parser_.GetExpr() << "= " << calc.calculate() << endl;
        return os;
    }


    double Calculator::calculate() const
    {
        try
        {
            return parser_.Eval();
        }
        catch (Parser::exception_type& e)
        {
            cerr << e.GetMsg() << endl;
            throw CalculatorError(ustring::compose(_("Error when calculating %1"),e.GetExpr()));
        }
    }
}

