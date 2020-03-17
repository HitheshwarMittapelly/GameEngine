#include "DescriptorList.h"

#include <cstdint>
#include <iostream>
#include <assert.h>


#include "ConsolePrint.h"
#include "HeapManager.h"
using namespace std;
void DescriptorList::addDescriptor(Descriptor * newDescriptor)
{
	Descriptor * temp;
	if (head == nullptr) {
		head = newDescriptor;

		head->next = nullptr;
	}
	else
	{
		temp = head;
		while (temp->next != nullptr) {
			temp = temp->next;

		}

		temp->next = newDescriptor;
		temp = temp->next;


		temp->next = nullptr;

	}

}

void DescriptorList::addDescriptorBlock(Descriptor * newDescriptor)
{
	Descriptor * temp;
	if (head == nullptr) {
		head = newDescriptor;

		head->nextDescriptor = nullptr;
	}
	else
	{
		temp = head;
		while (temp->nextDescriptor != nullptr) {
			temp = temp->nextDescriptor;

		}

		temp->nextDescriptor = newDescriptor;
		temp->nextDescriptor->nextDescriptor = nullptr;
		

	}
}

Descriptor * DescriptorList::getFirstFit(size_t size)
{
	bool foundInLoop = false;
	Descriptor * returnBlock = nullptr;
	Descriptor * temp = head;
	if (temp->blockSize >= size)
		returnBlock = head;
	else
	{
		while (temp != nullptr)
		{
			if (temp->blockSize > size) {
				returnBlock = temp;
				foundInLoop = true;
				break;
			}
			temp = temp->next;
		}
		if (!foundInLoop) {


			DEBUG_PRINT("returning null ptr ");
			return nullptr;

		}
	}
	deleteDescriptor(returnBlock);
	return returnBlock;
}

void DescriptorList::deleteDescriptor(Descriptor * deleteThis)
{
	Descriptor * current;
	Descriptor * previous;



	if (head == deleteThis) {
		head = head->next;
	}
	else
	{
		bool foundInLoop = false;
		current = head;
		previous = head;
		while (current != nullptr)
		{

			if (current == deleteThis) {
				previous->next = current->next;
				current->next = nullptr;
				foundInLoop = true;
				break;

			}
			previous = current;
			current = current->next;
		}
		if (!foundInLoop) {
			assert(foundInLoop);
		}


	}
}

void DescriptorList::deleteDescriptorBlock(Descriptor * deleteThis)
{
	Descriptor * current;
	Descriptor * previous;



	if (head == deleteThis) {
		head = head->nextDescriptor;
	}
	else
	{
		bool foundInLoop = false;
		current = head;
		previous = head;
		while (current != nullptr)
		{

			if (current == deleteThis) {
				previous->nextDescriptor = current->nextDescriptor;
				current->nextDescriptor = nullptr;
				foundInLoop = true;
				break;

			}
			previous = current;
			current = current->nextDescriptor;
		}
		if (!foundInLoop) {
			assert(foundInLoop);
		}


	}

}

Descriptor * DescriptorList::getDescriptorFromStartAddress(void * startAdd)
{
	bool foundInLoop = false;
	Descriptor * pReturn = nullptr;
	Descriptor * current = head;

	//If there is only head
	if (current->startAddress == reinterpret_cast<uintptr_t>(startAdd))
		pReturn = current;

	//if not look for it using iterator
	else
	{
		while (current != nullptr)
		{
			if (current->startAddress == reinterpret_cast<uintptr_t>(startAdd))
			{
				pReturn = current;
				foundInLoop = true;
			}
			current = current->next;
		}
		//////if it is not found in the loop
		if (!foundInLoop)
		{
			assert(foundInLoop);
		}
	}

	return pReturn;
}

