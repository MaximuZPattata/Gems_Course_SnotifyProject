#ifndef _cSnotify_HG_
#define _cSnotify_HG_

#include "cPerson.h"
#include "cSong.h"
#include "tMyLinkedList.h"


class cSnotify
{
public:
	cSnotify();
	~cSnotify();

	bool AddUser(cPerson* pPerson, std::string& errorString);

	bool UpdateUser(cPerson* pPerson, std::string& errorString);

	bool DeleteUser(unsigned int SnotifyUserID, std::string& errorString);

	bool AddSong(cSong* pSong, std::string& errorString);
	
	bool UpdateSong(cSong* pSong, std::string& errorString);

	bool DeleteSong(unsigned int UniqueSongID, std::string& errorString);

	bool AddSongToUserLibrary(unsigned int snotifyUserID, cSong* pNewSong, std::string& errorString);

	bool RemoveSongFromUserLibrary(unsigned int snotifyUserID, unsigned int SnotifySongID, std::string& errorString);

	bool UpdateRatingOnSong(unsigned int SnotifyUserID, unsigned int songUniqueID, unsigned int newRating);

	cSong* GetSong(unsigned int SnotifyUserID, unsigned int songUniqueID, std::string& errorString);
	
	bool GetCurrentSongRating(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int &songRating);

	bool GetCurrentSongNumberOfPlays(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int &numberOfPlays);

	cPerson* FindUserBySIN(unsigned int SIN);

	cPerson* FindUserBySnotifyID(unsigned int SnotifyID);

	cSong* FindSong(std::string title, std::string artist);

	cSong* FindSong(unsigned int uniqueID);

	// Sorting required

	bool GetUsersSongLibrary(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary);

	bool GetUsersSongLibraryAscendingByTitle(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary);

	bool GetUsersSongLibraryAscendingByArtist(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary);

	bool GetUsers(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray);

	bool GetUsersByID(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray);

	bool FindUsersFirstName(std::string firstName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray);
	
	bool FindUsersLastName(std::string lastName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray);
	
	bool FindUsersFirstLastNames(std::string firstName, std::string lastName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray);

private:
	struct sSnotifyUser
	{
		cPerson* personData;
		tMyLinkedList<cSong*> userSongLibrary;

		void InitializeUser(cPerson* personUsingSpotify)
		{
			personData = personUsingSpotify;
		}
	};

	tMyLinkedList<cSong*> mSongsList;
	tMyLinkedList<sSnotifyUser*> mSnotifyUsersList;
};

#endif // !_cSnotify_HG_
