#pragma once

// A manager to create and manage id-s for component classes
namespace ClassManager
{
    int GetNewId();

    template <class T>
    int GetClassId()
    {
        static int cid = GetNewId();
        return cid;
    }
};


// Abstract Base Class for all components
class Component
{
public:
    virtual int GetId() = 0;
};

// Python wrapper for the Component class
class ComponentPythonWrap : public Component, public wrapper<Component>
{
public:
    int GetId()
    {
        return get_override("GetId")();
    }
};


// A simpler base class for component with GetID() already implmented
template <class T>
class ComponentBase : public Component
{
public:
    int GetId() { return ClassManager::GetClassId<T>(); }
};


