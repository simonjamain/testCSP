/*
    quadrilaterals example (http://www.badros.com/greg/cassowary/js/quaddemo.html) implemented with rhea
    source code from rhea doc : http://rhea.readthedocs.org/en/latest/examples.html
*/

#include <rhea/simplex_solver.hpp>
#include <rhea/iostream.hpp>


rhea::simplex_solver solver;

struct point
{
    rhea::variable x, y;
};

namespace std
{
ostream& operator<< (ostream& in, const point& p)
{
    return in << "(" << p.x << ", " << p.y << ")";
}
}


int main( int argc, const char* argv[] )
{
    auto p = std::vector<point>{{10, 10}, {10, 200}, {200, 200}, {200, 10}};
    auto m = std::vector<point>(4);

    for (auto& i : p)
        solver.add_stays({i.x, i.y});

    for (auto i = 0; i < 4; ++i)
        solver.add_constraints({
                                   m[i].x == p[i].x / 2 + p[i + 1 % 4].x / 2,
                                   m[i].y == p[i].y / 2 + p[i + 1 % 4].y / 2
                               });

    solver.add_constraints({
                               p[0].x + 20 <= p[2].x,
                               p[0].x + 20 <= p[3].x,

                               p[1].x + 20 <= p[2].x,
                               p[1].x + 20 <= p[3].x,

                               p[0].y + 20 <= p[1].y,
                               p[0].y + 20 <= p[1].y,

                               p[3].y + 20 <= p[1].y,
                               p[3].y + 20 <= p[1].y
                           });

    for (auto& i : p)
        solver.add_constraints({
                                   i.x >= 0,
                                   i.y >= 0,
                                   i.x <= 500,
                                   i.y <= 500
                               });

    for (auto& i : m)
        std::cout << i << std::endl;

    solver.suggest({{p[2].x, 300}, {p[2].y, 400}});

    for (auto& i : m)
        std::cout << i << std::endl;

    return 0;
}
