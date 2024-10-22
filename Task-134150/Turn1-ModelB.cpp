
#include <iostream>
#include <vector>
#include <algorithm>
#include <Eigen/Dense>

using namespace Eigen;

// Pure function to calculate drag for a single point
double calculateDrag(const Vector3d& point, const Vector3d& velocity, const double& lift) {
    const Vector3d relativeVelocity = velocity - point.cross(lift);
    return relativeVelocity.squaredNorm();
}

// Pure function to calculate drag for a list of points using map
std::vector<double> calculateDragForPoints(const std::vector<Vector3d>& points, const Vector3d& velocity, const double& lift) {
    return std::vector<double>(points.size(), [&](size_t i) { return calculateDrag(points[i], velocity, lift); });
}

// Pure function to filter points based on a drag threshold
std::vector<Vector3d> filterPointsByDrag(const std::vector<Vector3d>& points, const std::vector<double>& drag, const double& threshold) {
    return std::vector<Vector3d>(points.size(), [&](size_t i) { return drag[i] > threshold ? points[i] : Vector3d::Zero(); });
}

// Pure function to calculate total drag using reduce
double calculateTotalDrag(const std::vector<double>& drag) {
    return std::accumulate(drag.begin(), drag.end(), 0.0);
}

int main() {
    // Initialize wing geometry and flow conditions
    const int numPoints = 1000;
    const Vector3d wingSpan(10.0, 0.0, 0.0);
    const Vector3d velocity(100.0, 0.0, 0.0);
    const double lift = 1000.0;
    const double dragThreshold = 100.0;

    // Generate random points on the wing
    std::vector<Vector3d> points;
    for (int i = 0; i < numPoints; ++i) {
        double x = static_cast<double>(i) / (numPoints - 1) * wingSpan.x();
        points.push_back(Vector3d(x, 0.0, 0.0));
    }

    // Calculate drag for each point using map
    std::vector<double> drag = calculateDragForPoints(points, velocity, lift);

    // Filter points based on drag threshold using filter
    std::vector<Vector3d> filteredPoints = filterPointsByDrag(points, drag, dragThreshold);

    // Calculate total drag using reduce
    double totalDrag = calculateTotalDrag(drag);

    // Print results
    std::cout << "Total drag: " << totalDrag << std::endl;
    std::cout << "Number of filtered points: " << filteredPoints.size() << std::endl;

    return 0;
}
