#include "Stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

GameNode* SceneManager::_currentScene = nullptr;
GameNode* SceneManager::_loadingScene = nullptr;
GameNode* SceneManager::_readyScene = nullptr;

DWORD CALLBACK loadingThread(LPVOID prc)
{
	// ��ü�� ���� �Լ� ����
	SceneManager::_readyScene->init();

	// ���� ���� ��ü�� ������ ����
	SceneManager::_currentScene = SceneManager::_readyScene;

	// �ε� �� ����
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

	// ���μ��� ª�ٰ� ���� �ڵ�� �ƴ� ������ üũ ���ϰ� �����
	//for each(auto scene in _mSceneList)
	//{
	//	scene.second->release();
	//	SAFE_DELETE(scene.second);
	//}

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != nullptr)
		{
			// ������ ����
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
	// ���� ���� �����ϸ� ���� ���� ����
	if (_currentScene) _currentScene->update();
}

void SceneManager::render(void)
{
	// ���� ���� �����ϸ� ���� ���� ����
	if (_currentScene) _currentScene->render();
}

// �� �߰�
GameNode* SceneManager::addScene(string sceneName, GameNode * scene)
{
	// ���� ���ٸ� ����
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

// �� ����
HRESULT SceneManager::changeScene(string sceneName)
{
	// �����Ϸ��� �ϴ� ���� ã�´�
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
