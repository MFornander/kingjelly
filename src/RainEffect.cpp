#include "RainEffect.h"
#include "lib/color.h"
#include "lib/effect.h"
#include "lib/effect_runner.h"
#include "lib/noise.h"

#include <math.h>
#include <algorithm>

#define NUM_LEDS            (NUM_LEDS_PER_STRAND * STRANDS)
#define NUM_LEDS_PER_STRAND 100
#define STRANDS             16

RainEffect::RainEffect() :
	offset (0),
	noise  (1.5)
{}

void RainEffect::beginFrame(const FrameInfo& frame)
{
	// advance down the strand 
	offset++;
	//offset %= NUM_LEDS_PER_STRAND;
}

void RainEffect::shader(Vec3& rgb, const PixelInfo& pixel) const
{

	// position within a given strand
	int pos = pixel.index % (int)(NUM_LEDS_PER_STRAND * noise);

	// distance from the center pixel of the wave
    int distance = std::abs(std::min((pos - offset/10) % NUM_LEDS_PER_STRAND, 
	        	                     (offset/10 - pos) % NUM_LEDS_PER_STRAND));

    // get dimmer based on distance from center
	float wave = std::max(0.0,(10-distance)/10.0);

	hsv2rgb(rgb, 0.5, 1.0, wave);

}

