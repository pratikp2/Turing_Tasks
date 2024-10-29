#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// Define the TreeNode struct
struct TreeNode {
    int attribute; // Index of the attribute at this node
    double threshold; // Threshold value for the attribute
    std::vector<TreeNode*> children; // Pointers to child nodes
    int classLabel; // Class label if it's a leaf node

    TreeNode() : attribute(-1), threshold(0), classLabel(-1) {}
};

// Function to calculate the entropy of a dataset
double calculateEntropy(const std::vector<int>& labels) {
    int numSamples = labels.size();
    if (numSamples == 0) {
        return 0;
    }

    std::unordered_map<int, int> labelCounts;
    for (int label : labels) {
        labelCounts[label]++;
    }

    double entropy = 0;
    for (const auto& entry : labelCounts) {
        double prob = static_cast<double>(entry.second) / numSamples;
        entropy -= prob * std::log2(prob);
    }

    return entropy;
}

// Function to calculate the information gain for an attribute
double calculateInformationGain(const std::vector<int>& labels, const std::vector<std::vector<int>>& attributeValues, int attribute) {
    double entropyS = calculateEntropy(labels);
    double informationGain = 0;

    int numSamples = labels.size();
    for (int i = 0; i < attributeValues[attribute].size(); i++) {
        std::vector<int> subLabels;
        for (int j = 0; j < numSamples; j++) {
            if (attributeValues[attribute][j] == i) {
                subLabels.push_back(labels[j]);
            }
        }

        double prob = static_cast<double>(subLabels.size()) / numSamples;
        informationGain += prob * calculateEntropy(subLabels);
    }

    return entropyS - informationGain;
}

// Function to build the decision tree using ID3 algorithm
TreeNode* buildDecisionTree(const std::vector<int>& labels, const std::vector<std::vector<int>>& attributeValues, const std::vector<int>& attributes) {
    // Base case: If all samples belong to the same class, return a leaf node
    if (std::all_of(labels.begin(), labels.end(), [&](int label) { return label == labels[0]; })) {
        TreeNode* node = new TreeNode();
        node->classLabel = labels[0];
        return node;
    }

    // Base case: If there are no more attributes to split on, return a leaf node with the majority class label
    if (attributes.empty()) {
        TreeNode* node = new TreeNode();
        node->classLabel = std::distance(labels.begin(), std::max_element(labels.begin(), labels.end()));
        return node;
    }

    // Find the attribute that maximizes the information gain
    double maxInformationGain = 0;
    int bestAttribute = -1;
    for (int attribute : attributes) {
        double informationGain = calculateInformationGain(labels, attributeValues, attribute);
        if (informationGain > maxInformationGain) {
            maxInformationGain = informationGain;
            bestAttribute = attribute;
        }
    }

    // Create a new node with the best attribute
    TreeNode* node = new TreeNode();
    node->attribute = bestAttribute;