#pragma once

namespace Geom
{

// if one of parameters of the constructor is NaN
class ExceptionNaNCtorParam {};

class Point3D
{
private:
    double x_, y_, z_;
public:
    Point3D(double x, double y, double z);

    double x() const {return x_;};
    double y() const {return y_;};
    double z() const {return z_;};
};

class Vector3D
{
private:
    double x_, y_, z_;
public:
    Vector3D(double x, double y, double z);

    double x() const {return x_;};
    double y() const {return y_;};
    double z() const {return z_;};

    Vector3D& operator+=(const Vector3D& rhs);

    //Vector3D norm();
};

Vector3D operator+(const Vector3D& lhs, const Vector3D& rhs);


// class Plane3D
// {
// private:
//     Vector3D n_vec;
//     Point3D p;
// public:
//     Plane3D(Vector3D n_vec, Point3D p);
// };

} // namespace Geom