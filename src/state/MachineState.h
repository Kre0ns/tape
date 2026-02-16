#pragma once

#include <cstdint>
#include <cstddef>
#include <vector>

struct MachineState
{
    static constexpr std::size_t TapeSize = 30000;
    static constexpr std::uint8_t InitialCellValue = 0;
    static constexpr std::size_t InitialPointer = 0;
    
    std::vector<std::uint8_t> tape;
    std::size_t pointer;

    MachineState();
};
