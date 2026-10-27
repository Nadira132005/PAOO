#pragma once
#include "lab/Device.h"
#include <string>
#include <vector>

namespace lab {
class MeasurementSession {
public:
    explicit MeasurementSession(std::string name);
    ~MeasurementSession();
    MeasurementSession(const MeasurementSession& other);
    MeasurementSession(MeasurementSession&& other) noexcept;
    MeasurementSession& operator=(const MeasurementSession& other);
    MeasurementSession& operator=(MeasurementSession&& other) noexcept;
    void addDevice(Device device);
    void addNote(std::string note);
    Device& device(std::size_t index);
    const Device& device(std::size_t index) const;
    const std::string& note(std::size_t index) const;
    const std::string& name() const noexcept { return name_; }
    std::size_t deviceCount() const noexcept { return devices_.size(); }
    std::size_t noteCount() const noexcept { return noteCount_; }
private:
    std::string name_;
    std::vector<Device> devices_;
    std::string* notes_;
    std::size_t noteCount_, noteCapacity_;
};
}
