#include <iostream>

#include "triangles.hpp"

int main()
{
    using namespace Geom;

    int i = 0;

    Vector3D v2{-10,-20,-30};
    Plane p2{v2, Point3D{-345,345,234}};

    return 0;
}