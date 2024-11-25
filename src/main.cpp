#include <iostream>

#include "triangles.hpp"

int main()
{
    using namespace Geom;

    int i = 0;

    Triangle3D t{{0,0,0}, {0,1,0}, {0,0,1}};


    std::cout << std::boolalpha;
    std::cout << t.has_point({0, 0.8, 0.2}) << std::endl;

    return 0;
}