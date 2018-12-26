#pragma once

class Random
{
public:
	static int Next();
	static float Range(float l, float r);

private:
	static bool isinited;
	static void InitSeed();

};
