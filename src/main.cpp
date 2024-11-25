#include <iostream>

#include "triangles.hpp"

int main()
{
    using namespace Geom;

    int i = 0;

    Triangle3D t{{0,0,0}, {0,1,0}, {0,0,1}};

    

    std::cout << std::boolalpha;
    std::cout << t.intersects_LineSeg3D({Point3D{1,0.5,0.5},Point3D{-1,0.5,0.5}}) << std::endl;

    return 0;
}