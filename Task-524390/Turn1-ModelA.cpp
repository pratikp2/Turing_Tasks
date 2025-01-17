#include <iostream>
#include <memory>
#include <vector>

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
    virtual void attack() = 0;
    virtual ~CombatStrategy() = default;
};

// Concrete Strategies for Combat
class WarriorCombat : public CombatStrategy {
public:
    void attack() override {
        std::cout << "Warrior swings a mighty sword!\n";
    }
};

class MageCombat : public CombatStrategy {
public:
    void attack() override {
        std::cout << "Mage casts a powerful spell!\n";
    }
};

class ArcherCombat : public CombatStrategy {
public:
    void attack() override {
        std::cout << "Archer fires an arrow with deadly precision!\n";
    }
};

// Abstract Strategy for Defense
class DefenseStrategy {
public:
    virtual void defend() = 0;
    virtual ~DefenseStrategy() = default;
};

// Concrete Strategies for Defense
class WarriorDefense : public DefenseStrategy {
public:
    void defend() override {
        std::cout << "Warrior raises shield to block the attack!\n";
    }
};

class MageDefense : public DefenseStrategy {
public:
    void defend() override {
        std::cout << "Mage casts a shield spell!\n";
    }
};

class ArcherDefense : public DefenseStrategy {
public:
    void defend() override {
        std::cout << "Archer dodges swiftly!\n";
    }
};

// Context class that uses the strategies
class Character {
private:
    std::unique_ptr<MovementStrategy> movementStrategy;
    std::unique_ptr<CombatStrategy> combatStrategy;
    std::unique_ptr<DefenseStrategy> defenseStrategy;

public:
    Character(std::unique_ptr<MovementStrategy> movement,
              std::unique_ptr<CombatStrategy> combat,
              std::unique_ptr<DefenseStrategy> defense)
        : movementStrategy(std::move(movement)),
          combatStrategy(std::move(combat)),
          defenseStrategy(std::move(defense)) {}

    void performMove() {
        movementStrategy->move();
    }
    
    void performAttack() {
        combatStrategy->attack();
    }
    
    void performDefense() {
        defenseStrategy->defend();
    }
};

// Factory to create Characters based on type
class CharacterFactory {
public:
    static Character createWarrior() {
        return Character(std::make_unique<WarriorMovement>(),
                         std::make_unique<WarriorCombat>(),
                         std::make_unique<WarriorDefense>());
    }

    static Character createMage() {
        return Character(std::make_unique<MageMovement>(),
                         std::make_unique<MageCombat>(),
                         std::make_unique<MageDefense>());
    }

    static Character createArcher() {
        return Character(std::make_unique<ArcherMovement>(),
                         std::make_unique<ArcherCombat>(),
                         std::make_unique<ArcherDefense>());
    }
};

int main() {
    // Example user selection
    int characterType;
    std::cout << "Select a character type (1: Warrior, 2: Mage, 3: Archer): ";
    std::cin >> characterType;

    Character character;
    
    switch (characterType) {
        case 1:
            character = CharacterFactory::createWarrior();
            break;
        case 2:
            character = CharacterFactory::createMage();
            break;
        case 3:
            character = CharacterFactory::createArcher();
            break;
        default:
            std::cout << "Invalid selection!\n";
            return 1;
    }

    // Perform actions
    character.performMove();
    character.performAttack();
    character.performDefense();

    return 0;
}
