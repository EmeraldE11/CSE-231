/***********************************************************************
 * testCollision.h
 * Unit tests for collision detection helpers and destroy/spawn behavior.
 ************************************************************************/

#pragma once

#include "bullet.h"
#include "fragment.h"
#include "gps.h"
#include "part.h"
#include "satellite.h"
#include "unitTest.h"
#include <vector>

// Minimal concrete satellite for collision geometry tests.
class CollisionTestSat : public Satellite
{
public:
   CollisionTestSat(double x, double y, double r) : Satellite(x, y, 0.0, 0.0) { radius = r; }
   void draw(ogstream&) override {}
};

class TestCollision : public UnitTest
{
public:
   void run()
   {
      satellitesCollide_separated_false();
      satellitesCollide_overlapping_true();
      satellitesCollide_touchingFromOutside_false();
      satelliteHitsEarth_inOrbit_false();
      satelliteHitsEarth_overlappingSurface_true();

      gps_destroy_spawnsPartsAndFragments();
      collision_bulletAndPart_partSpawnsFragments();
      collision_fragmentAndPart_bothProcessed();

      report("Collision");
   }

private:
   void satellitesCollide_separated_false()
   {
      CollisionTestSat a(0.0, GEO_DISTANCE, 10.0);
      CollisionTestSat b(5000.0, GEO_DISTANCE, 10.0);
      assertUnit(!satellitesCollide(a, b));
   }

   void satellitesCollide_overlapping_true()
   {
      CollisionTestSat a(0.0, GEO_DISTANCE, 100.0);
      CollisionTestSat b(150.0, GEO_DISTANCE, 100.0);
      assertUnit(satellitesCollide(a, b));
   }

   void satellitesCollide_touchingFromOutside_false()
   {
      Position zref;
      double z = zref.getZoom();
      CollisionTestSat a(0.0, GEO_DISTANCE, 10.0);
      // 20 px apart in world-space meters: touching externally, not overlapping.
      CollisionTestSat b(20.0 * z, GEO_DISTANCE, 10.0);
      assertUnit(!satellitesCollide(a, b));
   }

   void satelliteHitsEarth_inOrbit_false()
   {
      CollisionTestSat s(0.0, GEO_DISTANCE, 10.0);
      assertUnit(!satelliteHitsEarth(s, EARTH_RADIUS));
   }

   void satelliteHitsEarth_overlappingSurface_true()
   {
      CollisionTestSat s(EARTH_RADIUS + 5.0, 0.0, 10.0);
      assertUnit(satelliteHitsEarth(s, EARTH_RADIUS));
   }

   void gps_destroy_spawnsPartsAndFragments()
   {
      GPS g(0.0, GEO_DISTANCE, 0.0, 0.0);
      std::vector<Simulatable*> spawned;
      g.destroy(spawned);
      assertUnit(spawned.size() == 5);
      for (Simulatable* p : spawned)
         delete p;
   }

   void collision_bulletAndPart_partSpawnsFragments()
   {
      SatelliteFixture parent(0.0, GEO_DISTANCE, 0.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(0.0, 0.0);
      Part p(parent, off, kick);
      Bullet b(parent, off, kick);
      std::vector<Simulatable*> spawned;
      p.destroy(spawned);
      assertUnit(spawned.size() == 2);
      b.destroy(spawned);
      assertUnit(spawned.size() == 2);
      for (Simulatable* x : spawned)
         delete x;
   }

   void collision_fragmentAndPart_bothProcessed()
   {
      SatelliteFixture parent(0.0, GEO_DISTANCE, 0.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(100.0, 0.0);
      Fragment f(parent, off, kick);
      Part p(parent, off, kick);
      std::vector<Simulatable*> bodies;
      f.destroy(bodies);
      assertUnit(bodies.empty());
      p.destroy(bodies);
      assertUnit(bodies.size() == 2);
      for (Simulatable* x : bodies)
         delete x;
   }
};
