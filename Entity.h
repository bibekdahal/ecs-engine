#pragma once
#include "Component.h"

/*
Entity Class
============
Each entity stores a collection of components.
This design pattern supports only one component for each type.
Component can be easily and speedily added and acquired.
*/
class Entity
{
public:
    /*
    For each of below methods, the template versions are faster
    as they are processed at compile time.
    However, they are not available for scripting and when Component type is determined at runtime
    So, alternate methods are provided
    */

    // Add component to the entity
    template <class T>
    void AddComponent(T* component) { AddComponent(ClassManager::GetClassId<T>(), component); }
    void AddComponent(int classId, Component* component) { m_components[classId] = component; }
    void AddComponent(Component* component) { AddComponent(component->GetId(), component); }
    
    // Get a component of the entity
    template <class T>
    T* GetComponent() { return GetComponent(ClassManager::GetClassId<T>()); }
    Component* GetComponent(int classId) { return m_components[classId]; }

    // Check if the entity has a component
    template <class T>
    bool HasComponent() { return HasComponent(ClassManager::GetClassId<T>()); }
    bool HasComponent(int classId) { return m_components.find(classId) != m_components.end(); }

    // For debugging functionaslity, see id-s of types of components that are added
    void Display()
    {
        int i=1;
        for (auto it = m_components.begin(); it != m_components.end(); ++it)
        {
            Component* comp = it->second;
            std::cout << (i++) << ". Component ID: " << it->first << std::endl;
        }
    }
    
private:
    std::unordered_map<int, Component*> m_components;
};


