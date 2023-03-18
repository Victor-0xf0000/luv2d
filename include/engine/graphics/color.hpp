#pragma once

namespace luv
{
	struct Color
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
      return this->r / 255.f;
    }

    float norm_g()
    {
      return this->g / 255.f;
    }

    float norm_b()
    {
      return this->b / 255.f;
    }

    float norm_a()
    {
      return this->a / 255.f;
    }
	};
};
