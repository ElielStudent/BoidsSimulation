#pragma once
//#define WIDTH 1200
#define WIDTH 1500
#define HEIGHT	900

#define GWIDTHPer 0.75
#define GWIDTH (int(WIDTH * GWIDTHPer))
#define GHEIGHT (HEIGHT)
#define GOFFSET (MWIDTH)

#define MWIDTHPer 0.25
#define MWIDTH (int(WIDTH * MWIDTHPer))
#define MHEIGHT (HEIGHT)

#define WORLDSIZE 200

#define QUADCAPACITY 10

#define BOIDSIGHT 30
#define SEPRANGE 20

#define ALIGNMENT 0.3
#define COHESION 0.7
#define SEPARATION 0.8

#define MAXSPEED 5 
#define MAXFORCE 0.5
#define TURNFACTOR 1
#define BORDERSIZE 50