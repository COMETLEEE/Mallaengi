#include "pch.h"
#include "CodingGuideLine.h"

CodingGuideLine::CodingGuideLine()
	: mNumber(nullptr)							// 변수 초기화 해주기
{
	// 초기화 안에서도 가능
}

CodingGuideLine::~CodingGuideLine()
{
}

void CodingGuideLine::Initialize()
{
	int num = 10;
	SetNumber(num);

	// == 이 아닌 != 을 사용하여 nullptr 이 아닐때를 정의  ->  이게 설명이 맞나?
	if (mNumber != nullptr)
	{
		
	}
}
