#include "cMusicGenerator.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>

cMusicGenerator::cMusicGenerator() {}

cMusicGenerator::~cMusicGenerator() {}

bool cMusicGenerator::LoadMusicInformation(std::string musicFileName, std::string& errorString)
{
	std::ifstream songListFile(musicFileName);

	if (!songListFile.is_open())
	{
		errorString = "ERROR : UNABLE TO OPEN SONG LIST FILE";
		return false;
	}

	std::string line;
	std::string songName;
	std::string artistName;

	int lineCount = 0;

	while (std::getline(songListFile, line)) //delimiter for new line
	{
		std::stringstream ssLine(line);
		std::string dataFromFile;

		unsigned int columnCount = 1;

		lineCount++;

		if (lineCount == 1)
			continue;

		cSong* newSongEntry;

		while (std::getline(ssLine, dataFromFile, ',')) // delimiter for comma (,)
		{
			if (columnCount == 4)
				songName = dataFromFile;

			if (columnCount == 5)
				artistName = dataFromFile;

			columnCount++;
		}

		//----------Checking for duplicates-------------------------

		newSongEntry = findSong(songName, artistName);

		if (newSongEntry == NULL)
		{
			newSongEntry = new cSong();

			newSongEntry->name = songName;
			newSongEntry->artist = artistName;

			mSongsList.PushToEnd(newSongEntry);
		}
	}

	std::cout << std::endl;
	std::cout << "[" << musicFileName << "]" << " FILE READ SUCCESSFULLY - " << lineCount << " ENTRIES LOADED FROM FILE" << std::endl;
}

cSong* cMusicGenerator::getRandomSong(void)
{
	// Seeding with a random device
	std::random_device rd;
	std::mt19937 gen(rd());

	if (!mSongsList.IsEmpty())
	{
		// Fixing the random index range
		std::uniform_int_distribution<> dist(0, mSongsList.GetArraySize() - 1);

		int randomIndexValue = dist(gen);

		cSong* songAtIndex;

		if (mSongsList.GetAtIndex(randomIndexValue, songAtIndex))
			return songAtIndex;
	}
	
	return NULL;
}

cSong* cMusicGenerator::findSong(std::string songName, std::string artist)
{
	for (int index = 0; index < mSongsList.GetArraySize(); index++)
	{
		cSong* findSong;
		
		if (mSongsList.GetAtIndex(index, findSong))
		{
			if (findSong->name == songName && findSong->artist == artist)
				return findSong;
		}
	}

	return NULL;
}