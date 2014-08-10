#include "EffectMattias.h"
#include "lib/noise.h"
#include "lib/color.h"

// --- PerlinRainbow ---
PerlinRainbow::PerlinRainbow() :
	mCycle(0),
	mSaturation(0),
	mVerticalOffset(0)
{}

void PerlinRainbow::beginFrame(const FrameInfo& frame)
{
	const float speed2 = Input(Pot1);
	mSaturation = Input(Pot2);
	mCycle = fmodf(mCycle + frame.timeDelta * speed2, 2 * M_PI);
	mVerticalOffset += Input(Pot3) * 2.0f * frame.timeDelta;
}

void PerlinRainbow::shader(Vec3& rgb, const PixelInfo& pixel) const
{
	Vec3 point = pixel.point;
	point[1] += mVerticalOffset;

	float distance = len(pixel.point);
	float perlin3 = noise3(point);
	float wave1 = sinf(0.5 * distance - mCycle) + perlin3;
	float wave2 = sinf(3.0 * distance - mCycle) - perlin3;
	float wave3 = sinf(mCycle);

	hsv2rgb(rgb, wave1, mSaturation * wave3, wave2);
}


// --- ColorFlow ---
ColorFlow::ColorFlow() :
	mPerlinOctaves(1),
	mPosition{0}
{}

void ColorFlow::beginFrame(const FrameInfo& frame)
{
	if (InputClicked(JoyUp))
		mPerlinOctaves = min(5, mPerlinOctaves+1);
	if (InputClicked(JoyDown))
		mPerlinOctaves = max(0, mPerlinOctaves-1);

	for (int index = 0; index < 3; ++index)
		mPosition[index] += frame.timeDelta * (Input(static_cast<EInput>(index)) - 0.5f);
}

void ColorFlow::shader(Vec3& rgb, const PixelInfo& pixel) const
{
	for (int index = 0; index < 3; ++index)
	{
		Vec3 perlinPoint(pixel.point);
		perlinPoint[1] += mPosition[index];
		rgb[index] = fbm_noise3(perlinPoint, mPerlinOctaves);
	}
}

// --- GlitterEffect ---
Glitter::Glitter() :
	mChance(0.5f),
	mCycle(0),
	mBrightness(0)
{}

void Glitter::beginFrame(const FrameInfo& frame)
{
	mChance = Input(Pot1) * RAND_MAX;
	mCycle += frame.timeDelta;
	mBrightness = 2.0f * Input(Pot2) + sin(mCycle) / 2.0f;
}

void Glitter::shader(Vec3& rgb, const PixelInfo& pixel) const
{
	float value = static_cast<uint32_t>(rand()) <= mChance ? mBrightness : mBrightness - 0.2f;
	Vec3 perlinPoint(pixel.point);
	perlinPoint[1] += mCycle;
	rgb.MakeBlock(value * fbm_noise3(perlinPoint, 3));
}

// --- Water ---
Water::Water() :
	mTime(0),
	mIterations(5),
	mSize(0.5f),
	mGain(0.5f),
	mHue(0.5f)
{}

void Water::beginFrame(const FrameInfo& frame)
{
	mTime += frame.timeDelta;
	InputJoystick(mIterations, 1, 10);

	mSize = 1.0f + Input(Pot1) * 10.0f;
	mGain = 1.1f + Input(Pot2) / 2.0f;
	mHue =  Input(Pot3);
}

void Water::shader(Vec3& rgb, const PixelInfo& pixel) const
{
	Vec2 location = JellyPixel(pixel).Square();
	Vec2 p = location * mSize - Vec2().MakeBlock(2.0f * mSize);
	Vec2 i = p;
	float c = 1.0f;
	float intensity = 0.05f;

	for (int n = 0; n < mIterations; n++)
	{
		float time = mTime * (1.0f - (3.0f / static_cast<float>(n+1)));

		i = p + Vec2(cos(time - i[0]) + sin(time + i[1]),
		             sin(time - i[1]) + cos(time + i[0]));

		c += 1.0f / len(Vec2(p[0] / (sin(time + i[0]) / intensity),
		                     p[1] / (cos(time + i[1]) / intensity)));
	}

	c /= static_cast<float>(mIterations);
	c = mGain - sqrt(c);

	hsv2rgb(rgb, mHue, 0.5f, c*c*c*c);
	rgb += Vec3().MakeBlock(c*c*c*c);
}


