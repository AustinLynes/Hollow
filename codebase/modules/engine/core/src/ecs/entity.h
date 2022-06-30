#pragma once
#include "cpch.h"
#include "cdefs.h"

#include <mathematics.h>

struct Entity {
	matrix4f world;
public:
	void set_position(float3 pos) { world.row3 = { pos.x, pos.y, pos.z, world.row3.w }; }
	void set_scale(float3 scale) { 
		world.row0.x = scale.x; 
		world.row1.y = scale.y; 
		world.row2.z = scale.z; 
	}
	
	float3 position() { return world.row3.xyz(); }
	float3 scale() { return { world.row0.x , world.row1.y , world.row2.z }; };

	float3 right() { return world.row0.xyz(); }
	float3 up() { return world.row1.xyz(); }
	float3 forward() { return world.row2.xyz(); }
};