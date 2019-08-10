#ifndef		COLOR_H
#define		COLOR_H
#pragma once

#include <iostream>

struct Color
{
public:
	// These colors should only be the ones used (because of COLOR_ID hack)
	static const Color White;
	static const Color Black;
	static const Color Red;
	static const Color Green;
	static const Color Blue;

	static uint8_t COLOR_ID;

	Color(void);
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

public:
	uint8_t r, g, b, a;
	uint8_t ID;
};
#endif