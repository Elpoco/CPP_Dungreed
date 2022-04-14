#pragma once
class SoundLoader
{
public:
	SoundLoader();
	~SoundLoader();

	HRESULT init();
	void release();

	void loadSounds();

};

