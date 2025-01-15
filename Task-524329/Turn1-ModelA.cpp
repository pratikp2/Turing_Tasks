#include <iostream>
#include <memory>

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

// Context that uses the Strategy
class Game {
public:
    Game(std::unique_ptr<DifficultyStrategy> strategy)
        : m_strategy(std::move(strategy)) {}

    void setDifficultyStrategy(std::unique_ptr<DifficultyStrategy> strategy) {
        m_strategy = std::move(strategy);
    }

    void adjustEnemy(Enemy& enemy) {
        m_strategy->adjustEnemyBehavior(enemy);
    }

private:
    std::unique_ptr<DifficultyStrategy> m_strategy;
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

// Main function to demonstrate the usage
int main() {
    Enemy enemy;

    Game game(std::make_unique<EasyDifficulty>());
    game.adjustEnemy(enemy);
    enemy.displayStats();  // Easy: Health = 150, Damage = 5

    game.setDifficultyStrategy(std::make_unique<MediumDifficulty>());
    game.adjustEnemy(enemy);
    enemy.displayStats();  // Medium: Health = 100, Damage = 10

    game.setDifficultyStrategy(std::make_unique<HardDifficulty>());
    game.adjustEnemy(enemy);
    enemy.displayStats();  // Hard: Health = 50, Damage = 20

    return 0;
}
