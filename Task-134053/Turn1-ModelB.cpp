   // Example 2: Improved Code

   #include <iostream>
   #include <vector>
   #include <boost/mpi.hpp>

   namespace mpi = boost::mpi;

   void simulateParticles(int num_steps, std::vector<double>& positions, mpi::communicator& world) {
     for (int step = 0; step < num_steps; ++step) {
         // Perform calculations on each particle
         for (int i = 0; i < positions.size(); ++i) {
             positions[i] += 0.1;
         }

         // Gather positions from all ranks
         mpi::gather(world, positions, 0);

         // Broadcast positions to all ranks
         mpi::broadcast(world, positions, 0);
     }
   }

   int main(int argc, char* argv[]) {
     mpi::environment env(argc, argv);
     mpi::communicator world;

     // Simulation data
     int num_steps = 1000;
     std::vector<double> positions(world.size(), 0.0);

     // Simulation call
     simulateParticles(num_steps, positions, world);

     return 0;
   }