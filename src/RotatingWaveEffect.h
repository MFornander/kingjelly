#pragma once
#include "BaseEffect.h"

EFFECT(D001, RotatingWaveEffect)
	static const int maxWaves = 10;
	int waveCount;
	float wavePeriods[maxWaves];

	float interpolateFloat(float a, float b, float distance);
	float totalTime;

	struct Hsv {
		Hsv() :
				h(0.0f), s(0.0f), v(0.0f) {
		}
		Hsv(float h, float s, float v) :
				h(h), s(s), v(v) {
		}

		float h;
		float s;
		float v;
	};

	//Hsv interpolate(Hsv a, Hsv b, float distance);

	Hsv pixels[JellyPixel::kStrandCount][JellyPixel::kLedCount];
	Hsv waveColors[maxWaves];


	Hsv interpolate(Hsv a, Hsv b, float distance) {
		Hsv result = Hsv();
		result.h = interpolateFloat(a.h, b.h, distance);
		result.s = interpolateFloat(a.s, b.s, distance);
		result.v = interpolateFloat(a.v, b.v, distance);
		return result;
	}
};
