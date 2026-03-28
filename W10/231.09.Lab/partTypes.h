/***********************************************************************
 * partTypes.h
 * Concrete part types (type identity for each satellite). Drawing is inherited
 * from Part unless a subclass overrides for a different appearance.
 ************************************************************************/

#pragma once

#include "part.h"

class GPSPart : public Part
{
public:
   GPSPart(const Satellite& parent, const Position& offset, const Velocity& kick);
};

class HubblePart : public Part
{
public:
   HubblePart(const Satellite& parent, const Position& offset, const Velocity& kick);
};

class SputnikPart : public Part
{
public:
   SputnikPart(const Satellite& parent, const Position& offset, const Velocity& kick);
};

class CrewDragonPart : public Part
{
public:
   CrewDragonPart(const Satellite& parent, const Position& offset, const Velocity& kick);
};

class StarlinkPart : public Part
{
public:
   StarlinkPart(const Satellite& parent, const Position& offset, const Velocity& kick);
};
