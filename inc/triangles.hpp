#pragma once

#include <numeric>
#include <cmath>

namespace Geom
{

const double DBL_PRECISION = 1e-7;

inline bool eq(double a, double b)
{
    return abs(a - b) < DBL_PRECISION;
}

// if one of parameters of the constructor is NaN
class ExceptionNaNCtorParam {};

class Point3D final
{
private:
    double x_, y_, z_;
public:
    Point3D(double x, double y, double z);

    double x() const {return x_;};
    double y() const {return y_;};
    double z() const {return z_;};

    bool operator==(const Point3D& rhs) const;
};

// TODO check if "final" is needed
class Vector3D final
{
private:
    double x_, y_, z_;
public:
    Vector3D(double x, double y, double z);
    Vector3D(Point3D p_start, Point3D p_end);

    double x() const {return x_;};
    double y() const {return y_;};
    double z() const {return z_;};

    Vector3D& operator+=(const Vector3D& rhs);
    bool operator==(const Vector3D& rhs) const;

    Vector3D norm() const;
};

Vector3D operator+(const Vector3D& lhs, const Vector3D& rhs);
Vector3D cross_prod(const Vector3D& lhs, const Vector3D& rhs);

class Plane final
{
private:
    Vector3D n_vec_;
    Point3D p_;
public:
    class DegeneratedPlane {}; 
    
    Plane(Vector3D n_vec, Point3D p) : n_vec_(n_vec.norm()), p_(p) {};
    Plane(Point3D p1, Point3D p2, Point3D p3);

    bool operator==(const Plane &rhs) const;
};

} // namespace Geom