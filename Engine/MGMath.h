#pragma once

/// <summary>
/// 여러가지 유용한 수학 함수들을 모아놓은 클래스입니다.
/// 
/// 2022. 02. 07. MG의 영혼
/// </summary>
class MGMath
{
public:
	template<typename T>
	static T Clamp(T value, T min, T max);
};

template<typename T>
T MGMath::Clamp(T value, T min, T max)
{
	if (value < min)
		return min;

	if (value > max)
		return max;

	return value;
}