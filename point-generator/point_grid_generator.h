//
// Created by maxshavarsky on 25.12.2022.
//

#ifndef ALGORITHMS_POINT_GRID_GENERATOR_H
#define ALGORITHMS_POINT_GRID_GENERATOR_H

#include <vector>
#include "../utils/vector3d.h"

class PointGridGenerator {
public:
    static std::vector<Vector3d> GenerateUniform(const Vector3d &leftBottom, const Vector3d &rightTop, double step);
    static std::vector<Vector3d> GenerateRandom(const Vector3d &leftBottom, const Vector3d &rightTop, size_t size);

private:
    static double RandomNumberInRange(double lowerBound, double upperBound);
};


#endif //ALGORITHMS_POINT_GRID_GENERATOR_H
