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
    EXPECT_THROW((Point3D{std::numeric_limits<scalar_t>::quiet_NaN(), 0, 0}), NaNCtorParam);
    
    EXPECT_THROW((Point3D{0, std::numeric_limits<scalar_t>::quiet_NaN(), 0}), NaNCtorParam);
    
    EXPECT_THROW((Point3D{0, 0, std::numeric_limits<scalar_t>::quiet_NaN()}), NaNCtorParam);
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
    EXPECT_THROW((Vector3D{std::numeric_limits<scalar_t>::quiet_NaN(), 0, 0}), NaNCtorParam);
    
    EXPECT_THROW((Vector3D{0, std::numeric_limits<scalar_t>::quiet_NaN(), 0}), NaNCtorParam); 
    
    EXPECT_THROW((Vector3D{0, 0, std::numeric_limits<scalar_t>::quiet_NaN()}), NaNCtorParam);
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

TEST(Vector3D, MulScalar)
{
    EXPECT_TRUE((Vector3D{1, 2, 3}*42 == 42*Vector3D{1,2,3}));

    EXPECT_DOUBLE_EQ((Vector3D{1,2,3}*0).len(), 0);

    EXPECT_TRUE((3 * Vector3D{1,2,3} == Vector3D{3,6,9}));
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
    EXPECT_DOUBLE_EQ(dot_prod(v1, v2), -1*v1.len()*v1.len());
    EXPECT_DOUBLE_EQ(dot_prod(v1, v1), v1.len() * v1.len());
    
    Vector3D v3{35.32, -235325.43, 435.345};
    Vector3D v4{-345.3, 4353.4, 43458.879};
    EXPECT_DOUBLE_EQ(dot_prod(v3, v4), dot_prod(v4, v3));
    EXPECT_DOUBLE_EQ(dot_prod(v3, v3), v3.len() * v3.len());
    EXPECT_DOUBLE_EQ(dot_prod(v4, v4), v4.len() * v4.len());
}

TEST(Vector3D, UnMinus)
{
    Vector3D v1{1, 2, 3};
    Vector3D v2 = -v1;
    EXPECT_DOUBLE_EQ(v1.x(), -v2.x());
    EXPECT_DOUBLE_EQ(v1.y(), -v2.y());
    EXPECT_DOUBLE_EQ(v1.z(), -v2.z());
}

TEST(Line3D, CtorOk)
{
    Line3D l1{Point3D{0,0,0}, Point3D{1,1,1}};
    EXPECT_TRUE((l1.dir() == Vector3D{1,1,1}.norm_vec()));
}

TEST(Line3D, CtorDegenerate)
{
    EXPECT_THROW((Line3D{Vector3D{0,0,0}, {0,0,0}}), Line3D::DegeneratedLine);
    EXPECT_THROW((Line3D{Point3D{1,1,1}, Point3D{1,1,1}}), Line3D::DegeneratedLine);
}

TEST(Line3D, NormalVecHasUnitLen)
{
    EXPECT_DOUBLE_EQ((Line3D{Vector3D{123,-456,789}, {0,0,0}}.dir().len()), 1);

    EXPECT_DOUBLE_EQ((Line3D{Point3D{123,-456,789}, {-435,42,0}}.dir().len()), 1);
}

TEST(Line3D, Equality)
{
    EXPECT_TRUE((Line3D{Vector3D{1,1,1}, {0,0,0}} == Line3D{Vector3D{-2,-2,-2}, {3,3,3}}));

    EXPECT_TRUE((Line3D{Vector3D{2,2,2}, {1,0,0}} == Line3D{Point3D{1,0,0}, {3,2,2}}));
}

TEST(Line3D, HasPoint)
{
    Line3D l{Point3D{0,0,0}, Point3D{1,2,3}};

    EXPECT_TRUE(l.has_point({0,0,0}));
    EXPECT_TRUE(l.has_point({1,2,3}));
    EXPECT_TRUE(l.has_point({-1,-2,-3}));
    
    EXPECT_FALSE(l.has_point({1,-2,3}));
}

