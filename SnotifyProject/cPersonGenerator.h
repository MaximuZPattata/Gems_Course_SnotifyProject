#ifndef _cPersonGenerator_HG_
#define _cPersonGenerator_HG_

#include <string>
#include "cPerson.h"
#include "tMySmartArray.h"

struct sFirstNameData
{
	std::string firstName;
	std::string gender;
};

struct sSurnameData
{
	std::string lastName;
};

struct sStreetNameData
{
	std::string streetName;
	std::string streetType;
	std::string postDirection;
};

class cPersonGenerator
{
public:
	cPersonGenerator();
	~cPersonGenerator();


	bool LoadCensusFiles(std::string babyNameFile, std::string surnameFile, std::string streetNameFile, std::string& errorString);

	unsigned int getNumberOfNamesLoaded(void);
	unsigned int getNumberOfSurnamesLoaded(void);
	unsigned int getNumberOfStreetsLoaded(void);

	cPerson* generateRandomPerson(void);

private:
	tMySmartArray<cPerson*> mPersonList;
	tMySmartArray<sFirstNameData*> mFirstNameList;
	tMySmartArray<sSurnameData*> mSurnameList;
	tMySmartArray<sStreetNameData*> mStreetNameList;

	unsigned int mNamesLoadCount;
	unsigned int mSurnamesLoadCount;
	unsigned int mStreetsLoadCount;

	unsigned int GenerateRandomNumber(unsigned int arraySize);
};


#endif 
