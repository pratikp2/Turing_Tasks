#include <iostream>
#include <memory>
#include <string>
#include <random>

// Abstract Strategy for Movement
class MovementStrategy {
public:
    virtual void move() = 0;
    virtual ~MovementStrategy() = default;
};

// Concrete Strategies for Movement
class WarriorMovement : public MovementStrategy {
public:
    void move() override {
        std::cout << "Warrior moves with heavy steps.\n";
    }
};

class MageMovement : public MovementStrategy {
public:
    void move() override {
        std::cout << "Mage floats gracefully.\n";
    }
};

class ArcherMovement : public MovementStrategy {
public:
    void move() override {
        std::cout << "Archer moves swiftly and silently.\n";
    }
};

// Abstract Strategy for Combat
class CombatStrategy {
public:
    virtual int attack() = 0;
    virtual std::string getAttackDescription() = 0;
    virtual ~CombatStrategy() = default;
};

// Concrete Strategies for Combat
class WarriorCombat : public CombatStrategy {
public:
    int attack() override {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(10, 20);
        return dist(gen); // Generate random damage between 10 and 20
    }

    std::string getAttackDescription() override {
        return "Warrior swings a mighty sword!";
    }
};

class MageCombat : public CombatStrategy {
public:
    int attack() override {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(20, 30);
        return dist(gen); // Generate random damage between 20 and 30
    }

    std::string getAttackDescription() override {
        return "Mage casts a powerful fireball!";
    }
};

class ArcherCombat : public CombatStrategy {
public:
    int attack() override {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(15, 25);
        return dist(gen); // Generate random damage between 15 and 25
    }

    std::string getAttackDescription() override {
        return "Archer fires an arrow with deadly precision!";
    }
};

// Abstract Strategy for Defense
class DefenseStrategy {
public:
    virtual int defend() = 0;
    virtual std::string getDefenseDescription() = 0;
    virtual ~DefenseStrategy() = default;
};

// Concrete Strategies for Defense
class WarriorDefense : public DefenseStrategy {
public:
    int defend() override {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(5, 15);
        return dist(gen); // Generate random defense value between 5 and 15
    }

    std::string getDefenseDescription() override {
        return "Warrior raises shield to block the attack!";
    }
};

class MageDefense : public DefenseStrategy {
public:
    int defend() override {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(10, 20);
        return dist(gen); // Generate random defense value between 10 and 20
    }

    std::string getDefenseDescription() override {
        return "Mage casts a shield spell!";
    }
};

class ArcherDefense : public DefenseStrategy {
public:
    int defend() override {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(8, 18);
        return dist(gen); // Generate random defense value between 8 and 18
    }

    std::string getDefenseDescription() override {
        return "Archer dodges swiftly!";
    }
};

// Context class that uses the strategies
class Character {
private:
    std::unique_ptr<MovementStrategy> movementStrategy;
    std::unique_ptr<CombatStrategy> combatStrategy;
    std::unique_ptr<DefenseStrategy> defenseStrategy;
    std::string name;

public:
    Character(const std::string& name,
              std::unique_ptr<MovementStrategy> movement,
              std::unique_ptr<CombatStrategy> combat,
              std::unique_ptr<DefenseStrategy> defense)
        : name(name), movementStrategy(std::move(movement)),
          combatStrategy(std::move(combat)), defenseStrategy(std::move(defense)) {}

    void performMove() {
        movementStrategy->move();
    }

    void performAttack(Character& enemy) {
        int damageDealt = combatStrategy->attack() - enemy.defenseStrategy->defend();
        if (damageDealt > 0) {
            std::cout << name << " attacks " << enemy.name << " for " << damageDealt << " damage:\n"
                      << combatStrategy->getAttackDescription() << "\n"
                      << enemy.name << " defends with:\n"
                      << enemy.defenseStrategy->getDefenseDescription() << "\n";
        } else {
            std::cout << name << "'s attack was blocked by " << enemy.name << "!\n";
        }
    }

    void performDefense() {
        std::cout << name << " defends:\n"
                  << defenseStrategy->getDefenseDescription() << "\n";
    }
};

// Factory to create Characters based on type
class CharacterFactory {
public:
    static Character createWarrior() {
        return Character("Warrior",
                         std::make_unique<WarriorMovement>(),
                         std::make_unique<WarriorCombat>(),
                         std::make_unique<WarriorDefense>());
    }

    static Character createMage() {
        return Character("Mage",
                         std::make_unique<MageMovement>(),
                         std::make_unique<MageCombat>(),
                         std::make_unique<MageDefense>());
    }

    static Character createArcher() {
        return Character("Archer",
                         std::make_unique<ArcherMovement>(),
                         std::make_unique<ArcherCombat>(),
                         std::make_unique<ArcherDefense>());
    }
};

int main() {
    Character warrior = CharacterFactory::createWarrior();
    Character mage = CharacterFactory::createMage();

    warrior.performMove();
    warrior.performAttack(mage);
    mage.performDefense();
    mage.performAttack(warrior);

    return 0;
}
