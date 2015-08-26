/*!
 * \file    calculator.h
 * \brief   Header for the essential function of libcsuper
 * \author  Remi BERTHO
 * \date    26/08/15
 * \version 4.3.0
 */

/*
* calculator.h
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

#ifndef CALCULATOR_H_INCLUDED
#define CALCULATOR_H_INCLUDED

#include "muParser.h"
#include "share.h"


namespace csuper
{
    /*! \class Calculator
    *   \brief This class represent a calculator
    */
    class Calculator
    {
    private:
        mu::Parser parser_; /*!< The parser */

    public:
        //
        // Constructor
        //
        /*!
         *  \brief Default constructor
         */
        Calculator();


        /*!
         *  \brief Constructor with the expression
         *  \param s the expression
         */
        Calculator(const std::string& s);


        //
        // Function
        //
        /*!
         *  \brief Change the expression
         *  \param s the expression
         */
        inline Calculator &changeExpression(const std::string& s)
        {
            parser_.SetExpr(s);
            return *this;
        }

        /*!
         *  \brief Calculate the expression
         *  \return the result of the expression
         *  \exception csuper::CalculatorError if bad expression
         */
        double calculate() const;

        //
        // Operator
        //
        /*!
         *  \brief Operator <<
         *  \param os the ostream
         *  \param calc the calculator
         *  \return the ostream
         */
        friend std::ostream& operator<<(std::ostream& os, const Calculator& calc);

        //
        // Static function
        //
        /*!
         *  \brief Calculate an expression
         *  \param s the expression
         *  \return the result of the expression
         *  \exception csuper::CalculatorError if bad expression
         */
        static double calculate(const std::string& s);
    };
}




#endif // CALCULATOR_H_INCLUDED
