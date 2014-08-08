/*---------------------------------------------------------
 *   Includes
 *--------------------------------------------------------*/
#include "KingJelly.h"
#include "OriginalRainEffect.h"

BaseEffect* OriginalRainEffect::Create() {

	return new OriginalRainEffect();
}

OriginalRainEffect::OriginalRainEffect() :
	totalTime(4) {

	for (int dropIndex = 0; dropIndex < kMaxDropCount; ++dropIndex) {
		mDrops[dropIndex].birth = 0;
		mDrops[dropIndex].tail = 0;
	}
}

void OriginalRainEffect::beginFrame(const FrameInfo& frame) {
	totalTime += frame.timeDelta;
	//cout << "total time: " << totalTime << "\n";

	int dropCount = 100 * Input(Pot1);
	float hueShift = Input(Pot2) - 0.5f;

	bool dropAdded = false;
	for (int dropIndex = 0; dropIndex < dropCount; ++dropIndex) {
		RainDrop& drop = mDrops[dropIndex];
		int led = 100 * (totalTime - drop.birth)  / 3 ;
		//cout << "led: " << led << "\n";
		if (led < 100 + drop.tail) {
			for (uint32_t tailIndex = 0; tailIndex < drop.tail; ++tailIndex) {
				float brightness = (255 - tailIndex * 255 / drop.tail) / 255.0f;
				int32_t newLed = led - tailIndex;
				if (newLed >= 0 && newLed < static_cast<int32_t>(JellyPixel::kLedCount)) {
					pixels[drop.strip][newLed].h = drop.hue;
					pixels[drop.strip][newLed].s = drop.saturation;
					pixels[drop.strip][newLed].v = brightness;
				}
			}
		}

		if (led >= 100 + drop.tail && !dropAdded && (random() & 0xF)) {
			drop.birth = totalTime;
			drop.strip = random() % JellyPixel::kStrandCount;
			drop.hue = (112 + random() % 96) / 255.0f + hueShift;
			drop.saturation = (64 + random() % 160 ) / 255.0f;
			drop.tail = 5 + random() % 40;
			dropAdded = true;
		}
	}
}

void OriginalRainEffect::shader(Vec3& rgb, const PixelInfo& pixel) const {
	JellyPixel jp = JellyPixel(pixel);
	Hsv hsv = pixels[jp.Strand()][jp.Led()];

	hsv2rgb(rgb, hsv.h, hsv.s, hsv.v);
}
