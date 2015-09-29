#include <rhea/simplex_solver.hpp>
#include <rhea/iostream.hpp>

using namespace rhea;

int main( int argc, const char* argv[] )
{
    variable t1(0), t2(10), min1(5), max1(15), nom1(10);
    simplex_solver solver;
    //solver.set_autosolve(false);

    solver.add_stays({min1,max1}, strength::required());
    solver.add_stays({t1,t2}, strength::medium());

    solver.add_constraints(
    {
                    min1 >= 0,
                    nom1 >= min1,
                    max1 >= nom1,
                    t2 == nom1 + t1/*,
                    max1 >= t2 - t1,
                    min1 <= t2 - t1*/
    });


    solver.suggest(t2, 19);

    std::cout << t1 << " " << min1 << " " << nom1 << " " << t2 << " " << max1 << std::endl;

    return 0;
}
