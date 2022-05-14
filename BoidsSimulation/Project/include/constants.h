#pragma once
#define WIDTH 1500
#define HEIGHT	900

#define GWIDTHPer 0.75f
#define GWIDTH (int(WIDTH * GWIDTHPer))
#define GHEIGHT (HEIGHT)
#define GOFFSET (MWIDTH)

#define MWIDTHPer 0.25f
#define MWIDTH (int(WIDTH * MWIDTHPer))
#define MHEIGHT (HEIGHT)

#define WORLDSIZE 200
#define REALWORLDSIZE (WORLDSIZE*10)

#define QUADCAPACITY 5

#define BOIDRADIUS 6
#define BOIDSIGHT 35
#define SEPRANGE 15
#define MAXVISUALRANGE (BOIDSIGHT*2)
#define MINVISUALRANGE (BOIDSIGHT-20)
#define TRAILSIZE 50

//#define ALIGNMENT 0.05f
//#define COHESION 0.005f
//#define SEPARATION 0.05f

#define ALIGNMENT 0.05f
#define COHESION 0.005f
#define SEPARATION 0.05f

#define ESCAPEFORCE 5
#define CHASINGFORCE 5

#define MAXSPEED 20.f
#define MINSPEED 5.f
#define MAXFORCE 0.5f
#define TURNFACTOR 1.f
#define BORDERSIZE 50

#define TABNUMBER 3