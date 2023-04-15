#include "PreCompiledHeader.h"
#include "StageThree.h"

StageThree::StageThree():
Scene("StageThree")
{
}

StageThree::~StageThree()
{
}

void StageThree::BuildScene()
{
	Scene::BuildScene();
	
	SoundManager::GetInstance()->Play(500004,1.0f);
}