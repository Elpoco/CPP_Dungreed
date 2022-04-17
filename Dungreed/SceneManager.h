#pragma once
#include "SingletonBase.h"

class GameNode;

class SceneManager : public SingletonBase<SceneManager>
{
public:
	typedef map<string, GameNode*> mapSceneList;
	typedef map<string, GameNode*>::iterator mapSceneIter;

private:
	static GameNode* _currentScene;
	static GameNode* _loadingScene;
	static GameNode* _readyScene;

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	string _currentSceneName;

	BOOL _isChangeScene;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	GameNode* addScene(string sceneName, GameNode* scene);
	GameNode* addLoadingScene(string loadingSceneName, GameNode* scene);

	HRESULT changeScene(string sceneName);

	friend DWORD CALLBACK loadingThread(LPVOID prc);

	inline string getCurrentSceneName() { return _currentSceneName; }
	inline void setChangeScene(BOOL isChange) { _isChangeScene = isChange; }
	inline BOOL getChangeScene() { return _isChangeScene; }

	SceneManager() {}
	~SceneManager() {}

};

