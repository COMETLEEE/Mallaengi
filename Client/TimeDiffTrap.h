#pragma once

class FallingBlock;
/**
 * 시간차를 두고 공중에서 떨어지는 함정. 닿으면 죽는다.
 *
 * 2022. 02. 13. Comet
 */
class TimeDiffTrap : public GameObject
{
public:
	TimeDiffTrap();
	virtual ~TimeDiffTrap();

	std::vector<FallingBlock*> mFallingBlocks;

public:
	virtual void FixedUpdate() override;
	virtual void Update() override;
};