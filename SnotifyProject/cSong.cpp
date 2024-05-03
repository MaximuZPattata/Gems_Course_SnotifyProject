#include "cSong.h"

#pragma warning( disable : 26812 )

cSong::cSong()
{
	this->rating = 0;
	this->numberOfTimesPlayed = 0;

	// Generating unique Song ID
	this->uniqueID = cSong::mNEXT_UniqueSongID;

	const unsigned int MAX_ID_INCREEMNT = 11;
	cSong::mNEXT_UniqueSongID += (rand() % MAX_ID_INCREEMNT);
}

unsigned int cSong::mNEXT_UniqueSongID = 10000000;

cSong::~cSong() {}

unsigned int cSong::getUniqueID(void)
{
	return this->uniqueID;
}