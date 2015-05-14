#pragma once
#include "Entity.h"

// Base class for all systems
class System
{
public:
    // Add type(s) of components that this system process
    void AddComponentType(int id) { m_componentTypes.push_back(id); }
    void AddComponentTypes(std::vector<int> ids) { m_componentTypes.insert(m_componentTypes.end(), ids.begin(), ids.end()); }

    // Add entity to system if all ComponentTypes belong to the Entity
    bool AddEntity(Entity* entity)
    {
        for (auto c : m_componentTypes)
            if (!entity->HasComponent(c))
                return false;
        m_entities.push_back(entity);
        return true;
    }
    // Remove an entity from the system
    void RemoveEntity(Entity* entity)
    {
        m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());
    }
    
    // Number of entities
    size_t GetEntitiesCount() const { return m_entities.size(); }
    // Get a entity
    Entity* GetEntity(size_t index) const { return m_entities[index]; }

    // Some virtual methods each system can implement
    virtual void Init() {};
    virtual void Update(double dt) {};
    virtual void Render() {};
    virtual void CleanUp() {}

protected:
    std::vector<int> m_componentTypes;
    std::vector<Entity*> m_entities;
};

// A Python wrapper for the System base class
class SystemPythonWrap : public System, public wrapper<System>
{
public:
    void Init()
    {
        if (override f = get_override("Init"))
            f();
        else
            System::Init();
    }
    void default_Init() { return System::Init(); }

    void Update(double dt)
    {
        if (override f = get_override("Update"))
            f(dt);
        else
            System::Update(dt);
    }
    void default_Update(double dt) { return System::Update(dt); }
    
    void Render()
    {
        if (override f = get_override("Render"))
            f();
        else
            System::Render();
    }
    void default_Render() { return System::Render(); }

    void CleanUp()
    {
        if (override f = get_override("CleanUp"))
            f();
        else
            System::CleanUp();
    }
    void default_CleanUp() { return System::CleanUp(); }
};


