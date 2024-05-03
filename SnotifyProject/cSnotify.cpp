#include "cSnotify.h"

cSnotify::cSnotify() {}

cSnotify::~cSnotify() {}

//-------------------------Song manipulation functions-------------------------------------------

bool cSnotify::AddSong(cSong* pSong, std::string& errorString)
{
	if (pSong == NULL)
	{
		errorString = "ERROR : SONG NOT INSTANTIATED";
		return false;
	}

	mSongsList.InsertBeforeCurrentNode(pSong);
	return true;
}

bool cSnotify::AddSongToUserLibrary(unsigned int snotifyUserID, cSong* pNewSong, std::string& errorString)
{
	cPerson* findPersonUsingUniqueId = FindUserBySnotifyID(snotifyUserID);

	if (findPersonUsingUniqueId == NULL)
	{
		errorString = "ERROR : PERSON DATA NOT FOUND";
		return false;
	}

	//----------------Checking if song already exists using unique song id-------------------------------

	mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.MoveToLastNode();
	cSong* lastSongNode = mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue();

	mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.MoveToFirstNode();

	while (mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue() != lastSongNode)
	{
		if (pNewSong->getUniqueID() == mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue()->getUniqueID())
		{
			return true; // Song already exists
		}

		mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.MoveToNextNode();
	}

	mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.InsertBeforeCurrentNode(pNewSong);

	return true;
}

bool cSnotify::UpdateSong(cSong* pSong, std::string& errorString)
{
	cSong* findSongUsingUniqueId = FindSong(pSong->getUniqueID());

	if (findSongUsingUniqueId == NULL)
	{
		errorString = "ERROR : SONG DATA NOT FOUND";
		return false;
	}
	
	findSongUsingUniqueId->artist = pSong->artist;
	findSongUsingUniqueId->name = pSong->name;
	findSongUsingUniqueId->uniqueID = pSong->getUniqueID();
	findSongUsingUniqueId->rating = pSong->rating;
	findSongUsingUniqueId->numberOfTimesPlayed = pSong->numberOfTimesPlayed;

	return true;
}

bool cSnotify::UpdateRatingOnSong(unsigned int SnotifyUserID, unsigned int songUniqueID, unsigned int newRating)
{
	cPerson* findPersonUsingUniqueId = FindUserBySnotifyID(SnotifyUserID);

	if (findPersonUsingUniqueId == NULL)
		return false;

	mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.MoveToLastNode();
	cSong* lastSongNode = mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue();

	mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.MoveToFirstNode();

	while (mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue() != lastSongNode)
	{
		if (songUniqueID == mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue()->getUniqueID())
		{
			mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue()->rating = newRating;
			return true;
		}

		mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.MoveToNextNode();
	}

	return false;

}

bool cSnotify::DeleteSong(unsigned int UniqueSongID, std::string& errorString)
{
	//--------------Deleting node from Snotify-------------------------

	cSong* findSongUsingUniqueId = FindSong(UniqueSongID);

	if (findSongUsingUniqueId == NULL)
	{
		errorString = "ERROR : SONG DATA NOT FOUND";
		return false;
	}

	if (!mSongsList.DeleteCurrentNode())
	{
		errorString = "ERROR : DELETING SONG IN SNOTIFY FAILED";
		return false;
	}
	
	//---------Deleting node from each Snotify user--------------------

	mSnotifyUsersList.MoveToLastNode();
	sSnotifyUser* lastNode = mSnotifyUsersList.GetCurrentNodeValue();

	mSnotifyUsersList.MoveToFirstNode();

	while (mSnotifyUsersList.GetCurrentNodeValue() != lastNode)
	{
		mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.MoveToLastNode();
		cSong* lastSongNode = mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue();

		mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.MoveToFirstNode();

		while (mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue() != lastSongNode)
		{
			if (UniqueSongID == mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue()->getUniqueID())
			{
				if (!mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.DeleteCurrentNode())
				{
					errorString = "ERROR : DELETING SONG IN USER LIBRARY FAILED";
					return false;
				}
			}

			mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.MoveToNextNode();
		}

		mSnotifyUsersList.MoveToNextNode();
	}

	return true;
}

