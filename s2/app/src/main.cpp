#include "lab/MeasurementSession.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

using lab::Device;
using lab::MeasurementSession;

static void check(bool condition, const char* name) {
    if (!condition) throw std::runtime_error(std::string("FAILED: ") + name);
    std::cout << "PASS: " << name << '\n';
}
static void demonstrations() {
    Device sensor("Temperature", 1, "C");
    sensor.addReading(20, "09:00"); sensor.addReading(24, "09:05");
    Device copy(sensor); copy.setReading(0, 99);
    check(sensor.reading(0) == 20 && copy.reading(0) == 99 && copy.timestamp(1) == "09:05", "Device copy constructor: independent readings");
    Device moved(std::move(copy));
    check(moved.reading(0) == 99 && copy.size() == 0, "Device move constructor: transferred readings");
    Device assigned("unused", 0); assigned = sensor; assigned.setReading(1, 42);
    check(sensor.reading(1) == 24 && assigned.reading(1) == 42, "Device copy assignment: independent readings");
    Device moveAssigned("unused", 0); moveAssigned = std::move(assigned);
    check(moveAssigned.reading(1) == 42 && assigned.size() == 0, "Device move assignment: transferred readings");
    check(sensor.capacity() >= 2 && sensor.minimum() == 20 && sensor.maximum() == 24 && sensor.average() == 22 && sensor.unit() == "C", "Device growth and statistics");
    bool emptyError = false, boundsError = false;
    try { Device empty("empty", 0); empty.average(); } catch (const std::logic_error&) { emptyError = true; }
    try { sensor.reading(2); } catch (const std::out_of_range&) { boundsError = true; }
    check(emptyError && boundsError, "Device rejects empty statistics and invalid indexes");

    MeasurementSession session("Experiment"); session.addDevice(sensor); session.addNote("Initial observation");
    MeasurementSession snapshot(session); snapshot.device(0).setReading(0, 77); snapshot.addNote("Changed snapshot");
    check(session.device(0).reading(0) == 20 && session.noteCount() == 1 && snapshot.noteCount() == 2, "Session copy constructor: independent snapshot");
    MeasurementSession archive(std::move(snapshot));
    check(archive.device(0).reading(0) == 77 && archive.note(1) == "Changed snapshot" && snapshot.deviceCount() == 0, "Session move constructor: archived snapshot");
    MeasurementSession assignedSession("unused"); assignedSession = session; assignedSession.device(0).setReading(1, 66);
    check(session.device(0).reading(1) == 24 && assignedSession.device(0).reading(1) == 66, "Session copy assignment: independent snapshot");
    MeasurementSession movedSession("unused"); movedSession = std::move(assignedSession);
    check(movedSession.device(0).reading(1) == 66 && assignedSession.deviceCount() == 0, "Session move assignment: transferred snapshot");
}

static void menu() {
    MeasurementSession session("Interactive experiment");
    for (;;) {
        std::cout << "\n1 Add device  2 Add reading  3 Add note  4 Show session  5 Copy and archive  0 Exit\n> ";
        int choice;
        if (!(std::cin >> choice) || choice == 0) return;
        try {
            if (choice == 1) {
                std::string name, unit; std::cout << "Name and unit (one word each): ";
                if (!(std::cin >> name >> unit)) return;
                session.addDevice(Device(name, 1, unit));
            } else if (choice == 2) {
                std::size_t index; double value; std::string timestamp;
                std::cout << "Device index, value, timestamp (one word): ";
                if (!(std::cin >> index >> value >> timestamp)) return;
                session.device(index).addReading(value, timestamp);
            } else if (choice == 3) {
                std::string note; std::cout << "Note: "; std::getline(std::cin >> std::ws, note); session.addNote(note);
            } else if (choice == 4) {
                std::cout << session.name() << '\n';
                for (std::size_t i = 0; i < session.deviceCount(); ++i) {
                    const auto& d = session.device(i);
                    std::cout << i << ": " << d.name() << " (" << d.unit() << "), " << d.size() << " readings";
                    if (d.size()) std::cout << ", min " << d.minimum() << ", max " << d.maximum() << ", average " << d.average();
                    std::cout << '\n';
                    for (std::size_t j = 0; j < d.size(); ++j) std::cout << "  " << d.timestamp(j) << ": " << d.reading(j) << '\n';
                }
                for (std::size_t i = 0; i < session.noteCount(); ++i) std::cout << "Note: " << session.note(i) << '\n';
            } else if (choice == 5) {
                MeasurementSession snapshot(session); MeasurementSession archive(std::move(snapshot));
                std::cout << "Archived snapshot with " << archive.deviceCount() << " devices and " << archive.noteCount() << " notes.\n";
            } else std::cout << "Unknown option.\n";
        } catch (const std::exception& e) { std::cout << "Error: " << e.what() << '\n'; }
    }
}
int main(int argc, char** argv) {
    try {
        demonstrations();
        if (argc > 1 && std::string(argv[1]) == "--demo-only") return 0;
        menu();
    } catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
}
