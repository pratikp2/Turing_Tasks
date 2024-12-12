#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

// Struct to represent a person with a first and last name
struct Person {
    std::string firstName;
    std::string lastName;
};

// Comparator function to sort persons by last name, then by first name
// This comparator is used with std::sort to provide a well-defined ordering of Person objects
bool CompareByLastNameThenFirstName(const Person& lhs, const Person& rhs) {
    // First, compare last names
    if (lhs.lastName != rhs.lastName) {
        return lhs.lastName < rhs.lastName; // Sort by last name
    }
    // If last names are the same, compare first names
    return lhs.firstName < rhs.firstName; // Sort by first name
}

int main() {
    std::vector<Person> people = {
        {"John", "Doe"},
        {"Alice", "Smith"},
        {"John", "Adams"},
        {"Jane", "Doe"},
        {"Alice", "Doe"}
    };

    // Sort using the defined comparator
    std::sort(people.begin(), people.end(), CompareByLastNameThenFirstName);

    // Print sorted results
    for (const auto& person : people) {
        std::cout << person.firstName << " " << person.lastName << std::endl;
    }

    return 0;
}
