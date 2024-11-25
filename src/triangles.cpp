#include "triangles.hpp"

#include <cmath>
#include <cassert>

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

Vector3D &Vector3D::operator*=(scalar_t rhs)
{
    x_ *= rhs; y_ *= rhs; z_ *= rhs;
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

Vector3D::operator Point3D() const
{
    return Point3D{x_, y_, z_};
}

Vector3D Vector3D::norm_vec() const
{
    scalar_t len = sqrt(x_*x_ + y_*y_ + z_*z_);
    if (is_zero())
        return Vector3D{0, 0, 0};
    return Vector3D{x_/len, y_/len, z_/len};
}

scalar_t Vector3D::len() const
{
    return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}

bool Vector3D::is_zero() const
{
    return eq(len(), 0);
}

Vector3D operator+(const Vector3D &lhs, const Vector3D &rhs)
{
    Vector3D tmp{lhs}; tmp += rhs;
    return tmp;
}

Vector3D operator-(const Vector3D &lhs, const Vector3D &rhs)
{
    return lhs + -rhs;
}

Vector3D operator*(scalar_t scalar, const Vector3D& vector)
{
    Vector3D tmp{vector}; tmp *= scalar;
    return tmp;
}

Vector3D operator*(const Vector3D &vector, scalar_t scalar)
{
    Vector3D tmp{vector}; tmp *= scalar;
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

scalar_t dot_prod(const Vector3D &lhs, const Vector3D &rhs)
{
    return lhs.x()*rhs.x() + lhs.y()*rhs.y() + lhs.z()*rhs.z();
}

scalar_t scalar_triple_prod(const Vector3D &a, const Vector3D &b, const Vector3D &c)
{
    return dot_prod(a, cross_prod(b, c));
}

std::optional<Line3D> intersect_planes(Plane p1, Plane p2)
{
    Vector3D n1 = p1.n_vec();
    Vector3D n2 = p2.n_vec();

    Vector3D line_dir = cross_prod(n1, n2);
    if (eq(line_dir.len(), 0))
        return std::nullopt;

    scalar_t s1 = dot_prod(n1, p1.p());
    scalar_t s2 = dot_prod(n2, p2.p());

    scalar_t n1n2dot = dot_prod(n1, n2);
    scalar_t n1n2dotsqr = n1n2dot * n1n2dot;
    scalar_t a = (s2 * n1n2dot - s1) / (n1n2dotsqr - 1);
    scalar_t b = (s1 * n1n2dot - s2) / (n1n2dotsqr - 1);

    Point3D line_point = a*n1 + b*n2;
    return Line3D{line_dir, line_point};
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

Point3D Plane::p() const
{
    return p_;
}

bool Plane::has_point(Point3D q) const
{
    return eq(dot_prod(Vector3D{p_, q}, n_vec_), 0);
}

scalar_t Plane::signed_dist_to_point(Point3D q) const
{
   return dot_prod(n_vec_, Vector3D{p_, q});
}

Line3D::Line3D(Vector3D dir, Point3D p)
    : dir_(dir.norm_vec()), p_(p)
{
    if (eq(dir_.len(), 0))
        throw DegeneratedLine();
}

Line3D::Line3D(Point3D p1, Point3D p2)
    : dir_(Vector3D{p1, p2}.norm_vec()), p_(p1)
{
    if (eq(dir_.len(), 0))
        throw DegeneratedLine();
}

bool Line3D::operator==(const Line3D &rhs) const
{
    return (dir_ == rhs.dir_ || dir_ == -rhs.dir_) && has_point(rhs.p_);
}

bool Line3D::is_parallel_to(const Line3D &rhs) const
{
    return dir_ == rhs.dir_ || dir_ == -rhs.dir_;
}

Vector3D Line3D::dir() const
{
    return dir_;
}

Point3D Line3D::p() const
{
    return p_;
}

bool Line3D::has_point(Point3D q) const
{
    return cross_prod(dir_, Vector3D{q} + -Vector3D{p_}).is_zero();
}

LineSeg3D::LineSeg3D(Point3D p1, Point3D p2) :
    p1_(p1), p2_(p2), vec_(p1, p2)
{
    if (eq(vec_.len(), 0))
        throw DegeneratedLineSeg();
}

LineSeg3D::LineSeg3D(Point3D p, Vector3D v) :
    p1_(p), p2_(p + v), vec_(v)
{
    if (eq(vec_.len(), 0))
        throw DegeneratedLineSeg();
}

Point3D LineSeg3D::p1() const
{
    return p1_;
}

Point3D LineSeg3D::p2() const
{
    return p2_;
}

Vector3D LineSeg3D::vec() const
{
    return vec_;
}

bool LineSeg3D::has_point(Point3D q) const
{
    Vector3D dir{p1_, q};
    return cross_prod(vec_, dir).is_zero() && geq(dot_prod(vec_, dir), 0) && leq(dir.len(), vec_.len());
}

std::optional<Point3D> LineSeg3D::intersect_with_complanar_line(const Line3D &line) const
{
    assert(eq(scalar_triple_prod(vec_, line.dir(), line.p() - p1_), 0));

    if (cross_prod(vec_, line.dir()).is_zero())
        return std::nullopt;

    Vector3D a = line.p() - p1_;
    Vector3D norm_lineseg_vec = vec_.norm_vec();
    Vector3D b = -a + dot_prod(a, norm_lineseg_vec) * norm_lineseg_vec;
    scalar_t b_len = b.len();
    return line.p() + line.dir() * ((b_len * b_len) / dot_prod(b, line.dir()));
}

Triangle3D::Triangle3D(Point3D p1, Point3D p2, Point3D p3) : 
    p1_(p1), p2_(p2), p3_(p3), plane_(Vector3D{1,0,0}, Point3D{0,0,0})
{
    if (p1_ == p2_ || p2_ == p3_ || p1_ == p3_)
        throw DegeneratedTriangle();

    plane_ = Plane{p1, p2, p3};
}

Point3D Triangle3D::p1() const
{
    return p1_;
}

Point3D Triangle3D::p2() const
{
    return p2_;
}

Point3D Triangle3D::p3() const
{
    return p3_;
}

Plane Triangle3D::plane() const
{
    return plane_;
}

bool Triangle3D::has_point(const Point3D &p) const
{
    if (!plane_.has_point(p))
        return false;

    Vector3D v1 = cross_prod(p2_ - p1_, p - p1_);
    Vector3D v2 = cross_prod(p3_ - p2_, p - p2_);
    Vector3D v3 = cross_prod(p1_ - p3_, p - p3_);

    scalar_t s1 = dot_prod(v1, plane_.n_vec());
    scalar_t s2 = dot_prod(v2, plane_.n_vec());
    scalar_t s3 = dot_prod(v3, plane_.n_vec());

    if ((geq(s1, 0) && geq(s2, 0) && geq(s3, 0) ) || (leq(s1, 0) && leq(s2, 0) && leq(s3, 0)))
        return true;

    return false; 
}

bool Triangle3D::intersects_LineSeg3D(const LineSeg3D &lineseg) const
{
    // check if any of the endpoints of lineseg belong to the triangle
    if (has_point(lineseg.p1()) || has_point(lineseg.p2()))
        return true;

    // check if points are on different sides of the triangle's plane
    scalar_t s_dist1 = plane_.signed_dist_to_point(lineseg.p1());
    scalar_t s_dist2 = plane_.signed_dist_to_point(lineseg.p2());

    if ((geq(s_dist1, 0) && geq(s_dist2, 0)) || (leq(s_dist1, 0) && leq(s_dist2, 0)))
        return false;

    // get line of the lineseg, intersect it with the triangle's plane, check if 
    // intersection point belongs to the triangle

    Line3D line{lineseg.p1(), lineseg.vec()};
    ...
}

} // namespace Geom
