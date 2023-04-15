#pragma once
#include "TemplateSingleton.h"
#include "Products.h"
#include "SoundTable.h"

#include "..\\inc\\fmod.hpp"
#pragma comment(lib, "..\\lib\\fmod_vc.lib")

#include <map>

using std::map;

using namespace FMOD;

class SoundManager : public TemplateSingleton<SoundManager>
{
private:
	System* mSystem;
	Sound** mSound;							// Resource 자원
	Channel** mChannel;						// 재생 사운드 채널
	Channel** mBgmChannel;

	//SoundTable* mSoundTable;
	std::list<SoundTable> mSoundList;

	unsigned int buffer;					// 버퍼
	float mBGMVolume;						// 볼륨
	float mSFXVolume;						// 볼륨

	std::map<int, Sound*>sounds;			// 음원 개수
	std::map<int, Sound**>::iterator iter;    


public:
	SoundManager();
	~SoundManager();

	void Update();
	void Initialize();
	void LoadJsonAddSound();
	void Play(int num );
	void Stop(int num);
	void Pause(int num);
	void Resume(int num);

	bool Playing(int num);
	int	 GetCurrentPlayBGM();
	bool Paused(int num);

	void Volume(int num, float volume);

	float GetCurrentPlayBGMVolume();
	float GetVolume(int num);

	float GetBGMVolume() { return mBGMVolume; }
	void SetBGMVolume(float volume);
	float GetSFXVolume() { return mSFXVolume; }
	void SetSFXVolume(float volume);

	std::list<SoundTable>& GetSoundList() { return mSoundList; }
};