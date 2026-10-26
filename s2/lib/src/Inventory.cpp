#include "lab/Inventory.h"
#include <utility>

namespace lab {
void Inventory::add(Device device) { devices_.push_back(std::move(device)); }
const Device& Inventory::at(std::size_t index) const { return devices_.at(index); }
}
