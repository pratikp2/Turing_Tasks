#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

// 'Observer' Design Pattern
class GameStateObserver {
public:
	virtual void notify_state_change(const std::vector<int>& new_state) = 0;
	virtual ~GameStateObserver() = default;
};

class HeuristicCalculatorObserver : public GameStateObserver {
public:
	void notify_state_change(const std::vector<int>& new_state) override {
		heuristic_value = calculate_heuristic(new_state);
	}

	double get_heuristic_value() const { return heuristic_value; }

private:
	double calculate_heuristic(const std::vector<int>& state) {
		// Heuristic calculation logic
		// ...
		return 0.0;
	}

	double heuristic_value = 0.0;
};

// 'Subject' Design Pattern
class GameStateManager {
public:
	void attach(std::unique_ptr<GameStateObserver> observer) {
		observers.push_back(std::move(observer));
	}

	void set_state(const std::vector<int>& new_state) {
		state = new_state;
		notify_all();
	}

	const std::vector<int>& get_state() const { return state; }

private:
	void notify_all() {
		for (const auto& observer : observers) {
			observer->notify_state_change(state);
		}
	}

	std::vector<int> state;
	std::vector<std::unique_ptr<GameStateObserver>> observers;
};

// 'Strategy' Design Pattern
class PathfindingStrategy {
public:
	virtual void find_path(const std::vector<int>& state) = 0;
	virtual ~PathfindingStrategy() = default;
};

class AStarStrategy : public PathfindingStrategy {
public:
	void find_path(const std::vector<int>& state) override {
		// A* pathfinding algorithm implementation
		// ...
	}
};

class GameController {
public:
	GameController() {
		state_manager.attach(std::make_unique<HeuristicCalculatorObserver>());
	}

	void set_pathfinding_strategy(std::unique_ptr<PathfindingStrategy> strategy) {
		pathfinding_strategy = std::move(strategy);
	}

	void start_game() {
		// Game loop
		// ...

		pathfinding_strategy->find_path(state_manager.get_state());
	}

private:
	GameStateManager state_manager;
	std::unique_ptr<PathfindingStrategy> pathfinding_strategy;
};

int main() {
	GameController controller;
	controller.set_pathfinding_strategy(std::make_unique<AStarStrategy>());
	controller.start_game();
	return 0;
}
