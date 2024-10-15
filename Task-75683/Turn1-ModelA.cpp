#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <unordered_map>
#include <queue>

// Simulated Network Delay
const int NETWORK_DELAY_MS = 50;

class LogEntry {
public:
	int term;
	std::string command;

	LogEntry(int term, const std::string& command) : term(term), command(command) {}
};

class RaftNode {
public:
	RaftNode(int id, std::vector<int> peerIds) : id(id), peerIds(peerIds), currentTerm(0), votedFor(-1), commitIndex(0), lastApplied(0) {
		log.push_back(LogEntry(0, "")); // Initial empty log entry
	}

	void Start();
	void AppendEntries(int leaderId, int prevLogIndex, int prevLogTerm, std::vector<LogEntry> entries, int leaderCommit);
	void RequestVote(int candidateId, int lastLogIndex, int lastLogTerm);

private:
	void Run();
	void BecomeFollower();
	void BecomeCandidate();
	void BecomeLeader();
	void HandleAppendEntriesResponse(int peerId, bool success);
	void HandleRequestVoteResponse(int peerId, bool granted);

	int id;
	std::vector<int> peerIds;
	std::thread thread;
	std::mutex mutex;
	std::condition_variable cv;

	int currentTerm;
	int votedFor;
	std::vector<LogEntry> log;
	int commitIndex;
	int lastApplied;
	std::atomic<bool> running{true};
	std::unordered_map<int, std::pair<int, std::vector<LogEntry>>> nextIndexAndMatchIndex; // For each peer, (nextIndex, matchIndex)
};

void RaftNode::Start() {
	thread = std::thread(&RaftNode::Run, this);
}

void RaftNode::Run() {
	BecomeFollower();

	while (running) {
		std::unique_lock<std::mutex> lock(mutex);
		cv.wait(lock, [this] { return !running || state != Follower; });

		if (state == Candidate) {
			BecomeCandidate();
		} else if (state == Leader) {
			BecomeLeader();
		}
	}
}

int main() {
	// Example usage:
	std::vector<int> peerIds1 = {2, 3};
	RaftNode node1(1, peerIds1);
	node1.Start();

	std::vector<int> peerIds2 = {1, 3};
	RaftNode node2(2, peerIds2);
	node2.Start();

	std::vector<int> peerIds3 = {1, 2};
	RaftNode node3(3, peerIds3);
	node3.Start();

	// Let the nodes run for some time or send commands as needed
	// ...

	node1.SubmitCommand("AddEmployee John Doe");

	// Cleanup
	node1.Stop();
	node2.Stop();
	node3.Stop();
	return 0;
}