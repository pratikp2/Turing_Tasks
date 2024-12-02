#include <iostream>
#include <set>
#include <mpi.h>

using namespace std;

// Function to perform set union using STL algorithms
set<int> distributedSetUnion(const set<int>& localSet, int numNodes, int rank) {
    // Gather all local sets to the root node
    vector<set<int>> allSets;
    if (rank == 0) {
        allSets.resize(numNodes);
    }

    MPI_Gather(&localSet, 1, MPI_DATATYPE_NULL, &allSets[0], 1, MPI_DATATYPE_NULL, 0, MPI_COMM_WORLD);

    // Perform set union on the root node
    set<int> globalSet;
    if (rank == 0) {
        for (const set<int>& set : allSets) {
            globalSet.insert(set.begin(), set.end());
        }
    }

    // Broadcast the global set back to all nodes
    MPI_Bcast(&globalSet, 1, MPI_DATATYPE_NULL, 0, MPI_COMM_WORLD);

    return globalSet;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int numNodes, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &numNodes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Generate local sets for each node
    set<int> localSet;
    for (int i = rank; i < 1000000; i += numNodes) {
        localSet.insert(i);
    }

    // Perform set union using the custom function
    set<int> globalSet = distributedSetUnion(localSet, numNodes, rank);

    // Print the size of the global set to verify the result
    if (rank == 0) {
        cout << "Global set size: " << globalSet.size() << endl;
    }

    MPI_Finalize();
    return 0;
}
