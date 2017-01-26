#pragma once
#include "Init.hh"
struct Transform {
	union {
		SDL_Rect rect;
		struct { Sint32 x, y, w, h; };
	};
	Transform(int x_, int y_) :x(x_), y(y_), w(0), h(0) {};

	friend bool operator==(Transform &lhs, Transform &rhs) {
		return (lhs.x == rhs.x &&
			lhs.y == rhs.y &&
			lhs.w == rhs.w &&
			lhs.h == rhs.h);
	};
};