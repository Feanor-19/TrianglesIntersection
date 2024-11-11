#include <iostream>

#include "triangles.hpp"

int main()
{
    using namespace Geom;

    int i = 0;

    std::cout << std::boolalpha;
    std::cout << (Line3D{Vector3D{2,2,2}, {1,0,0}} == Line3D{Point3D{1,0,0}, {3,2,2}}) << std::endl;

    return 0;
}