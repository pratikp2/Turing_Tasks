#include <iostream>
#include <string>
#include <memory>

// Abstract Strategy class for Movement mechanics
class MovementStrategy {
public:
    virtual ~MovementStrategy() = default;
    virtual void move(float speed) = 0;
};

// Concrete Strategy: Warrior Movement (slow but steady)
class WarriorMovementStrategy : public MovementStrategy {
public:
    void move(float speed) override {
        std::cout << "Warrior moves at " << speed << " units per second." << std::endl;
    }
};

// Concrete Strategy: Mage Movement (faster but slower turning)
class MageMovementStrategy : public MovementStrategy {
public:
    void move(float speed) override {
        std::cout << "Mage moves at " << speed * 1.2f << " units per second." << std::endl;
    }
};

// Abstract Strategy class for Combat Attack mechanics
class CombatAttackStrategy {
public:
    virtual ~CombatAttackStrategy() = default;
    virtual void attack() = 0;
};

// Concrete Strategy: Warrior Combat Attack (melee)
class WarriorCombatAttackStrategy : public CombatAttackStrategy {
public:
    void attack() override {
        std::cout << "Warrior performs a melee attack." << std::endl;
    }
};

// Concrete Strategy: Mage Combat Attack (spell)
class MageCombatAttackStrategy : public CombatAttackStrategy {
public:
    void attack() override {
        std::cout << "Mage casts a fireball spell." << std::endl;
    }
};

// Abstract Strategy class for Defensive Action mechanics
class DefensiveActionStrategy {
public:
    virtual ~DefensiveActionStrategy() = default;
    virtual void defend() = 0;
};

// Concrete Strategy: Warrior Defensive Action (block)
class WarriorDefensiveActionStrategy : public DefensiveActionStrategy {
public:
    void defend() override {
        std::cout << "Warrior blocks the attack." << std::endl;
    }
};

// Concrete Strategy: Mage Defensive Action (magic shield)
class MageDefensiveActionStrategy : public DefensiveActionStrategy {
public:
    void defend() override {
        std::cout << "Mage erects a magic shield." << std::endl;
    }
};

// Context class that uses the Strategy objects
class Character {
private:
    std::unique_ptr<MovementStrategy> movementStrategy;
    std::unique_ptr<CombatAttackStrategy> attackStrategy;
    std::unique_ptr<DefensiveActionStrategy> defendStrategy;

public:
    Character(std::unique_ptr<MovementStrategy> movement,
              std::unique_ptr<CombatAttackStrategy> attack,
              std::unique_ptr<DefensiveActionStrategy> defend)
        : movementStrategy(std::move(movement)),
          attackStrategy(std::move(attack)),
          defendStrategy(std::move(defend)) {}

    void setMovementStrategy(std::unique_ptr<MovementStrategy> strategy) {
        movementStrategy = std::move(strategy);
    }

    void setAttackStrategy(std::unique_ptr<CombatAttackStrategy> strategy) {
        attackStrategy = std::move(strategy);
    }

    void setDefendStrategy(std::unique_ptr<DefensiveActionStrategy> strategy) {
        defendStrategy = std::move(strategy);
    }

    void move(float speed) {
        movementStrategy->move(speed);
    }

    void attack() {
        attackStrategy->attack();
    }

    void defend() {
        defendStrategy->defend();
    }
};

int main() {
    // Create characters with default strategies
    auto warriorMovement = std::make_unique<WarriorMovementStrategy>();
    auto warriorAttack = std::make_unique<WarriorCombatAttackStrategy>();
    auto warriorDefend = std::make_unique<WarriorDefensiveActionStrategy>();
    Character warrior(std::move(warriorMovement), std::move(warriorAttack), std::move(warriorDefend));

    auto mageMovement = std::make_unique<MageMovementStrategy>();
    auto mageAttack = std::make_unique<MageCombatAttackStrategy>();
    auto mageDefend = std::make_unique<MageDefensiveActionStrategy>();
    Character mage(std::move(mageMovement), std::move(mageAttack), std::move(mageDefend));

    // Gameplay actions
    warrior.move(5.0f);
    warrior.attack();
    warrior.defend();

    mage.move(5.0f);
    mage.attack();
    mage.defend();

    // Mage changes her attack strategy to a special spell
    mage.setAttackStrategy(std::make_unique<LightningStrikeStrategy>());
    mage.attack();  // Now mage casts a lightning strike

    return 0;
}
