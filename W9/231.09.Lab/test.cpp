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
#include "testSatellite.h"
#include "testGPS.h"
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
   TestSatellite().run();
   TestGPS().run();

   std::cout.flush();
}

