// Potential Overhead in notify_all()
     for (const auto& observer : observers) {
         observer->notify_state_change(state); // Virtual function call
     }
