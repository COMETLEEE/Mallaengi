#pragma once

/// <summary>
/// 2022. 02. 08. MG
/// 
/// 코딩 가이드라인을 위한 클래스
/// 
/// 클래스 위에는 주석으로 글 남기기(방식은 달라도 OK)
/// </summary>
class CodingGuideLine
{
public:
	// 생성자, 소멸자는 기본으로 생성, 만든 생성자가 있다면 그 생성자만 적기
	CodingGuideLine();
	~CodingGuideLine();

	// 클래스의 처음에 변수 만들어주기
private:
	int* mNumber;									// 변수는 보통의 경우 private 으로 선언


	// 아래에 함수 만들어주기
public:
	// 기능적 함수 먼저
	void Initialize();



	// Get, Set 한 함수 맨 마지막
	int GetNumber() { return *mNumber; }				// private 변수이므로 밖에서 쓸 수 있도록 Get 만들어주기
	void SetNumber(int num) { *mNumber = num; }		// 변수의 값 변화 필요한 경우 Set 만들어주기
};

