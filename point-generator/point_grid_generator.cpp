//
// Created by maxshavarsky on 25.12.2022.
//

#include <random>
#include "point_grid_generator.h"

std::vector<Vector3d> PointGridGenerator::GenerateUniform(const Vector3d &leftBottom, const Vector3d &rightTop, double step) {
    std::vector<Vector3d> points;
    for (double dx = leftBottom.X(); dx < rightTop.X(); dx += step) {
        for (double dy = leftBottom.Y(); dy < rightTop.Y(); dy += step) {
            for (double dz = leftBottom.Z(); dz < rightTop.Z(); dz += step) {
                Vector3d p = {dx, dy, dz};
                points.emplace_back(p);
            }
        }
    }

    return points;
}

std::vector<Vector3d>
PointGridGenerator::GenerateRandom(const Vector3d &leftBottom, const Vector3d &rightTop, size_t size) {
    std::vector<Vector3d> result;

    for (size_t i = 0; i < size; i++) {
        auto x = RandomNumberInRange(leftBottom.X(), rightTop.X());
        auto y = RandomNumberInRange(leftBottom.Y(), rightTop.Y());
        auto z = RandomNumberInRange(leftBottom.Z(), rightTop.Z());
        result.emplace_back(x,y,z);
    }

    return result;
}

double PointGridGenerator::RandomNumberInRange(double lowerBound, double upperBound) {
    static std::mt19937 rng{ std::random_device{}() };
    std::uniform_real_distribution<double> unif(lowerBound,upperBound);
    return unif(rng);
}
