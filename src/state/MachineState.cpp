#include "MachineState.h"

MachineState::MachineState(std::size_t tapeSize) 
    : tape(tapeSize, InitialCellValue), pointer(InitialPointer)
{
}