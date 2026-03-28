/***********************************************************************
 * part.h
 * Base for debris pieces broken from satellites. Drawing and breakup are
 * complete here; concrete *Part types identify which satellite produced the
 * debris (Straightforward adaptability: add a subclass + createPart override).
 * Parts do not expire.
 ************************************************************************/

#pragma once

#include "satellite.h"

class Part : public Satellite
{
public:
   void destroy(std::vector<Simulatable*>& satellites) override;
   void draw(ogstream& gout) override;

protected:
   Part(const Satellite& parent, const Position& offset, const Velocity& kick);

private:
   void spawnTwoFragmentsOrthogonal(std::vector<Simulatable*>& satellites);
};
