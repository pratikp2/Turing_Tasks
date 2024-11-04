#include <iostream>
#include <vector>
#include <memory>

// Base Heuristic class
class Heuristic {
public:
	virtual double calculate_heuristic(const std::vector<int>& state) = 0;
	virtual ~Heuristic() = default;
};

// Concrete Heuristic 1: "Manhattan Distance"
class ManhattanHeuristic : public Heuristic {
public:
	double calculate_heuristic(const std::vector<int>& state) override {
		// Heuristic calculation logic
		double sum = 0.0;
		// ... (Calculation code)
		return sum;
	}
};

// Concrete Heuristic 2: "Euclidean Distance"
class EuclideanHeuristic : public Heuristic {
public:
	double calculate_heuristic(const std::vector<int>& state) override {
		// Heuristic calculation logic
		double sum = 0.0;
		// ... (Calculation code different from Manhattan)
		return sum;
	}
};

// Context class that uses the Heuristic
class HeuristicContext {
public:
	HeuristicContext(std::unique_ptr<Heuristic> heuristic) : heuristic(std::move(heuristic)) {}

	double calculate_heuristic(const std::vector<int>& state) {
		return heuristic->calculate_heuristic(state);
	}

	void set_heuristic(std::unique_ptr<Heuristic> heuristic) {
		this->heuristic = std::move(heuristic);
	}

private:
	std::unique_ptr<Heuristic> heuristic;
};

int main() {
	// Client code using the Strategy Pattern
	std::vector<int> game_state = {1, 2, 3, 8, 0, 4, 7, 6, 5};

	{
		// Using Manhattan Heuristic
		auto manhattanHeuristic = std::make_unique<ManhattanHeuristic>();
		HeuristicContext context(std::move(manhattanHeuristic));
		double heuristic_value = context.calculate_heuristic(game_state);
		std::cout << "Manhattan Heuristic Value: " << heuristic_value << std::endl;
	}

	{
		// Using Euclidean Heuristic at runtime
		auto euclideanHeuristic = std::make_unique<EuclideanHeuristic>();
		HeuristicContext context(std::move(euclideanHeuristic));
		double heuristic_value = context.calculate_heuristic(game_state);
		std::cout << "Euclidean Heuristic Value: " << heuristic_value << std::endl;
	}

	return 0;
}
