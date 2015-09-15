#include <kiwi/kiwi.h>
#include <stdio.h>
/*
 * c++ version of Chris Colbert example here
 * https://groups.google.com/d/msg/enaml/DVaSWDGfLkc/dutzhOB7ALsJ
 * */

using namespace kiwi;

int main( int argc, const char* argv[] )
{
    // 0|-------------| x1 ----- xm ----- x2 |-----------------------|100

    /*
    x1 = kiwi.Variable('x1')
    x2 = kiwi.Variable('x2')
    xm = kiwi.Variable('xm')
    */

    Variable x1("x1");
    Variable x2("x2");
    Variable xm("xm");

    /*
    constraints = [
        x1 >= 0,
        x2 <= 100,
        x2 >= x1 + 10,
        xm == (x1 + x2) / 2,
    ]  # these all have strength 'required'
    */
    Constraint constraints[] = {
        Constraint {x1 >= 0},
        Constraint {x2 <= 100},
        Constraint {x2 >= x1 + 10},
        Constraint {xm == (x1 + x2) / 2}
    };

 // solver = kiwi.Solver()
    Solver solver;

    /*
    for cn in constraints:
        solver.addConstraint(cn)
    */
    for(auto& constraint : constraints)
    {
        solver.addConstraint(constraint);
    }

 // solver.addEditVariable(xm, 'strong')
    solver.addEditVariable(xm, strength::strong);

    /*
        for val in (-20, 0, 20, 50, 80, 100, 140):
            solver.suggestValue(xm, val)
            solver.updateVariables()
            print 'x1:', x1.value()
            print 'x2:', x2.value()
            print 'xm:', xm.value()
            print 'suggested xm:', val
            print

    */
    int values[] = {-20, 0, 20, 50, 80, 100, 140};
    for(auto value : values)
    {
        solver.suggestValue(xm, value);
        solver.updateVariables();
        std::cout << "x1:" << x1.value() << "\n";
        std::cout << "x2:" << x2.value() << "\n";
        std::cout << "xm:" << xm.value() << "\n";
        std::cout << "suggested xm:" << value << "\n";
        std::cout << "\n";
    }

    return 0;
}
/*
SHOULD PRINT:
x1: 0.0
x2: 10.0
xm: 5.0
suggested xm: -20


x1: 0.0
x2: 10.0
xm: 5.0
suggested xm: 0


x1: 15.0
x2: 25.0
xm: 20.0
suggested xm: 20


x1: 45.0
x2: 55.0
xm: 50.0
suggested xm: 50


x1: 75.0
x2: 85.0
xm: 80.0
suggested xm: 80


x1: 90.0
x2: 100.0
xm: 95.0
suggested xm: 100


x1: 90.0
x2: 100.0
xm: 95.0
suggested xm: 140
*/
