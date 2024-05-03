#include "cPerson.h"

#pragma warning( disable : 26812 )

cPerson::cPerson()
{
	this->gender = cPerson::RATHER_NOT_SAY_UNKNOWN;
	this->streetNumber = 0;
	this->age = -1;
	this->SIN = 0;

	// Generating unique Snotify ID
	this->m_Snotify_UniqueUserID = cPerson::m_NEXT_Snotify_UniqueUSerID;

	const unsigned int MAX_ID_INCREEMNT = 11;
	cPerson::m_NEXT_Snotify_UniqueUSerID += (rand() % MAX_ID_INCREEMNT);
}

unsigned int cPerson::m_NEXT_Snotify_UniqueUSerID = 10000000;

cPerson::~cPerson() {}

unsigned int cPerson::getSnotifyUniqueUserID(void)
{
	return this->m_Snotify_UniqueUserID;
}

std::string cPerson::getGenderAsString(void)
{
	switch (this->gender)
	{
	case cPerson::MALE:
		return "MALE";
		break;
	case cPerson::FEMALE:
		return "FEMALE";
		break;
	case cPerson::NON_BINARY:
		return "NON_BINARY";
		break;
	default:
		return "RATHER_NOT_SAY_UNKNOWN";
		break;
	}
}

