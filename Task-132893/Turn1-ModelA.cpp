
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

// 2D Point class for geospatial data
class Point {
public:
	double x;
	double y;

	Point(double x, double y) : x(x), y(y) {}
};

// K-D Tree Node
class KDTreeNode {
public:
	Point point;
	KDTreeNode* left;
	KDTreeNode* right;

	KDTreeNode(Point point) : point(point), left(nullptr), right(nullptr) {}
};

// K-D Tree class
class KDTree {
public:
	KDTree(const std::vector<Point>& points) {
		root = buildKDTree(points, 0);
	}

	~KDTree() {
		deleteTree(root);
	}

	// Find the K nearest neighbors to a given query point
	std::vector<Point> findNearestNeighbors(Point query, int k) {
		std::vector<Point> neighbors;
		std::priority_queue<std::pair<double, Point>, std::vector<std::pair<double, Point>>, std::greater<std::pair<double, Point>>> pq;

		findNearestNeighbors(root, query, k, pq);

		while (!pq.empty()) {
			neighbors.push_back(pq.top().second);
			pq.pop();
		}

		std::reverse(neighbors.begin(), neighbors.end());
		return neighbors;
	}

private:
	KDTreeNode* root;

	KDTreeNode* buildKDTree(const std::vector<Point>& points, int depth) {
		// Base case: If the list is empty, return nullptr
		if (points.empty()) {
			return nullptr;
		}

		// Pick an arbitrary point as the pivot
		int pivotIndex = points.size() / 2;
		Point pivot = points[pivotIndex];

		KDTreeNode* node = new KDTreeNode(pivot);

		// Create left and right subtrees
		std::vector<Point> leftPoints, rightPoints;
		for (size_t i = 0; i < points.size(); i++) {
			if (i == pivotIndex) continue;
			if (shouldGoLeft(points[i], pivot, depth)) {
				leftPoints.push_back(points[i]);
			} else {
				rightPoints.push_back(points[i]);
			}
		}

		node->left = buildKDTree(leftPoints, depth + 1);
		node->right = buildKDTree(rightPoints, depth + 1);

		return node;
	}

	void deleteTree(KDTreeNode* node) {
		if (node) {
			deleteTree(node->left);
			deleteTree(node->right);
			delete node;
		}
	}

	bool shouldGoLeft(const Point& point, const Point& pivot, int depth) {
		if (depth % 2 == 0) {
			return point.x < pivot.x;
		} else {
			return point.y < pivot.y;
		}
	}

	void findNearestNeighbors(KDTreeNode* node, Point query, int k, std::priority_queue<std::pair<double, Point>, std::vector<std::pair<double, Point>>, std::greater<std::pair<double, Point>>>& pq) {
		if (node == nullptr) {
			return;
		}

		double distance = calculateDistance(node->point, query);

		// If the current node's distance is less than the maximum distance in the priority queue, add it to the queue
		if (pq.size() < k || distance < pq.top().first) {
			pq.push({distance, node->point});
			if (pq.size() > k) {
				pq.pop();
			}
		}

		// Recursively search the left and right subtrees
		int axis = (pq.size() % 2 == 0) ? 0 : 1;
		double queryAxisValue = (axis == 0) ? query.x : query.y;
		double nodeAxisValue = (axis == 0) ? node->point.x : node->point.y;

		if (queryAxisValue < nodeAxisValue) {
			findNearestNeighbors(node->left, query, k, pq);
			if (std::abs(queryAxisValue - nodeAxisValue) < pq.top().first) {
				findNearestNeighbors(node->right, query, k, pq);
			}
		} else {
			findNearestNeighbors(node->right, query, k, pq);
			if (std::abs(queryAxisValue - nodeAxisValue) < pq.top().first) {
				findNearestNeighbors(node->left, query, k, pq);
			}
		}
	}

	double calculateDistance(Point p1, Point p2) {
		return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
	}
};

int main() {
	// Sample geospatial data points
	std::vector<Point> points = {
		{1.1, 2.2}, {3.3, 4.4}, {5.5, 6.6}, {7.7, 8.8}, {9.9, 1.1}, {2.2, 3.3}, {4.4, 5.5}, {6.6, 7.7}, {8.8, 1.1}
	};

	// Build the K-D tree
	KDTree kdTree(points);

	// Query point
	Point query(5.0, 6.0);
	int k = 3; // Find 3 nearest neighbors

	// Find nearest neighbors
	std::vector<Point> neighbors = kdTree.findNearestNeighbors(query, k);

	// Display nearest neighbors
	std::cout << "Nearest Neighbors:" << std::endl;
	for (const Point& neighbor : neighbors) {
		std::cout << "(" << neighbor.x << ", " << neighbor.y << ")" << std::endl;
	}
	return 0;
}  