bool cSnotify::RemoveSongFromUserLibrary(unsigned int snotifyUserID, unsigned int SnotifySongID, std::string& errorString)
{
	cPerson* findPersonUsingUniqueId = FindUserBySnotifyID(snotifyUserID);

	if (findPersonUsingUniqueId == NULL)
	{
		errorString = "ERROR : PERSON DATA NOT FOUND";
		return false;
	}

	mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.MoveToLastNode();
	cSong* lastSongNode = mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue();

	mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.MoveToFirstNode();

	while (mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue() != lastSongNode)
	{
		if (SnotifySongID == mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue()->getUniqueID())
		{
			if (mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.DeleteCurrentNode())
				return true;
			else
			{
				errorString = "ERROR : DELETING SONG IN USER LIBRARY FAILED";
				return false;
			}
		}

		mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.MoveToNextNode();
	}

	errorString = "ERROR : SONG DATA NOT FOUND IN USER LIBRARY";
	return false;

}

//-------------------------User manipulation functions-------------------------------------------

bool cSnotify::AddUser(cPerson* pPerson, std::string& errorString)
{
	if (pPerson == NULL)
	{
		errorString = "ERROR : PERSON NOT INSTANTIATED";
		return false;
	}

	sSnotifyUser* newSnotifyUser = new sSnotifyUser();
	newSnotifyUser->InitializeUser(pPerson);

	mSnotifyUsersList.InsertBeforeCurrentNode(newSnotifyUser);

	return true;
}

bool cSnotify::UpdateUser(cPerson* pPerson, std::string& errorString)
{
	cPerson* findPersonUsingUniqueUserID = FindUserBySnotifyID(pPerson->getSnotifyUniqueUserID());

	cPerson* findPersonUsingSIN = FindUserBySIN(pPerson->SIN);

	if (findPersonUsingUniqueUserID == NULL || findPersonUsingSIN == NULL)
	{
		errorString = "ERROR : USER NOT FOUND";
		return false;
	}

	if (findPersonUsingSIN != findPersonUsingUniqueUserID)
	{
		errorString = "ERROR : SIN(USER INSTANCE) DOESN'T MATCH WITH UNIQUE USER ID(USER INSTANCE)";
		return false;
	}

	findPersonUsingSIN->first = pPerson->first;
	findPersonUsingSIN->middle = pPerson->middle;
	findPersonUsingSIN->last = pPerson->last;
	findPersonUsingSIN->streetName = pPerson->streetName;
	findPersonUsingSIN->streetType = pPerson->streetType;
	findPersonUsingSIN->streetDirection = pPerson->streetDirection;
	findPersonUsingSIN->city = pPerson->city;
	findPersonUsingSIN->province = pPerson->province;

	for (size_t i = 0; i < 6; i++)
		findPersonUsingSIN->postalCode[i] = pPerson->postalCode[i];

	findPersonUsingSIN->SIN = pPerson->SIN;
	findPersonUsingSIN->age = pPerson->age;

	return true;
}

bool cSnotify::DeleteUser(unsigned int SnotifyUserID, std::string& errorString)
{
	mSnotifyUsersList.MoveToLastNode();
	sSnotifyUser* lastNode = mSnotifyUsersList.GetCurrentNodeValue();

	mSnotifyUsersList.MoveToFirstNode();

	while (mSnotifyUsersList.GetCurrentNodeValue() != lastNode)
	{
		if (SnotifyUserID == mSnotifyUsersList.GetCurrentNodeValue()->personData->getSnotifyUniqueUserID())
		{
			if (mSnotifyUsersList.DeleteCurrentNode())
			{
				return true;
			}
			else
			{
				errorString = "ERROR : DELETING USER FAILED";
				return false;
			}
		}

		mSnotifyUsersList.MoveToNextNode();
	}
	errorString = "ERROR : USER DATA NOT FOUND";
	return false;
}

//----------------------------All Finding functions----------------------------------------------

cPerson* cSnotify::FindUserBySIN(unsigned int SIN)
{
	mSnotifyUsersList.MoveToLastNode();
	sSnotifyUser* lastNode = mSnotifyUsersList.GetCurrentNodeValue();

	mSnotifyUsersList.MoveToFirstNode();

	while (mSnotifyUsersList.GetCurrentNodeValue() != lastNode)
	{
		if (SIN == mSnotifyUsersList.GetCurrentNodeValue()->personData->SIN)
			return mSnotifyUsersList.GetCurrentNodeValue()->personData;

		mSnotifyUsersList.MoveToNextNode();
	}
	return NULL;
}

