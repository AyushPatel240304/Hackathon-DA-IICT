#include <iostream>
#include <vector>
#include <string>
#include <map>

class Doctor {
public:
    Doctor(const std::string& name, const std::string& specialization)
        : name(name), specialization(specialization) {}

    std::string getName() const { return name; }
    std::string getSpecialization() const { return specialization; }

private:
    std::string name;
    std::string specialization;
};

class Appointment {
public:
    Appointment(const std::string& patientName, const std::string& disease, bool isTelemedicine)
        : patientName(patientName), disease(disease), isTelemedicine(isTelemedicine) {}

    std::string getPatientName() const { return patientName; }
    std::string getDisease() const { return disease; }
    bool getIsTelemedicine() const { return isTelemedicine; }

private:
    std::string patientName;
    std::string disease;
    bool isTelemedicine;
};

class AppointmentSystem {
public:
    void addDoctor(const Doctor& doctor) {
        doctors.push_back(doctor);
    }

    void bookAppointment(const Doctor& doctor, const Appointment& appointment) {
        appointments[doctor.getName()].push_back(appointment);
    }

    bool doesDoctorExist(const std::string& doctorName) {
        for (const Doctor& doctor : doctors) {
            if (doctor.getName() == doctorName) {
                return true;
            }
        }
        return false;
    }

    std::vector<Doctor> getDoctors() const {
        return doctors;
    }

    void displayAppointments(const Doctor& doctor) {
        std::cout << "Appointments for Dr. " << doctor.getName() << ":" << std::endl;
        const auto& doctorAppointments = appointments[doctor.getName()];
        for (const Appointment& appointment : doctorAppointments) {
            std::cout << "- Patient: " << appointment.getPatientName() << " | Disease: " << appointment.getDisease()
                      << " | Telemedicine: " << (appointment.getIsTelemedicine() ? "Yes" : "No") << std::endl;
        }
    }

private:
    std::vector<Doctor> doctors;
    std::map<std::string, std::vector<Appointment>> appointments;
};

int main() {
    AppointmentSystem appointmentSystem;

    Doctor doctor1("Dr. Smith", "Cardiologist");
    Doctor doctor2("Dr. Johnson", "Dermatologist");

    appointmentSystem.addDoctor(doctor1);
    appointmentSystem.addDoctor(doctor2);

    int choice;
    do {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Book Appointment" << std::endl;
        std::cout << "2. Display Appointments" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "Doctors Available:" << std::endl;
                for (const Doctor& doctor : appointmentSystem.getDoctors()) {
                    std::cout << "- " << doctor.getName() << " (" << doctor.getSpecialization() << ")" << std::endl;
                }

                std::string doctorName, patientName, disease;
                int isTelemedicine;

                std::cout << "Enter doctor's name: ";
                std::cin.ignore();
                std::getline(std::cin, doctorName);

                bool doctorExists = appointmentSystem.doesDoctorExist(doctorName);
                if (!doctorExists) {
                    std::cout << "Doctor not found. Please select a valid doctor." << std::endl;
                    continue;
                }

                std::cout << "Enter patient's name: ";
                std::getline(std::cin, patientName);

                std::cout << "Enter disease: ";
                std::getline(std::cin, disease);

                std::cout << "Is it a telemedicine appointment? (0/1): ";
                std::cin >> isTelemedicine;

                bool telemedicine = (isTelemedicine == 1);
                appointmentSystem.bookAppointment(Doctor(doctorName, ""), Appointment(patientName, disease, telemedicine));
                break;
            }
            case 2: {
                std::cout << "Doctors Available:" << std::endl;
                for (const Doctor& doctor : appointmentSystem.getDoctors()) {
                    std::cout << "- " << doctor.getName() << " (" << doctor.getSpecialization() << ")" << std::endl;
                }

                std::string doctorName;
                std::cout << "Enter doctor's name: ";
                std::cin.ignore();
                std::getline(std::cin, doctorName);

                bool doctorExists = appointmentSystem.doesDoctorExist(doctorName);
                if (!doctorExists) {
                    std::cout << "Doctor not found. Please select a valid doctor." << std::endl;
                    continue;
                }

                appointmentSystem.displayAppointments(Doctor(doctorName, ""));
                break;
            }
            case 3:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please select a valid option." << std::endl;
                break;
        }

    } while (choice != 3);

    return 0;
}
