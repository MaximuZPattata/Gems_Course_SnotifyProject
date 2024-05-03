#include "cPersonGenerator.h"
#include "cMusicGenerator.h"
#include "cSnotify.h"
#include "cPerson.h"

#include <iostream>
#include <string>

void printGenerationMessage(cPerson* newPerson)
{
	if (newPerson == NULL)
		std::cout << "ERROR : UNABLE TO GENERATE PERSON" << std::endl;
	else
		std::cout << "SUCCESS : PERSON GENERATED" << std::endl;
}

void printGenerationMessage(cSong* newSong)
{
	if (newSong == NULL)
		std::cout << "ERROR : UNABLE TO GENERATE SONG" << std::endl;
	else
		std::cout << "SUCCESS : SONG GENERATED" << std::endl;
}

int main()
{
	//----------------------Initializing data------------------------------

	cPersonGenerator personGenerator;
	cMusicGenerator musicGenerator;
	cSnotify snotifyApp;

	std::string errorString;

	//--------------------Loading data from files--------------------------

	personGenerator.LoadCensusFiles("yob2019.txt", "Names_2010Census.csv", "Street_Names.csv", errorString);

	musicGenerator.LoadMusicInformation("hot_stuff_2.csv", errorString);

	//--------------------Generate random person---------------------------

	cPerson* person01 = personGenerator.generateRandomPerson();
	printGenerationMessage(person01);	

	cPerson* person02 = personGenerator.generateRandomPerson();
	printGenerationMessage(person02);

	cPerson* person03 = personGenerator.generateRandomPerson();
	printGenerationMessage(person03);

	cPerson* person04 = personGenerator.generateRandomPerson();
	printGenerationMessage(person04);

	cPerson* person05 = personGenerator.generateRandomPerson();
	printGenerationMessage(person05);

	//--------------------Add user to Snotify---------------------------

	if (snotifyApp.AddUser(person01, errorString))
		std::cout << "SUCCESS : USER ADDED TO SNOTIFY" << std::endl;
	else
		std::cout << "ERROR : UNABLE TO ADD USER TO SNOTIFY" << std::endl;

	if (snotifyApp.AddUser(person02, errorString))
		std::cout << "SUCCESS : USER ADDED TO SNOTIFY" << std::endl;
	else
		std::cout << "ERROR : UNABLE TO ADD USER TO SNOTIFY" << std::endl;

	if(snotifyApp.AddUser(person03, errorString))
		std::cout << "SUCCESS : USER ADDED TO SNOTIFY" << std::endl;
	else
		std::cout << "ERROR : UNABLE TO ADD USER TO SNOTIFY" << std::endl;

	if(snotifyApp.AddUser(person04, errorString))
		std::cout << "SUCCESS : USER ADDED TO SNOTIFY" << std::endl;
	else
		std::cout << "ERROR : UNABLE TO ADD USER TO SNOTIFY" << std::endl;

	if(snotifyApp.AddUser(person05, errorString))
		std::cout << "SUCCESS : USER ADDED TO SNOTIFY" << std::endl;
	else
		std::cout << "ERROR : UNABLE TO ADD USER TO SNOTIFY" << std::endl;

	//--------------------Generate random song---------------------------

	cSong* song01 = musicGenerator.getRandomSong();
	printGenerationMessage(song01);

	cSong* song02 = musicGenerator.getRandomSong();
	printGenerationMessage(song02);

	cSong* song03 = musicGenerator.getRandomSong();
	printGenerationMessage(song03);

	cSong* song04 = musicGenerator.getRandomSong();
	printGenerationMessage(song04);

	//--------------------Add song to Snotify-----------------------------

	if(snotifyApp.AddSong(song01, errorString))
		std::cout << "SUCCESS : SONG ADDED TO SNOTIFY" << std::endl;
	else
		std::cout << "ERROR : UNABLE TO ADD SONG TO SNOTIFY" << std::endl;

	if(snotifyApp.AddSong(song02, errorString))
		std::cout << "SUCCESS : SONG ADDED TO SNOTIFY" << std::endl;
	else
		std::cout << "ERROR : UNABLE TO ADD SONG TO SNOTIFY" << std::endl;

	if(snotifyApp.AddSong(song03, errorString))
		std::cout << "SUCCESS : SONG ADDED TO SNOTIFY" << std::endl;
	else
		std::cout << "ERROR : UNABLE TO ADD SONG TO SNOTIFY" << std::endl;

	if(snotifyApp.AddSong(song04, errorString))
		std::cout << "SUCCESS : SONG ADDED TO SNOTIFY" << std::endl;
	else
		std::cout << "ERROR : UNABLE TO ADD SONG TO SNOTIFY" << std::endl;
}