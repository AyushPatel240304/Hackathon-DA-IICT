#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream> // For file I/O

class Patient {
public:
    Patient(std::string name) : name(name) {}

    std::string getName() const {
        return name;
    }

private:
    std::string name;
};

class Doctor {
public:
    Doctor(std::string name, std::string specialization) : name(name), specialization(specialization) {}

    std::string getName() const {
        return name;
    }

    std::string getSpecialization() const {
        return specialization;
    }

private:
    std::string name;
    std::string specialization;
};

class Appointment {
public:
    Appointment(const Doctor& doctor, const Patient& patient, std::tm time)
        : doctor(doctor), patient(patient), time(time) {}

    Doctor getDoctor() const {
        return doctor;
    }

    Patient getPatient() const {
        return patient;
    }

    std::tm getTime() const {
        return time;
    }

private:
    Doctor doctor;
    Patient patient;
    std::tm time;
};

class TelemedicinePlatform {
public:
    void scheduleAppointment(const Doctor& doctor, const Patient& patient, std::tm time) {
        Appointment appointment(doctor, patient, time);
        appointments.push_back(appointment);
    }

    void listAppointments() const {
        for (const Appointment& appointment : appointments) {
            std::cout << "Time: " << appointment.getTime().tm_hour << ":" << appointment.getTime().tm_min << std::endl;
            std::cout << "Doctor: " << appointment.getDoctor().getName() << " (" << appointment.getDoctor().getSpecialization() << ")" << std::endl;
            std::cout << "Patient: " << appointment.getPatient().getName() << std::endl;
            std::cout << std::endl;
        }
    }

    void saveAppointmentsToFile(const std::string& filename) const {
        std::ofstream outputFile(filename);
        for (const Appointment& appointment : appointments) {
            outputFile << "Time: " << appointment.getTime().tm_hour << ":" << appointment.getTime().tm_min << std::endl;
            outputFile << "Doctor: " << appointment.getDoctor().getName() << " (" << appointment.getDoctor().getSpecialization() << ")" << std::endl;
            outputFile << "Patient: " << appointment.getPatient().getName() << std::endl;
            outputFile << std::endl;
        }
        outputFile.close();
        std::cout << "Appointments saved to " << filename << std::endl;
    }

    void deleteAppointments() {
        appointments.clear();
        std::cout << "All appointments deleted." << std::endl;
    }

private:
    std::vector<Appointment> appointments;
};

int main() {
    TelemedicinePlatform platform;

    std::string doctorName, doctorSpecialization, patientName;
    int appointmentHour, appointmentMinute;

    std::cout << "Enter doctor's name: ";
    std::getline(std::cin, doctorName);

    std::cout << "Enter doctor's specialization: ";
    std::getline(std::cin, doctorSpecialization);

    std::cout << "Enter patient's name: ";
    std::getline(std::cin, patientName);

    std::cout << "Enter appointment hour (0-23): ";
    std::cin >> appointmentHour;

    std::cout << "Enter appointment minute (0-59): ";
    std::cin >> appointmentMinute;

    Doctor doctor(doctorName, doctorSpecialization);
    Patient patient(patientName);

    std::tm appointmentTime{};
    appointmentTime.tm_hour = appointmentHour;
    appointmentTime.tm_min = appointmentMinute;

    platform.scheduleAppointment(doctor, patient, appointmentTime);

    int choice;
    std::cout << "1. Display Appointments" << std::endl;
    std::cout << "2. Save Appointments to File" << std::endl;
    std::cout << "3. Delete Appointments" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            std::cout << "Upcoming Appointments:" << std::endl;
            platform.listAppointments();
            break;
        case 2: {
            std::string filename;
            std::cout << "Enter file name to save appointments: ";
            std::cin.ignore(); // Clear the newline character from previous input
            std::getline(std::cin, filename);
            platform.saveAppointmentsToFile(filename);
            break;
        }
        case 3:
            platform.deleteAppointments();
            break;
        default:
            std::cout << "Invalid choice." << std::endl;
    }

    return 0;
}
