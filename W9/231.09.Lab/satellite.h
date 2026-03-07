/***********************************************************************
 * satellite.h
 * Simulatable base and bodies: Earth (rotate only), Satellite (gravity and motion),
 * Hubble (one concrete satellite). Physics helpers declared for use in advance().
 ************************************************************************/

#pragma once

#include "position.h"
#include "velocity.h"
#include "direction.h"
#include "acceleration.h"
#include "uiDraw.h"
#include <cmath>
#include <vector>

extern const double EARTH_RADIUS;
extern const double GRAVITY_SEA_LEVEL;
extern const double GEO_DISTANCE;
extern const double GEO_VELOCITY;
extern const double TIME_PER_FRAME;
extern const double ROTATION_PER_FRAME;

Acceleration getGravity(const Position& pos, double earthRadius, double gravitySeaLevel);
void updateVelocity(Velocity& v, const Acceleration& a, double time);
void updatePosition(Position& pos, const Velocity& v, const Acceleration& a, double time);

/*********************************************
 * Simulatable
 * Abstract base for simulation bodies. advance() updates state; draw() renders.
 *********************************************/
class Simulatable
{
public:
   virtual ~Simulatable() {}
   virtual void advance(double timePerFrame, double earthRadius, double gravitySeaLevel) = 0;
   virtual void draw(ogstream& gout) = 0;
   Position position;
};

/*********************************************
 * Earth
 * Fixed at origin. advance() updates rotation angle; draw() draws the earth.
 *********************************************/
class Earth : public Simulatable
{
public:
   Earth();
   void advance(double timePerFrame, double earthRadius, double gravitySeaLevel) override;
   void draw(ogstream& gout) override;
   double angle;
};

/*********************************************
 * Satellite
 * Orbital body with velocity and direction. advance() applies gravity,
 * updates velocity and position, rotates direction. draw() is overridden by subclasses.
 *********************************************/
class Satellite : public Simulatable
{
public:
   Satellite();
   Satellite(double x, double y, double vx, double vy);
   void advance(double timePerFrame, double earthRadius, double gravitySeaLevel) override;
   virtual void draw(ogstream& gout) override = 0;

   double getRadius() const { return radius; }
   bool isDead() const { return dead; }
   const Position& getPosition() const { return position; }
   void kill() { dead = true; }

protected:
   Velocity velocity;
   Direction direction;
   double angularVelocity;
   double radius;
   bool dead;
};

/*********************************************
 * Hubble
 * GEO satellite. draw() renders using drawHubble at position with direction angle.
 *********************************************/
class Hubble : public Satellite
{
public:
   Hubble();
   void draw(ogstream& gout) override;
};
