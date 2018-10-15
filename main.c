/*
 * Find middle of a rectangle
 *
 */
#include "RP6RobotBaseLib.h"
#include <stdlib.h>
/* Parameter */
uint8_t bumper;
uint8_t initBumper;
uint8_t angle;
int i;
/* Methods Header */
void checkBumper();
void rotateAheadWall();
int main();
/* Methods implemented */
void checkBumper()
{
    stop();
    /* Testen wie dass ist wenn beide gedrückt sind */
    if(getBumperLeft() && getBumperRight())
    {
        writeString_P("Bumper Left and Right \n");
    }
    else if(getBumperLeft() && getBumperRight() == false )
    {
        writeString_P("Bumper Left \n");
        bumper = LEFT;
        initBumper = LEFT;
    }
    else if(getBumperRight())
    {
        writeString_P("Bumper Left \n");
        bumper = RIGHT;
        initBumper = RIGHT;
    }
    angle = 20;
    rotateAheadWall();
}
void rotateAheadWall()
{
    if(bumper == initBumper)
    {
        writeString_P("rotateAheadWall - Zürucksetzen \n");
        move(40, BWD, DIST_MM(500), true);
        writeString_P("rotateAheadWall - Drehen \n");
        rotate(40, bumper, angle, true);
        writeString_P("rotateAheadWall - Vorwärtsfahren \n");
        move(40, FWD, DIST_MM(500), true);
        writeString_P("rotateAheadWall - Winkel verkleinern \n");
        angle = angle - 5;
        /*-----------------------------------*/
        writeString("Rekursionsaufruf Nr.: ");
        writeInteger(i++, DEC);
        writeString("\n");
        /*-----------------------------------*/
        rotateAheadWall();
    }
}

int main(void)
{

    initRobotBase();
    powerON();

    BUMPERS_setStateChangedHandler(checkBumper);

    moveAtSpeed(40,40);

    while(1)
    {
        task_Bumpers();
        task_motionControl();
        task_ADC();
    }

    return 0;
}
