#pragma once

typedef struct Vec2
{
	float x, y;
} Vec2;

typedef struct Vec3
{
	float x, y, w;
} Vec3;

typedef struct Vec4
{
	float x, y, w, h;
} Vec4;

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define MIN_WINDOW_WIDTH 640
#define MIN_WINDOW_HEIGHT 480

#define PARTICLE_SCALE 5
