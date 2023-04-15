#include "PreCompiledHeader.h"
#include "CollisionGrid.h"

CollisionGrid::CollisionGrid(Vector2D centerPos):
mCollisions(std::vector<Collision*>())
{
	SetTag("CollisionGrid");

	mTransform->SetPosition(centerPos);

	mCollisionOfGrid = AddAABBCollision();

	mCollisionOfGrid->SetSize({ 2000.f, 1000.f });
}

CollisionGrid::~CollisionGrid()
{

}