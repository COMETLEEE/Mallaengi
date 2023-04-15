#include "PreCompiledHeader.h"
#include "Platform.h"

Platform::Platform():
	PlatformBase()
{
	// 태그를 플랫폼으로 설정한다.
	SetTag("Platform");
}

Platform::~Platform()
{

}

void Platform::FixedUpdate()
{
	PlatformBase::FixedUpdate();
}

void Platform::Update()
{
	PlatformBase::Update();
}