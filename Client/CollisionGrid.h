#pragma once

#define GRID_HALF_WIDTH 1000.f
#define GRID_HALF_HEIGHT 500.f

/**
 * \brief 월드를 쪼개서 충돌검사를 실시할 것이다 ..
 */
class CollisionGrid : public GameObject
{
public:
	CollisionGrid(Vector2D centerPos);
	virtual ~CollisionGrid();

	// 이 그리드와 충돌한 Collision들의 모임
	std::vector<Collision*> mCollisions;

	AABBCollision* mCollisionOfGrid;
};