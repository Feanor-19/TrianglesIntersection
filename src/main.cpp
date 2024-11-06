#include <iostream>

#include "triangles.hpp"

int main()
{
    using namespace Geom;

    int i = 0;

    Plane p{Vector3D{1.23, -4.56, 7.89}, Point3D{0, 0, 0}};
    Plane q{Point3D{1234.435, 324.456, -45.245}, 
            Point3D{24.235, -45.535, 4353.45}, 
            Point3D{-252.435,233.43,454}
            };

    std::cout << p.n_vec().len() << std::endl;
    std::cout << q.n_vec().len() << std::endl;

    return 0;
}