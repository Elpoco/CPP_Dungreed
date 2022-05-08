#pragma once

class Skill
{
protected:
	string _iconName;
	float _runTime;
	float _cooltime;

public:
	Skill();
	virtual ~Skill();

	virtual void run(float x, float y, float angle = 0.0f) {}
	string getIconName() { return _iconName; }
	float getCooltime() { return _cooltime * PLAYERMANAGER->getSkillCooltime(); }
	float getRunTime() { return _runTime; }
	BOOL isUsing() { return _runTime + _cooltime * PLAYERMANAGER->getSkillCooltime() < TIMEMANAGER->getWorldTime(); }

};

