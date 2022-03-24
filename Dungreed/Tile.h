#pragma once
class Tile
{
private:
	enum class PixelTileType
	{

	};

private:
	RECT _rc;
	float _x;
	float _y;
	PixelTileType _type;

	bool _isClick;

public:
	HRESULT init(void);
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(HDC hdc);

	Tile();
	~Tile() {}
};

