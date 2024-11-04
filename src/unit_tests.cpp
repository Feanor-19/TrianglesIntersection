#include <gtest/gtest.h>
#include <cmath>
#include <numeric>

#include "triangles.hpp"

using namespace Geom;

TEST(Point3D, CtorOk)
{
    double x = 1, y = 2, z = 3;
    Point3D p{x, y, z};

    EXPECT_DOUBLE_EQ(x, p.x());
    EXPECT_DOUBLE_EQ(y, p.y());
    EXPECT_DOUBLE_EQ(z, p.z());
}

TEST(Point3D, CtorNaN)
{
    try {Point3D{std::numeric_limits<double>::quiet_NaN(), 0, 0}; }
    catch(...) {};
    
    try {Point3D{0, std::numeric_limits<double>::quiet_NaN(), 0}; }
    catch(...) {};
    
    try {Point3D{0, 0, std::numeric_limits<double>::quiet_NaN()}; }
    catch(...) {};
    
    SUCCEED();
}