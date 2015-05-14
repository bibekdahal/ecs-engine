#pragma once

#include "iter_convert.h"
#include "System.h"

// Initialize the ECS engine
void InitEngine();

// Python namespace for the engine
extern object EngineNamespace;
// Python main namespace
extern object MainNamespace;




// Register a C++ component-class for Python
// This automatically adds additional attributes for the class required
template<class T>
class_<T, bases<Component>> RegisterComponent(const char* name)
{
    class_<T, bases<Component>> c = class_<T, bases<Component>>(name);
    c.attr("id") = ClassManager::GetClassId<T>();
    EngineNamespace[name] = c;
    return c;
}


// Add a system to the engine
void AddSystem(System* system);
// Get number of systems
size_t GetSystemsCount();
// Get a system
System* GetSystem(size_t index);

