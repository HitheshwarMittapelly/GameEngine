#pragma once
#include "Point2D.h"
#include "ConsolePrint.h"
#include "SmartPointer.h"
#include "InputSystem.h"
using namespace Engine;
class GameObject2D
{
public:
	
	GameObject2D & operator=(const GameObject2D & i_other)
	{
		this->m_Position = i_other.GetPosition();
		return *this;
	}

	static SmartPointer<GameObject2D> Create(const char * name, const Point2D & i_Position, const float i_rotation)
	{
		return SmartPointer<GameObject2D>(new GameObject2D(name,i_Position,i_rotation));
	}
	~GameObject2D() {
		
		DEBUG_PRINT("Deleting gameobject");
		
		delete[] m_Name;
		
	}
	void SetPosition(Point2D  newPosition);
	Point2D GetPosition() const { return m_Position; }
	float GetZRotation() const { return m_ZRotation; }
	void SetZRotation(float newRotation) { m_ZRotation = newRotation; }
		
	const char * GetName() const { return m_Name; }
	
private:
	GameObject2D(const char * name, const Point2D & i_Position, const float i_rotation) :
		m_Name(name),
		m_Position(i_Position),
		m_ZRotation(i_rotation)
	{
				
	}
	
	const char * m_Name;
	Point2D m_Position;
	float m_ZRotation;
	
};