#pragma once
#include "ConsolePrint.h"
#include "stdint.h"
#include <assert.h>

struct RefCount {
	uint32_t m_SmartCount, m_WeakCount;
	RefCount(uint32_t i_SmartCount,uint32_t i_WeakCount):
		m_SmartCount(i_SmartCount),
		m_WeakCount(i_WeakCount)
	{
		
	}
	RefCount(const RefCount & i_Other) {
		m_SmartCount = i_Other.m_SmartCount;
		m_WeakCount = i_Other.m_WeakCount;
	}
	

	RefCount& operator=(const RefCount & i_Other)
	{
		m_SmartCount = i_Other.m_SmartCount;
		m_WeakCount = i_Other.m_WeakCount;

		return *this;
	}

	RefCount& operator=(const RefCount * i_Other)
	{
		m_SmartCount = i_Other->m_SmartCount;
		m_WeakCount = i_Other->m_WeakCount;

		return *this;
	}
	

};

template <class U>
class WeakPointer;

template <class T>
class SmartPointer
{
	template <class U>
	friend class WeakPointer;

	template <class U>
	friend class SmartPointer;

public:
	SmartPointer() : m_ObjectPtr(nullptr), m_refCount(nullptr)
	{ }

	// Constructor
	SmartPointer(T* i_ptr) : m_ObjectPtr(i_ptr),
		m_refCount(new RefCount(1,0))
	{}

	// Copy constructor 
	SmartPointer(const SmartPointer & i_other) :
		m_ObjectPtr(i_other.m_ObjectPtr), m_refCount(i_other.m_refCount)
	{
		m_refCount->m_SmartCount++;
	}

	// Copy Constructor for inherited objects
	
	template <class U>
	SmartPointer(const SmartPointer<U> & i_other) :
		m_ObjectPtr(i_other), m_refCount(i_other.m_refCount)
	{
		m_refCount->m_SmartCount++;
	}

	~SmartPointer()
	{
		if (m_refCount != NULL || m_ObjectPtr != NULL) {
			// delete the underlying pointer if smart count reaches to zero
			m_refCount->m_SmartCount--;
			if (m_refCount->m_SmartCount == 0)
			{
				delete m_ObjectPtr;
				//Always good to dereference it
				m_ObjectPtr = nullptr;
				//If weak count is also zero we can safely delete the refcount too
				if (m_refCount->m_WeakCount == 0)
				{

					delete m_refCount;
					m_refCount = nullptr;
				}
			}
		}
	}

	// copy constructor for weak pointer
	SmartPointer(const WeakPointer<T> & i_Other)
	{
		//if (m_refCount != nullptr) {
			if (i_Other.m_refCount->m_SmartCount != 0)
			{
				m_refCount = i_Other.m_refCount;
				m_ObjectPtr = i_Other.m_ObjectPtr;

				m_refCount->m_SmartCount++;
			}
			else
			{
				//return nullptr;
			}
		//}
	}

	
	// Assignmnet Operator 
	SmartPointer & operator=(const SmartPointer<T> & i_Other)
	{
		// Am I trying to assign to the same underlying pointer?
		if (m_ObjectPtr == i_Other.m_ObjectPtr)
		{ 
			return *this;
		}
		else
		{
			
			//Release the current reference
			ReleaseReference();
			//Acquire new reference
			m_ObjectPtr = i_Other.m_ObjectPtr;
			m_refCount = i_Other.m_refCount;
			m_refCount->m_SmartCount++;
			return *this;
		}
	}

	// Assignment operator for 
	// polymorphic copying
	template <class U>
	SmartPointer & operator=(const SmartPointer<U> & i_Other)
	{
		// if they are same
		if (m_ObjectPtr = i_Other.m_ObjectPtr)
		{ // return a reference
			return *this;
		}
		else
		{
			// release the current reference
			ReleaseReference();
			//Acquire new reference
			m_ObjectPtr = i_Other.m_ObjectPtr;
			m_refCount = i_Other.m_refCount;
			//Increase its smart count
			m_refCount->m_SmartCount++;
			return *this;
		}
	}
	void ReleaseReference() {
		
		m_refCount->m_SmartCount--;
		// delete if this was the last one
		if (m_refCount->m_SmartCount == 0)
		{
			delete m_ObjectPtr;
			m_ObjectPtr = nullptr;
			//Well if its the last one standing
			if (m_refCount->m_WeakCount == 0)
			{
				delete m_refCount;
				m_refCount = nullptr;
			}
		}
	 }
	

	//Operators for accessing underlying object 
	T & operator*() {
		return *m_ObjectPtr;
	}
	
	T* operator->() const
	{
		return m_ObjectPtr;
	}

	//All types of operators
	bool operator==(const SmartPointer<T> & i_Other) const
	{
		return m_ObjectPtr == i_Other.m_ObjectPtr;
	}

	
	template <class U>
	bool operator==(const SmartPointer<U> & i_Other) const
	{
		return m_ObjectPtr == i_Other.m_ObjectPtr;
	}

	
	bool operator==(const WeakPointer<T> & i_Other) const
	{
		return m_ObjectPtr == i_Other.m_ObjectPtr;
	}

	
	template <class U>
	bool operator==(const WeakPointer<U> & i_Other) const
	{
		return m_ObjectPtr == i_Other.m_ObjectPtr;
	}

	
	bool operator==(T* i_ptr)
	{
		return m_ObjectPtr == i_ptr;
	}

	
	bool operator==(std::nullptr_t null) const
	{
		return m_ObjectPtr == null;
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

	
	bool operator!=(const WeakPointer<T> & i_Other) const
	{
		return m_ObjectPtr != i_Other.m_ObjectPtr;
	}

	
	template <class U>
	bool operator!=(const WeakPointer<U> & i_Other) const
	{
		return m_ObjectPtr != i_Other.m_ObjectPtr;
	}

	
	bool operator!=(T* i_ptr) const
	{
		return m_ObjectPtr != i_ptr;
	}

	
	bool operator!=(std::nullptr_t null) const
	{
		return m_ObjectPtr != null;
	}

	
	operator bool() const
	{
		return m_ObjectPtr != nullptr;
	}

	

private:
	T* m_ObjectPtr;
	RefCount * m_refCount;
};