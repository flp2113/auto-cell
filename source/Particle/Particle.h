#include "../defs.h"

enum Particle_Type
{
	EMPTY = 0, SAND, ROCK, WATER
};

typedef struct Particle
{
	Vec4 color;
	Particle_Type type;
} Particle;