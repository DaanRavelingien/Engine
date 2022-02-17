#pragma once
#include "Observer.h"

//the type of payload the notify carries with it
template <typename T>
class Subject
{
public: 
	void AddObserver(Observer<T>* pObserver)
	{
		m_Observers.push_back(pObserver);
	};

	void RemoveObserver(Observer<T>* pObserver)
	{
		auto it = std::remove_if(m_Observers.begin(), m_Observers.end(), [pObserver](Observer<T>* pOtherObserver)
			{
				if (pObserver == pOtherObserver)
					return true;
				return false;
			});

		if (it == m_Observers.end())
			Logger::GetInstance().LogWarning("Subject::RemoveObserver(Observer<T>*), did not remove observer becouse it could not find it");
		else
			m_Observers.erase(it, m_Observers.end());

	};

	void Notify(T payload, Event event)
	{
		for (Observer<T>* pObserver : m_Observers)
		{
			pObserver->Notify(payload, event);
		}
	};

private:
	std::vector<Observer<T>*> m_Observers{};
};

