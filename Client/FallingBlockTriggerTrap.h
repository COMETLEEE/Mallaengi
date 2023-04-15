#pragma once


class BlockBase;
/**
 * \brief : 블럭 N개로 이루어져 있는데 블럭임. 옆 위에선 밟을 수 있음.
 *
 * 플레이어가 아래로 오면 맞아 죽음. 2022. 02. 21. Comet
 */
class FallingBlockTriggerTrap : public GameObject
{
public:
	FallingBlockTriggerTrap(Vector2D startPos, int column);
	virtual ~FallingBlockTriggerTrap();

	std::vector<BlockBase*> mBlocks;

	int mColumn;

	bool mTrigger;

	float mTimer;

	float mFallingSpeed;

	Player* mGamePlayer;
public:
	virtual void Update() override;
};