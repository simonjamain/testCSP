#include <kiwi/kiwi.h>
#include <stdio.h>

using namespace kiwi;

int main( int argc, const char* argv[] )
{
    Solver solver;

    Variable t1("t1");
    Variable t2("t2");
    Variable min1("min1");
    Variable max1("max1");
    Variable nom1("nom1");

    t1.setValue(0);
    t2.setValue(10);
    min1.setValue(5);
    nom1.setValue(10);
    max1.setValue(20);

    solver.addEditVariable(t1, strength::strong);
    solver.addEditVariable(t2, strength::strong);
    //solver.addEditVariable(min1, strength::required);
    //solver.addEditVariable(max1, strength::required);
    solver.addEditVariable(nom1, strength::medium);

    solver.addConstraint(min1 >= 0);
    solver.addConstraint(min1 <= nom1);
    solver.addConstraint(nom1 <= max1);
    solver.addConstraint(t2 == t1 + nom1);



    solver.dump();

    solver.suggestValue(t2,25);
    solver.updateVariables();

    std::cout << t2.value() << "\n";


    return 0;
}
