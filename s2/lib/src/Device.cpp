#include "lab/Device.h"
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <utility>

namespace lab {
    // default constructor for Device
    Device::Device(std::string name, std::size_t capacity, std::string unit)
    : name_(std::move(name)), unit_(std::move(unit)), capacity_(capacity), size_(0),
      readings_(capacity ? new Reading[capacity]{} : nullptr) {}

Device::~Device() { delete[] readings_; }
Device::Device(const Device& other)
    : name_(other.name_), unit_(other.unit_), capacity_(other.capacity_), size_(other.size_), readings_(nullptr) {
    std::unique_ptr<Reading[]> copy(capacity_ ? new Reading[capacity_]{} : nullptr);
    for (std::size_t i = 0; i < size_; ++i) copy[i] = other.readings_[i];
    readings_ = copy.release();
}
Device::Device(Device&& other) noexcept
    : name_(std::move(other.name_)), unit_(std::move(other.unit_)), capacity_(other.capacity_),
      size_(other.size_), readings_(other.readings_) {
    other.readings_ = nullptr; other.size_ = other.capacity_ = 0;
}
Device& Device::operator=(const Device& other) {
    if (this != &other) { Device copy(other); *this = std::move(copy); }
    return *this;
}
Device& Device::operator=(Device&& other) noexcept {
    if (this != &other) {
        delete[] readings_; name_ = std::move(other.name_); unit_ = std::move(other.unit_);
        capacity_ = other.capacity_; size_ = other.size_; readings_ = other.readings_;
        other.readings_ = nullptr; other.size_ = other.capacity_ = 0;
    }
    return *this;
}
void Device::addReading(double value, std::string timestamp) {
    if (size_ == capacity_) {
        const auto next = capacity_ ? capacity_ * 2 : 1;
        if (next < capacity_) throw std::length_error("Device capacity overflow");
        std::unique_ptr<Reading[]> expanded(new Reading[next]{});
        for (std::size_t i = 0; i < size_; ++i) expanded[i] = readings_[i];
        delete[] readings_; readings_ = expanded.release(); capacity_ = next;
    }
    readings_[size_] = Reading{value, std::move(timestamp)};
    ++size_;
}
void Device::setReading(std::size_t index, double value) {
    if (index >= size_) throw std::out_of_range("Reading index out of range");
    readings_[index].value = value;
}
double Device::reading(std::size_t index) const {
    if (index >= size_) throw std::out_of_range("Reading index out of range");
    return readings_[index].value;
}
const std::string& Device::timestamp(std::size_t index) const {
    if (index >= size_) throw std::out_of_range("Reading index out of range");
    return readings_[index].timestamp;
}
double Device::average() const {
    if (!size_) throw std::logic_error("No readings available");
    double sum = 0; for (std::size_t i = 0; i < size_; ++i) sum += readings_[i].value;
    return sum / size_;
}
double Device::minimum() const {
    if (!size_) throw std::logic_error("No readings available");
    double result = readings_[0].value;
    for (std::size_t i = 1; i < size_; ++i) result = std::min(result, readings_[i].value);
    return result;
}
double Device::maximum() const {
    if (!size_) throw std::logic_error("No readings available");
    double result = readings_[0].value;
    for (std::size_t i = 1; i < size_; ++i) result = std::max(result, readings_[i].value);
    return result;
}
}
