#pragma once
#include "Skill.h"

class CosmosSwrod : public Skill
{
private:

public:
	CosmosSwrod();
	virtual ~CosmosSwrod();

	virtual void run(float x, float y, float angle = 0.0f) override;

};

