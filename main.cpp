//
// Created by maxshavarsky on 25.12.2022.
//

#include "fixed-radius-near-neighbor/fixed_radius_near_neighbor.h"
#include "plotter/plotter.h"
#include "point-generator/point_grid_generator.h"

void Vector3dToVector1d(const std::vector<Vector3d>& points,
        std::vector<double> &x,
        std::vector<double> &y,
        std::vector<double> &z) {
    for (const auto &point : points) {
        x.emplace_back(point.X());
        y.emplace_back(point.Y());
        z.emplace_back(point.Z());
    }
}

void Vector3dToVector1d(const std::vector<Vector3d>& points,
                        const std::vector<size_t>& indexes,
                        std::vector<double> &x,
                        std::vector<double> &y,
                        std::vector<double> &z) {
    for (const auto & index : indexes) {
        auto point = points[index];

        x.emplace_back(point.X());
        y.emplace_back(point.Y());
        z.emplace_back(point.Z());
    }
}

int main() {
    std::vector<Vector3d> points = {
            {1, 1, 0},
            {-1, -1, 0},
            {1, 2, 0},
            {-1, 5, 0},
            {-5, 3, 0},
            {-5, 1, 0},
            {3, -1, 0},
            {2, -4, 0},
            {2.5, -0.5, 0},
            {0.5, 1.5, 0},
            {-4.5, 2.5, 0},
            {1.5, 0.5, 0},
            {-1.7, 1.99, 0},
    };

    points = PointGridGenerator::GenerateUniform({-5., -5., 0.}, {5., 5., 0.25}, 0.25);

    FixedRadiusNearNeighbor f([](const Vector3d& p1, const Vector3d& p2){ return (p2-p1).Norm(); }, points, 2.0);

    Vector3d leftBottom, rightTop;
    f.GridBoundaries(leftBottom, rightTop);

    Plotter plotter(leftBottom, rightTop, 800.0, 600.0);

    auto grid = f.Grid();
    for (const auto &bucket : grid) {
        std::vector<double> x,y,z;
        Vector3dToVector1d(points, bucket.second.PointInd, x, y, z);
        plotter.AddSeries(x, y);

        std::cout << "Bucket Id [" << bucket.first[0] << " " << bucket.first[1] << " " << bucket.first[2] << "]\n";
        for (const auto &neigh : bucket.second.PointInd)
            std::cout << "\tPoint [" << points[neigh] << "]\n";
        std::cout << "\n";
    }

    plotter.Plot();
    plotter.ConvertToPng("C:\\Users\\maxshavarsky\\CLionProjects\\algorithms\\plotter\\plots\\frnn.png");

    return 0;
}
