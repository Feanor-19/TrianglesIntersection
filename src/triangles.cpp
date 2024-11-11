#include "triangles.hpp"

#include <cmath>

namespace Geom
{

Point3D::Point3D(scalar_t x, scalar_t y, scalar_t z) :
    x_(x), y_(y), z_(z)
{
    if (std::isnan(x) || std::isnan(y) || std::isnan(z))
        throw NaNCtorParam();
}

bool Point3D::operator==(const Point3D &rhs) const
{
    return eq(x_, rhs.x_) && eq(y_, rhs.y_) && eq(z_, rhs.z_);
}

Vector3D::Vector3D(scalar_t x, scalar_t y, scalar_t z) : 
    x_(x), y_(y), z_(z)
{
    if (std::isnan(x) || std::isnan(y) || std::isnan(z))
        throw NaNCtorParam();
}

Vector3D::Vector3D(Point3D p_start, Point3D p_end) : 
    x_(p_end.x()-p_start.x()), 
    y_(p_end.y()-p_start.y()), 
    z_(p_end.z()-p_start.z())
{
}

Vector3D &Vector3D::operator+=(const Vector3D &rhs)
{
    x_ += rhs.x_; y_ += rhs.y_; z_ += rhs.z_;
    return *this;
}

bool Vector3D::operator==(const Vector3D &rhs) const
{
    return eq(x_, rhs.x_) && eq(y_, rhs.y_) && eq(z_, rhs.z_);
}

Vector3D Vector3D::operator-() const
{
    return Vector3D{-x_, -y_, -z_};
}

Vector3D Vector3D::norm_vec() const
{
    scalar_t len = sqrt(x_*x_ + y_*y_ + z_*z_);
    if (iszero(len))
        return Vector3D{0, 0, 0};
    return Vector3D{x_/len, y_/len, z_/len};
}

scalar_t Vector3D::len() const
{
    return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}

Vector3D operator+(const Vector3D &lhs, const Vector3D &rhs)
{
    Vector3D tmp{lhs}; tmp += rhs;
    return tmp;
}

Vector3D cross_prod(const Vector3D &lhs, const Vector3D &rhs)
{
    return Vector3D{
        lhs.y() * rhs.z() - lhs.z() * rhs.y(),
        lhs.z() * rhs.x() - lhs.x() * rhs.z(),
        lhs.x() * rhs.y() - lhs.y() * rhs.x()
    };
}

scalar_t scalar_prod(const Vector3D &lhs, const Vector3D &rhs)
{
    return lhs.x()*rhs.x() + lhs.y()*rhs.y() + lhs.z()*rhs.z();
}

Plane::Plane(Vector3D n_vec, Point3D p)
    : n_vec_(n_vec.norm_vec()), p_(p)
{
    if (eq(n_vec_.len(), 0))
        throw DegeneratedPlane();    
}

Plane::Plane(Point3D p1, Point3D p2, Point3D p3) 
    : n_vec_(cross_prod(Vector3D{p1, p2}, Vector3D{p1, p3}).norm_vec()), p_(p1)
{
    if (eq(n_vec_.len(), 0))
        throw DegeneratedPlane();
}

bool Plane::operator==(const Plane &rhs) const
{
    return (n_vec_ == rhs.n_vec_ || n_vec_ == -rhs.n_vec_) && has_point(rhs.p_);
}

bool Plane::is_parallel_to(const Plane &rhs) const
{
    return (n_vec_ == rhs.n_vec_ || n_vec_ == -rhs.n_vec_);
}

Vector3D Plane::n_vec() const
{
    return n_vec_;
}

bool Plane::has_point(Point3D q) const
{
    return eq(scalar_prod(Vector3D{p_, q}, n_vec_), 0);
}

scalar_t Plane::signed_dist_to_point(Point3D q) const
{
   return scalar_prod(n_vec_, Vector3D{p_, q});
}

Line3D::Line3D(Vector3D dir, Point3D p)
    : dir_(dir.norm_vec()), p_(p)
{
    if (eq(dir_.len(), 0))
        throw DegeneratedLine();
}

Line3D::Line3D(Point3D p1, Point3D p2)
    : dir_(p1, p2), p_(p1)
{
    if (eq(dir_.len(), 0))
        throw DegeneratedLine();
}

Vector3D Line3D::dir() const
{
    return dir_;
}

Point3D Line3D::p() const
{
    return p_;
}

} // namespace Geom
