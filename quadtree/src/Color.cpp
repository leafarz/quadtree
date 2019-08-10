#pragma once

#include "Color.h"

// These colors should only be the ones used (because of COLOR_ID hack)
const Color Color::White	=	Color(	255,	255,	255,	255);
const Color Color::Black	=	Color(	0,		0,		0,		255);
const Color Color::Red		=	Color(	255,	0,		0,		255);
const Color Color::Green	=	Color(	0,		255,	0,		255);
const Color Color::Blue		=	Color(	0,		0,		255,	255);
uint8_t Color::COLOR_ID = 0;

Color::Color(void)
	: r(0), g(0), b(0), a(255), ID(++COLOR_ID)
{ }

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	: r(r), g(g), b(b), a(a), ID(++COLOR_ID)
{ }
