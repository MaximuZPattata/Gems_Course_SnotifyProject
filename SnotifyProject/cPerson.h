// A classic type of header guard
#ifndef _cPerson_HG_2020_09_26_
#define _cPerson_HG_2020_09_26_

#pragma warning( disable : 26812 )

#include <string>

class cPerson
{
public:
	cPerson();		
	~cPerson();

	std::string first;
	std::string middle;
	std::string last;

	enum eGenderType
	{
		MALE = 0,
		FEMALE,
		NON_BINARY,
		RATHER_NOT_SAY_UNKNOWN
	};

	eGenderType gender;
	std::string getGenderAsString(void);

	int age;

	int streetNumber;	
	std::string streetName;
	std::string streetType;
	std::string streetDirection;

	std::string city;
	std::string province;
	char postalCode[6];	

	unsigned int SIN;	

	unsigned int getSnotifyUniqueUserID(void);

private:
	unsigned int m_Snotify_UniqueUserID;
	// 
	static unsigned int m_NEXT_Snotify_UniqueUSerID;
};



#endif
