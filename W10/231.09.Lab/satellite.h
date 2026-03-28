/***********************************************************************
 * satellite.h
 * Simulatable base and bodies: Earth (rotate only), Satellite (gravity and motion),
 * Hubble, GPS (concrete satellites). Physics helpers declared for use in advance().
 ************************************************************************/

#pragma once

#include "position.h"
#include "velocity.h"
#include "direction.h"
#include "acceleration.h"
#include "uiDraw.h"
#include <cmath>
#include <vector>

class Interface;

extern const double EARTH_RADIUS;
extern const double GRAVITY_SEA_LEVEL;
extern const double GEO_DISTANCE;
extern const double GEO_VELOCITY;
extern const double GPS_DISTANCE;
extern const double GPS_VELOCITY;
extern const double KICK_VELOCITY;
extern const double BULLET_RELATIVE_SPEED;
extern const double TIME_PER_FRAME;
extern const double ROTATION_PER_FRAME;
extern const int SHORT_LIVED_LIFETIME_FRAMES;

// Angle is an orientation type used for rotation; implemented with Direction.
typedef Direction Angle;

Acceleration getGravity(const Position& pos, double earthRadius, double gravitySeaLevel);
void updateVelocity(Velocity& v, const Acceleration& a, double time);
void updatePosition(Position& pos, const Velocity& v, const Acceleration& a, double time);

class TestEarth;

/*********************************************
 * Simulatable
 * Abstract base for simulation bodies. advance() updates state; draw() renders.
 *********************************************/
class Simulatable
{
public:
   friend class TestEarth;
   virtual ~Simulatable() {}
   virtual void advance(double timePerFrame, double earthRadius, double gravitySeaLevel) = 0;
   virtual void draw(ogstream& gout) = 0;
protected:
   Position position;
};

/*********************************************
 * Earth
 * Fixed at origin. advance() updates rotation angle; draw() draws the earth.
 *********************************************/
class Earth : public Simulatable
{
public:
   friend class TestEarth;
   Earth();
   void advance(double timePerFrame, double earthRadius, double gravitySeaLevel) override;
   void draw(ogstream& gout) override;

protected:
   Angle angle;
};

class TestSatellite;

/*********************************************
 * Satellite
 * Orbital body with velocity and direction. advance() applies gravity,
 * updates velocity and position, rotates direction. draw() is overridden by subclasses.
 *********************************************/
class Satellite : public Simulatable
{
public:
   friend class TestSatellite;

   Satellite();
   Satellite(double x, double y, double vx, double vy);
   Satellite(const Satellite& parent, const Direction& kickDirection);
   void advance(double timePerFrame, double earthRadius, double gravitySeaLevel) override;
   virtual void move(double time);
   virtual void destroy(std::vector<Simulatable*>& satellites);
   virtual void input(const Interface* pUI, std::vector<Simulatable*>& satellites) {}
   virtual void draw(ogstream& gout) override = 0;

   double getRadius() const { return radius; }
   bool isDead() const { return dead; }
   const Position& getPosition() const { return position; }
   const Velocity& getVelocity() const { return velocity; }
   double getDirectionRadians() const { return direction.getRadians(); }
   void kill() { dead = true; }

protected:
   void spawnPart(std::vector<Simulatable*>& out, const Position& offset, const Velocity& kick);
   void spawnFragment(std::vector<Simulatable*>& out, const Position& offset, const Velocity& kick);
   void spawnDebrisOnCollision(std::vector<Simulatable*>& out, int numParts, int numFragments);

   Velocity velocity;
   Direction direction;
   double angularVelocity;
   double radius;
   bool dead;
   int age;
};

/*********************************************
 * Projectile
 * Small satellite created from a parent with offset position and kick velocity.
 *********************************************/
class Projectile : public Satellite
{
public:
   Projectile(const Satellite& parent, const Position& offset, const Velocity& kick);
   void draw(ogstream& gout) override;
};
