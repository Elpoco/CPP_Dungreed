#pragma once
class EnemyHpBar
{
private:
	RECT _rcMaxHp;
	RECT _rcCurHp;
	float _x;
	float _y;

public:
	EnemyHpBar();
	~EnemyHpBar();

	HRESULT init();
	void release();
	void update(float x, float y, float per);
	void render(HDC hdc);

};

