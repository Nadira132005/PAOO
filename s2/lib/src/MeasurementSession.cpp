#include "lab/MeasurementSession.h"
#include <stdexcept>
#include <utility>

namespace lab {
MeasurementSession::MeasurementSession(std::string name)
    : name_(std::move(name)), notes_(nullptr), noteCount_(0), noteCapacity_(0) {}
MeasurementSession::~MeasurementSession() { delete[] notes_; }
MeasurementSession::MeasurementSession(const MeasurementSession& other)
    : name_(other.name_), devices_(other.devices_), notes_(nullptr),
      noteCount_(other.noteCount_), noteCapacity_(other.noteCapacity_) {
    std::string* copy = noteCapacity_ ? new std::string[noteCapacity_] : nullptr;
    try {
        for (std::size_t i = 0; i < noteCount_; ++i) copy[i] = other.notes_[i];
    } catch (...) {
        delete[] copy;
        throw;
    }
    notes_ = copy;
}
MeasurementSession::MeasurementSession(MeasurementSession&& other) noexcept
    : name_(std::move(other.name_)), devices_(std::move(other.devices_)), notes_(other.notes_),
      noteCount_(other.noteCount_), noteCapacity_(other.noteCapacity_) {
    other.notes_ = nullptr; other.noteCount_ = other.noteCapacity_ = 0;
    other.devices_.clear();
}
MeasurementSession& MeasurementSession::operator=(const MeasurementSession& other) {
    if (this != &other) { MeasurementSession copy(other); *this = std::move(copy); }
    return *this;
}
MeasurementSession& MeasurementSession::operator=(MeasurementSession&& other) noexcept {
    if (this != &other) {
        delete[] notes_;
        name_ = std::move(other.name_); devices_ = std::move(other.devices_);
        notes_ = other.notes_; noteCount_ = other.noteCount_; noteCapacity_ = other.noteCapacity_;
        other.notes_ = nullptr; other.noteCount_ = other.noteCapacity_ = 0;
        other.devices_.clear();
    }
    return *this;
}
void MeasurementSession::addDevice(Device device) { devices_.push_back(std::move(device)); }
void MeasurementSession::addNote(std::string note) {
    if (noteCount_ == noteCapacity_) {
        const auto next = noteCapacity_ ? noteCapacity_ * 2 : 1;
        if (next < noteCapacity_) throw std::length_error("Note capacity overflow");
        std::string* expanded = new std::string[next];
        try {
            for (std::size_t i = 0; i < noteCount_; ++i) expanded[i] = notes_[i];
        } catch (...) {
            delete[] expanded;
            throw;
        }
        delete[] notes_; notes_ = expanded; noteCapacity_ = next;
    }
    notes_[noteCount_] = std::move(note);
    ++noteCount_;
}
Device& MeasurementSession::device(std::size_t index) { return devices_.at(index); }
const Device& MeasurementSession::device(std::size_t index) const { return devices_.at(index); }
const std::string& MeasurementSession::note(std::size_t index) const {
    if (index >= noteCount_) throw std::out_of_range("Note index out of range");
    return notes_[index];
}
}