// --- Bounce ---
Bounce::Bounce() :
	mTime(0),
	mSpread(0),
	mHue(0),
	mHueRange(0)
{}

void Bounce::beginFrame(const FrameInfo& frame)
{
	mTime += frame.timeDelta;
}

float Ring(float time, const Vec2& pos)
{
	return sin( cos(time/4.0f) + 1.2f * cos(time) * len(pos) * 8.0f);
}

void Bounce::shader(Vec3& rgb, const PixelInfo& pixel) const
{
	Vec2 location = JellyPixel(pixel).Radial();

	rgb = Vec3(
		Ring(mTime,  location/1.2f),
		0.5f + Ring(mTime, location/1.3f - Vec2().MakeBlock(0.3f * sin(mTime * 0.9f))),
		0.3f + Ring(mTime, location/1.5f + Vec2().MakeBlock(0.2f * sin(mTime))));
}


// --- Swirl ---
Swirl::Swirl() :
	mTime(0),
	mGrain(0),
	mHue1(0),
	mHue2(0)
{}

void Swirl::beginFrame(const FrameInfo& frame)
{
	mTime += frame.timeDelta / 10;
	mGrain = Input(Pot1);
	mHue1 = Input(Pot2);
	mHue2 = Input(Pot3);
}

void Swirl::shader(Vec3& rgb, const PixelInfo& pixel) const
{
	Vec2 location = JellyPixel(pixel).Radial();
	float x = len(location) * mGrain;
	float c = pow(2.0f * fabs((x - mTime) - floorf(x - mTime) - 0.5f), 2.0f);
	c = sin(atan2(location[1], location[0]) + c * M_PI * 4.0f);

	if (mHue1 == 0.0f && mHue2 == 0.0f)
		hsv2rgb(rgb, 1.0f, 0.0f, c);
	else if (mHue2 == 0.0f)
		hsv2rgb(rgb, mHue1, 0.5f, c);
	else
		hsv2rgb(rgb, mix(mHue1, mHue2, c), 0.5f, c + 0.3f);
}


// --- SinusSnake ---
SinusSnake::SinusSnake() :
	mTime(0)
{}

void SinusSnake::beginFrame(const FrameInfo& frame)
{
	mTime += frame.timeDelta;
}

float Band(const Vec2& pos, float amplitude, float frequency, float time)
{
	const float scale = 0.8f;
	float wave = scale * amplitude * sin(1.0f * M_PI * frequency * pos[0] + time) / 5.0f;
	float light = Clip(amplitude * frequency * 0.02f,
	                   0.05f + 0.001f / scale,
			           50.0f) * scale / fabs(wave - pos[1] + 0.5f);
	return light;
}

void SinusSnake::shader(Vec3& rgb, const PixelInfo& pixel) const
{
	Vec2 location = JellyPixel(pixel).Square();
	Vec3 color = Vec3(1.1f + cos(mTime), sin(mTime)+1.2, sin(3.14 * mTime));

	const float time = mTime * 0.7f + location[0] * 10.0f;
	float spectrum = Band(location, 1.0f * cos(sin(3.14f * time)), sin(cos(3.14f * time)), mTime);

	rgb = color * spectrum;
}

// --- Fire ---
Fire::Fire() :
	mTime(0),
	mScale(0)
{}

void Fire::beginFrame(const FrameInfo& frame)
{
	mTime += frame.timeDelta;
	mScale = Input(Pot1) * 10.0f;
	hsv2rgb(mHighLight, Input(Pot2), 1.0f, 0.7f); // Hard left = red
	hsv2rgb(mLowLight,  Input(Pot3) + 1.0f / 6, 1.0f, 1.0f); // Hard left = yellow
}

