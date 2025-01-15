#include <iostream>
#include <vector>
#include <string>

// Difficulty Level Strategy interface
class DifficultyLevel {
public:
    virtual ~DifficultyLevel() = default;

    virtual void applyDifficulty() = 0;
    virtual std::string getName() const = 0;
};

// Concrete Difficulty Levels (Easy, Medium, Complex)
class EasyDifficulty : public DifficultyLevel {
public:
    void applyDifficulty() override {
        std::cout << "Applying Easy Difficulty:\n";
        std::cout << "Enemy Health: 50\n";
        std::cout << "Enemy Damage: 10\n";
    }
    std::string getName() const override {
        return "Easy";
    }
};

class MediumDifficulty : public DifficultyLevel {
public:
    void applyDifficulty() override {
        std::cout << "Applying Medium Difficulty:\n";
        std::cout << "Enemy Health: 100\n";
        std::cout << "Enemy Damage: 15\n";
    }
    std::string getName() const override {
        return "Medium";
    }
};

class ComplexDifficulty : public DifficultyLevel {
public:
    void applyDifficulty() override {
        std::cout << "Applying Complex Difficulty:\n";
        std::cout << "Enemy Health: 150\n";
        std::cout << "Enemy Damage: 20\n";
    }
    std::string getName() const override {
        return "Complex";
    }
};

// Difficulty Level Manager
class DifficultyLevelManager {
private:
    std::vector<DifficultyLevel*> difficulties;

public:
    DifficultyLevelManager() {
        // Register all available difficulty levels
        registerDifficulty(new EasyDifficulty());
        registerDifficulty(new MediumDifficulty());
        registerDifficulty(new ComplexDifficulty());
    }

    ~DifficultyLevelManager() {
        for (DifficultyLevel* difficulty : difficulties) {
            delete difficulty;
        }
    }

    void registerDifficulty(DifficultyLevel* difficulty) {
        difficulties.push_back(difficulty);
    }

    void applyDifficultyByName(const std::string& name) {
        for (const DifficultyLevel* difficulty : difficulties) {
            if (difficulty->getName() == name) {
                difficulty->applyDifficulty();
                return;
            }
        }
        std::cout << "Difficulty level '" << name << "' not found.\n";
    }

    void printAvailableDifficulties() const {
        std::cout << "Available Difficulty Levels:\n";
        for (const DifficultyLevel* difficulty : difficulties) {
            std::cout << "- " << difficulty->getName() << "\n";
        }
    }
};

int main() {
    DifficultyLevelManager manager;
    manager.printAvailableDifficulties();

    manager.applyDifficultyByName("Medium");

    return 0;
}
