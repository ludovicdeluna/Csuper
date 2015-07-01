

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
