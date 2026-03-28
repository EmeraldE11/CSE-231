/***********************************************************************
 * Source File:
 *    Test : Test runner
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The test runner for all the unit tests
 ************************************************************************/

#include "test.h"
#include "testPosition.h"
#include "testVelocity.h"
#include "testDirection.h"
#include "testAcceleration.h"
#include "testPhysics.h"
#include "testEarth.h"
#include "testSatellite.h"
#include "testGPS.h"
#include "testSputnik.h"
#include "testCrewDragon.h"
#include "testStarlink.h"
#include "testPart.h"
#include "testFragment.h"
#include "testDraw.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <iostream>
using namespace std;
#endif

/*****************************************************************
 * testRunner
 * Runs all unit tests for Position, Velocity, Direction, Acceleration, Satellite, GPS.
 ****************************************************************/
void testRunner()
{
#ifdef _WIN32
   AllocConsole();
   FILE* stream;
   errno_t err;
   err = freopen_s(&stream, "CONOUT$", "a", stdout);
#endif // _WIN32

   TestPosition().run();
   TestVelocity().run();
   TestDirection().run();
   TestAcceleration().run();
   TestPhysics().run();
   TestEarth().run();
   TestSatellite().run();
   TestGPS().run();
   TestSputnik().run();
   TestCrewDragon().run();
   TestStarlink().run();
   TestPart().run();
   TestFragment().run();
   TestDraw().run();

   std::cout.flush();
}

