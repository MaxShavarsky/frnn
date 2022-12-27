//
// Created by maxshavarsky on 25.12.2022.
//

#include "fixed_radius_near_neighbor.h"
#include <iostream>

FixedRadiusNearNeighbor::FixedRadiusNearNeighbor(Metric metric, const std::vector<Vector3d> &points, double r)
    : metric_(metric), points_(points), r_(r)  {

    GridBoundaries();
    FillGrid();

    std::cout  << "Grid size: "<< grid_.size() << "\n";
}

std::vector<size_t> FixedRadiusNearNeighbor::PointNeighbours(const Vector3d &point, double r) const {
    std::vector<size_t> neighbours;
    for (size_t i = 0; i < points_.size(); i++) {
        if (metric_(point, points_[i]) < r)
            neighbours.emplace_back(i);
    }
    return neighbours;
}

std::vector<size_t> FixedRadiusNearNeighbor::PointNeighboursFaster(const Vector3d &point, double r) const {
    std::vector<size_t> neighbours;

    auto xInd = int(point.X() / r_);
    auto yInd = int(point.Y() / r_);
    auto zInd = int(point.Z() / r_);
    Key bucketId = {xInd, yInd, zInd};
    auto it = grid_.at(bucketId); // works like assert here

    auto bucketNeigh = BucketNeighbours(bucketId, true);
    for (const auto &bucket : bucketNeigh) {
        auto toFind = grid_.find(bucket);
        if (toFind != grid_.end())
            for (const auto & pointInd : toFind->second.PointInd)
                if (metric_(points_[pointInd], point) < r)
                    neighbours.emplace_back(pointInd);
    }

    return neighbours;
}

void FixedRadiusNearNeighbor::FillGrid() {
    for (size_t i = 0; i < points_.size(); i++) {
        auto point = points_[i];

        auto xInd = point.X() / r_;
        xInd = xInd > 0 ? std::ceil(xInd) : std::floor(xInd);
        auto yInd = point.Y() / r_;
        yInd = yInd > 0 ? std::ceil(yInd) : std::floor(yInd);
        auto zInd = point.Z() / r_;
        zInd = zInd > 0 ? std::ceil(zInd) : std::floor(zInd);

        Key key = {int(xInd), int(yInd), int(zInd)};
        auto it = grid_.find(key);
        if (it == grid_.end()) {
            Bucket bucket;
            bucket.PointInd.emplace_back(i);
            grid_[key] = bucket;
        } else {
            it->second.PointInd.emplace_back(i);
        }
    }
}

void FixedRadiusNearNeighbor::GridBoundaries() {
    leftBottom_ = Vector3d(1000.0f,1000.0f,1000.0f);
    rightTop_ = Vector3d(-1000.0f,-1000.0f,-1000.0f);

    for (const auto &p : points_) {
        if (p.X() > rightTop_.X())
            rightTop_.X(p.X());

        if (p.Y() > rightTop_.Y())
            rightTop_.Y(p.Y());

        if (p.Z() > rightTop_.Z())
            rightTop_.Z(p.Z());

        if (p.X() < leftBottom_.X())
            leftBottom_.X(p.X());

        if (p.Y() < leftBottom_.Y())
            leftBottom_.Y(p.Y());

        if (p.Z() < leftBottom_.Z())
            leftBottom_.Z(p.Z());
    }

    auto padding = 1.0;

    std::cout << "Left Bottom: " << leftBottom_ << "\n";
    std::cout << "Right Top: " << rightTop_ << "\n";

    leftBottom_.X(leftBottom_.X() - padding);
    leftBottom_.Y(leftBottom_.Y() - padding);
    leftBottom_.Z(leftBottom_.Z() - padding);
    rightTop_.X(rightTop_.X() + padding);
    rightTop_.Y(rightTop_.Y() + padding);
    rightTop_.Z(rightTop_.Z() + padding);

    std::cout << "Left Bottom with padding: " << leftBottom_ << "\n";
    std::cout << "Right Top with padding: " << rightTop_ << "\n";
}


std::vector<Key> FixedRadiusNearNeighbor::BucketNeighbours(const Key &bucketId, bool includeItself) const {
    auto x = bucketId[0];
    auto y = bucketId[1];
    auto z = bucketId[2];

    std::vector<Key> keys;
    if (includeItself) {
        Key k = {x,y,z};
        keys.emplace_back(k);
    }

    for (int dz = z - 1; dz <= z + 1; ++dz)
        for (int dy = y - 1; dy <= y + 1; ++dy)
            for (int dx = x - 1; dx <= x + 1; ++dx)
                if ((dx != x) || (dy != y) || (dz != z)) {
                    Key k = {dx,dy,dz};
                    keys.emplace_back(k);
                }

    return keys;
}

std::map<Key, Bucket> FixedRadiusNearNeighbor::Grid() const {
    return grid_;
}

void FixedRadiusNearNeighbor::GridBoundaries(Vector3d &leftBottom, Vector3d &rightTop) {
    leftBottom = leftBottom_;
    rightTop = rightTop_;
}

