#pragma once
//
//color.h
//

#ifndef COLOR_H__
#define COLOR_H__

namespace df {
	//Colors Dragonfly recognizes
	enum Color {
		UNDEFINED_COLOR = -1,
		BLACK = 0,
		RED = 1,
		GREEN = 2,
		YELLOW = 3,
		BLUE = 4,
		MAGENTA = 5,
		CYAN = 6,
		WHITE = 7,
	};

	//If color is not specified, default to this color
	const Color COLOR_DEFAULT = WHITE;

}

#endif