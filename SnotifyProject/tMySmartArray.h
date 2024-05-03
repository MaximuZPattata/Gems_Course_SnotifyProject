#pragma once

template <typename T>

// This is a templated class and can only be implemented in a header file because of how C++ is compiled
class tMySmartArray
{
public:
	tMySmartArray()
	{
		InitializeArray();
	}

	~tMySmartArray()
	{
		DeleteArray();
	}

	void PushToEnd(T objInstance)
	{
		// Checking if array needs to be resized
		if (this->mNextIndexLocation == this->mArrayCapacity)
			this->ResizeArray();

		this->mArrayPointer[this->mNextIndexLocation] = objInstance;

		this->mNextIndexLocation++;
	}

	bool GetAtIndex(unsigned int index, T& foundObjInstance)
	{
		if (index >= this->mNextIndexLocation || index < 0)
			return false;

		foundObjInstance = this->mArrayPointer[index];

		return true;
	}

	unsigned int GetArraySize(void)
	{
		return this->mNextIndexLocation;
	}

	void ClearArray()
	{
		DeleteArray();
		
		InitializeArray();

		this->mNextIndexLocation = 0;
	}

	bool IsEmpty()
	{
		if (mNextIndexLocation < 1)
			return true;
		else
			return false;
	}

private:

	static const unsigned int INITIAL_ARRAY_CAPACITY = 10;

	unsigned int mNextIndexLocation = 0;
	unsigned int mArrayCapacity;

	T* mArrayPointer = NULL;

	void InitializeArray()
	{
		this->mArrayCapacity = this->INITIAL_ARRAY_CAPACITY;
		this->mArrayPointer = new T[this->mArrayCapacity];
	}

	void DeleteArray()
	{
		delete[] this->mArrayPointer;
	}

	void ResizeArray(void)
	{
		//--------Create new array with double the array capacity----------------------

		T* newTempArray = new T[this->mArrayCapacity * 2];

		for (unsigned int index = 0; index < this->mArrayCapacity; index++)
			newTempArray[index] = this->mArrayPointer[index];

		this->mArrayCapacity *= 2;

		//----------------------Delete old array---------------------------------------

		DeleteArray();

		//------------Point our array to the new temporary array-----------------------

		this->mArrayPointer = newTempArray;
	}
};