TEST(Line3D, IsParallelTo)
{
    Vector3D v1{1,2,3};
    Vector3D v2{-10,-20,-30};
    Vector3D v3{1,-2,3};

    Line3D l1{v1, Point3D{34,45,-67}};
    Line3D l2{v2, Point3D{-345,345,234}}; 
    Line3D l3{v3, Point3D{0,0,0}};

    EXPECT_TRUE(l1.is_parallel_to(l2));
    EXPECT_TRUE(l2.is_parallel_to(l1));

    EXPECT_FALSE(l1.is_parallel_to(l3));
    EXPECT_FALSE(l2.is_parallel_to(l3));
    EXPECT_FALSE(l3.is_parallel_to(l1));
    EXPECT_FALSE(l3.is_parallel_to(l2));
}

TEST(Common, IntersectPlanes)
{
    Plane p1 = {{1,1,1}, {0,0,0}};
    Plane p2 = {{1,1,1}, {1,1,1}};
    EXPECT_TRUE(intersect_planes(p1, p2) == std::nullopt);

    p1 = {{13,0,0}, {0,0,0}};
    p2 = {{0,42,0}, {0,0,0}};
    Line3D l = {Vector3D{0,0,19}, Point3D{0,0,0}};
    EXPECT_TRUE(l == *intersect_planes(p1, p2));
}

TEST(LineSeg3D, CtorOk)
{
    LineSeg3D ls = {Point3D{1,2,3}, Point3D{4,5,6}};
    EXPECT_TRUE((ls.vec() == Vector3D{3,3,3}));

    ls = {Point3D{1,2,3}, Vector3D{3,3,3}};
    EXPECT_TRUE((ls.p2() == Point3D{4,5,6}));
}

TEST(LineSeg3D, CtorDegenerate)
{
    Point3D p = {1,1,1};
    Vector3D zero = {0,0,0};
    EXPECT_THROW((LineSeg3D{p, p}), LineSeg3D::DegeneratedLineSeg);
    EXPECT_THROW((LineSeg3D{p, zero}), LineSeg3D::DegeneratedLineSeg);
}

TEST(LineSeg3D, HasPoint)
{
    Point3D a{1,2,3};
    Point3D b{4,-5,6};

    LineSeg3D ls{a, b};

    EXPECT_TRUE(ls.has_point(a));
    EXPECT_TRUE(ls.has_point(b));
    EXPECT_TRUE(ls.has_point((a+b)*0.5));
    
    EXPECT_FALSE(ls.has_point({0,0,0}));
    EXPECT_FALSE(ls.has_point(a + -ls.vec()));
    EXPECT_FALSE(ls.has_point(b + ls.vec()));
}

TEST(LineSeg3D, VecConsistent)
{
    LineSeg3D ls{Point3D{1,2,3}, Point3D{4,5,6}};
    EXPECT_TRUE((ls.vec() == Vector3D{3,3,3}));

    LineSeg3D ls2{Point3D{1,2,3}, Vector3D{4,5,6}};
    EXPECT_TRUE((ls2.vec() == Vector3D{4,5,6}));
}

TEST(LineSeg3D, IntersectsLineSeg3D)
{
    EXPECT_FALSE((LineSeg3D{Point3D{0,0,0},Point3D{1,0,0}}
     .intersects_LineSeg3D({Point3D{0,0,1},Point3D{0,1,1}})));

    EXPECT_TRUE((LineSeg3D{Point3D{0,0,0},Point3D{1,0,0}}
    .intersects_LineSeg3D({Point3D{0,0,0},Point3D{0,1,0}})));

    EXPECT_TRUE((LineSeg3D{Point3D{0,0,0},Point3D{1,0,0}}
    .intersects_LineSeg3D({Point3D{0,1,0},Point3D{0,0,0}})));

    EXPECT_TRUE((LineSeg3D{Point3D{0,0,0},Point3D{1,0,0}}
    .intersects_LineSeg3D({Point3D{0.5,-1,0},Point3D{0,1,0}})));

    EXPECT_TRUE((LineSeg3D{Point3D{0,0,0},Point3D{1,0,0}}
    .intersects_LineSeg3D({Point3D{0,1,0},Point3D{0.5,-1,0}})));
}

