#include "pch.h"
#include "Math.h"

float getDistance(vec to, vec from)
{
	return (float)
		(sqrt(
			powf(to.x - from.x, 2.0) +
			powf(to.y - from.y, 2.0) +
			powf(to.z - from.z, 2.0)
		));

}
vec normalizeAngle(vec angle)
{
	vec newAngle = angle;
	if (newAngle.x > 180)
		newAngle.x -= 360;
	if (newAngle.x < -180)
		newAngle.x += 360;
	return newAngle;
}