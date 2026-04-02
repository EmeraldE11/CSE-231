/***********************************************************************
 * testShip.h
 * Unit tests for the Ship class.
 ************************************************************************/

#pragma once

#include "bullet.h"
#include "ship.h"
#include "satellite.h"
#include "unitTest.h"
#include "uiInteract.h"
#include "position.h"
#include <cmath>
#include <vector>

 // Map GLUT keys for the test runner if they aren't defined
#if !defined(GLUT_KEY_LEFT)
#define GLUT_KEY_LEFT 100
#define GLUT_KEY_UP 101
#define GLUT_KEY_RIGHT 102
#endif

class TestShip : public UnitTest
{
public:
    void run()
    {
        constructor_initialState();

        input_rotateLeft();
        input_rotateRight();

        input_thrustChangesVelocity();

        input_fireBulletSpawnsObject();
        input_fireBulletDistance();
        input_fireBulletVelocity();
        input_fireBullet_fixedSpeedAfterThrust();
        input_secondSpaceWithoutAdvance_doesNotSpawnSecondBullet();

        report("Ship");
    }

private:
    /*****************************************************************
     * RESET INPUT
     * Initialize input values.
     *****************************************************************/
    void resetInput(Interface& ui)
    {
        ui.keyEvent(GLUT_KEY_LEFT, false);
        ui.keyEvent(GLUT_KEY_RIGHT, false);
        ui.keyEvent(GLUT_KEY_UP, false);
        ui.keyEvent(' ', false);
    }

    /*****************************************************************
	 * CONSTRUCTOR : INITIAL STATE
     *****************************************************************/
    void constructor_initialState()
    {
        Ship s;
        assertEquals(s.getPosition().getMetersX(), GPS_DISTANCE);
        assertEquals(s.getPosition().getMetersY(), 0.0);
        assertUnit(!s.isDead());
    }

    /*****************************************************************
	 * INPUT ROTATE LEFT/RIGHT
	 * Makes sure ship rotates left and right when the appropriate keys are pressed.
     *****************************************************************/
    void input_rotateLeft()
    {
        Ship s;
        Interface ui;
        resetInput(ui);
        ui.keyEvent(GLUT_KEY_LEFT, true);
        double dirBefore = s.getDirectionRadians();
        std::vector<Simulatable*> satellites;

        s.input(&ui, satellites);

        assertUnit(s.getDirectionRadians() < dirBefore);
        resetInput(ui);
    }

    void input_rotateRight()
    {
        Ship s;
        Interface ui;
        resetInput(ui);
        ui.keyEvent(GLUT_KEY_RIGHT, true);
        double dirBefore = s.getDirectionRadians();
        std::vector<Simulatable*> satellites;

        s.input(&ui, satellites);

        assertUnit(s.getDirectionRadians() > dirBefore);
        resetInput(ui);
    }

    /*****************************************************************
    * INPUT THRUST AND SHOOTING
	* Makes sure ship moves and shoots when the appropriate keys are pressed.
    *****************************************************************/
    void input_thrustChangesVelocity()
    {
        Ship s;
        Interface ui;
        resetInput(ui);
        ui.keyEvent(GLUT_KEY_UP, true);
        double vXBefore = s.getVelocity().getDx();
        std::vector<Simulatable*> satellites;

        s.input(&ui, satellites);

        assertUnit(s.getVelocity().getDx() != vXBefore ||
            s.getVelocity().getDy() != 0.0);
        resetInput(ui);
    }

    void input_fireBulletSpawnsObject()
    {
        Ship s;
        Interface ui;
        resetInput(ui);
        ui.keyEvent(' ', true);
        std::vector<Simulatable*> satellites;

        s.input(&ui, satellites);

        assertEquals(satellites.size(), 1);

        for (auto sat : satellites) delete sat;
        resetInput(ui);
    }

    /*****************************************************************
    * INPUT FIRE PROJECTILE DISTANCE
    * Make sure the projectile in the right place.
    *****************************************************************/
    void input_fireBulletDistance()
    {
        // SETUP
        Ship s;
        Interface ui;
        resetInput(ui);
        ui.keyEvent(' ', true);
        std::vector<Simulatable*> satellites;

        // EXERCISE
        s.input(&ui, satellites);

        // VERIFY
        if (!satellites.empty())
        {
            Satellite* pBullet = (Satellite*)satellites[0];

            Position shipPos = s.getPosition();
            Position projPos = pBullet->getPosition();

            double distance = computeDistance(shipPos, projPos);
            double z = s.getPosition().getZoom();
            assertUnit(distance >= (SHIP_NOSE_OFFSET_PIXELS + BULLET_RADIUS_PIXELS) * z);
        }
        else
        {
            assertUnit(false);
        }

        // TEARDOWN
        for (auto sat : satellites) delete sat;
        resetInput(ui);
    }

    /*****************************************************************
    * INPUT FIRE PROJECTILE VELOCITY
	* Verify the projectile has proper velocity.
    *****************************************************************/
    void input_fireBulletVelocity()
    {
        Ship s;
        Interface ui;
        resetInput(ui);
        ui.keyEvent(' ', true);
        std::vector<Simulatable*> satellites;

        s.input(&ui, satellites);

        if (!satellites.empty())
        {
            Satellite* p = (Satellite*)satellites[0];
            double nx = std::sin(s.getDirectionRadians());
            double ny = std::cos(s.getDirectionRadians());
            double vx = p->getVelocity().getDx();
            double vy = p->getVelocity().getDy();
            double svx = s.getVelocity().getDx();
            double svy = s.getVelocity().getDy();
            assertEqualsTolerance(vx, svx + BULLET_RELATIVE_KICK * nx, 1.0);
            assertEqualsTolerance(vy, svy + BULLET_RELATIVE_KICK * ny, 1.0);
        }

        for (auto sat : satellites) delete sat;
        resetInput(ui);
    }

    void input_fireBullet_fixedSpeedAfterThrust()
    {
        Ship s;
        Interface ui;
        resetInput(ui);
        ui.keyEvent(GLUT_KEY_UP, true);
        std::vector<Simulatable*> empty;
        s.input(&ui, empty);
        resetInput(ui);
        ui.keyEvent(' ', true);
        std::vector<Simulatable*> satellites;
        s.input(&ui, satellites);
        assertUnit(satellites.size() == 1);
        Satellite* p = (Satellite*)satellites[0];
        double nx = std::sin(s.getDirectionRadians());
        double ny = std::cos(s.getDirectionRadians());
        double svx = s.getVelocity().getDx();
        double svy = s.getVelocity().getDy();
        assertEqualsTolerance(p->getVelocity().getDx(), svx + BULLET_RELATIVE_KICK * nx, 1.0);
        assertEqualsTolerance(p->getVelocity().getDy(), svy + BULLET_RELATIVE_KICK * ny, 1.0);
        for (auto sat : satellites) delete sat;
        resetInput(ui);
    }

    void input_secondSpaceWithoutAdvance_doesNotSpawnSecondBullet()
    {
        Ship s;
        Interface ui;
        resetInput(ui);
        ui.keyEvent(' ', true);
        std::vector<Simulatable*> satellites;

        s.input(&ui, satellites);
        assertUnit(satellites.size() == 1);
        s.input(&ui, satellites);
        assertUnit(satellites.size() == 1);

        for (auto sat : satellites) delete sat;
        resetInput(ui);
    }
};