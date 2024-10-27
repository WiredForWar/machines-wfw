/*
 * S I M . H P P
 * (c) Charybdis Limited, 1997. All Rights Reserved
 */

/*
    General include for the Sim library, with forward declarations.
*/

#pragma once

#include <cstdint>
#include <vector>

// Forward declarations
using SimPriority = uint32_t;
class SimManager;
class SimProcess;
class SimActor;
class SimEventDiary;
class SimDiscreteEvent;

// Collection of SimActor*'s
using SimActors = std::vector<SimActor*>;
