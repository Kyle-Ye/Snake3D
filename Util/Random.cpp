#include "../Head/Random.h"
#include <stdlib.h>
#include <time.h>

bool Random::isinited = false;

int Random::Next()
{
	if (!isinited)
		InitSeed();
	return rand();
}

float Random::Range(float l, float r)
{
	if (!isinited)
		InitSeed();
	if (l > r) {
		return 0.0f;
	}
	float ratio = (float)rand() / (float)RAND_MAX;
	float result = l + ratio * (r - l);
	return result;
}

void Random::InitSeed()
{
	srand((unsigned)time(NULL));
	isinited = true;
}
