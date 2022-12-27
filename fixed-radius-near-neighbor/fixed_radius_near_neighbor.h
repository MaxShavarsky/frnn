//
// Created by maxshavarsky on 25.12.2022.
//

#ifndef ALGORITHMS_FIXED_RADIUS_NEAR_NEIGHBOR_H
#define ALGORITHMS_FIXED_RADIUS_NEAR_NEIGHBOR_H

#include <vector>
#include <map>
#include <iostream>
#include <functional>
#include <cmath>
#include "../utils/vector3d.h"


struct Bucket {
    std::vector<size_t> PointInd;
};

typedef const std::function<double(const Vector3d &, const Vector3d &)> & Metric;
typedef std::vector<int> Key;

class FixedRadiusNearNeighbor {
public:
    explicit FixedRadiusNearNeighbor(Metric metric, const std::vector<Vector3d> & points, double r);

    [[nodiscard]] std::vector<size_t> PointNeighbours(const Vector3d &point, double r) const;
    [[nodiscard]] std::vector<size_t> PointNeighboursFaster(const Vector3d &point, double r) const;

    [[nodiscard]] std::map<Key, Bucket> Grid() const;

    void GridBoundaries(Vector3d &leftBottom, Vector3d &rightTop);

private:
    void FillGrid();
    void GridBoundaries();

    [[nodiscard]] std::vector<Key> BucketNeighbours(const Key &bucketId, bool includeItself = false) const;
private:
    Vector3d leftBottom_, rightTop_;
    std::map<Key, Bucket> grid_;

    Metric metric_;
    std::vector<Vector3d> points_;
    double r_;
};


#endif //ALGORITHMS_FIXED_RADIUS_NEAR_NEIGHBOR_H
