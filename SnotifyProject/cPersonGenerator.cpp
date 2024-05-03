#include "cPersonGenerator.h"

#pragma warning( disable : 26812 )

#include <iostream>
#include <fstream>
#include <sstream>	
#include <string>
#include <random>

cPersonGenerator::cPersonGenerator() 
{
	mNamesLoadCount = 0;
	mSurnamesLoadCount = 0;
	mStreetsLoadCount = 0;
}

cPersonGenerator::~cPersonGenerator() {}

bool cPersonGenerator::LoadCensusFiles(std::string babyNameFile, std::string surnameFile, std::string streetNameFile, std::string& errorString)
{

	//---------------------------Reading the baby name file--------------------------------------

	std::ifstream nameListFile(babyNameFile);

	if (!nameListFile.is_open())
	{
		errorString = "ERROR : UNABLE TO OPEN NAME LIST FILE";
		return false;
	}

	std::string line;

	while (std::getline(nameListFile, line))
	{
		std::stringstream ssLine(line);
		std::string dataFromFile;

		unsigned int columnCount = 1;

		mNamesLoadCount++;

		sFirstNameData* newFirstNameData = new sFirstNameData();

		while (std::getline(ssLine, dataFromFile, ','))
		{
			if (columnCount == 1)
				newFirstNameData->firstName = dataFromFile;

			if (columnCount == 2)
				newFirstNameData->gender = dataFromFile;

			columnCount++;
		}

		mFirstNameList.PushToEnd(newFirstNameData);
	}

	std::cout << std::endl;
	std::cout << "[" << babyNameFile << "]" << " FILE READ SUCCESSFULLY - " << mNamesLoadCount << " ENTRIES LOADED FROM FILE" << std::endl;

	//----------------------------Reading the surname file---------------------------------------

	line = "";

	std::ifstream surnameListFile(surnameFile);

	if (!surnameListFile.is_open())
	{
		errorString = "ERROR : UNABLE TO OPEN SURNAME LIST FILE";
		return false;
	}
	
	bool ignoreFirstLine = false;

	while (std::getline(surnameListFile, line))
	{
		std::stringstream ssLine(line);
		std::string dataFromFile;

		if (!ignoreFirstLine)
		{
			ignoreFirstLine = true;
			continue;
		}

		unsigned int columnCount = 1;

		mSurnamesLoadCount++;

		sSurnameData* newSurnameData = new sSurnameData();

		while (std::getline(ssLine, dataFromFile, ','))
		{
			if (columnCount == 1)
			{
				newSurnameData->lastName = dataFromFile;
				break;
			}
		}

		mSurnameList.PushToEnd(newSurnameData);
	}

	std::cout << std::endl;
	std::cout << "[" << surnameFile << "]" << " FILE READ SUCCESSFULLY - " << mSurnamesLoadCount << " ENTRIES LOADED FROM FILE" << std::endl;


	//--------------------------Reading the streetName file--------------------------------------

	line = "";
	ignoreFirstLine = false;

	std::ifstream streetNamesFile(streetNameFile);

	if (!streetNamesFile.is_open())
	{
		errorString = "ERROR : UNABLE TO OPEN STREET NAME LIST FILE";
		return false;
	}

	while (std::getline(streetNamesFile, line))
	{
		std::stringstream ssLine(line);
		std::string dataFromFile;

		if (!ignoreFirstLine)
		{
			ignoreFirstLine = true;
			continue;
		}

		unsigned int columnCount = 1;

		mStreetsLoadCount++;

		sStreetNameData* newStreetNameData = new sStreetNameData();

		while (std::getline(ssLine, dataFromFile, ','))
		{
			if (columnCount == 2)
				newStreetNameData->streetName = dataFromFile;

			if (columnCount == 3)
				newStreetNameData->streetType = dataFromFile;

			if (columnCount == 4)
				newStreetNameData->postDirection = dataFromFile;

			columnCount++;
		}

		mStreetNameList.PushToEnd(newStreetNameData);
	}

	std::cout << std::endl;
	std::cout << "[" << streetNameFile << "]" << " FILE READ SUCCESSFULLY - " << mStreetsLoadCount << " ENTRIES LOADED FROM FILE" << std::endl;

	return true;
}

unsigned int cPersonGenerator::getNumberOfNamesLoaded(void)
{
	return mNamesLoadCount;
}

unsigned int cPersonGenerator::getNumberOfSurnamesLoaded(void)
{
	return mSurnamesLoadCount;
}

unsigned int cPersonGenerator::getNumberOfStreetsLoaded(void)
{
	return mStreetsLoadCount;
}

