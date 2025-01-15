#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

// Forward declaration
class Enemy;

// Abstract base class for Difficulty Strategy
class DifficultyStrategy {
public:
    virtual ~DifficultyStrategy() = default;
    virtual void adjustEnemyBehavior(Enemy& enemy) = 0;
};

// Concrete Strategy classes for each difficulty level
class EasyDifficulty : public DifficultyStrategy {
public:
    void adjustEnemyBehavior(Enemy& enemy) override;
};

class MediumDifficulty : public DifficultyStrategy {
public:
    void adjustEnemyBehavior(Enemy& enemy) override;
};

class HardDifficulty : public DifficultyStrategy {
public:
    void adjustEnemyBehavior(Enemy& enemy) override;
};

// The enemy class
class Enemy {
public:
    void setHealth(int health) { m_health = health; }
    void setDamage(int damage) { m_damage = damage; }

    void displayStats() const {
        std::cout << "Enemy Health: " << m_health << ", Damage: " << m_damage << std::endl;
    }

private:
    int m_health{100};
    int m_damage{10};
};

// Factory for creating Difficulty Strategy instances
class DifficultyFactory {
public:
    static std::unique_ptr<DifficultyStrategy> createDifficultyStrategy(const std::string& difficultyLevel) {
        if (difficultyLevel == "easy") {
            return std::make_unique<EasyDifficulty>();
        } else if (difficultyLevel == "medium") {
            return std::make_unique<MediumDifficulty>();
        } else if (difficultyLevel == "hard") {
            return std::make_unique<HardDifficulty>();
        } else {
            throw std::invalid_argument("Invalid difficulty level");
        }
    }
};

// Observer Interface
class Observer {
public:
    virtual ~Observer() = default;
    virtual void onDifficultyChanged(const std::string& newDifficulty) = 0;
};

// Subject Interface
class DifficultySubject {
public:
    virtual ~DifficultySubject() = default;
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify() = 0;
};

// Singleton Game class (Context) that uses the Strategy
class Game : public DifficultySubject {
public:
    // Singleton Accessor
    static Game& getInstance() {
        static Game instance; // Guaranteed to be destroyed and instantiated on first use.
        return instance;
    }

    Game(const Game&) = delete; // Disable copy constructor
    Game& operator=(const Game&) = delete; // Disable assignment operator

    void setDifficultyStrategy(std::unique_ptr<DifficultyStrategy> strategy, const std::string& difficultyLevel) {
        m_strategy = std::move(strategy);
        m_difficultyLevel = difficultyLevel;
        notify();  // Notify observers when difficulty changes
    }

    void adjustEnemy(Enemy& enemy) {
        m_strategy->adjustEnemyBehavior(enemy);
    }

    void attach(Observer* observer) override {
        observers.push_back(observer);
    }

    void detach(Observer* observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify() override {
        for (auto* observer : observers) {
            observer->onDifficultyChanged(m_difficultyLevel);
        }
    }

private:
    // Private constructor ensures Singleton
    Game() : m_strategy(DifficultyFactory::createDifficultyStrategy("medium")), m_difficultyLevel("medium") {}

    std::unique_ptr<DifficultyStrategy> m_strategy;
    std::string m_difficultyLevel;
    std::vector<Observer*> observers;  // List of observers
};

// Implementation of the difficulty strategies
void EasyDifficulty::adjustEnemyBehavior(Enemy& enemy) {
    enemy.setHealth(150);
    enemy.setDamage(5);
}

void MediumDifficulty::adjustEnemyBehavior(Enemy& enemy) {
    enemy.setHealth(100);
    enemy.setDamage(10);
}

void HardDifficulty::adjustEnemyBehavior(Enemy& enemy) {
    enemy.setHealth(50);
    enemy.setDamage(20);
}

// Concrete Observer classes
class UI : public Observer {
public:
    void onDifficultyChanged(const std::string& newDifficulty) override {
        std::cout << "UI updated for difficulty level: " << newDifficulty << std::endl;
    }
};

class AudioSettings : public Observer {
public:
    void onDifficultyChanged(const std::string& newDifficulty) override {
        std::cout << "Audio settings adjusted for difficulty level: " << newDifficulty << std::endl;
    }
};

// Main function to demonstrate the usage
int main() {
    Enemy enemy;

    // Access the Game singleton instance
    Game& game = Game::getInstance();

    // Create observers
    UI ui;
    AudioSettings audioSettings;

    // Attach observers to the game
    game.attach(&ui);
    game.attach(&audioSettings);

    // Adjust enemy based on initial difficulty
    game.adjustEnemy(enemy);
    enemy.displayStats();  // Displays enemy stats for default (medium) level

    // Change difficulty and observe notifications
    game.setDifficultyStrategy(DifficultyFactory::createDifficultyStrategy("hard"), "hard");
    game.adjustEnemy(enemy);
    enemy.displayStats();  // Displays enemy stats for hard level

    game.setDifficultyStrategy(DifficultyFactory::createDifficultyStrategy("easy"), "easy");
    game.adjustEnemy(enemy);
    enemy.displayStats();  // Displays enemy stats for easy level

    return 0;
}