Descriptor * DescriptorList::getDescriptorBlockFromStartAddress(void * startAdd)
{
	bool foundInLoop = false;
	Descriptor * pReturn = nullptr;
	Descriptor * current = head;

	//If there is only head
	if (current->startAddress == reinterpret_cast<uintptr_t>(startAdd))
		pReturn = current;

	//if not look for it using iterator
	else
	{
		while (current != nullptr)
		{
			if (current->startAddress == reinterpret_cast<uintptr_t>(startAdd))
			{
				pReturn = current;
				foundInLoop = true;
			}
			current = current->nextDescriptor;
		}
		//////if it is not found in the loop
		if (!foundInLoop)
		{
			assert(foundInLoop);
		}
	}

	return pReturn;
	
}

Descriptor * DescriptorList::getNextFromList()
{
	if (head == nullptr)
		return nullptr;
	Descriptor * pReturn = head;

	return pReturn;

}

void DescriptorList::displayList(int i)
{
	if (head == nullptr)
	{
		if (i == 2)
		{
			DEBUG_PRINT("No list");
			cout << "No Outstanding Allocations" << endl;
		}

	}
	Descriptor * temp = head;


	while (temp != nullptr)
	{
		if (i == 1)
		{
			DEBUG_PRINT("Free Block Start Address -- %p    Size -- %lu ", temp->startAddress, temp->blockSize);
			cout << "Free block size -- " << temp->blockSize << endl;
		}
		else if (i == 2)
		{
			DEBUG_PRINT("Outstanding Block Start Address -- %p    Size -- %lu ", temp->startAddress, temp->blockSize);
			cout << "Outstanding block size -- " << temp->blockSize << endl;
		}
		temp = temp->next;
	}



}
size_t DescriptorList::getTotalMemory()
{
	Descriptor * temp;
	size_t returningSize = 0;
	if (!head)
		returningSize = 0;
	else
	{
		temp = head;
		while (temp != nullptr)
		{
			returningSize += temp->blockSize;
			temp = temp->next;
		}

	}
	return returningSize;
}
size_t DescriptorList::getLargestBlock()
{
	Descriptor * temp;

	temp = head;
	size_t returningSize = temp->blockSize;
	while (temp->next != nullptr)
	{
		if (returningSize <= temp->blockSize)
		{
			returningSize = temp->blockSize;
		}

		temp = temp->next;
	}
	if (temp->blockSize >= returningSize)
		returningSize = temp->blockSize;
	return returningSize;

}
void  DescriptorList::joinConsecutiveBlocks(DescriptorList * descriptorFreeList, DescriptorList * descriptorAllocatedList)
{
	int numOfCollects=0;
	bool foundInLoop = false;
	Descriptor * temp1 = head;
	Descriptor * temp2 = head;
	while (temp1 != nullptr)
	{
		temp2 = head;
		while (temp2 != nullptr)
		{
			foundInLoop = false;
			if ((temp1->startAddress) + (temp1->blockSize) == (temp2->startAddress))
			{
				Descriptor * temp3 = temp2;

				foundInLoop = true;
				temp1->blockSize = temp1->blockSize + temp3->blockSize;
				
				
				deleteDescriptor(temp3);
				numOfCollects++;
			}
			if (foundInLoop)
				temp2 = head;
			else
				temp2 = temp2->next;

		}
		temp1 = temp1->next;

	}

	cout << "Garbage collected " << numOfCollects << " blocks" << endl;

}

void DescriptorList::deleteList()
{

	Descriptor * nextDescriptor = head;

	while (head != nullptr)
	{
		nextDescriptor = head->next;
		freeDescriptorPtr(head);
		head = nullptr;

		head = nextDescriptor;
	}
}
void DescriptorList::freeDescriptorPtr(Descriptor * deletePtr)
{
	size_t blockSize = sizeof(Descriptor);
	//rewrite the values to null
	char * rewrite = reinterpret_cast<char *>(deletePtr);
	while (blockSize > (size_t)0)
	{
		*rewrite = 0;
		rewrite += (size_t)1;
		blockSize -= (size_t)1;
	}

}





DescriptorList::~DescriptorList()
{

}