TEST(Plane, CtorOk)
{
    Plane p{{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};
    EXPECT_TRUE((p.n_vec() == Vector3D{0, 0, 1}));
}

TEST(Plane, CtorDegenerate)
{
    EXPECT_THROW((Plane{{0,0,0}, {0,0,0}, {1,1,1}}), Plane::DegeneratedPlane);

    EXPECT_THROW((Plane{Vector3D{0,0,0}, {0,0,0}}), Plane::DegeneratedPlane);
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

TEST(Plane, HasPoint)
{
    Point3D p1{1,2,3};
    Point3D p2{4,5,-6};
    Point3D p3{-7,8,19};

    Plane plane1{p1,p2,p3};
    EXPECT_TRUE(plane1.has_point(p1));
    EXPECT_TRUE(plane1.has_point(p2));
    EXPECT_TRUE(plane1.has_point(p3));

    Plane plane2{Vector3D{0,0,1}, Point3D{0,0,0}};
    EXPECT_TRUE(plane2.has_point({19,-38, 0}));
    EXPECT_FALSE(plane2.has_point({0,0,1}));
}

TEST(Plane, SignedDistToPoint)
{
    Point3D point{1, 2, 3};
    Plane plane{Vector3D{1,1,1}, point};

    EXPECT_DOUBLE_EQ(plane.s_dist_to_point(point), 0);
    EXPECT_GT(plane.s_dist_to_point({2,3,4}), 0);
    EXPECT_LT(plane.s_dist_to_point({0,1,2}), 0);
}

TEST(Plane, IsParallelTo)
{
    Vector3D v1{1,2,3};
    Vector3D v2{-10,-20,-30};
    Vector3D v3{1,-2,3};

    Plane p1{v1, Point3D{34,45,-67}};
    Plane p2{v2, Point3D{-345,345,234}}; 
    Plane p3{v3, Point3D{0,0,0}};

    EXPECT_TRUE(p1.is_parallel_to(p2));
    EXPECT_TRUE(p2.is_parallel_to(p1));

    EXPECT_FALSE(p1.is_parallel_to(p3));
    EXPECT_FALSE(p2.is_parallel_to(p3));
    EXPECT_FALSE(p3.is_parallel_to(p1));
    EXPECT_FALSE(p3.is_parallel_to(p2));
}

TEST(Triangle3D, CtorOk)
{
    Point3D p1{0,0,0};
    Point3D p2{0,1,0};
    Point3D p3{0,0,1};
    
    Triangle3D t{p1, p2, p3};

    EXPECT_TRUE(t.p1() == p1);
    EXPECT_TRUE(t.p2() == p2);
    EXPECT_TRUE(t.p3() == p3);
    EXPECT_TRUE((t.plane() == Plane{p1, p2, p3}));
}

TEST(Triangle3D, PlaneNVecIsRight)
{
    Triangle3D t{{1.23, -4.56, 7.89}, {4.5, 45.4, -4.56}, {-7.34, 5.345, 9.386}};
    EXPECT_TRUE(t.plane().n_vec() == cross_prod({t.p1(), t.p2()}, {t.p1(), t.p3()}).norm_vec());
}

TEST(Triangle3D, CtorDegenerate)
{
    Point3D p1{1,2,3};
    Point3D p2{4,-5,9};
    EXPECT_THROW((Triangle3D{p1,p1,p2}), Triangle3D::DegeneratedTriangle);
    EXPECT_THROW((Triangle3D{p1,p2,p2}), Triangle3D::DegeneratedTriangle);
    EXPECT_THROW((Triangle3D{p2,p1,p2}), Triangle3D::DegeneratedTriangle);
    EXPECT_THROW((Triangle3D{p1,p1,p1}), Triangle3D::DegeneratedTriangle);
}

TEST(Triangle3D, HasPoint)
{
    Triangle3D t{{0,0,0}, {0,1,0}, {0,0,1}};

    EXPECT_TRUE(t.has_point({0, 0, 0}));
    EXPECT_TRUE(t.has_point({0, 1, 0}));
    EXPECT_TRUE(t.has_point({0, 0, 1}));

    EXPECT_FALSE(t.has_point({1,0,0}));
    EXPECT_FALSE(t.has_point({-1,0,0}));
    EXPECT_FALSE(t.has_point({0,2,0}));
    EXPECT_FALSE(t.has_point({0,1,1}));
    EXPECT_FALSE(t.has_point({0,0,2}));
    EXPECT_FALSE(t.has_point({0,-1,0}));
    EXPECT_FALSE(t.has_point({0,0,-1}));

    EXPECT_TRUE(t.has_point({0, 0.2, 0.2}));
    EXPECT_TRUE(t.has_point({0, 0.5, 0.5}));
    EXPECT_TRUE(t.has_point({0, 0.8, 0.2}));
    EXPECT_TRUE(t.has_point({0, 0.2, 0.8}));
    EXPECT_TRUE(t.has_point({0,0.5,0}));
    EXPECT_TRUE(t.has_point({0, 0, 0.5}));

    t = Triangle3D{{0,0,0}, {0,0,1}, {0,1,0}};

    EXPECT_TRUE(t.has_point({0, 0, 0}));
    EXPECT_TRUE(t.has_point({0, 1, 0}));
    EXPECT_TRUE(t.has_point({0, 0, 1}));

    EXPECT_FALSE(t.has_point({1,0,0}));
    EXPECT_FALSE(t.has_point({-1,0,0}));
    EXPECT_FALSE(t.has_point({0,2,0}));
    EXPECT_FALSE(t.has_point({0,1,1}));
    EXPECT_FALSE(t.has_point({0,0,2}));
    EXPECT_FALSE(t.has_point({0,-1,0}));
    EXPECT_FALSE(t.has_point({0,0,-1}));

    EXPECT_TRUE(t.has_point({0, 0.2, 0.2}));
    EXPECT_TRUE(t.has_point({0, 0.5, 0.5}));
    EXPECT_TRUE(t.has_point({0, 0.8, 0.2}));
    EXPECT_TRUE(t.has_point({0, 0.2, 0.8}));
    EXPECT_TRUE(t.has_point({0,0.5,0}));
    EXPECT_TRUE(t.has_point({0, 0, 0.5}));
}

TEST(Triangle3D, IntersectsLineSeg3D)
{
    Triangle3D t{{0,0,0}, {0,1,0}, {0,0,1}};

    EXPECT_TRUE(t.intersects_LineSeg3D({Point3D{0,0,0},Point3D{2,2,2}}));
    EXPECT_TRUE(t.intersects_LineSeg3D({Point3D{0,1,0},Point3D{2,2,2}}));
    EXPECT_TRUE(t.intersects_LineSeg3D({Point3D{0,0,1},Point3D{2,2,2}}));
    EXPECT_TRUE(t.intersects_LineSeg3D({Point3D{2,2,2},Point3D{0,0,0}}));
    EXPECT_TRUE(t.intersects_LineSeg3D({Point3D{2,2,2},Point3D{0,1,0}}));
    EXPECT_TRUE(t.intersects_LineSeg3D({Point3D{2,2,2},Point3D{0,0,1}}));

    EXPECT_TRUE(t.intersects_LineSeg3D({Point3D{1,0.5,0.5},Point3D{-1,0.5,0.5}}));
    EXPECT_TRUE(t.intersects_LineSeg3D({Point3D{1,0.5,0.5},Point3D{-1,0,0}}));
    
    EXPECT_FALSE(t.intersects_LineSeg3D({Point3D{1,1,1}, Point3D{2,2,2}}));
    EXPECT_FALSE(t.intersects_LineSeg3D({Point3D{1,0,0}, Point3D{1,2,2}}));
    EXPECT_FALSE(t.intersects_LineSeg3D({Point3D{-1,0,0}, Point3D{-1,2,2}}));

    EXPECT_FALSE(t.intersects_LineSeg3D({Point3D{1,2.5,0.5},Point3D{-1,2.5,0.5}}));
    EXPECT_FALSE(t.intersects_LineSeg3D({Point3D{1,0.5,2.5},Point3D{-1,0.5,2.5}}));
}

TEST(Triangle3D, IntersectsTriangle3D)
{
    // https://www.desmos.com/3d/ehdtqku6u9

    // triangle with itself
    EXPECT_TRUE(( Triangle3D{{1.23,-4.56,7.89}, {4.5,45.4,-4.56}, {-7.34,5.345,9.386}}
     .intersects_Triangle3D({{1.23,-4.56,7.89}, {4.5,45.4,-4.56}, {-7.34,5.345,9.386}})));

    // one point intersection, vertex & vertex, not complanar
    EXPECT_TRUE(( Triangle3D{{0,0,0}, {1,0,0}, {0,1,0}}
     .intersects_Triangle3D({{0,1,0}, {0,1,1}, {0,2,1}})));

    // one point intersection, vertex & vertex, complanar
    EXPECT_TRUE(( Triangle3D{{0,0,0}, {1,0,0}, {0,1,0}}
     .intersects_Triangle3D({{0,1,0}, {1,1,0}, {0,2,0}})));

    // one point intersection, non-vertex & vertex, complanar
    EXPECT_TRUE(( Triangle3D{{0,0,0}, {1,0,0}, {0,1,0}}
     .intersects_Triangle3D({{0.5,0.5,0}, {1,1,0}, {0,2,0}})));

    // one point intersection, non-vertex & vertex, not complanar
    EXPECT_TRUE(( Triangle3D{{0,0,0}, {1,0,0}, {0,1,0}}
    .intersects_Triangle3D({{0.5,0.5,0}, {1,1,1}, {0,2,1}})));

    // one point intersection, non-vertex & non-vertex, not complanar
    EXPECT_TRUE(( Triangle3D{{0,0,0}, {1,0,0}, {0,1,0}}
     .intersects_Triangle3D({{0,0.5,-1}, {0,0.5,1}, {-1,2,1}})));

    // one point intersection, non-vertex & non-vertex, not complanar
    EXPECT_TRUE(( Triangle3D{{0,0,0}, {1,0,0}, {0,1,0}}
     .intersects_Triangle3D({{0,0.5,-0.5}, {0,0.5,0.5}, {-1,0,0}})));

    // lineseg on edge, not complanar
    EXPECT_TRUE(( Triangle3D{{0,0,0}, {1,0,0}, {0,1,0}}
     .intersects_Triangle3D({{0,0.5,-1}, {0,0.5,1}, {0,2,1}})));

    // lineseg on edge, complanar
    EXPECT_TRUE(( Triangle3D{{0,0,0}, {1,0,0}, {0,1,0}}
     .intersects_Triangle3D({{0,0.5,0}, {0,2,0}, {-1,2,0}})));

    // complanar, no intersection
    EXPECT_FALSE(( Triangle3D{{1, 1, 0}, {3, 1, 0}, {1, 3, 0}}
     .intersects_Triangle3D({{0, 0, 0}, {1, 0, 0}, {0, 1, 0}})));

    // from random
    Triangle3D t0{{331.45348239878297, 946.1053420056721, 952.8130103892371},
                  {329.3675304584714, 950.149787753491, 955.6291984713811},
                  {329.22924771213985, 947.6454053402665, 958.2453650715645}};

    Triangle3D t1{{505.04444670411795, 712.7749969460839, 644.9757087997505},
                  {503.8788993236424, 706.4415126134443, 636.7896903311087},
                  {504.6340512609518, 712.8683327073852, 645.114914183536}};
    EXPECT_FALSE(t0.intersects_Triangle3D(t1));

    t0 = {{262.8291506593867, 738.8902664246145, 184.07270169509806},
          {263.92326377188147, 744.9257758705741, 191.98754127204313},
          {255.05569075140053, 745.0833699978822, 178.5923009811677}};

    t1 = {{271.50486167797413, 743.7270637671139, 180.50289912002347},
          {263.62623527710156, 745.1230254904556, 175.10729737918282},
          {261.92930739757537, 741.4502078216377, 187.08101408287405}};
    EXPECT_TRUE(t0.intersects_Triangle3D(t1));
}

TEST(BoundingBox, Intersects)
{
    // https://www.desmos.com/3d/taxvrz4rog

    EXPECT_TRUE((BoundingBox{{1, 2, 3}, {4, 5, 6}}
     .intersects(BoundingBox{{1, 2, 3}, {4, 5, 6}})));

    // one dot intersection (extreme)
    EXPECT_TRUE((BoundingBox{{0, 0, 0}, {1, 1, 1}}
     .intersects(BoundingBox{{0, 0, 0}, {-1, -1, -1}})));

    // one dot intersection (non-extreme)
    EXPECT_TRUE((BoundingBox{{0, 0, 0}, {1, 1, 1}}
     .intersects(BoundingBox{{1, -1, 1}, {2, 0, 2}})));
     
    // edge intersection (non-extreme)
    EXPECT_TRUE((BoundingBox{{0, 0, 0}, {1, 1, 1}}
     .intersects(BoundingBox{{2, 0, 2}, {1, -1, -1}})));

    // one inside another
    EXPECT_TRUE((BoundingBox{{0, 0, 0}, {1, 1, 1}}
     .intersects(BoundingBox{{-1, -1, -1}, {2, 2, 2}})));

    // face intersection
    EXPECT_TRUE((BoundingBox{{0, 0, 0}, {1, 1, 1}}
     .intersects(BoundingBox{{2, 0, 2}, {-1, -1, -1}})));

    EXPECT_TRUE((BoundingBox{{0, 0, 0}, {1, 1, 1}}
     .intersects(BoundingBox{{-1, 0.5, -1}, {2, 0.7, 2}})));
}