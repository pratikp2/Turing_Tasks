#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Forward declaration
class Enemy;

// Interface for observers
class Observer {
public:
    virtual ~Observer() = default;
    virtual void updateDifficulty() = 0;
};

// Abstract base class for Difficulty Strategy
class DifficultyStrategy {
public:
    virtual ~DifficultyStrategy() = default;
    virtual void adjustEnemyBehavior(Enemy& enemy) = 0;
    virtual void addObserver(Observer* observer) { m_observers.push_back(observer); }
    virtual void removeObserver(Observer* observer) {
        auto it = std::find(m_observers.begin(), m_observers.end(), observer);
        if (it != m_observers.end()) {
            m_observers.erase(it);
        }
    }
    virtual void notifyObservers() {
        for (const auto& observer : m_observers) {
            observer->updateDifficulty();
        }
    }

protected:
    std::vector<Observer*> m_observers;
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

// Game class (Context) that uses the Strategy
class Game {
public:
    Game(std::unique_ptr<DifficultyStrategy> strategy)
        : m_strategy(std::move(strategy)) {}

    void setDifficultyStrategy(std::unique_ptr<DifficultyStrategy> strategy) {
        m_strategy = std::move(strategy);
        m_strategy->notifyObservers(); // Notify observers when difficulty changes
    }

    void adjustEnemy(Enemy& enemy) {
        m_strategy->adjustEnemyBehavior(enemy);
    }

    std::unique_ptr<DifficultyStrategy> getStrategy() const { return m_strategy; }

private:
    std::unique_ptr<DifficultyStrategy> m_strategy;
};

// Example: UI class that acts as an Observer
class UIComponent : public Observer {
public:
    UIComponent(Game& game) { game.getStrategy()->addObserver(this); }
    void updateDifficulty() override {
        std::cout << "UI Updated: Difficulty level changed." << std::endl;
        // Perform UI updates here, such as updating difficulty text or indicators
    }
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

    std::string playerPreference = "medium";

    Game game(DifficultyFactory::createDifficultyStrategy(playerPreference));
    UIComponent ui(game);

    game.adjustEnemy(enemy);
    enemy.displayStats(); // Enemy stats set to Medium difficulty

    // Change difficulty level at runtime
    playerPreference = "hard";
    game.setDifficultyStrategy(DifficultyFactory::createDifficultyStrategy(playerPreference));

    game.adjustEnemy(enemy);
    enemy.displayStats(); // Enemy stats set to Hard difficulty

    return 0;
}
