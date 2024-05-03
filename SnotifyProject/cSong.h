#ifndef _cSong_HG_
#define _cSong_HG_

#include <string>

// This class represents a song in the Snotify class
class cSong
{
public:
	std::string name;
	std::string artist;

	int rating;					// On a scale of 0 - 5
	int numberOfTimesPlayed;

	unsigned int uniqueID;

	cSong();
	~cSong();

	unsigned int getUniqueID(void);

private:
	static unsigned int mNEXT_UniqueSongID;
}; 

#endif

