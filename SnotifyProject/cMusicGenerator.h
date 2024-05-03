#ifndef _cMusicGenerator_HG_
#define _cMusicGenerator_HG_

#include "cSong.h"
#include "tMySmartArray.h"

class cMusicGenerator
{
public:
	cMusicGenerator();
	~cMusicGenerator();

	bool LoadMusicInformation(std::string musicFileName, std::string& errorString);

	cSong* getRandomSong(void);

	cSong* findSong(std::string songName, std::string artist);

private:
	tMySmartArray<cSong*> mSongsList;
};

#endif
