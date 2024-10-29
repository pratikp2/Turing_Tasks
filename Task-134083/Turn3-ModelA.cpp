
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <memory>
#include <fstream>
#include <sstream>

// Additional tip: Use smart pointers to manage memory efficiently
struct TreeNode {
	int attribute;
	double threshold;
	std::vector<std::unique_ptr<TreeNode>> children;
	int classLabel;

	TreeNode() : attribute(-1), threshold(0), classLabel(-1) {}
};

// Function to calculate entropy (remains the same)
// ...

// Function to build the decision tree (remains the same)
// ...

// Function for cost-sensitive pruning (remains the same)
// ...

// Additional tip: Implement online learning for updating the decision tree as new data becomes available
void updateDecisionTree(TreeNode*& root, const std::vector<int>& newLabels, const std::vector<std::vector<int>>& newAttributeValues, double learningRate = 0.1) {
	// Implement the online learning algorithm to update the decision tree based on new data
	// This could involve retraining the tree from scratch or using incremental learning methods
	// For simplicity, let's just retrain the tree for demonstration purposes
	root = buildDecisionTree(newLabels, newAttributeValues, std::vector<int>(newAttributeValues.size()));
}

int main() {
	// Sample data for testing
	std::vector<int> labels = {0, 1, 0, 1, 0, 1};
	std::vector<std::vector<int>> attributeValues = {
		{1, 2, 1, 2, 3, 1},     // Attribute 1 values
		{0, 1, 0, 1, 0, 1},     // Attribute 2 values
		{100, 150, 80, 120, 90, 110} // Attribute 3: Price
	};
	std::vector<int> attributes = {0, 1, 2};

	std::unique_ptr<TreeNode> decisionTree = std::make_unique<TreeNode>();
	decisionTree = buildDecisionTree(labels, attributeValues, attributes);

	// Prune the tree
	std::cout << "Starting pruning process..." << std::endl;
	pruneTree(decisionTree.get(), 0.1);

	// Simulate new data arriving and update the tree
	std::vector<int> newLabels = {1, 0, 1};
	std::vector<std::vector<int>> newAttributeValues = {{2, 1, 120}, {1, 0, 100}, {0, 1, 90}};
	std::cout << "\nUpdating decision tree with new data..." << std::endl;
	updateDecisionTree(decisionTree, newLabels, newAttributeValues);

	// Cleanup is automatic with smart pointers