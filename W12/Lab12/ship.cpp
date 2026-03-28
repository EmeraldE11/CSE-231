/***********************************************************************
 * ship.cpp
 * Ship
 ************************************************************************/

#include "ship.h"
#include "bullet.h"
#include "uiDraw.h"
#include "uiInteract.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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
   // Fire bullet at sprite nose (rate-limited so rounds cannot pile up and collide).
   if (pUI && pUI->isSpace() && bulletFireCooldown <= 0)
   {
      double noseX = std::sin(angle);
      double noseY = std::cos(angle);
      double z = position.getZoom();
      double spawnDist = (SHIP_NOSE_OFFSET_PIXELS + BULLET_RADIUS_PIXELS
                         + BULLET_SPAWN_CLEARANCE_PIXELS) * z;
      Position offset;
      offset.setMeters(spawnDist * noseX, spawnDist * noseY);
      // World velocity = ship velocity + muzzle velocity along nose (see BULLET_RELATIVE_KICK).
      Velocity kick;
      kick.setDx(velocity.getDx() + BULLET_RELATIVE_KICK * noseX);
      kick.setDy(velocity.getDy() + BULLET_RELATIVE_KICK * noseY);
      satellites.push_back(new Bullet(*this, offset, kick));
      bulletFireCooldown = BULLET_FIRE_COOLDOWN_FRAMES;
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
   if (bulletFireCooldown > 0)
      bulletFireCooldown--;
}

void Ship::move(double time)
{
   // Only move position; DO NOT touch direction here
   position.addMetersX(velocity.getDx() * time);
   position.addMetersY(velocity.getDy() * time);
}

void Ship::destroy(std::vector<Simulatable*>& satellites)
{
   spawnDebrisOnCollision(satellites, 3, 2);
}
