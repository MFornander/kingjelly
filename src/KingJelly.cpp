#include "KingJelly.h"

#include <math.h>
#include "lib/color.h"
#include "lib/effect.h"
#include "lib/effect_runner.h"
#include "lib/noise.h"


class MyEffect : public Effect
{
public:
    MyEffect()
        : cycle (0)
	{}

    float cycle;

    virtual void beginFrame(const FrameInfo& frame) override
    {
        const float speed = 1.0;
        cycle = fmodf(cycle + frame.timeDelta * speed, 2 * M_PI);
    }

    virtual void shader(Vec3& rgb, const PixelInfo& pixel) const override
    {
        float distance = len(pixel.point);
        float perlin3 = noise3(pixel.point);
        float wave1 = sinf(0.5 * distance - cycle) + perlin3;
        float wave2 = sinf(3.0 * distance - cycle) - perlin3;
        float wave3 = sinf(cycle);
        hsv2rgb(rgb, wave1, wave3, wave2);
    }
};

int main(int argc, char** argv)
{
    EffectRunner r;

    MyEffect e;
    r.setEffect(&e);

    // Defaults, overridable with command line options
    r.setMaxFrameRate(1000);
    r.setLayout("scripts/jelly16x100.json");

    return r.main(argc, argv);
}
