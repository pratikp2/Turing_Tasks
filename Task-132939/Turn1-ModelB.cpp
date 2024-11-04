// Base class for heuristic algorithms
class Heuristic {
public:
    virtual double calculateCost(const GameState& state) = 0;
};

// Concrete heuristic algorithms (e.g., A*, Dijkstra's, Greedy)
class AStarHeuristic : public Heuristic {
public:
    double calculateCost(const GameState& state) override {
        // Implement A* algorithm
        // ...
    }
};

class DijkstraHeuristic : public Heuristic {
public:
    double calculateCost(const GameState& state) override {
        // Implement Dijkstra's algorithm
        // ...
    }
};

// Context class that uses the heuristic algorithm
class Pathfinder {
public:
    void setHeuristic(std::unique_ptr<Heuristic> heuristic) {
        m_heuristic = std::move(heuristic);
    }

    Path findPath(const GameState& start, const GameState& goal) {
        // Use the selected heuristic to find the path
        // ...
    }

private:
    std::unique_ptr<Heuristic> m_heuristic;
};

// Usage example
int main() {
    Pathfinder pathfinder;

    // Switch between heuristic algorithms dynamically
    if (useAStar) {
        pathfinder.setHeuristic(std::make_unique<AStarHeuristic>());
    } else {
        pathfinder.setHeuristic(std::make_unique<DijkstraHeuristic>());
    }

    // Find the path using the selected heuristic
    Path path = pathfinder.findPath(startState, goalState);

    return 0;
}
// Heuristic factory
class HeuristicFactory {
public:
    static std::unique_ptr<Heuristic> createHeuristic(HeuristicType type) {
        switch (type) {
            case HeuristicType::AStar:
                return std::make_unique<AStarHeuristic>();
            case HeuristicType::Dijkstra:
                return std::make_unique<DijkstraHeuristic>();
            // Add more heuristic types as needed
            default:
                throw std::invalid_argument("Invalid heuristic type");
        }
    }
};

// Usage example
int main() {
    Pathfinder pathfinder;

    // Create heuristic algorithm using the factory
    HeuristicType heuristicType = HeuristicType::AStar;
    pathfinder.setHeuristic(HeuristicFactory::createHeuristic(heuristicType));

    // Find the path using the selected heuristic
    Path path = pathfinder.findPath(startState, goalState);

    return 0;
}
