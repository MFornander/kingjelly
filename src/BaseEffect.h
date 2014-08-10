#pragma once
#include "KingJelly.h"
#include "lib/effect.h"
#include "lib/color.h"

/**
 * Base class for all KingJelly effects.
 * Please look at PerlinRainbow for a full example. */
class BaseEffect: public Effect
{
public:
	enum EInput
	{
		Pot0 = 0,
		Pot1,
		Pot2,
		Pot3,
		JoyUp,
		JoyDown,
		kInputCount,
	};

	/// Input setter used by main loop to transfer controller data
	/// TODO: refactor with less hardcoded counts
	void SetInput(EInput index, float value);

	/// Print out all inputs every second in verbose mode
	virtual void debug(const DebugInfo& info);


protected:
	BaseEffect();

	/// Input getter used by the effects
	float Input(EInput index) const;

	/// Return true if the given input was non-zero last call and zero this call
	bool InputClicked(EInput index);

	/// Control ioValue with JoyUp/JoyDown and bound it to min/max
	void InputJoystick(int32_t& ioValue, int32_t min, int32_t max);

	// FIELDS
	vector<float> mCurrentInputs;
	vector<bool>  mLastDown;
};

/**
 * Efficient access to jelly strand+led with a single ldiv float operation. */
class JellyPixel
{
public:
	static const uint32_t kStrandCount = 16;  // Strands on Jelly
	static const uint32_t kLedCount = 100;    // LEDs per strand

	JellyPixel(const Effect::PixelInfo& pixelInfo) :
		mJellyInfo(ldiv(pixelInfo.index, kLedCount))
	{}

	uint32_t Strand() const { return static_cast<uint32_t>(mJellyInfo.quot); }
	uint32_t Led() const    { return static_cast<uint32_t>(mJellyInfo.rem); }

	/// LED's location on a 2D plane if the strands were laid out radially with a radius of 1
	Vec2 Radial() const;

	/// LED's location on a 2D plane if the strands were laid out flat as a square with length 1
	Vec2 Square() const;

private:
	const ldiv_t mJellyInfo;
};

// Helper macros and functions for debugging
#define LVAL(a) " " #a "=" << (a)
inline ostream& operator<<(ostream& os, const Vec2& vec) { return os << '[' << vec[0] << ',' << vec[1] << ']'; }
inline ostream& operator<<(ostream& os, const Vec3& vec) { return os << '[' << vec[0] << ',' << vec[1] << ',' << vec[2] << ']'; }

/// Macro to reduce code duplication since most effect declarations look the same
#define EFFECT(name) \
class name : public BaseEffect \
{ \
public: \
	static BaseEffect* Create() { return new name(); }             /* Required factory method for all effects */ \
	virtual void beginFrame(const FrameInfo& frame);               /* Called once per frame */ \
	virtual void shader(Vec3& rgb, const PixelInfo& pixel) const;  /* Called once per LED */ \
private: \
	name();  /* Private ctor forcing factory-only contruction */
