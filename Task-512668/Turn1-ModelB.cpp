#include <iostream>
#include <string>

using namespace std;

enum class EnvironmentalEvent {
    none = 0,
    high_temperature = 1 << 0,
    low_humidity = 1 << 1,
    rain = 1 << 2,
    strong_wind = 1 << 3
};

int main() {
    EnvironmentalEvent events = EnvironmentalEvent::high_temperature | EnvironmentalEvent::low_humidity;

    cout << "Detected environmental events: ";
    if (events & EnvironmentalEvent::high_temperature) {
        cout << "High temperature, ";
    }
    if (events & EnvironmentalEvent::low_humidity) {
        cout << "Low humidity, ";
    }
    if (events & EnvironmentalEvent::rain) {
        cout << "Rain, ";
    }
    if (events & EnvironmentalEvent::strong_wind) {
        cout << "Strong wind" << endl;
    } else {
        cout << "None" << endl;
    }

    // Trying to handle specific combinations using bitwise AND
    if (events == (EnvironmentalEvent::high_temperature & EnvironmentalEvent::low_humidity)) {
        cout << "Warning: High temperature and low humidity detected." << endl;
    }

    // Let's check for a combination that might not be explicitly represented in the enum
    EnvironmentalEvent new_events = events | EnvironmentalEvent::rain;
    if (new_events == (EnvironmentalEvent::high_temperature | EnvironmentalEvent::low_humidity | EnvironmentalEvent::rain)) {
        cout << "Alert: High temp, low humidity, and rain!" << endl;
    }
    else {
        cout << "Could not detect specific combination" << endl;
    }
    return 0;
}
