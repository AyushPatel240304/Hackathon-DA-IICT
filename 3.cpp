#include <iostream>
#include <string>
#include <vector>

struct UserIntake {
    std::string name;
    std::string organization;
    std::string strategyDescription;
};

// Function to gather user input for Laboratory Testing Optimization
UserIntake gatherUserInput() {
    UserIntake intake;

    std::cout << "Laboratory Testing Optimization Intake\n";

    std::cout << "Name: ";
    std::getline(std::cin, intake.name);

    std::cout << "Organization: ";
    std::getline(std::cin, intake.organization);

    std::cout << "Strategy Description:\n";
    std::getline(std::cin, intake.strategyDescription);

    return intake;
}

// Function to display a list of saved records
void displayRecords(const std::vector<UserIntake>& records) {
    std::cout << "\nSaved Records:\n";
    for (size_t i = 0; i < records.size(); ++i) {
        std::cout << "Record " << i + 1 << ":\n";
        std::cout << "Name: " << records[i].name << "\n";
        std::cout << "Organization: " << records[i].organization << "\n";
        std::cout << "Strategy Description:\n" << records[i].strategyDescription << "\n\n";
    }
}

int main() {
    std::vector<UserIntake> savedRecords;

    while (true) {
        std::cout << "Options:\n";
        std::cout << "1. Add Record\n";
        std::cout << "2. Display Saved Records\n";
        std::cout << "3. Delete Record\n";
        std::cout << "4. Exit\n";
        std::cout << "Select an option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(); // Clear newline from the buffer

        switch (choice) {
            case 1: {
                UserIntake userInput = gatherUserInput();
                savedRecords.push_back(userInput);
                std::cout << "Record saved!\n";
                break;
            }
            case 2:
                displayRecords(savedRecords);
                break;
            case 3: {
                displayRecords(savedRecords);
                std::cout << "Enter the index of the record to delete: ";
                int index;
                std::cin >> index;
                if (index >= 0 && index < savedRecords.size()) {
                    savedRecords.erase(savedRecords.begin() + index);
                    std::cout << "Record deleted!\n";
                } else {
                    std::cout << "Invalid index.\n";
                }
                break;
            }
            case 4:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please select a valid option.\n";
        }
    }

    return 0;
}
