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

