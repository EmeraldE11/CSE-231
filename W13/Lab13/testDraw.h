/***********************************************************************
 * testDraw.h
 * Unit tests for draw() on Earth and all satellite types.
 * Uses a test ogstream that records draw calls to a string.
 * Each test follows SETUP / EXERCISE / VERIFY / TEARDOWN.
 ************************************************************************/

#pragma once

#include "bullet.h"
#include "uiDraw.h"
#include "satellite.h"
#include "sputnik.h"
#include "gps.h"
#include "hubble.h"
#include "crewDragon.h"
#include "starlink.h"
#include "unitTest.h"
#include <string>

class TestGout : public ogstream
{
public:
   TestGout() : ogstream() {}
   ~TestGout() { str(""); }
   void flush() override {}
   void drawEarth(const Position&, double) override { *this << "Earth"; }
   void drawHubble(const Position&, double) override { *this << "Hubble"; }
   void drawGPS(const Position&, double) override { *this << "GPS"; }
   void drawSputnik(const Position&, double) override { *this << "Sputnik"; }
   void drawCrewDragon(const Position&, double) override { *this << "CrewDragon"; }
   void drawStarlink(const Position&, double) override { *this << "Starlink"; }
   void drawProjectile(const Position&) override { *this << "Projectile"; }
};

class TestDraw : public UnitTest
{
public:
   void run()
   {
      draw_earthWritesEarth();
      draw_hubbleWritesHubble();
      draw_gpsWritesGPS();
      draw_sputnikWritesSputnik();
      draw_crewDragonWritesCrewDragon();
      draw_starlinkWritesStarlink();
      draw_bulletWritesProjectileMarker();
      report("Draw");
   }

private:
   void draw_earthWritesEarth()
   {
      // SETUP
      TestGout gout;
      Earth e;
      // EXERCISE
      e.draw(gout);
      // VERIFY
      assertUnit(gout.str().find("Earth") != std::string::npos);
      // TEARDOWN
      // (none)
   }

   void draw_hubbleWritesHubble()
   {
      // SETUP
      TestGout gout;
      Hubble h;
      // EXERCISE
      h.draw(gout);
      // VERIFY
      assertUnit(gout.str().find("Hubble") != std::string::npos);
      // TEARDOWN
      // (none)
   }

   void draw_gpsWritesGPS()
   {
      // SETUP
      TestGout gout;
      GPS g;
      // EXERCISE
      g.draw(gout);
      // VERIFY
      assertUnit(gout.str().find("GPS") != std::string::npos);
      // TEARDOWN
      // (none)
   }

   void draw_sputnikWritesSputnik()
   {
      // SETUP
      TestGout gout;
      Sputnik s;
      // EXERCISE
      s.draw(gout);
      // VERIFY
      assertUnit(gout.str().find("Sputnik") != std::string::npos);
      // TEARDOWN
      // (none)
   }

   void draw_crewDragonWritesCrewDragon()
   {
      // SETUP
      TestGout gout;
      CrewDragon c;
      // EXERCISE
      c.draw(gout);
      // VERIFY
      assertUnit(gout.str().find("CrewDragon") != std::string::npos);
      // TEARDOWN
      // (none)
   }

   void draw_starlinkWritesStarlink()
   {
      // SETUP
      TestGout gout;
      Starlink s;
      // EXERCISE
      s.draw(gout);
      // VERIFY
      assertUnit(gout.str().find("Starlink") != std::string::npos);
      // TEARDOWN
      // (none)
   }

   void draw_bulletWritesProjectileMarker()
   {
      // SETUP
      TestGout gout;
      Hubble parent;
      Position offset(0.0, 0.0);
      Velocity kick(100.0, 0.0);
      Bullet p(parent, offset, kick);
      // EXERCISE
      p.draw(gout);
      // VERIFY
      assertUnit(gout.str().find("Projectile") != std::string::npos);
      // TEARDOWN
      // (none)
   }
};
