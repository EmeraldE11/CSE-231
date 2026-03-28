/***********************************************************************
 * sputnik.h
 * Sputnik satellite: elliptical retrograde orbit, radius 4 pixels.
 ************************************************************************/

#pragma once

#include "satellite.h"

class Sputnik : public Satellite
{
public:
   Sputnik();
   void draw(ogstream& gout) override;
   void destroy(std::vector<Simulatable*>& satellites) override;

protected:
   Part* createPart(const Position& offset, const Velocity& kick) override;
};
