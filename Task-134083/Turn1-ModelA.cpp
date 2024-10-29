
#include <iostream>
#include <dtree.h>

using namespace std;

// Function to create a decision tree for real estate classification
DTree* createDecisionTreeForRealEstate() {
   DTree* tree = dtree_new(DTREE_CLASSIFICATION, 2, "High", "Low");

   // Add attributes
   dtree_add_attribute(tree, "Location", DTYPE_STRING);
   dtree_add_attribute(tree, "Size", DTYPE_REAL);

   // Add nodes and branches
   dtree_node_t* root = dtree_add_node(tree, NULL, "Root");

   dtree_node_t* node1 = dtree_add_node(tree, root, "Location=Urban");
   dtree_add_leaf(tree, node1, "High", 0.8);
   dtree_add_leaf(tree, node1, "Low", 0.2);

   dtree_node_t* node2 = dtree_add_node(tree, root, "Location=Suburban");
   dtree_node_t* node3 = dtree_add_node(tree, node2, "Size<1000");
   dtree_add_leaf(tree, node3, "High", 0.6);
   dtree_add_leaf(tree, node3, "Low", 0.4);

   dtree_node_t* node4 = dtree_add_node(tree, node2, "Size>=1000");
   dtree_add_leaf(tree, node4, "High", 0.4);
   dtree_add_leaf(tree, node4, "Low", 0.6);
   
   return tree;
}

int main() {
   // Create the decision tree
   DTree* tree = createDecisionTreeForRealEstate();

   // Prune the tree using Chi-squared test
   dtree_prune(tree, DTR_PRUNING_CHI2, 0.01);

   // Example input for prediction
   double input[2] = {1.0, 2000.0}; // Location=Urban, Size=2000

   // Predict the class
   const char* predictedClass = dtree_predict(tree, input);
   cout << "Predicted Class: " << predictedClass << endl;

   // Free memory
   dtree_free(tree);
   return 0;
}