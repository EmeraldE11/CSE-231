/***********************************************************************
 * ship.h
 ************************************************************************/

#pragma once
#include <vector>
#include "satellite.h"   // for Satellite, Position, Velocity, Direction, Acceleration
class Interface;
class ogstream;

/*********************************************
 * Ship
 * A controllable satellite. The user can rotate
 * the ship, apply thrust, brake, and fire projectiles.
 * Physics (gravity, velocity, position) follow the
 * same rules as other satellites.
 *********************************************/
class Ship : public Satellite
{
public:
   Ship();
   // Handle player input (rotate, thrust, brake, fire).
   void input(const Interface* pUI, std::vector<Simulatable*>& satellites) override;
   // Draw the ship.
   void draw(ogstream& gout) override;
   // Override to keep direction under player control
   void advance(double timePerFrame,
                double earthRadius,
                double gravitySeaLevel) override;
   void move(double time) override;

private:
   bool thrust {false};
};
