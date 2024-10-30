#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <unordered_map>

// ... (Rest of the code remains the same)

class KDTree {
public:
	// ... (Rest of the code remains the same)

private:
	// Add a cache to store previously computed distances
	std::unordered_map<std::pair<Point, Point>, double> distanceCache;

	double calculateDistance(Point p1, Point p2) {
		// Check if the distance is already cached
		auto key = std::make_pair(p1, p2);
		auto it = distanceCache.find(key);
		if (it != distanceCache.end()) {
			return it->second;
		}

		double distance = std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));

		// Store the distance in the cache
		distanceCache[key] = distance;
		return distance;
	}
};

int main() {
	// ... (Rest of the code remains the same)
	return 0;
}