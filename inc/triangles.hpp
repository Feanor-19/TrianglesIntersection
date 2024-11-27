#pragma once

#include <numeric>
#include <cmath>
#include <stdexcept>
#include <optional>

namespace Geom
{

using scalar_t = double;

const scalar_t DBL_PRECISION = 1e-10;

class GeomException : std::logic_error 
{
public:
    GeomException(const char *err_msg) : std::logic_error(err_msg) {}
};

inline bool eq(scalar_t a, scalar_t b)
{
    return fabs(a - b) < DBL_PRECISION;
}

inline bool geq(scalar_t a, scalar_t b)
{
    return (a > b) || eq(a, b);
}

inline bool leq(scalar_t a, scalar_t b)
{
    return (a < b) || eq(a, b);
}

// if one of parameters of the constructor is NaN
class NaNCtorParam : GeomException 
{
public:
    NaNCtorParam() : GeomException("At least one of parametres passed to constructor is a NaN") {}
};

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
    Vector3D(Point3D p) : x_(p.x()), y_(p.y()), z_(p.z()) {};

    scalar_t x() const {return x_;};
    scalar_t y() const {return y_;};
    scalar_t z() const {return z_;};

    Vector3D& operator+=(const Vector3D& rhs);
    Vector3D& operator*=(scalar_t rhs);
    bool operator==(const Vector3D& rhs) const;
    Vector3D operator-() const;
    operator Point3D() const;

    Vector3D norm_vec() const;
    scalar_t len() const;
    bool is_zero() const;
};

Vector3D operator+(const Vector3D& lhs, const Vector3D& rhs);
Vector3D operator-(const Vector3D& lhs, const Vector3D& rhs);
Vector3D operator*(scalar_t scalar, const Vector3D& vector);
Vector3D operator*(const Vector3D& vector, scalar_t scalar);
Vector3D cross_prod(const Vector3D& lhs, const Vector3D& rhs);
scalar_t dot_prod(const Vector3D& lhs, const Vector3D& rhs);
scalar_t scalar_triple_prod(const Vector3D& a, const Vector3D& b, const Vector3D& c);

class Line3D final
{
private:
    Vector3D dir_; // always normalized
    Point3D p_;
public:
    class DegeneratedLine : public GeomException 
    {
    public:
        DegeneratedLine() : GeomException("Attempt to construct a degenerated line") {}
    };

    Line3D(Vector3D dir, Point3D p);
    Line3D(Point3D p1, Point3D p2);

    bool operator==(const Line3D &rhs) const;
    bool is_parallel_to(const Line3D &rhs) const;

    Vector3D dir() const;
    Point3D p() const;

    bool has_point(Point3D q) const;
};

class LineSeg3D final 
{
private:
    Point3D p1_;
    Point3D p2_;
    Vector3D vec_; //must be (p2_- p1_)
public:
    class DegeneratedLineSeg : GeomException
    {
    public:
        DegeneratedLineSeg() : GeomException("Attempt to construct a degenerated line segment") {}
    }; 

    LineSeg3D(Point3D p1, Point3D p2);
    LineSeg3D(Point3D p, Vector3D v);

    Point3D p1() const;
    Point3D p2() const;
    Vector3D vec() const;

    bool has_point(Point3D q) const;
    
    // finds point of intersection with line, which must be in the same plane as this segment
    // if the intersection is not a point (or there is no intersection), std::nullopt is returned
    // TODO CHECK IF IT IS ACTUALLY NEEDED
    std::optional<Point3D> intersect_with_complanar_line(const Line3D &line) const;
};

class Plane final
{
private:
    Vector3D n_vec_; // always normalized
    Point3D p_;
public:
    class DegeneratedPlane : GeomException
    {
    public:
        DegeneratedPlane() : GeomException("Attempt to construct a degenerated plane") {}
    }; 
    
    Plane(Vector3D n_vec, Point3D p);
    Plane(Point3D p1, Point3D p2, Point3D p3);

    bool operator==(const Plane &rhs) const;
    bool is_parallel_to(const Plane &rhs) const;

    Vector3D n_vec() const;
    Point3D p() const;

    bool has_point(Point3D q) const;

    scalar_t s_dist_to_point(Point3D q) const;
};

std::optional<Line3D> intersect_planes(Plane p1, Plane p2);

class Triangle3D final 
{
private:
    Point3D p1_; 
    Point3D p2_;
    Point3D p3_; 
    Plane plane_; // must be consistent with other private fields:
                  // plane_.n_vec must be [p1p2, p1p3]
public:
    class DegeneratedTriangle : GeomException
    {
    public:
        DegeneratedTriangle() : GeomException("Attempt to construct a degenerated plane") {}    
    };

    Triangle3D(Point3D p1, Point3D p2, Point3D p3);

    Point3D p1() const;
    Point3D p2() const;
    Point3D p3() const;
    Plane plane() const;

    bool has_point(const Point3D& p) const;

    bool intersects_LineSeg3D(const LineSeg3D& lineseg) const;
    bool intersects_Triangle3D(const Triangle3D& triangle) const;
};

} // namespace Geom