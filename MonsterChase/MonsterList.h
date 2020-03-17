#pragma once
#include "Monster.h"
	
class MonsterList {
	public:
		MonsterList();
		~MonsterList();

		void addMonster(SmartPointer<GameObject2D> newMonster);
		void deleteMonster();
		
		void setFocusForMonsters(Point2D focus);
		void printAllMonstersInfo();
		void moveAllMonsters();
		
		

	private:
		Monster * head;
		
	
};