cPerson* cSnotify::FindUserBySnotifyID(unsigned int SnotifyID)
{
	mSnotifyUsersList.MoveToLastNode();
	sSnotifyUser* lastNode = mSnotifyUsersList.GetCurrentNodeValue();

	mSnotifyUsersList.MoveToFirstNode();

	while (mSnotifyUsersList.GetCurrentNodeValue() != lastNode)
	{
		if (SnotifyID == mSnotifyUsersList.GetCurrentNodeValue()->personData->getSnotifyUniqueUserID())
			return mSnotifyUsersList.GetCurrentNodeValue()->personData;

		mSnotifyUsersList.MoveToNextNode();
	}
	return NULL;
}

cSong* cSnotify::FindSong(std::string title, std::string artist)
{
	mSongsList.MoveToLastNode();
	cSong* lastNode = mSongsList.GetCurrentNodeValue();

	mSongsList.MoveToFirstNode();

	while (mSongsList.GetCurrentNodeValue() != lastNode)
	{
		if (title == mSongsList.GetCurrentNodeValue()->name && artist == mSongsList.GetCurrentNodeValue()->artist)
			return mSongsList.GetCurrentNodeValue();

		mSongsList.MoveToNextNode();
	}
	return NULL;
}

cSong* cSnotify::FindSong(unsigned int uniqueID)
{
	mSongsList.MoveToLastNode();
	cSong* lastNode = mSongsList.GetCurrentNodeValue();

	mSongsList.MoveToFirstNode();

	while (mSongsList.GetCurrentNodeValue() != lastNode)
	{
		if (uniqueID == mSongsList.GetCurrentNodeValue()->getUniqueID())
			return mSongsList.GetCurrentNodeValue();

		mSongsList.MoveToNextNode();
	}
	return NULL;
}

//-----------------------------All Getter functions----------------------------------------------

cSong* cSnotify::GetSong(unsigned int SnotifyUserID, unsigned int songUniqueID, std::string& errorString)
{
	cPerson* findPersonUsingUniqueId = FindUserBySnotifyID(SnotifyUserID);

	if (findPersonUsingUniqueId == NULL)
	{
		errorString = "ERROR : PERSON DATA NOT FOUND";
		return NULL;
	}

	//----------------Increment number of times played in the user library-------------------------------

	mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.MoveToLastNode();
	cSong* lastSongNode = mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue();

	mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.MoveToFirstNode();

	while (mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue() != lastSongNode)
	{
		if (songUniqueID == mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue()->getUniqueID())
		{
			mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue()->numberOfTimesPlayed++;

			return mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue();
		}

		mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.MoveToNextNode();
	}

	errorString = "ERROR : SONG DATA NOT FOUND";
	return NULL;
}

bool cSnotify::GetCurrentSongRating(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int& songRating)
{
	cPerson* findPersonUsingUniqueId = FindUserBySnotifyID(snotifyUserID);

	if (findPersonUsingUniqueId == NULL)
		return false;

	//----------------Checking the user library for song rating-------------------------------

	mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.MoveToLastNode();
	cSong* lastSongNode = mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue();

	mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.MoveToFirstNode();

	while (mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue() != lastSongNode)
	{
		if (songUniqueID == mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue()->getUniqueID())
		{
			songRating = mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue()->rating;
			
			return true;
		}

		mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.MoveToNextNode();
	}

	return false;
}

bool cSnotify::GetCurrentSongNumberOfPlays(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int& numberOfPlays)
{
	cPerson* findPersonUsingUniqueId = FindUserBySnotifyID(snotifyUserID);

	if (findPersonUsingUniqueId == NULL)
		return false;

	//----------------Checking the user library for number of times played-------------------------------

	mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.MoveToLastNode();
	cSong* lastSongNode = mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue();

	mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.MoveToFirstNode();

	while (mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue() != lastSongNode)
	{
		if (songUniqueID == mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue()->getUniqueID())
		{
			numberOfPlays = mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.GetCurrentNodeValue()->numberOfTimesPlayed;

			return true;
		}

		mSnotifyUsersList.GetCurrentNodeValue()->userSongLibrary.MoveToNextNode();
	}

	return false;
}

//-------------------------------Sorting functions-----------------------------------------------


bool cSnotify::FindUsersFirstName(std::string firstName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	return true;
}

bool cSnotify::FindUsersLastName(std::string lastName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	return true;
}

bool cSnotify::FindUsersFirstLastNames(std::string firstName, std::string lastName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	return true;
}


bool cSnotify::GetUsersSongLibrary(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	return true;
}

bool cSnotify::GetUsersSongLibraryAscendingByTitle(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	return true;
}

bool cSnotify::GetUsersSongLibraryAscendingByArtist(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	return true;
}

bool cSnotify::GetUsers(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	return true;
}

bool cSnotify::GetUsersByID(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	return true;
}
