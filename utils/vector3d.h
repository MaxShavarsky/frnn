//
// Created by maxshavarsky on 25.12.2022.
//

#ifndef ALGORITHMS_VECTOR3D_H
#define ALGORITHMS_VECTOR3D_H

#include <cmath>
#include <iostream>

class Vector3d {
public:
    Vector3d() = default;
    Vector3d(double x, double y, double z) : x_(x), y_(y), z_(z) {}


    Vector3d operator-(const Vector3d& in) const {
        return Vector3d(x_ - in.x_, y_ - in.y_, z_ - in.z_);
    }

    double Norm() {
        return sqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2));
    }

    [[nodiscard]] double X() const {
        return x_;
    }

    [[nodiscard]] double Y() const {
        return y_;
    }

    [[nodiscard]] double Z() const {
        return z_;
    }

    void X(double x) {
        x_ = x;
    }

    void Y(double y) {
        y_ = y;
    }

    void Z(double z) {
        z_ = z;
    }

private:
    double x_ = 0, y_ = 0, z_ = 0;
};

inline std::ostream& operator<<(std::ostream& os, const Vector3d& obj) {
    os << "x:" << obj.X() << " y: " << obj.Y() << " z:" << obj.Z();
    return os;
}


#endif //ALGORITHMS_VECTOR3D_H
