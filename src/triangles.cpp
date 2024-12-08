#include "triangles.hpp"

#include <cmath>
#include <cassert>
#include <tuple>

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

Vector3D &Vector3D::operator-=(const Vector3D &rhs)
{
    x_ -= rhs.x_; y_ -= rhs.y_; z_ -= rhs.z_;
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
    assert(!eq(n1n2dotsqr, 1));
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

scalar_t Plane::s_dist_to_point(Point3D q) const
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
    p1_(p1), p2_(p2), vec_(p1, p2), bound_box_({p1, p2})
{
    if (eq(vec_.len(), 0))
        throw DegeneratedLineSeg();
}

LineSeg3D::LineSeg3D(Point3D p, Vector3D v) :
    p1_(p), p2_(p + v), vec_(v), bound_box_({p, p + v})
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

BoundingBox LineSeg3D::bound_box() const
{
    return bound_box_;
}

bool LineSeg3D::has_point(Point3D q) const
{
    Vector3D dir{p1_, q};
    return cross_prod(vec_, dir).is_zero() && geq(dot_prod(vec_, dir), 0) && leq(dir.len(), vec_.len());
}

bool LineSeg3D::intersects_LineSeg3D(const LineSeg3D &ls) const
{
    if (!eq(scalar_triple_prod(vec_, ls.vec_, p1_ - ls.p1_), 0))
        return false;

    bool trivial_case = has_point(ls.p1_) || has_point(ls.p2_) || ls.has_point(p1_) || ls.has_point(p2_); 
    if (trivial_case)
        return true;

    Vector3D n = cross_prod(vec_.norm_vec(), ls.vec_.norm_vec());
    if (n.is_zero())
        return trivial_case;

    Vector3D a = ls.p1_ - p1_;
    Vector3D norm_ls_vec = vec_.norm_vec();
    Vector3D norm_other_ls_vec = ls.vec_.norm_vec();
    Vector3D b = -a + dot_prod(a, norm_ls_vec) * norm_ls_vec;
    scalar_t b_len = b.len();
    Point3D p_intsc = ls.p1_ + norm_other_ls_vec * ((b_len * b_len) / dot_prod(b, norm_other_ls_vec));

    return has_point(p_intsc);
}

Triangle3D::Triangle3D(Point3D p1, Point3D p2, Point3D p3) : 
    p1_(p1), p2_(p2), p3_(p3), plane_(Vector3D{1,0,0}, Point3D{0,0,0}), bound_box_({p1, p2, p3})
{
    if (p1_ == p2_ || p2_ == p3_ || p1_ == p3_)
        throw DegeneratedTriangle();

    plane_ = Plane{cross_prod({p1_, p2_}, {p1_, p3_}), p1_};
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

BoundingBox Triangle3D::bound_box() const
{
    return bound_box_;
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
    if (!bound_box_.intersects(lineseg.bound_box()))
        return false;

    // check if any of the endpoints of lineseg belong to the triangle
    if (has_point(lineseg.p1()) || has_point(lineseg.p2()))
        return true;

    // check if points are on the same side of the triangle's plane
    scalar_t s_dist1 = plane_.s_dist_to_point(lineseg.p1());
    scalar_t s_dist2 = plane_.s_dist_to_point(lineseg.p2());

    if ((geq(s_dist1, 0) && geq(s_dist2, 0)) || (leq(s_dist1, 0) && leq(s_dist2, 0)))
        return false;

    // get line of the lineseg, intersect it with the triangle's plane, check if 
    // intersection point belongs to the triangle
    Point3D line_p = lineseg.p1();
    Vector3D line_vec = lineseg.vec();
    Vector3D plane_n = plane_.n_vec();

    Vector3D intsc_dir = (-plane_.s_dist_to_point(line_p) / dot_prod(line_vec, plane_n)) * line_vec; 
    Point3D intsc_p = line_p + intsc_dir;

    return has_point(intsc_p);
}

// helper for 'intersects_Triangle3D'
namespace PullDiffSign{

using PairPointSc = std::pair<Point3D, scalar_t>;
using Tuple3 = std::tuple<PairPointSc,PairPointSc,PairPointSc>;

// assumes that two of the given numbers has one sign, and the other one - another sign,
// (all non-zero) and returns the one with different from the other two's sign,
inline Tuple3 pull_diff_sign(PairPointSc a, PairPointSc b, PairPointSc c) {
    assert(!eq(a.second, 0) && !eq(b.second, 0) && !eq(c.second, 0));
    
    if (a.second > b.second)
        std::swap(a, b);
    if (a.second > c.second)
        std::swap(a, c);
    if (b.second > c.second)
        std::swap(b, c);

    if (b.second < 0) // if two were negative, one positive 
        return {c, b, a};

    // if two were positive, one negative
    return {a, b, c};
}

} // namespace PullDiffSign

// helper for 'intersects_Triangle3D'
inline bool are_all_the_same_sign(scalar_t a, scalar_t b, scalar_t c)
{
    return (a > 0 && b > 0 && c > 0)
        || (a < 0 && b < 0 && c < 0);
}

// helper for 'intersects_Triangle3D'
// computes interval on the line, clipped by the triangle, intersecting it
inline std::pair<scalar_t, scalar_t> compute_interval(Line3D intsc_line, 
                                                      Point3D p1_, Point3D p2_, Point3D p3_,
                                                      scalar_t s_dist1_, scalar_t s_dist2_, scalar_t s_dist3_)
{
    assert(!(eq(s_dist1_, 0) && eq(s_dist2_, 0) && eq(s_dist3_, 0)));
    
    Point3D l_p = intsc_line.p();
    Vector3D l_d = intsc_line.dir(); 
    auto proj_on_line = [l_p, l_d](const Point3D &p) {return dot_prod(p-l_p,l_d);};

    bool s_dist1_0 = eq(s_dist1_, 0), s_dist2_0 = eq(s_dist2_, 0), s_dist3_0 = eq(s_dist3_, 0); 

    // if two of the given points are on the line
    if (s_dist1_0 && s_dist2_0) return {proj_on_line(p1_),proj_on_line(p2_)};
    if (s_dist2_0 && s_dist3_0) return {proj_on_line(p2_),proj_on_line(p3_)};
    if (s_dist1_0 && s_dist3_0) return {proj_on_line(p1_),proj_on_line(p3_)};

    // if exaclty one of the points is on the line
    if (s_dist1_0) return {proj_on_line(p1_),proj_on_line(p1_)};
    if (s_dist2_0) return {proj_on_line(p2_),proj_on_line(p2_)};
    if (s_dist3_0) return {proj_on_line(p3_),proj_on_line(p3_)};

    auto [pps_df, pps0, pps1] = PullDiffSign::pull_diff_sign({p1_, s_dist1_}, {p2_, s_dist2_}, {p3_, s_dist3_});
    auto [p_df, s_dist_df] = pps_df; auto [p0, s_dist0] = pps0; auto [p1, s_dist1] = pps1;

    // projecting points on the line
    scalar_t pr_p0   = proj_on_line(p0);
    scalar_t pr_p1   = proj_on_line(p1);
    scalar_t pr_p_df = proj_on_line(p_df);

    scalar_t t0 = pr_p0 + (pr_p_df - pr_p0) * s_dist0 / (s_dist0 - s_dist_df);
    scalar_t t1 = pr_p1 + (pr_p_df - pr_p1) * s_dist1 / (s_dist1 - s_dist_df);
    return {t0, t1};
}

bool Triangle3D::intersects_Triangle2D(const Triangle3D &t0, const Triangle3D &t1)
{
    assert(t0.plane_ == t1.plane_);

    // Eberly, Schneider – Geometric Tools for Computer Graphics, 2002 (7.7.2)

    //REVIEW - Попытка уменьшить количество _маленького_ одинакового кода, но не используя макросы
    // returns true if ax_dir is a separating ax
    auto check_edge = [](const Point3D &p_i, const Point3D &p_i_plus_1, const Vector3D &n, const Triangle3D &other_t)
    {
        Vector3D ax_dir = cross_prod(p_i_plus_1 - p_i, n);
        return !leq(dot_prod(ax_dir, other_t.p1_ - p_i), 0)
            && !leq(dot_prod(ax_dir, other_t.p2_ - p_i), 0) 
            && !leq(dot_prod(ax_dir, other_t.p3_ - p_i), 0);
    };

    // returns true if separating ax among edges of this_t is found (triangles don't intersect)
    auto no_intersection = [check_edge](const Triangle3D &this_t, const Triangle3D &other_t)
    {
        Vector3D this_n = this_t.plane().n_vec();
        return check_edge(this_t.p1_, this_t.p2_, this_n, other_t) 
            || check_edge(this_t.p2_, this_t.p3_, this_n, other_t)
            || check_edge(this_t.p3_, this_t.p1_, this_n, other_t);
    };

    return !no_intersection(t0, t1) && !no_intersection(t1, t0);
}

bool Triangle3D::intersects_Triangle3D(const Triangle3D &triangle) const
{
    if (!bound_box_.intersects(triangle.bound_box_))
          return false;

    // Eberly, Schneider – Geometric Tools for Computer Graphics, 2002 (11.5.4)
    Triangle3D t0 = *this;
    Triangle3D t1 = triangle;

    //centering
    scalar_t div = 1. / 6.;
    Vector3D r_c = t0.p1_ * div + t0.p2_ * div + t0.p3_ * div + 
                   t1.p1_ * div + t1.p2_ * div + t1.p3_ * div;

    t0 = {t0.p1_ - r_c, t0.p2_ - r_c, t0.p3_ - r_c};
    t1 = {t1.p1_ - r_c, t1.p2_ - r_c, t1.p3_ - r_c};

    scalar_t s_dist11 = t0.plane_.s_dist_to_point(t1.p1_);
    scalar_t s_dist12 = t0.plane_.s_dist_to_point(t1.p2_);
    scalar_t s_dist13 = t0.plane_.s_dist_to_point(t1.p3_);

    if (are_all_the_same_sign(s_dist11, s_dist12, s_dist13))
        return false;

    if (t0.plane_.is_parallel_to(t1.plane_))
    {
        if (!(t0.plane_ == t1.plane_))
            return false;

        return intersects_Triangle2D(t0, t1);
    } 

    scalar_t s_dist01 = t1.plane_.s_dist_to_point(t0.p1_);
    scalar_t s_dist02 = t1.plane_.s_dist_to_point(t0.p2_);
    scalar_t s_dist03 = t1.plane_.s_dist_to_point(t0.p3_);

    if (are_all_the_same_sign(s_dist01, s_dist02, s_dist03))
        return false;

    Line3D intsc_line = *intersect_planes(t0.plane_, t1.plane_);

    auto [t00, t01] = compute_interval(intsc_line, t0.p1_, t0.p2_, t0.p3_, s_dist01, s_dist02, s_dist03);
    auto [t10, t11] = compute_interval(intsc_line, t1.p1_, t1.p2_, t1.p3_, s_dist11, s_dist12, s_dist13);

    return in_range(t00, t10, t01) || in_range(t00, t11, t01) 
        || in_range(t10, t00, t11) || in_range(t10, t01, t11);    
}

BoundingBox::BoundingBox(std::initializer_list<Point3D> points):
    min_x_(points.begin()->x()), min_y_(points.begin()->y()), min_z_(points.begin()->z()),
    max_x_(min_x_), max_y_(min_y_), max_z_(min_z_)
{
    for (auto it = std::next(points.begin()); it != points.end(); it++)
    {
        if      (it->x() < min_x_) min_x_ = it->x();
        else if (it->x() > max_x_) max_x_ = it->x();

        if      (it->y() < min_y_) min_y_ = it->y();
        else if (it->y() > max_y_) max_y_ = it->y();

        if      (it->z() < min_z_) min_z_ = it->z();
        else if (it->z() > max_z_) max_z_ = it->z();        
    }
}

bool BoundingBox::intersects(const BoundingBox &other) const
{
    if (!leq(min_x_, other.max_x_) || !leq(other.min_x_, max_x_) )
        return false;

    if (!leq(min_y_, other.max_y_) || !leq(other.min_y_, max_y_) )
        return false;

    if (!leq(min_z_, other.max_z_) || !leq(other.min_z_, max_z_) )
        return false;

    return true;
}

} // namespace Geom
