/***********************************************************************
 * ship.cpp
 * Ship
 ************************************************************************/

#include "ship.h"
#include "uiDraw.h"
#include "uiInteract.h"
#include <cmath>
#include <corecrt_math_defines.h>

extern const double TIME_PER_FRAME;
// define a small thrust acceleration for the ship:
const double SHIP_THRUST = 25.0;
const double SHIP_ROTATION_PER_FRAME = M_PI / 30.0; // ~6 degrees per frame

/*********************************************
 * Ship : constructor
 * Start the ship in a reasonable orbit (example:
 * GPS altitude and orbital velocity). Adjust as needed.
 *********************************************/
Ship::Ship()
   : Satellite(GPS_DISTANCE, 0.0,          // position: x, y  (m)
               0.0, GPS_VELOCITY)         // velocity: vx, vy (m/s)
{
   // Reasonable defaults; tweak to match your art / spec
   radius         = 10.0;   // for collision / drawing scaling
   angularVelocity = 0.0;
   dead           = false;
   age            = 0;
   // Point the ship “up” by default (pi/2 from +x axis)
   direction.setRadians(M_PI_2);
}

/*********************************************
 * Ship : input
 * - LEFT  : rotate CCW
 * - RIGHT : rotate CW
 * - UP    : apply thrust (change velocity in nose direction)
 * - DOWN : slow down
 * - SPACE : fire a projectile
 *
 * NOTE: This assumes BYU Interface methods:
 *  - pUI->isLeft(), isRight(), isUp(), isDown(), isSpace().
 * Adjust if your Interface uses different names.
 *********************************************/
void Ship::input(const Interface* pUI, std::vector<Simulatable*>& satellites)
{
   thrust = false;
   
   if (pUI && pUI->isLeft())
      direction.rotate( -SHIP_ROTATION_PER_FRAME );
   if (pUI && pUI->isRight())
      direction.rotate( SHIP_ROTATION_PER_FRAME );
   double angle = direction.getRadians();
   // Forward thrust (UP): dv = a * dt in nose direction
   if (pUI && pUI->isUp())
   {
      double dvx = SHIP_THRUST * TIME_PER_FRAME * std::sin(angle);
      double dvy = SHIP_THRUST * TIME_PER_FRAME * std::cos(angle);
      velocity.setDx(velocity.getDx() + dvx);
      velocity.setDy(velocity.getDy() + dvy);
      thrust = true;
   }
//   // Brake: apply thrust opposite current velocity
//   if (pUI && pUI->isDown())
//   {
//      double vx = velocity.getDx();
//      double vy = velocity.getDy();
//      double speed = std::sqrt(vx * vx + vy * vy);
//      if (speed > 0.0)
//      {
//         // unit vector opposite velocity
//         double ux = -vx / speed;
//         double uy = -vy / speed;
//         double dv = SHIP_THRUST * TIME_PER_FRAME;  // change in speed this frame
//         double dvx = dv * ux;
//         double dvy = dv * uy;
//         velocity.setDx(velocity.getDx() + dvx);
//         velocity.setDy(velocity.getDy() + dvy);
//      }
//   }
   // Fire projectile with SPACE (same as before)
   if (pUI && pUI->isSpace())
   {
      Position offset = position;
      offset.setMetersX(radius * std::sin(angle));
      offset.setMetersY(radius * std::cos(angle));
      Velocity kick;
      kick.setDx(velocity.getDx() + KICK_VELOCITY * std::sin(angle));
      kick.setDy(velocity.getDy() + KICK_VELOCITY * std::cos(angle));
      satellites.push_back(new Projectile(*this, offset, kick));
   }
}

/*********************************************
 * Ship : draw
 * Use a ship-specific drawing function from uiDraw.
 * If your uiDraw uses a different name/signature,
 * change it here.
 *********************************************/
void Ship::draw(ogstream& gout)
{
   gout.drawShip(position, direction.getRadians(), thrust);
}

void Ship::advance(double timePerFrame,
                   double earthRadius,
                   double gravitySeaLevel)
{
   // Same gravity/physics as other satellites
   Acceleration a = getGravity(position, earthRadius, gravitySeaLevel);
   updateVelocity(velocity, a, timePerFrame);
   move(timePerFrame);
   age++;
}

void Ship::move(double time)
{
   // Only move position; DO NOT touch direction here
   position.addMetersX(velocity.getDx() * time);
   position.addMetersY(velocity.getDy() * time);
}
