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

#define WORLDSIZE 360
#define REALWORLDSIZE (WORLDSIZE*10)

#define QUADCAPACITY 5

#define BOIDRADIUS 6
#define BOIDSIGHT 50
#define SEPRANGE 20
#define MAXVISUALRANGE (BOIDSIGHT*2)
#define MINVISUALRANGE (BOIDSIGHT/2 + 5)

#define ALIGNMENT 0.3f
#define COHESION 0.7f
#define SEPARATION 0.8f

#define MAXSPEED 3 
#define MAXFORCE 0.5f
#define TURNFACTOR 1
#define BORDERSIZE 50