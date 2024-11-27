#include <iostream>
#include <memory>
#include <string>

class TreeNode {
public:
    TreeNode(const std::string& value) : value(value), parent(nullptr) {}

    void addChild(const std::shared_ptr<TreeNode>& child) {
        children.push_back(child);
    }

    std::shared_ptr<TreeNode> getParent() const { return parent; }
    void setParent(const std::shared_ptr<TreeNode>& parent) { this->parent = parent; }

    const std::string& getValue() const { return value; }

    void printNode() const {
        if (parent) {
            std::cout << "Parent: " << parent->getValue() << " ";
        }
        std::cout << value << std::endl;
    }

private:
    std::string value;
    std::vector<std::shared_ptr<TreeNode>> children;
    std::shared_ptr<TreeNode> parent;
};

int main() {
    auto root = std::make_shared<TreeNode>("Root");
    auto child1 = std::make_shared<TreeNode>("Child1");
    auto child2 = std::make_shared<TreeNode>("Child2");
    auto child3 = std::make_shared<TreeNode>("Child3");

    root->addChild(child1);
    root->addChild(child2);
    child1->addChild(child3);

    child1->setParent(root);
    child2->setParent(root);
    child3->setParent(child1);

    // Print the tree
    root->printNode();
    child1->printNode();
    child2->printNode();
    child3->printNode();

    // Even if the root is destroyed first, the children remain in memory
    root = nullptr;  

    // Accessing children still works
    child1->printNode();
    child2->printNode();
    child3->printNode();

    // Even child1 can be destroyed before child3
    child1 = nullptr;

    // child3 still exists and can be accessed and printed
    child3->printNode();

    return 0;
}