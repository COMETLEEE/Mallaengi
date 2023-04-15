#pragma once
#include "PlatformBase.h"

/// <summary>
/// 기본적인 플랫폼 객체. 이 친구를 먼저 채웁시다.
/// 
/// 2022. 02. 09. Comet
/// </summary>
class Platform : public PlatformBase
{
public:
	Platform();
	virtual ~Platform();

public:
	virtual void FixedUpdate() override;

	virtual void Update() override;
};