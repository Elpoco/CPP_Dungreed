#include "Stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

GameNode* SceneManager::_currentScene = nullptr;
GameNode* SceneManager::_loadingScene = nullptr;
GameNode* SceneManager::_readyScene = nullptr;

DWORD CALLBACK loadingThread(LPVOID prc)
{
	// 교체될 씬의 함수 실행
	SceneManager::_readyScene->init();

	// 현재 씬을 교체될 씬으로 변경
	SceneManager::_currentScene = SceneManager::_readyScene;

	// 로딩 씬 해제
	SceneManager::_loadingScene->release();
	SceneManager::_currentScene = nullptr;
	SceneManager::_readyScene = nullptr;

	return 0;
}

HRESULT SceneManager::init(void)
{
	SceneManager::_loadingScene = nullptr;
	SceneManager::_currentScene = nullptr;
	SceneManager::_readyScene = nullptr;

	return S_OK;
}

void SceneManager::release(void)
{
	mapSceneIter miSceneList = _mSceneList.begin();

	// 라인수가 짧다고 좋은 코드는 아님 포인터 체크 잘하고 지우기
	//for each(auto scene in _mSceneList)
	//{
	//	scene.second->release();
	//	SAFE_DELETE(scene.second);
	//}

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != nullptr)
		{
			// 안전에 안전
			if (miSceneList->second == _currentScene)
			{
				miSceneList->second->release();
			}

			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	_mSceneList.clear();
}

void SceneManager::update(void)
{
	// 현재 씬이 존재하면 현재 씬만 갱신
	if (_currentScene) _currentScene->update();
}

void SceneManager::render(void)
{
	// 현재 씬이 존재하면 현재 씬만 렌더
	if (_currentScene) _currentScene->render();
}

// 씬 추가
GameNode* SceneManager::addScene(string sceneName, GameNode * scene)
{
	// 씬이 없다면 리턴
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

GameNode* SceneManager::addLoadingScene(string loadingSceneName, GameNode * scene)
{
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

// 씬 변경
HRESULT SceneManager::changeScene(string sceneName)
{
	// 변경하려고 하는 씬을 찾는다
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;

	if (find->second == _currentScene) return S_OK;

	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		_currentSceneName = sceneName;

		return S_OK;
	}

	return E_FAIL;
}
