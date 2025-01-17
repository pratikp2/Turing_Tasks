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

// Context class that dynamically manages strategies
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
        int damageDealt = combatStrategy->attack() - enemy.defend();
        if (damageDealt > 0) {
            std::cout << name << " attacks " << enemy.getName() << " for " << damageDealt << " damage:\n"
                      << combatStrategy->getAttackDescription() << "\n";
        } else {
            std::cout << name << "'s attack was blocked by " << enemy.getName() << "!\n";
        }
    }

    int defend() {
        std::cout << name << " defends with:\n" << defenseStrategy->getDefenseDescription() << "\n";
        return defenseStrategy->defend();
    }

    void changeMovementStrategy(std::unique_ptr<MovementStrategy> newStrategy) {
        movementStrategy = std::move(newStrategy);
    }

    void changeCombatStrategy(std::unique_ptr<CombatStrategy> newStrategy) {
        combatStrategy = std::move(newStrategy);
    }

    void changeDefenseStrategy(std::unique_ptr<DefenseStrategy> newStrategy) {
        defenseStrategy = std::move(newStrategy);
    }

    const std::string& getName() const {
        return name;
    }

    void displayCurrentStrategies() const {
        std::cout << name << "'s Current Strategies: " 
                  << "\n Movement: "
                  << (dynamic_cast<WarriorMovement*>(movementStrategy.get()) ? "Warrior" :
                      dynamic_cast<MageMovement*>(movementStrategy.get()) ? "Mage" :
                      dynamic_cast<ArcherMovement*>(movementStrategy.get()) ? "Archer" : "None")
                  << "\n Combat: "
                  << (dynamic_cast<WarriorCombat*>(combatStrategy.get()) ? "Warrior" :
                      dynamic_cast<MageCombat*>(combatStrategy.get()) ? "Mage" :
                      dynamic_cast<ArcherCombat*>(combatStrategy.get()) ? "Archer" : "None")
                  << "\n Defense: "
                  << (dynamic_cast<WarriorDefense*>(defenseStrategy.get()) ? "Warrior" :
                      dynamic_cast<MageDefense*>(defenseStrategy.get()) ? "Mage" :
                      dynamic_cast<ArcherDefense*>(defenseStrategy.get()) ? "Archer" : "None")
                  << "\n";
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
    // Create characters
    Character warrior = CharacterFactory::createWarrior();
    Character mage = CharacterFactory::createMage();

    // Display initial strategies
    warrior.displayCurrentStrategies();
    mage.displayCurrentStrategies();

    // Basic Combat Loop
    for (int turn = 0; turn < 3; ++turn) {
        std::cout << "\nTurn " << turn + 1 << ":\n";
        warrior.performMove();
        warrior.performAttack(mage);
        mage.performDefend();
        mage.performMove();
        mage.performAttack(warrior);
        warrior.performDefend();
        
        // Example of changing strategy based on turn or condition (expandable)
        if (turn % 2 == 0) {
            std::cout << "\n" << warrior.getName() << " changes strategies!\n";
            warrior.changeCombatStrategy(std::make_unique<MageCombat>());
            warrior.changeDefenseStrategy(std::make_unique<MageDefense>());
            warrior.displayCurrentStrategies();
        }
    }

    return 0;
}
