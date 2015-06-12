#include "calculator.h"
#include "config.h"

namespace csuper
{
    using namespace mu;
    using namespace std;

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
}

