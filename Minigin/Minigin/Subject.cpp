#include "MiniginPCH.h"
#include "Subject.h"

#include "Observer.h"

void dae::Subject::AddObserver(const std::weak_ptr<dae::Observer>& observer)
{
    if (std::find_if(m_Observers.begin(), m_Observers.end(), 
        [&observer](const std::weak_ptr<dae::Observer>& A)
        {
            return !A.owner_before(observer) && !observer.owner_before(A);
        }) == m_Observers.end())
    {
        m_Observers.push_back(observer);
    }
}

void dae::Subject::RemoveObserver(const std::weak_ptr<dae::Observer>& observer)
{
    auto result = std::find_if(m_Observers.begin(), m_Observers.end(), 
        [&observer](const std::weak_ptr<dae::Observer>& A)
        {
            return !A.owner_before(observer) && !observer.owner_before(A);
        });
    if (result != m_Observers.end())
    {
        m_Observers.erase(result);
    }
}

void dae::Subject::Notify(std::shared_ptr<dae::GameObject> go, std::shared_ptr<EventAttributes> event)
{
	for(auto& curObserver : m_Observers)
	{
        curObserver.lock()->OnNotify(go, event);
	}
}
