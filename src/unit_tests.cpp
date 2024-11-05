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
    EXPECT_ANY_THROW((Point3D{std::numeric_limits<double>::quiet_NaN(), 0, 0}));
    
    EXPECT_ANY_THROW((Point3D{0, std::numeric_limits<double>::quiet_NaN(), 0}));
    
    EXPECT_ANY_THROW((Point3D{0, 0, std::numeric_limits<double>::quiet_NaN()}));
}

TEST(Point3D, Equality)
{
    Point3D p{1, 2, 3};
    Point3D q{1.0, 1.0 + 1.0, 2.0 + 1.0};

    EXPECT_TRUE(p == q);
}

TEST(Vector3D, CtorOk)
{
    double x = 1, y = 2, z = 3;
    Vector3D v1{x, y, z};

    EXPECT_DOUBLE_EQ(x, v1.x());
    EXPECT_DOUBLE_EQ(y, v1.y());
    EXPECT_DOUBLE_EQ(z, v1.z());

    Point3D p1{0, 0, 0};
    Point3D p2{x, y, z};
    Vector3D v2{p1, p2};

    EXPECT_DOUBLE_EQ(x, v2.x());
    EXPECT_DOUBLE_EQ(y, v2.y());
    EXPECT_DOUBLE_EQ(z, v2.z());    
}

TEST(Vector3D, CtorNaN)
{
    EXPECT_ANY_THROW((Vector3D{std::numeric_limits<double>::quiet_NaN(), 0, 0}));
    
    EXPECT_ANY_THROW((Vector3D{0, std::numeric_limits<double>::quiet_NaN(), 0})); 
    
    EXPECT_ANY_THROW((Vector3D{0, 0, std::numeric_limits<double>::quiet_NaN()}));
}

TEST(Vector3D, Norm)
{
    Vector3D v0 = Vector3D{0, 0, 0}.norm_vec();
    EXPECT_TRUE(eq(v0.x(), 0));
    EXPECT_TRUE(eq(v0.y(), 0));
    EXPECT_TRUE(eq(v0.z(), 0));

    Vector3D v1 = Vector3D{42, 0, 0}.norm_vec();
    EXPECT_TRUE(eq(v1.x(), 1));
    EXPECT_TRUE(eq(v1.y(), 0));
    EXPECT_TRUE(eq(v1.z(), 0));

    Vector3D v2 = Vector3D{0, 42, 0}.norm_vec();
    EXPECT_TRUE(eq(v2.x(), 0));
    EXPECT_TRUE(eq(v2.y(), 1));
    EXPECT_TRUE(eq(v2.z(), 0));

    Vector3D v3 = Vector3D{0, 0, 42}.norm_vec();
    EXPECT_TRUE(eq(v3.x(), 0));
    EXPECT_TRUE(eq(v3.y(), 0));
    EXPECT_TRUE(eq(v3.z(), 1));
}

TEST(Vector3D, Equality)
{
    Vector3D p{1, 2, 3};
    Vector3D q{1.0, 1.0 + 1.0, 2.0 + 1.0};

    EXPECT_TRUE(p == q);
}

TEST(Vector3D, CrossProd)
{
    Vector3D res = cross_prod(Vector3D{1, 0, 0}, Vector3D{0, 1, 0});
    EXPECT_TRUE((res == Vector3D{0, 0, 1}));
}

TEST(Plane, CtorOk)
{
    Plane p{{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};
    EXPECT_TRUE((p.n_vec() == Vector3D{0, 0, 1}));
}

TEST(Plane, CtorDegenerate)
{
    // didn't manage to make it work...
    //EXPECT_ANY_THROW((Plane p{{0,0,0}, {0,0,0}, {1,1,1}}));

    try {Plane p{{0,0,0}, {0,0,0}, {1,1,1}};}
    catch(...) {SUCCEED();}

    FAIL();
}

TEST(Plane, NormalVecHasUnitLen)
{
    Plane p{Vector3D{1.23, -4.56, 7.89}, Point3D{0, 0, 0}};
    EXPECT_TRUE(p.n_vec().len() == 1);

    Plane q{Point3D{1234.435, 324.456, -45.245}, 
            Point3D{24.235, -45.535, 4353.45}, 
            Point3D{-252.435,233.43,454}
            };
    EXPECT_TRUE(p.n_vec().len() == 1);
}

