#include <iostream>
#include <vector>

class SceneNode {
public:
    virtual ~SceneNode() = default;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void addChild(SceneNode* child) = 0;
    virtual void removeChild(SceneNode* child) = 0;
};

class LeafNode : public SceneNode {
public:
    void update(float deltaTime) override {
        // Update the leaf node's state here
    }

    void render() override {
        // Render the leaf node here
    }

    void addChild(SceneNode* child) override {
        // Leaf nodes cannot have children, so do nothing
    }

    void removeChild(SceneNode* child) override {
        // Leaf nodes cannot have children, so do nothing
    }
};

class CompositeNode : public SceneNode {
private:
    std::vector<SceneNode*> children;

public:
    void update(float deltaTime) override {
        // Update the composite node's state here
        // Then, update the state of all its children
        for (SceneNode* child : children) {
            child->update(deltaTime);
        }
    }

    void render() override {
        // Render the composite node here
        // Then, render all its children
        for (SceneNode* child : children) {
            child->render();
        }
    }

    void addChild(SceneNode* child) override {
        children.push_back(child);
    }

    void removeChild(SceneNode* child) override {
        children.erase(std::remove(children.begin(), children.end(), child), children.end());
    }
};

int main() {
    // Create the root node of the scene graph
    CompositeNode* root = new CompositeNode();

    // Create some leaf nodes
    LeafNode* leaf1 = new LeafNode();
    LeafNode* leaf2 = new LeafNode();
    LeafNode* leaf3 = new LeafNode();

    // Create a composite node to hold some leaf nodes
    CompositeNode* composite1 = new CompositeNode();
    composite1->addChild(leaf1);
    composite1->addChild(leaf2);

    // Add the composite node and a leaf node to the root node
    root->addChild(composite1);
    root->addChild(leaf3);

    // Update and render the scene graph
    root->update(1.0f);
    root->render();

    // Clean up the scene graph
    delete root;

    return 0;
}