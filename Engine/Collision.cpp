#include "pch.h"
#include "Collision.h"
#include "GameObject.h"

Collision::Collision(GameObject* object) :
	mGameObject(object),
	mIsCollision(false)
{

}

Collision::~Collision()
{

}