#pragma once
#include "Skill.h"

class LalaMagicWand : public Skill
{

public:
	LalaMagicWand();
	virtual ~LalaMagicWand();

	virtual void run(float x, float y, float angle = 0.0f) override;

};

