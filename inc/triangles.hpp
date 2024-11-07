#pragma once

#include <numeric>
#include <cmath>

namespace Geom
{

using scalar_t = double;

const scalar_t DBL_PRECISION = 1e-10;

inline bool eq(scalar_t a, scalar_t b)
{
    return abs(a - b) < DBL_PRECISION;
}

// if one of parameters of the constructor is NaN
class ExceptionNaNCtorParam {};

class Point3D final
{
private:
    scalar_t x_, y_, z_;
public:
    Point3D(scalar_t x, scalar_t y, scalar_t z);

    scalar_t x() const {return x_;};
    scalar_t y() const {return y_;};
    scalar_t z() const {return z_;};

    bool operator==(const Point3D& rhs) const;
};

// TODO check if "final" is needed
class Vector3D final
{
private:
    scalar_t x_, y_, z_;
public:
    Vector3D(scalar_t x, scalar_t y, scalar_t z);
    Vector3D(Point3D p_start, Point3D p_end);

    scalar_t x() const {return x_;};
    scalar_t y() const {return y_;};
    scalar_t z() const {return z_;};

    Vector3D& operator+=(const Vector3D& rhs);
    bool operator==(const Vector3D& rhs) const;
    Vector3D operator-() const;

    Vector3D norm_vec() const;
    scalar_t len() const;
};

Vector3D operator+(const Vector3D& lhs, const Vector3D& rhs);
Vector3D cross_prod(const Vector3D& lhs, const Vector3D& rhs);
scalar_t scalar_prod(const Vector3D& lhs, const Vector3D& rhs);

class Plane final
{
private:
    Vector3D n_vec_; // always normalized
    Point3D p_;
public:
    class DegeneratedPlane {}; 
    
    Plane(Vector3D n_vec, Point3D p) : n_vec_(n_vec.norm_vec()), p_(p) {};
    Plane(Point3D p1, Point3D p2, Point3D p3);

    bool operator==(const Plane &rhs) const;

    Vector3D n_vec() const;

    bool has_point(Point3D q) const;

    scalar_t signed_dist_to_point(Point3D q);
};

} // namespace Geom