#pragma once
#include <cstddef>
#include <string>

namespace lab {
struct Reading {
    double value;
    std::string timestamp;
};
class Device {
public:
    Device(std::string name, std::size_t capacity, std::string unit = "");
    ~Device();
    Device(const Device& other);
    Device(Device&& other) noexcept;
    Device& operator=(const Device& other);
    Device& operator=(Device&& other) noexcept;
    void addReading(double value, std::string timestamp = "");
    void setReading(std::size_t index, double value);
    double reading(std::size_t index) const;
    const std::string& timestamp(std::size_t index) const;
    double average() const;
    double minimum() const;
    double maximum() const;
    const std::string& name() const noexcept { return name_; }
    const std::string& unit() const noexcept { return unit_; }
    std::size_t size() const noexcept { return size_; }
    std::size_t capacity() const noexcept { return capacity_; }
private:
    std::string name_, unit_;
    std::size_t capacity_, size_;
    Reading* readings_;
};
}
