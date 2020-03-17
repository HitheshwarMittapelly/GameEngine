#pragma once
#include "SmartPointer.h"

template <class T>
class WeakPointer
{
	template <class U>
	friend class SmartPointer;

	template <class U>
	friend class WeakPointer;

public:

	
	WeakPointer() : m_refCount(nullptr), m_ObjectPtr(nullptr)
	{ }


	
	WeakPointer(const SmartPointer<T> & i_Other)
	{
		m_ObjectPtr = i_Other.m_ObjectPtr;
		m_refCount = i_Other.m_refCount;

		m_refCount->m_WeakCount++;
	}

	//polymorphic object
	template<class U>
	WeakPointer(const SmartPointer<U> & i_Other)
	{
		m_ObjectPtr = i_Other.m_ObjectPtr;
		m_refCount = i_Other.m_refCount;

		m_refCount->m_WeakCount++;
	}

	// Copy Constructor 
	WeakPointer(const WeakPointer & i_Other)
	{
		m_ObjectPtr = i_Other.m_ObjectPtr;
		m_refCount = i_Other.m_refCount;
		m_refCount->m_WeakCount++;
	}

	// Copy Constructor for polymorphic objects
	template<class U>
	WeakPointer(const WeakPointer<U> & i_Other)
	{
		m_ObjectPtr = i_Other.m_ObjectPtr;
		m_refCount = i_Other.m_refCount;
		m_refCount->m_WeakCount++;
	}

	SmartPointer<T> AquireOwnership()
	{
		//Upgrade to smart pointer
		if (m_refCount->m_SmartCount > 0)
		{
			//m_refCount->m_SmartCount++;
			return SmartPointer<T>(*this);
		}
		//return null 
		else
		{
			return nullptr; 
		}
	}

	~WeakPointer()
	{
		if (m_refCount) {
			m_refCount->m_WeakCount--;
			if (m_refCount->m_WeakCount == 0 && m_refCount->m_SmartCount == 0)
			{
				delete m_refCount;
				delete m_ObjectPtr;
				m_refCount = nullptr;
				m_ObjectPtr = nullptr;
			}
		}
	}

	// Assignment operator 
	WeakPointer & operator=(const WeakPointer & i_Other)
	{
		// Am I trying to assign to the same underlying pointer?
		if (m_ObjectPtr == i_Other.m_ObjectPtr)
		{
			return *this;
		}
		else
		{	
			//Release current reference
			ReleaseReference();

			//Grab the other one then
			m_ObjectPtr = i_Other.m_ObjectPtr;
			m_refCount = i_Other.m_refCount;
			m_refCount->m_WeakCount++;
			return *this;
			
		}
	}
	void ReleaseReference() {
		m_refCount->m_WeakCount--;
		if (m_refCount->m_WeakCount == 0 && m_refCount->m_SmartCount == 0)
		{
			delete m_refCount;
			
			m_refCount = nullptr;
			
		}
	}
	// Same stuff over and over...
	// Assignment operator for polymorphic objects
	template <class U>
	WeakPointer & operator=(const WeakPointer<U> & i_Other)
	{
		// Am I trying to assign to the same underlying pointer?
		if (m_ObjectPtr == i_Other.m_ObjectPtr)
		{
			return *this;
		}
		else
		{
			//Release current reference
			ReleaseReference();

			//Grab the other one then
			m_ObjectPtr = i_Other.m_ObjectPtr;
			m_refCount = i_Other.m_refCount;
			m_refCount->m_WeakCount++;
			return *this;

		}
	}

	//Operator stuff
	
	bool operator==(const WeakPointer<T> & i_Other) const
	{
		return m_ObjectPtr == i_Other.m_ObjectPtr;
	}

	
	template <class U>
	bool operator==(const WeakPointer<U> & i_Other) const
	{
		return m_ObjectPtr == i_Other.m_ObjectPtr;
	}

	
	bool operator==(const SmartPointer<T> & i_Other) const
	{
		return m_ObjectPtr == i_Other.m_ObjectPtr;
	}

	
	template <class U>
	bool operator==(const SmartPointer<U> & i_Other) const
	{
		return m_ObjectPtr == i_Other.m_ObjectPtr;
	}

	
	bool operator==(const T * i_Other) const
	{
		return m_ObjectPtr == i_Other;
	}

	
	template <class U>
	bool operator==(const U * i_Other)
	{
		return m_ObjectPtr == i_Other;
	}

	
	bool operator==(std::nullptr_t i_Other) const
	{
		return m_ObjectPtr == i_Other;
	}

	//Now the other way around. I can do this all day 
	bool operator!=(const WeakPointer<T> & i_Other) const
	{
		return m_ObjectPtr != i_Other.m_ObjectPtr;
	}

	
	template <class U>
	bool operator!=(const WeakPointer<U> & i_Other) const
	{
		return m_ObjectPtr != i_Other.m_ObjectPtr;
	}

	
	bool operator!=(const SmartPointer<T> & i_Other) const
	{
		return m_ObjectPtr != i_Other.m_ObjectPtr;
	}

	
	template <class U>
	bool operator!=(const SmartPointer<U> & i_Other) const
	{
		return m_ObjectPtr != i_Other.m_ObjectPtr;
	}

	
	bool operator!=(const T * i_Other) const
	{
		return m_ObjectPtr != i_Other;
	}

	
	template <class U>
	bool operator!=(const U * i_Other)
	{
		return m_ObjectPtr != i_Other;
	}

	
	operator bool() const
	{
		return m_ObjectPtr != nullptr;
	}

	

	

private:

	T* m_ObjectPtr;
	RefCount * m_refCount;
	
};
