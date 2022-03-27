#pragma once
#include "SingletonBase.h"

class Camera;
class UI;
class Object;

class CameraManager : public SingletonBase<CameraManager>
{
private:
	typedef vector<UI*> vUI;
	typedef vector<UI*>::iterator viUI;

	typedef vector<Object*> vObjects;
	typedef vector<Object*>::iterator viObjects;

private:
	Camera* _camera;

	vUI _vUI;
	vObjects _vObjects;

public:
	CameraManager();
	~CameraManager();

	HRESULT init();
	void release();
	void update();
	void render();
	void renderObject();

	void addRender(Object* object);

	float getRelX(float x);
	float getRelY(float y);
	float getAbsX();
	float getAbsY();

	void moveX(float x);
	void moveY(float y);

	void setCameraPos(float x, float y);

};

