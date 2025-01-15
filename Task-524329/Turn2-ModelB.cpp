#include <iostream>
#include <memory>
#include <string>

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
    void adjustEnemyBehavior(Enemy& enemy) override {
        enemy.setHealth(150);
        enemy.setDamage(5);
    }
};

class MediumDifficulty : public DifficultyStrategy {
public:
    void adjustEnemyBehavior(Enemy& enemy) override {
        enemy.setHealth(100);
        enemy.setDamage(10);
    }
};

class HardDifficulty : public DifficultyStrategy {
public:
    void adjustEnemyBehavior(Enemy& enemy) override {
        enemy.setHealth(50);
        enemy.setDamage(20);
    }
};

// Factory base class
class DifficultyStrategyFactory {
public:
    virtual ~DifficultyStrategyFactory() = default;
    virtual std::unique_ptr<DifficultyStrategy> createDifficultyStrategy(const std::string& difficulty) = 0;
};

// Concrete Factory class
class DefaultDifficultyStrategyFactory : public DifficultyStrategyFactory {
public:
    std::unique_ptr<DifficultyStrategy> createDifficultyStrategy(const std::string& difficulty) override {
        if (difficulty == "Easy") {
            return std::make_unique<EasyDifficulty>();
        } else if (difficulty == "Medium") {
            return std::make_unique<MediumDifficulty>();
        } else if (difficulty == "Hard") {
            return std::make_unique<HardDifficulty>();
        } else {
            std::cout << "Invalid difficulty level: " << difficulty << std::endl;
            return nullptr;
        }
    }
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

// Context that uses the Strategy
class Game {
public:
    Game(std::unique_ptr<DifficultyStrategyFactory> factory)
        : m_factory(std::move(factory)) {}

    void setDifficultyStrategy(const std::string& difficulty) {
        m_strategy = m_factory->createDifficultyStrategy(difficulty);
    }

    void adjustEnemy(Enemy& enemy) {
        if (m_strategy) {
            m_strategy->adjustEnemyBehavior(enemy);
        } else {
            std::cout << "No difficulty strategy set." << std::endl;
        }
    }

private:
    std::unique_ptr<DifficultyStrategyFactory> m_factory;
    std::unique_ptr<DifficultyStrategy> m_strategy;
};

// Main function to demonstrate the usage
int main() {
    Enemy enemy;

    std::unique_ptr<DifficultyStrategyFactory> factory = std::make_unique<DefaultDifficultyStrategyFactory>();
    Game game(std::move(factory));

    game.setDifficultyStrategy("Easy");
    game.adjustEnemy(enemy);
    enemy.displayStats();  // Easy: Health = 150, Damage = 5

    game.setDifficultyStrategy("Medium");
    game.adjustEnemy(enemy);
    enemy.displayStats();  // Medium: Health = 100, Damage = 10

    game.setDifficultyStrategy("Hard");
    game.adjustEnemy(enemy);
    enemy.displayStats();  // Hard: Health = 50, Damage = 20

    game.setDifficultyStrategy("Invalid");
    game.adjustEnemy(enemy);
    enemy.displayStats();  // Should remain unchanged (default values)

    return 0;
}
