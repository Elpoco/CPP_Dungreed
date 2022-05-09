#pragma once
#include "SingletonBase.h"
#pragma warning(disable:4996)

namespace PlayerManagerSet
{
	constexpr float DEFAULT_DASH_TIME = 1.5f;
	constexpr int DEFAULT_DASH_CNT = 2;
	constexpr int DEFAULT_HP = 80;
}

class PlayerManager : public SingletonBase<PlayerManager>
{
private:
	BOOL _isDie;
	BOOL _isClear;
	BOOL _isReturn;
	float _checkTime;

	int _level;

	float _dashChargeTime;
	float _dashTime;
	int _dashMaxCnt;
	int _dashCnt;

	int _maxHp;
	int _curHp;

	int _coin;

	BOOL _isTrueDmg;
	BOOL _isMultiBullet;
	BOOL _isSizeBullet;

	POINT* _ptPlayerBody;
	POINT* _ptPlayerHand;
	BOOL* _isPlayerLeft;

	int _power;
	int _bulletPower;
	int _defense;
	float _atkSpeed;
	float _shootSpeed;
	float _reloadSpeed;
	float _skillCooltime;

	int _wrath;
	int _patience;
	int _greed;

public:
	PlayerManager();
	~PlayerManager();

	HRESULT init();
	void release();
	void update();
	void render();

	int getLevel() { return _level; }
	int getAbility() { return _level - _wrath - _patience - _greed; }

	void wrathUp() { _wrath++; }
	void patienceUp() { _patience++; }
	void greeUp() { _greed++; setHp(AbilitySet::MAX_HP); }
	int getWrath() { return _wrath; }
	int getPatience() { return _patience; }
	int getGreed() { return _greed; }

	void resetAbility() { setHp(-_greed * AbilitySet::MAX_HP); _wrath = _patience = _greed = 0; }
	void updateMaxHp() { _curHp = _maxHp = PlayerManagerSet::DEFAULT_HP + _greed * AbilitySet::MAX_HP; }

	void dash();
	void chargeDash();
	BOOL canDash() { return _dashCnt < 1; }
	int getDashCnt() { return _dashCnt; }
	int getDashMaxCnt() { return _dashMaxCnt; }
	void addDashCnt(int cnt) { _dashMaxCnt += cnt; }

	// 골드
	void addCoin(int coin) { _coin += coin; }
	void useCoin(int coin) { _coin -= coin; }
	int getCoin() { return _coin; }
	char* getCoinChar()
	{
		string str = to_string(_coin);
		int len = str.length();
		char* arrChar;
		arrChar = new char[len];
		strcpy(arrChar, str.c_str());
		return arrChar;
	}

	// 체력
	void hit(int dmg);
	void recovery(int hp);
	int getMaxHp() { return _maxHp - PlayerManagerSet::DEFAULT_HP; }
	int getHp() { return _curHp; }

	int getPower() { return _power + _wrath * AbilitySet::POWER; }
	int getBulletPower() { return _power + _wrath * AbilitySet::POWER + _bulletPower; }
	void powerUp(int power) { _power += power; }
	int getDefense() { return _defense + _patience * AbilitySet::DEFENSE; }
	void defenseUp(int defense) { _defense += defense; }

	void setPower(int power) { _power += power; }
	void setBulletPower(int power) { _bulletPower += power; }
	void setDef(int def) { _defense += def; }
	void setHp(int hp)
	{
		_maxHp += hp;
		if (_curHp > 0)
		{
			_curHp += hp; 
		}
		if (_curHp < 0) _curHp = 1;
	}
	void setAtkSpeed(float speed) { _atkSpeed += speed; }
	void setShootSpeed(float speed) { _shootSpeed += speed; }
	float getAtkSpeed() { return _atkSpeed; }
	float getShootSpeed() { return _shootSpeed; }
	void setReloadSpeed(float speed) { _reloadSpeed += speed; }
	float getReloadSpeed() { return _reloadSpeed; }
	void setSkillCooltime(float time) { _skillCooltime += time; }
	float getSkillCooltime() { return _skillCooltime; }

	// 아이템 관련
	void setTrueDmg(BOOL b) { _isTrueDmg = b; }
	BOOL getTrueDmg() { return _isTrueDmg; }
	void setMultiBullet(BOOL b) { _isMultiBullet = b; }
	BOOL getMultiBullet() { return _isMultiBullet; }
	void setSizeBullet(BOOL b) { _isSizeBullet = b; }
	BOOL getSizeBullset() { return _isSizeBullet; }

	void setPlayerBody(POINT* pt) { _ptPlayerBody = pt; }
	void setPlayerHand(POINT* pt) { _ptPlayerHand = pt; }
	void setPlayerLeft(BOOL* isLeft) { _isPlayerLeft = isLeft; }
	POINT getPlayerBody() { return *_ptPlayerBody; }
	POINT getPlayerHand() { return *_ptPlayerHand; }
	BOOL getPlayerIsLeft() { return *_isPlayerLeft; }

	BOOL isDie() { return _isDie; }
	void setDie(BOOL b);
	void clearDungeon();
	BOOL isReturn() { return _isReturn; }
	void returnTown();

	void levelUp(int level);

};

