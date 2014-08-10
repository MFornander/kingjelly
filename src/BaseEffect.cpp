#include "BaseEffect.h"
#include <math.h>"

BaseEffect::BaseEffect() :
	mCurrentInputs(kInputCount),
	mLastDown(kInputCount)
{}

void BaseEffect::SetInput(EInput input, float value)
{
	if (input < kInputCount)
		mCurrentInputs.at(input) = value;
}

float BaseEffect::Input(EInput input) const
{
	if (input < kInputCount)
		return mCurrentInputs.at(input);
	return 0;
}

bool BaseEffect::InputClicked(EInput input)
{
	if (input >= kInputCount)
		return false;

	const bool clicked = Input(input) == 0 && mLastDown.at(input);
	mLastDown[input] = Input(input) != 0;
	return clicked;
}

void BaseEffect::InputJoystick(int32_t& ioValue, int32_t min, int32_t max)
{
	if (InputClicked(JoyUp))
		++ioValue;
	else if (InputClicked(JoyDown))
		--ioValue;

	ioValue = Clip(ioValue, min, max);
}


void BaseEffect::debug(const DebugInfo& /*info*/)
{
	fprintf(stderr, "Input:[%3u,%3u,%3u,%3u,%3u,%3u]",
		static_cast<uint32_t>(100 * Input(Pot0)),
		static_cast<uint32_t>(100 * Input(Pot1)),
		static_cast<uint32_t>(100 * Input(Pot2)),
		static_cast<uint32_t>(100 * Input(Pot3)),
		static_cast<uint32_t>(100 * Input(JoyUp)),
		static_cast<uint32_t>(100 * Input(JoyDown)));
}

Vec2 JellyPixel::Radial() const
{
	const float angle = 2.0f * M_PI / kStrandCount * Strand();
	const float distance = static_cast<float>(Led()) / kLedCount;

	return Vec2(distance * cos(angle), distance * sin(angle));
}

Vec2 JellyPixel::Square() const
{
	const float x = 1.0f / kStrandCount * Strand();
	const float y = 1.0f - static_cast<float>(Led()) / kLedCount;

	return Vec2(x,y);
}

