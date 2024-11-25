#include <iostream>
#include <vector>
#include <string>

// Base interface for scene graph nodes
class SceneNode {
public:
    virtual ~SceneNode() {}
    virtual void draw() const = 0;
    virtual void addChild(SceneNode* child) = 0;
    virtual void removeChild(SceneNode* child) = 0;
    virtual int getNumChildren() const = 0;
    virtual SceneNode* getChild(int index) const = 0;
};

// Leaf node: a simple object to be rendered
class MeshNode : public SceneNode {
public:
    MeshNode(const std::string& name) : name_(name) {}
    ~MeshNode() {}

    void draw() const override {
        std::cout << "Drawing mesh: " << name_ << std::endl;
    }

    void addChild(SceneNode* child) override {
        throw std::runtime_error("MeshNode cannot have children");
    }

    void removeChild(SceneNode* child) override {
        throw std::runtime_error("MeshNode cannot have children");
    }

    int getNumChildren() const override {
        return 0;
    }

    SceneNode* getChild(int index) const override {
        throw std::runtime_error("MeshNode cannot have children");
    }

private:
    std::string name_;
};

// Composite node: a group of scene graph nodes
class GroupNode : public SceneNode {
public:
    GroupNode() {}
    ~GroupNode() {}

    void draw() const override {
        for (const auto& child : children_) {
            child->draw();
        }
    }

    void addChild(SceneNode* child) override {
        children_.push_back(child);
    }

    void removeChild(SceneNode* child) override {
        children_.erase(std::remove_if(children_.begin(), children_.end(), [child](const auto& node) {
            return node.get() == child;
        }), children_.end());
    }

    int getNumChildren() const override {
        return children_.size();
    }

    SceneNode* getChild(int index) const override {
        if (index < 0 || index >= children_.size()) {
            throw std::runtime_error("Index out of bounds");
        }
        return children_[index];
    }

private:
    std::vector<SceneNode*> children_;
};

// Example usage
int main() {
    GroupNode* root = new GroupNode();
    MeshNode* cube = new MeshNode("Cube");
    MeshNode* sphere = new MeshNode("Sphere");
    GroupNode* car = new GroupNode();
    MeshNode* carBody = new MeshNode("CarBody");
    MeshNode* carWheel = new MeshNode("CarWheel");

    root->addChild(cube);
    root->addChild(sphere);
    root->addChild(car);

    car->addChild(carBody);
    car->addChild(carWheel);
    car->addChild(carWheel);
    car->addChild(carWheel);
    car->addChild(carWheel);

    // Draw the entire scene graph
    root->draw();

    delete cube;
    delete sphere;
    delete car;
    delete carBody;
    delete carWheel;
    delete root;

    return 0;
}