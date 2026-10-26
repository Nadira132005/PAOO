#pragma once
#include "lab/Device.h"
#include <cstddef>
#include <vector>

namespace lab {
class Inventory {
public:
    void add(Device device);
    const Device& at(std::size_t index) const;
    std::size_t size() const noexcept { return devices_.size(); }
private:
    std::vector<Device> devices_;
};
}
