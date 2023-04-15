#pragma once
#include <unordered_map>

class JsonManager;

/// <summary>
/// 리소스를 관리하는 Class
/// 
/// Game Class에 귀속되어 사용됩니다.
///  
/// 2022. 02. 12. Comet
/// </summary>
class Resource
{
public:
	Resource();
	~Resource();

public:
	// Game Class가 Initialize될 때, 모든 리소스를 로드하면서
	// 준비합니다.
	void Initialize();

private:
	// 모든 단일 스프라이트 정보를 관리합니다.
	// (애니메이션이 없는 객체들에 사용되는 스프라이트를 관리합니다.)
	std::unordered_map<std::string, Sprite*> mAllSprites;

	// 모든 애니메이션 정보를 관리합니다.
	std::unordered_map<std::string, AnimationClip*> mAllAnimationClips;

public:
	Sprite* GetSprite(std::string name) const { return mAllSprites.at(name); }

	AnimationClip* GetAnimationClip(std::string name) const { return mAllAnimationClips.at(name); }
};