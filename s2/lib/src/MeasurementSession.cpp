#include "lab/MeasurementSession.h"
#include <utility>

namespace lab {
MeasurementSession::MeasurementSession(std::string name) : name_(std::move(name)) {}
MeasurementSession::MeasurementSession(const MeasurementSession& other)
    : name_(other.name_), devices_(other.devices_), notes_(other.notes_) {}
MeasurementSession::MeasurementSession(MeasurementSession&& other) noexcept
    : name_(std::move(other.name_)), devices_(std::move(other.devices_)), notes_(std::move(other.notes_)) {
    other.devices_.clear(); other.notes_.clear();
}
MeasurementSession& MeasurementSession::operator=(const MeasurementSession& other) {
    if (this != &other) { MeasurementSession copy(other); *this = std::move(copy); }
    return *this;
}
MeasurementSession& MeasurementSession::operator=(MeasurementSession&& other) noexcept {
    if (this != &other) {
        name_ = std::move(other.name_); devices_ = std::move(other.devices_); notes_ = std::move(other.notes_);
        other.devices_.clear(); other.notes_.clear();
    }
    return *this;
}
void MeasurementSession::addDevice(Device device) { devices_.push_back(std::move(device)); }
void MeasurementSession::addNote(std::string note) { notes_.push_back(std::move(note)); }
Device& MeasurementSession::device(std::size_t index) { return devices_.at(index); }
const Device& MeasurementSession::device(std::size_t index) const { return devices_.at(index); }
const std::string& MeasurementSession::note(std::size_t index) const { return notes_.at(index); }
}
