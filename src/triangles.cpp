#include "triangles.hpp"

#include <cmath>

namespace Geom
{

Point3D::Point3D(double x, double y, double z) :
    x_(x), y_(y), z_(z)
{
    if (std::isnan(x) || std::isnan(y) || std::isnan(z))
        throw ExceptionNaNCtorParam();
}

bool Point3D::operator==(const Point3D &rhs) const
{
    return eq(x_, rhs.x_) && eq(y_, rhs.y_) && eq(z_, rhs.z_);
}

Vector3D::Vector3D(double x, double y, double z) : 
    x_(x), y_(y), z_(z)
{
    if (std::isnan(x) || std::isnan(y) || std::isnan(z))
        throw ExceptionNaNCtorParam();
}

Vector3D::Vector3D(Point3D p_start, Point3D p_end) : 
    x_(p_start.x()-p_end.x()), 
    y_(p_start.y()-p_end.y()), 
    z_(p_start.z()-p_end.z())
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

Vector3D Vector3D::norm() const
{
    double len = sqrt(x_*x_ + y_*y_ + z_*z_);
    if (iszero(len))
        return Vector3D{0, 0, 0};
    return Vector3D{x_/len, y_/len, z_/len};
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

Plane::Plane(Point3D p1, Point3D p2, Point3D p3) :
    n_vec_(cross_prod(Vector3D{p1, p2}, Vector3D{p1, p3})), p_(p1)
{
    if (n_vec_ == Vector3D{0, 0, 0})
        throw DegeneratedPlane();
}

bool Plane::operator==(const Plane &rhs) const
{
    return n_vec_ == rhs.n_vec_ && p_ == rhs.p_;
}

} // namespace Geom
