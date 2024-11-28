#include <iostream>

#include "triangles.hpp"

int main()
{
    using namespace Geom;

    int i = 0;

    Triangle3D t0{{1.23, -4.56, 7.89}, {4.5, 45.4, -4.56}, {-7.34, 5.345, 9.386}};

    std::cout << std::boolalpha;
    std::cout << t0.intersects_Triangle3D(t0) << std::endl;

    return 0;
}