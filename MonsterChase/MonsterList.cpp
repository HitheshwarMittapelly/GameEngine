#include "MonsterList.h"
#include <iostream>
using namespace std;



MonsterList::MonsterList() {
	head = nullptr;
	
}

void MonsterList::addMonster(SmartPointer<GameObject2D> newMonster) {

	Monster * temp;
	if (head) 
	{
		Monster * iterateNode;
		temp = new Monster(newMonster);
		iterateNode = head;
		while (iterateNode->next != nullptr)
			iterateNode = iterateNode->next;

		iterateNode->next = temp;
				
	}
	else
	{
		
		temp = new Monster(newMonster);
		head = temp;
		
	}

}

void MonsterList::deleteMonster() 
{

	Monster * prevNode;
	Monster * iterateNode;
	iterateNode = head;
	if (iterateNode->next == nullptr) {
		cout << "only one monster" << endl;
	}
	else
	{
		prevNode = iterateNode;
		while (iterateNode->next != nullptr) {
			prevNode = iterateNode;
			iterateNode = iterateNode->next;
			
		}
		
		delete iterateNode;
		prevNode->next = nullptr;
	}

}

void MonsterList::setFocusForMonsters(Point2D focus)
{
	Monster * iterateNode;
	iterateNode = head;
	while (iterateNode != nullptr) {
		iterateNode->setFocus(focus);
		iterateNode = iterateNode->next;
	}

	
}

void MonsterList::printAllMonstersInfo() {
	Monster * iterateNode;
	iterateNode = head;
	while (iterateNode->next != nullptr) {
		iterateNode->printInfo();
		iterateNode = iterateNode->next;
	}

		iterateNode->printInfo();
}

void MonsterList::moveAllMonsters() {
	Monster * iterateNode;
	iterateNode = head;
	while (iterateNode->next != nullptr) {
		iterateNode->move();
		iterateNode = iterateNode->next;
	}
	
	iterateNode->move();

}

MonsterList::~MonsterList() {
	
	Monster * deleteNode = head;
	while (deleteNode != nullptr) {
		Monster * nextNode = deleteNode->next;
		delete deleteNode;
		deleteNode = nextNode;
	}

	
	

}
