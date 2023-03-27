#pragma once

namespace luv
{
  static float inv255f = 1.f / 255.f;
	struct LUV2D_ENGINE_API Color
	{
		int r;
		int g;
		int b;
		int a;
		
		Color() {}

		Color(int r, int g, int b, int a)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}

    float norm_r()
    {
      return this->r * inv255f;
    }

    float norm_g()
    {
      return this->g * inv255f;
    }

    float norm_b()
    {
      return this->b * inv255f;
    }

    float norm_a()
    {
      return this->a * inv255f;
    }
	};
};
