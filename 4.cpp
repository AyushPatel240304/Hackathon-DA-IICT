#include <iostream>
#include <map>
#include <vector>

struct Medicine {
    std::string name;
    int stock;
    // Add more attributes as needed
};

int predictDemand(const Medicine& medicine) {
    // Implement a more sophisticated demand prediction algorithm here
    return medicine.stock / 10;
}

void distributeMedicines(std::map<std::string, Medicine>& medicineStock, const std::vector<std::string>& hospitals) {
    for (const std::string& hospital : hospitals) {
        if (medicineStock.empty()) {
            std::cout << "Medicine stock is empty. Cannot distribute to " << hospital << std::endl;
            return;
        }

        auto highestDemandMedicine = medicineStock.begin();
        for (auto it = medicineStock.begin(); it != medicineStock.end(); ++it) {
            if (predictDemand(it->second) > predictDemand(highestDemandMedicine->second)) {
                highestDemandMedicine = it;
            }
        }

        std::cout << "Distributing " << highestDemandMedicine->second.name
                  << " to " << hospital << std::endl;
        --highestDemandMedicine->second.stock;
        if (highestDemandMedicine->second.stock == 0) {
            medicineStock.erase(highestDemandMedicine);
        }
    }
}

int main() {
    std::map<std::string, Medicine> medicineStock;
    std::vector<std::string> hospitals;

    int numMedicines;
    std::cout << "Enter the number of medicines in stock: ";
    std::cin >> numMedicines;

    for (int i = 0; i < numMedicines; ++i) {
        Medicine medicine;
        std::cout << "Enter medicine name: ";
        std::cin >> medicine.name;
        std::cout << "Enter medicine stock: ";
        std::cin >> medicine.stock;
        medicineStock[medicine.name] = medicine;
    }

    int numHospitals;
    std::cout << "Enter the number of hospitals: ";
    std::cin >> numHospitals;

    for (int i = 0; i < numHospitals; ++i) {
        std::string hospitalName;
        std::cout << "Enter hospital name: ";
        std::cin >> hospitalName;
        hospitals.push_back(hospitalName);
    }

    distributeMedicines(medicineStock, hospitals);

    return 0;
}
