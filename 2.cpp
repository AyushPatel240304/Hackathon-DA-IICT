#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

class Employee {
public:
    std::string name;
    std::string role;
    int availability;

    Employee(const std::string& _name, const std::string& _role, int _availability)
        : name(_name), role(_role), availability(_availability) {}
};

class Facility {
public:
    std::string name;
    int capacity;

    Facility(const std::string& _name, int _capacity) : name(_name), capacity(_capacity) {}
};

void scheduleStaff(std::vector<Employee>& staff, const std::vector<Facility>& facilities) {
    for (const Facility& facility : facilities) {
        int remainingCapacity = facility.capacity;

        std::cout << "Scheduling for " << facility.name << ":" << std::endl;

        for (Employee& employee : staff) {
            if (remainingCapacity == 0) {
                std::cout << "Facility " << facility.name << " is fully staffed." << std::endl;
                break;
            }

            if (employee.availability > 0) {
                std::cout << "Assigned " << employee.role << " " << employee.name << " to " << facility.name << std::endl;
                remainingCapacity--;
                employee.availability--;
            }
        }

        std::cout << std::endl;
    }
}

int main() {
    std::vector<Employee> staff;
    int numStaff;
    std::cout << "Enter the number of staff members: ";
    std::cin >> numStaff;

    for (int i = 0; i < numStaff; ++i) {
        std::string name, role;
        int availability;

        std::cout << "Enter name of staff member " << i + 1 << ": ";
        std::cin >> name;
        std::cout << "Enter role of staff member " << i + 1 << ": ";
        std::cin >> role;
        std::cout << "Enter availability of staff member " << i + 1 << ": ";
        std::cin >> availability;

        staff.emplace_back(name, role, availability);
    }

    std::vector<Facility> facilities;
    int numFacilities;
    std::cout << "Enter the number of facilities: ";
    std::cin >> numFacilities;

    for (int i = 0; i < numFacilities; ++i) {
        std::string name;
        int capacity;

        std::cout << "Enter name of facility " << i + 1 << ": ";
        std::cin >> name;
        std::cout << "Enter capacity of facility " << i + 1 << ": ";
        std::cin >> capacity;

        facilities.emplace_back(name, capacity);
    }

    scheduleStaff(staff, facilities);

    return 0;
}
