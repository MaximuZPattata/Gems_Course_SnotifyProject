#pragma once

template <typename T>

// This is a templated class and can only be implemented in a header file because of how C++ is compiled
class tMyLinkedList
{
public:
	tMyLinkedList() {}
	~tMyLinkedList() {}

	void InsertBeforeCurrentNode(T objInstance)
	{
		if (this->mHeadNode == NULL)
		{
			sListNode* newNode = new sListNode();
			newNode->nodeValue = objInstance; 

			this->mCurrentNode = this->mTailNode = this->mHeadNode = newNode;
		}

		else
		{
			sListNode* newNode = new sListNode();
			newNode->nodeValue = objInstance;

			newNode->nextNodePointer = this->mCurrentNode;
			newNode->previousNodePointer = this->mCurrentNode->previousNodePointer;

			if (this->mCurrentNode->previousNodePointer == NULL)
				this->mHeadNode = this->mCurrentNode;

			if (this->mCurrentNode->nextNodePointer == NULL)
				this->mTailNode = this->mCurrentNode;

			this->mCurrentNode->previousNodePointer = newNode;

			this->mCurrentNode = newNode;
		}
	}

	bool DeleteCurrentNode()
	{
		if (!IsListEmpty())
		{
			sListNode* tempNextNode = this->mCurrentNode->nextNodePointer;
			sListNode* tempPreviousNode = this->mCurrentNode->previousNodePointer;

			delete this->mCurrentNode;

			if (tempNextNode != NULL && tempPreviousNode != NULL) // Checking if current node is not a Tail nor a Head Node
			{
				tempNextNode->previousNodePointer = tempPreviousNode;
				tempPreviousNode->nextNodePointer = tempNextNode;
			}
			else if (tempNextNode != NULL && tempPreviousNode == NULL) // Checking if current node is a Head node
				this->mCurrentNode = this->mHeadNode = tempNextNode;

			else if (tempNextNode == NULL && tempPreviousNode != NULL) // Checking if current node is a Tail node
				this->mCurrentNode = this->mTailNode = tempPreviousNode;

			return true;
		}
		else
			return false;
	}

	bool MoveToNextNode()
	{
		if (this->mCurrentNode->nextNodePointer != NULL)
		{
			this->mCurrentNode = this->mCurrentNode->nextNodePointer;
			return true;
		}
		else
			return false;
	}

	bool MoveToPreviousNode()
	{
		if (this->mCurrentNode->previousNodePointer != NULL)
		{
			this->mCurrentNode = this->mCurrentNode->previousNodePointer;
			return true;
		}
		else
			return false;
	}

	bool MoveToFirstNode()
	{
		if (this->mHeadNode != NULL)
		{
			this->mCurrentNode = this->mHeadNode;
			return true;
		}
		else
			return false;
	}

	bool MoveToLastNode()
	{
		if (this->mTailNode != NULL)
		{
			this->mCurrentNode = this->mTailNode;
			return true;
		}
		else
			return false;
	}

	T GetCurrentNodeValue()
	{
		return this->mCurrentNode->nodeValue;
	}

	bool IsListEmpty()
	{
		if (this->mHeadNode == NULL)
			return true;
		else
			return false;
	}

	void ClearList()
	{
		if (!IsListEmpty())
		{
			while (this->mHeadNode != NULL)
			{
				sListNode* nextNode = this->mHeadNode->nextNodePointer;

				delete this->mHeadNode;
				this->mHeadNode = nextNode;
			}
		}
	}

private:
	struct sListNode
	{
		T nodeValue;
		sListNode* nextNodePointer = NULL;
		sListNode* previousNodePointer = NULL;
	};

	sListNode* mHeadNode;
	sListNode* mTailNode;
	sListNode* mCurrentNode;
};