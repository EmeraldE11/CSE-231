/***********************************************************************
 * partTypes.cpp
 ************************************************************************/

#include "partTypes.h"

GPSPart::GPSPart(const Satellite& parent, const Position& offset, const Velocity& kick)
   : Part(parent, offset, kick) {}

HubblePart::HubblePart(const Satellite& parent, const Position& offset, const Velocity& kick)
   : Part(parent, offset, kick) {}

SputnikPart::SputnikPart(const Satellite& parent, const Position& offset, const Velocity& kick)
   : Part(parent, offset, kick) {}

CrewDragonPart::CrewDragonPart(const Satellite& parent, const Position& offset, const Velocity& kick)
   : Part(parent, offset, kick) {}

StarlinkPart::StarlinkPart(const Satellite& parent, const Position& offset, const Velocity& kick)
   : Part(parent, offset, kick) {}
