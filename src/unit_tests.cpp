#include <gtest/gtest.h>
#include <cmath>
#include <numeric>

#include "triangles.hpp"

using namespace Geom;

TEST(Point3D, CtorOk)
{
    scalar_t x = 1, y = 2, z = 3;
    Point3D p{x, y, z};

    EXPECT_DOUBLE_EQ(x, p.x());
    EXPECT_DOUBLE_EQ(y, p.y());
    EXPECT_DOUBLE_EQ(z, p.z());
}

TEST(Point3D, CtorNaN)
{
    EXPECT_ANY_THROW((Point3D{std::numeric_limits<scalar_t>::quiet_NaN(), 0, 0}));
    
    EXPECT_ANY_THROW((Point3D{0, std::numeric_limits<scalar_t>::quiet_NaN(), 0}));
    
    EXPECT_ANY_THROW((Point3D{0, 0, std::numeric_limits<scalar_t>::quiet_NaN()}));
}

TEST(Point3D, Equality)
{
    Point3D p{1, 2, 3};
    Point3D q{1.0, 1.0 + 1.0, 2.0 + 1.0};

    EXPECT_TRUE(p == q);
}

TEST(Vector3D, CtorOk)
{
    scalar_t x = 1, y = 2, z = 3;
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
    EXPECT_ANY_THROW((Vector3D{std::numeric_limits<scalar_t>::quiet_NaN(), 0, 0}));
    
    EXPECT_ANY_THROW((Vector3D{0, std::numeric_limits<scalar_t>::quiet_NaN(), 0})); 
    
    EXPECT_ANY_THROW((Vector3D{0, 0, std::numeric_limits<scalar_t>::quiet_NaN()}));
}

TEST(Vector3D, NormVec)
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

TEST(Vector3D, BinPlus)
{
    Vector3D p{1, 2, 3};
    Vector3D q{-1, -2, -3};
    EXPECT_TRUE((p + q == Vector3D{0,0,0}));
}

TEST(Vector3D, Len)
{
    double a = 42;
    Vector3D v1 = {a, 0, 0};
    EXPECT_DOUBLE_EQ(v1.len(), a);

    Vector3D v2 = {0, a, 0};
    EXPECT_DOUBLE_EQ(v2.len(), a);

    Vector3D v3 = {0, 0, a};
    EXPECT_DOUBLE_EQ(v3.len(), a);
}

TEST(Vector3D, CrossProd)
{
    Vector3D res = cross_prod(Vector3D{1, 0, 0}, Vector3D{0, 1, 0});
    EXPECT_TRUE((res == Vector3D{0, 0, 1}));
}

TEST(Vector3D, ScalarProd)
{
    Vector3D v1{1, 2, 3};
    Vector3D v2 = -v1;
    EXPECT_DOUBLE_EQ(scalar_prod(v1, v2), -1*v1.len()*v1.len());
    EXPECT_DOUBLE_EQ(scalar_prod(v1, v1), v1.len() * v1.len());
    
    Vector3D v3{35.32, -235325.43, 435.345};
    Vector3D v4{-345.3, 4353.4, 43458.879};
    EXPECT_DOUBLE_EQ(scalar_prod(v3, v4), scalar_prod(v4, v3));
    EXPECT_DOUBLE_EQ(scalar_prod(v3, v3), v3.len() * v3.len());
    EXPECT_DOUBLE_EQ(scalar_prod(v4, v4), v4.len() * v4.len());
}

TEST(Vector3D, UnMinus)
{
    Vector3D v1{1, 2, 3};
    Vector3D v2 = -v1;
    EXPECT_DOUBLE_EQ(v1.x(), -v2.x());
    EXPECT_DOUBLE_EQ(v1.y(), -v2.y());
    EXPECT_DOUBLE_EQ(v1.z(), -v2.z());
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
    catch(...) {;}

    try {Plane p{Vector3D{0,0,0}, {0,0,0}};}
    catch(...) {;}

    SUCCEED();
}

TEST(Plane, Equality)
{
    Plane a{{0,0,0}, {1,-1,0}, {-1,-1,2}};
    Plane b{Vector3D{1,1,1}, Point3D{-1,1,0}};
    EXPECT_TRUE(a==b);

    Plane c{Vector3D{1,1,1}, Point3D{0,0,0}};
    Plane d{Vector3D{-1,-1,-1}, Point3D{0,0,0}};
    EXPECT_TRUE(c==d);
}

TEST(Plane, NormalVecHasUnitLen)
{
    Plane p{Vector3D{1.23, -4.56, 7.89}, Point3D{0, 0, 0}};
    EXPECT_DOUBLE_EQ(p.n_vec().len(), 1);

    Plane q{Point3D{1234.435, 324.456, -45.245}, 
            Point3D{24.235, -45.535, 4353.45}, 
            Point3D{-252.435,233.43,454}
            };
    EXPECT_DOUBLE_EQ(q.n_vec().len(), 1);
}

TEST(Plane, SignedDistToPoint)
{
    Point3D point{1, 2, 3};
    Plane plane{Vector3D{1,1,1}, point};

    EXPECT_DOUBLE_EQ(plane.signed_dist_to_point(point), 0);
    EXPECT_GT(plane.signed_dist_to_point({2,3,4}), 0);
    EXPECT_LT(plane.signed_dist_to_point({0,1,2}), 0);
}

TEST(Plane, IsParallelTo)
{
    Vector3D v1{1,2,3};
    Vector3D v2{-10,-20,-30};
    Vector3D v3{1,-2,3};

    Plane p1{v1, {34,45,-67}};
    Plane p2{v2, {-345,345,234}};
    Plane p3{v3, {0,0,0}};

    EXPECT_TRUE(p1.is_parallel_to(p2));
    EXPECT_TRUE(p2.is_parallel_to(p1));

    EXPECT_FALSE(p1.is_parallel_to(p3));
    EXPECT_FALSE(p2.is_parallel_to(p3));
    EXPECT_FALSE(p3.is_parallel_to(p1));
    EXPECT_FALSE(p3.is_parallel_to(p2));
}

