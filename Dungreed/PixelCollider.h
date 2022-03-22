#pragma once

class PixelCollider
{
private:
	struct tagPixelColliderInfo
	{
		RECT* rc;
		float* x;
		float* y;
		bool* isJump;
	};

private:
	tagPixelColliderInfo _colliderInfo;
	int _proveY;

public:
	HRESULT init(RECT* rc, float* x, float* y, bool* isJump);
	void release(void);
	void update(void); 
	void render(HDC hdc);

	PixelCollider() {}
	~PixelCollider() {}
};