float Rand(const Vec2& n)
{
	float dummyIntpart;
	float fracPart = abs(modf(cos(dot(n, Vec2(12.9898f, 4.1414f))) * 43758.5453f, &dummyIntpart));

//	cout << LVAL(fracPart) << endl;
	return fracPart;
}

float SmoothStep(float edge0, float edge1, float x)
{
	float t = Clip((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
	float ss =  t * t * (3.0f - 2.0f * t);
//	cout << LVAL(ss) << endl;
	return ss;
}

float Noise(const Vec2& n)
{
	Vec2 b(floor(n[0]), floor(n[1]));
	Vec2 f = n - b;
	f[0] =  SmoothStep(0, 1, f[0]);
	f[1] =  SmoothStep(0, 1, f[1]);

	float noise = Mix(
			Mix(Rand(b),
				Rand(b + vl_x),
				f[0]),
			Mix(Rand(b + vl_y),
				Rand(b + vl_1),
				f[0]),
			f[1]);
//	cout << LVAL(n) << LVAL(b) << LVAL(f) << LVAL(noise) << endl;
	return noise;
}

// Fractional Brownian Amplitude
float Fbm(Vec2 n)
{
	float total = 0.0f;
	float amplitude = 1.0f;
	for (int i = 0; i < 4; i++)
	{
		total += Noise(n) * amplitude;
		n += n;
		amplitude *= 0.5f;
	}
//	cout << LVAL(total) << endl;
	return total;
}

void Fire::shader(Vec3& rgb, const PixelInfo& pixel) const
{
	// Colors
	static const Vec3 c1(0.0, 0.0, 0.1); // Black
//	static const Vec3 c2(0.7, 0.0, 0.0); // Light red
	static const Vec3 c3(0.2, 0.0, 0.0); // Dark red
//	static const Vec3 c4(1.0, 0.9, 0.0); // Yellow
	static const Vec3 c5(0.1, 0.1, 0.1); // Dark gray
	static const Vec3 c6(0.9, 0.9, 0.9); // Light gray

	Vec2 location = JellyPixel(pixel).Square();
	Vec2 pos(location[0] * mScale / 2.0f, location[1] * mScale); // Offset coordinates
	float q =     Fbm(pos + Vec2().MakeBlock(mTime * -0.1f)); // Noise offset for movement
	Vec2 r = Vec2(Fbm(pos + Vec2().MakeBlock(mTime *  0.7f + q - pos[0] - pos[1])),
			      Fbm(pos + Vec2().MakeBlock(mTime * -0.4f + q)));

//	cout << LVAL(location) << LVAL(pos) << LVAL(q) << LVAL(r);

	rgb = Mix(c1, mHighLight, Fbm(pos + r))
		+ Mix(c3, mLowLight, r[0])
		- Mix(c5, c6, r[1]);
//	cout << LVAL(rgb) << endl;

	rgb *= cos(M_PI/2 * location[1]); // Gradient towards dark top
//	cout << LVAL(rgb) << endl;
}


// --- Particles ---
Particles::Particles() :
	mTime(0),
	mCount(3),
	mSize(4),
	mHueRange(0.5f),
	mHueStart(0.5f)
{}

void Particles::beginFrame(const FrameInfo& frame)
{
	mTime += frame.timeDelta;
	InputJoystick(mCount, 1, kMaxCount);
	mSize = Input(Pot1) * 8.0f;
	mHueStart = Input(Pot2);
	mHueRange = Input(Pot3);
}

void Particles::shader(Vec3& rgb, const PixelInfo& pixel) const
{
	static float sTimeFactor[kMaxCount] = {1.1, 1.7, 2.1, 2.5, 3.6, 4.2, 4.4};
	Vec2 location = JellyPixel(pixel).Radial() * 2.1f;
	for (int32_t index = 0; index < mCount; ++index)
	{
		Vec3 color;
		hsv2rgb(color, mHueStart + mHueRange / mCount * index, 0.7f, 1.0f);
		rgb += color * ((1.0f + mSize + index / 10.0f ) / 20.0f / len(location - Vec2(
				sin(mTime) + sin(mTime * sTimeFactor[index]),
				cos(mTime) + cos(mTime * sTimeFactor[index]))));
	}
}
