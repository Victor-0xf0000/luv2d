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
	};
};
