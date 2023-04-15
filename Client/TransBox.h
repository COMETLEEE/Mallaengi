#pragma once
#include "BoxBase.h"

class TransBox : public BoxBase
{
public:
	TransBox();
	virtual ~TransBox();

public:

	virtual void TriggerEvent() override;
};