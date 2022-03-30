#pragma once

typedef struct tagARGB
{
	BYTE a;
	BYTE r;
	BYTE g;
	BYTE b;

	tagARGB() {}
	tagARGB(BYTE a, BYTE r, BYTE g, BYTE b)
	{
		this->a = a;
		this->r = r;
		this->g = g;
		this->b = b;
	}
} ARGB;