cPerson* cPersonGenerator::generateRandomPerson(void)
{
	cPerson* newPersonData = new cPerson();

	//------------------------Getting a random first name from the name list--------------------------------------
	
	unsigned int randomIndexValue = GenerateRandomNumber(mFirstNameList.GetArraySize() - 1);

	sFirstNameData* randomNameData;

	if (!mFirstNameList.IsEmpty())
	{
		if (mFirstNameList.GetAtIndex(randomIndexValue, randomNameData))
			newPersonData->first = randomNameData->firstName;
		else
		{
			std::cout << std::endl;
			std::cout << "<<UNABLE TO FIND NAME IN THE LIST FOR THIS INDEX - [" << randomIndexValue << "]>>" << std::endl;
			return NULL;
		}
	}
	else
	{
		std::cout << std::endl;
		std::cout << "<<NAME LIST ISN'T LOADED>>" << std::endl;
		return NULL;
	}

	//----------------------Checking if same name has more than one gender----------------------------------------

	int genderCount = 0;

	for (unsigned int index = 0; index < mFirstNameList.GetArraySize(); index++)
	{
		sFirstNameData* newDataToCompareGender;

		if (index != randomIndexValue)
		{
			if (mFirstNameList.GetAtIndex(index, newDataToCompareGender))
			{
				if (newPersonData->first == newDataToCompareGender->firstName)
					genderCount++;
			}
		}
	}

	if (genderCount > 0)
		newPersonData->gender = cPerson::NON_BINARY;
	else
	{
		if (randomNameData->gender == "M")
			newPersonData->gender = cPerson::MALE;
		else
			newPersonData->gender = cPerson::FEMALE;
	}
	
	//------------------------Getting a random middle name from the name list-------------------------------------

	randomIndexValue = GenerateRandomNumber(mFirstNameList.GetArraySize() - 1);

	sFirstNameData* randomMiddleNameData;

	if (mFirstNameList.GetAtIndex(randomIndexValue, randomMiddleNameData))
		newPersonData->middle = randomMiddleNameData->firstName;
	else
	{
		std::cout << std::endl;
		std::cout << "<<UNABLE TO FIND MIDDLE NAME IN THE LIST FOR THIS INDEX - [" << randomIndexValue << "]>>" << std::endl;
		return NULL;
	}

	//------------------------Getting a random last name from the surname list------------------------------------

	randomIndexValue = GenerateRandomNumber(mSurnameList.GetArraySize() - 1);

	sSurnameData* randomLastNameData;

	if (mSurnameList.GetAtIndex(randomIndexValue, randomLastNameData))
		newPersonData->last = randomLastNameData->lastName;
	else
	{
		std::cout << std::endl;
		std::cout << "<<UNABLE TO FIND LAST NAME IN THE LIST FOR THIS INDEX - [" << randomIndexValue << "]>>" << std::endl;
		return NULL;
	}

	//----------------------Getting a random street name from the street name list--------------------------------

	randomIndexValue = GenerateRandomNumber(mStreetNameList.GetArraySize() - 1);

	sStreetNameData* randomStreetNameData;

	if (mStreetNameList.GetAtIndex(randomIndexValue, randomStreetNameData))
	{
		newPersonData->streetName = randomStreetNameData->streetName;
		newPersonData->streetType = randomStreetNameData->streetType;
		newPersonData->streetDirection = randomStreetNameData->postDirection;
	}
	else
	{
		std::cout << std::endl;
		std::cout << "<<UNABLE TO FIND LAST NAME IN THE LIST FOR THIS INDEX - [" << randomIndexValue << "]>>" << std::endl;
		return NULL;
	}

	//--------------------------------Hardcoding rest of the values-----------------------------------------------

	newPersonData->city = "London";
	newPersonData->province = "Ontario";
	newPersonData->postalCode[0] = 'N';
	newPersonData->postalCode[1] = '6';
	newPersonData->postalCode[2] = 'B';
	newPersonData->postalCode[3] = '3';
	newPersonData->postalCode[4] = 'N';
	newPersonData->postalCode[5] = '7';

	newPersonData->age = GenerateRandomNumber(100);

	newPersonData->SIN = 10000000 + GenerateRandomNumber(8999999);

	int personListIndex = 0;

	//----------------------------------Checking if SIN is unique-------------------------------------------------

	while(personListIndex < mPersonList.GetArraySize())
	{
		cPerson* findPerson;

		if (mPersonList.GetAtIndex(personListIndex, findPerson))
		{
			if (findPerson->SIN == newPersonData->SIN)
			{
				newPersonData->SIN = 10000000 + GenerateRandomNumber(8999999);
				personListIndex = 0;
			}
			else
				personListIndex++;
		}
	}

	mPersonList.PushToEnd(newPersonData);
	return newPersonData;
}

unsigned int cPersonGenerator::GenerateRandomNumber(unsigned int arraySize)
{
	// Seeding with a random device
	std::random_device rd;
	std::mt19937 gen(rd());

	// Fixing the random index range
	std::uniform_int_distribution<> dist(0, arraySize);

	return dist(gen);
}
