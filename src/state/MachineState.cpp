#include "MachineState.h"

MachineState::MachineState() 
    : tape(TapeSize, InitialCellValue), pointer(InitialPointer)
{
}