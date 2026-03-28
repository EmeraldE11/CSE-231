/***********************************************************************
 * testCollision.h
 ************************************************************************/

#pragma once

#include "bullet.h"
#include "collision.h"
#include "fragment.h"
#include "part.h"
#include "position.h"
#include "satellite.h"
#include "unitTest.h"
#include <vector>

extern const double EARTH_RADIUS;
extern const double GRAVITY_SEA_LEVEL;
extern const double TIME_PER_FRAME;
extern const int SHORT_LIVED_LIFETIME_FRAMES;

class TestCollision : public UnitTest
{
private:
   class CollideSatellite : public Satellite
   {
   public:
      CollideSatellite(double x, double y, double vx, double vy, double r = 10.0)
         : Satellite(x, y, vx, vy)
      {
         radius = r;
      }
      void draw(ogstream&) override {}
   };

public:
   void run()
   {
      Position zoomScratch;
      double savedZoom = Position::getMetersFromPixels();
      zoomScratch.setZoom(1.0);

      collide_separatedNoHit();
      collide_overlappingHits();
      collideEarth_clearSkyNoHit();
      collideEarth_insideAtmosphere();
      resolve_twoSatellites_bothDestroyed();
      resolve_bulletAndFragment_bothKilled();
      resolve_bulletAndPart_partDestroyed();
      resolve_partAndFragment_partFragmentsFragmentGone();
      part_destroy_createsTwoFragments();
      fragment_diesAfterLifetime();
      bullet_diesAfterLifetime();

      zoomScratch.setZoom(savedZoom);
      report("Collision / debris");
   }

private:
   void collide_separatedNoHit()
   {
      CollideSatellite a(0.0, 1000.0, 0.0, 0.0, 10.0);
      CollideSatellite b(500.0, 1000.0, 0.0, 0.0, 10.0);
      assertUnit(!collide(a, b));
   }

   void collide_overlappingHits()
   {
      CollideSatellite a(0.0, 1000.0, 0.0, 0.0, 10.0);
      CollideSatellite b(15.0, 1000.0, 0.0, 0.0, 10.0);
      assertUnit(collide(a, b));
   }

   void collideEarth_clearSkyNoHit()
   {
      CollideSatellite s(0.0, EARTH_RADIUS + 500000.0, 0.0, 0.0, 10.0);
      assertUnit(!collideEarth(s, EARTH_RADIUS));
   }

   void collideEarth_insideAtmosphere()
   {
      CollideSatellite s(0.0, EARTH_RADIUS - 1.0, 0.0, 0.0, 10.0);
      assertUnit(collideEarth(s, EARTH_RADIUS));
   }

   void resolve_twoSatellites_bothDestroyed()
   {
      CollideSatellite a(0.0, 1000.0, 0.0, 0.0, 50.0);
      CollideSatellite b(0.0, 1000.0, 0.0, 0.0, 50.0);
      std::vector<Simulatable*> bodies;
      resolveCollision(&a, &b, bodies);
      assertUnit(a.isDead());
      assertUnit(b.isDead());
      assertEquals((int)bodies.size(), 6);
      for (Simulatable* p : bodies)
         delete p;
   }

   void resolve_bulletAndFragment_bothKilled()
   {
      CollideSatellite parentA(1.0e7, 1.0e7, 0.0, 0.0);
      CollideSatellite parentB(1.0e7, 1.0e7, 0.0, 0.0);
      Direction d;
      d.setRadians(0.0);
      Bullet bu(parentA, Position(0.0, 0.0), Velocity(100.0, 0.0));
      Fragment fr(parentB, d);
      std::vector<Simulatable*> bodies;
      resolveCollision(&bu, &fr, bodies);
      assertUnit(bu.isDead());
      assertUnit(fr.isDead());
      assertUnit(bodies.empty());
   }

   void resolve_bulletAndPart_partDestroyed()
   {
      CollideSatellite parent(1.0e7, 1.0e7, 0.0, 0.0);
      Direction d;
      d.setRadians(0.0);
      Bullet bu(parent, Position(0.0, 0.0), Velocity(100.0, 0.0));
      Part pt(parent, d);
      std::vector<Simulatable*> bodies;
      resolveCollision(&bu, &pt, bodies);
      assertUnit(bu.isDead());
      assertUnit(pt.isDead());
      assertEquals((int)bodies.size(), 2);
      for (Simulatable* p : bodies)
      {
         assertUnit(dynamic_cast<Fragment*>(p) != nullptr);
         delete p;
      }
   }

   void resolve_partAndFragment_partFragmentsFragmentGone()
   {
      CollideSatellite parentP(2.0e7, 2.0e7, 0.0, 0.0);
      CollideSatellite parentF(2.0e7, 2.0e7, 0.0, 0.0);
      Direction d;
      d.setRadians(0.0);
      Part pt(parentP, d);
      Fragment fr(parentF, d);
      std::vector<Simulatable*> bodies;
      resolveCollision(&pt, &fr, bodies);
      assertUnit(pt.isDead());
      assertUnit(fr.isDead());
      assertEquals((int)bodies.size(), 2);
      for (Simulatable* p : bodies)
      {
         assertUnit(dynamic_cast<Fragment*>(p) != nullptr);
         delete p;
      }
   }

   void part_destroy_createsTwoFragments()
   {
      CollideSatellite parent(3.0e7, 3.0e7, 0.0, 0.0);
      Direction d;
      d.setRadians(0.0);
      Part pt(parent, d);
      std::vector<Simulatable*> satellites;
      pt.destroy(satellites);
      assertUnit(pt.isDead());
      assertEquals((int)satellites.size(), 2);
      for (Simulatable* p : satellites)
      {
         assertUnit(dynamic_cast<Fragment*>(p) != nullptr);
         delete p;
      }
   }

   void fragment_diesAfterLifetime()
   {
      CollideSatellite parent(4.0e7, 4.0e7, 5000.0, 0.0);
      Direction d;
      d.setRadians(0.0);
      Fragment fr(parent, d);
      for (int i = 0; i < SHORT_LIVED_LIFETIME_FRAMES; i++)
         fr.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      assertUnit(fr.isDead());
   }

   void bullet_diesAfterLifetime()
   {
      CollideSatellite parent(5.0e7, 5.0e7, 5000.0, 0.0);
      Bullet bu(parent, Position(0.0, 0.0), Velocity(1000.0, 0.0));
      for (int i = 0; i < SHORT_LIVED_LIFETIME_FRAMES; i++)
         bu.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      assertUnit(bu.isDead());
   }
};
