#include <iostream>

#include "triangles.hpp"

int main()
{
    using namespace Geom;
    Vector3D vec1{1, 2, 3};
    Vector3D vec2{-1, -2, -3};

    std::cout << "Vec1: " << vec1.x() << vec1.y() << vec1.z() << std::endl;
    std::cout << "Vec2: " << vec2.x() << vec2.y() << vec2.z() << std::endl;

    Vector3D vec3 = vec1 + vec2;

    std::cout << "Vec3: " << vec3.x() << vec3.y() << vec3.z() << std::endl;

    return 0;
}