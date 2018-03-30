#ifndef QUAT_H
#define QUAT_H
#include <iostream>
#include <istream>
#include <cmath>

double dotProduct(const double x[3], const double y[3]);

class Quat {
private:
    double re;
    double im[3];
public:
    Quat() :
        re(0.),
        im{0., 0., 0.}
    {}
    Quat(double v[4]) :
        re(v[0]),
        im{v[1], v[2], v[3]}
    {}
    Quat(double r, double i[3]) :
        re(r),
        im{i[0], i[1], i[2]}
    {}
    Quat(double a, double b, double c, double d) :
        re(a),
        im{b, c, d}
    {}
    Quat(const Quat &q) :
        re(q.re),
        im{q.im[0], q.im[1], q.im[2]}
    {}
    ~Quat(){}

    Quat conjugate() const {
        return Quat(re, -im[0], -im[1], -im[2]);
    }
    double fabs2() const {
        return re * re + im[0] * im[0] + im[1] * im[1] + im[2] * im[2];
    }
    double fabs() const {
        return sqrt(fabs2());
    }
    Quat operator*(const double d) const{
        return Quat(re * d, im[0] * d, im[1] * d, im[2] * d);
    }
    Quat & operator*=(const double d){
        re *= d;
        for (size_t i = 0; i < 3; ++i)
            im[i] *= d;
        return *this;
    }
    Quat inverse() const {
        return conjugate() * (1. / fabs2());
    }

    Quat & operator=(const Quat &q){
        re = q.re;
        for (int i = 0; i < 3; ++i)
            im[i] = q.im[i];
        return *this;
    }
    Quat operator+(const Quat &q) const{
        double s[3];
        for (int i = 0; i < 3; ++i)
            s[i] = im[i] + q.im[i];
        return Quat(re + q.re, s);
    }
    Quat & operator+=(const Quat &q) {
        re += q.re;
        for (int i = 0; i < 3; ++i)
            im[i] += q.im[i];
        return *this;
    }
    Quat operator-(const Quat &q) const{
        double s[3];
        for (int i = 0; i < 3; ++i)
            s[i] = im[i] - q.im[i];
        return Quat(re - q.re, s);
    }
    Quat & operator-=(const Quat &q) {
        re -= q.re;
        for (int i = 0; i < 3; ++i)
            im[i] -= q.im[i];
        return *this;
    }
    Quat operator*(const Quat &q) const{
        double Re, Im[3];
        Re = re * q.re - dotProduct(im, q.im);
        int j, k;
        for (size_t i = 0; i < 3; ++i) {
            j = (i + 1) % 3;
            k = (i + 2) % 3;
            Im[i] = re * q.im[i] + q.re * im[i] + im[j] * q.im[k] - im[k] * q.im[j];
        }
        return Quat(Re, Im);
    }
    Quat &operator*=(const Quat &q){
        double Re, Im[3];
        Re = re * q.re - dotProduct(im, q.im);
        int j, k;
        for (size_t i = 0; i < 3; ++i) {
            j = (i + 1) % 3;
            k = (i + 2) % 3;
            Im[i] = re * q.im[i] + q.re * im[i] + im[j] * q.im[k] - im[k] * q.im[j];
        }
        re = Re;
        for (size_t i = 0; i < 3; ++i)
            im[i] = Im[i];
        return *this;
    }
    Quat operator/(const Quat &q) const{
        return *this * q.inverse();
    }
    Quat &operator/=(const Quat &q){
        *this *= q.inverse();
        return *this;
    }

    double operator [](int i) const {
        return (i == 0 ? re : im[i - 1]);
    }
    double & operator [](int i) {
        return (i == 0 ? re : im[i - 1]);
    }

    double arg() const {
        return sqrt(atan2(dotProduct(im, im), re));
    }

    friend std::ostream& operator << (std::ostream &s, const Quat &q) {
        s << "(" << q.re << ", ";
        for (int i = 0; i < 3; ++i)
            s << q.im[i] << (i < 2 ? ", " : "") ;
        s << ")";
        return s;
    }
    friend std::istream& operator >> (std::istream &s, Quat& q) {
        s >> q.re;
        for (size_t i = 0; i < 3; ++i)
            s >> q.im[i];
        return s;
    }
};
#endif
