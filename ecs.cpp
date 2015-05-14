#include "common.h"
#include <boost/python/reference_existing_object.hpp>
#include <boost/python/return_value_policy.hpp>
#include "ecs.h"

object EngineNamespace;
object MainNamespace;

// Python registration of Componenent, Entity and System classes
BOOST_PYTHON_MODULE(Engine) {
    class_<ComponentPythonWrap, boost::noncopyable>("Component")
        .def("GetId", pure_virtual(&Component::GetId));
    class_<Entity>("Entity")
        .def("Add", (void(Entity::*)(Component*))(&Entity::AddComponent))
        .def("Display", &Entity::Display)
        .def("Get", (Component*(Entity::*)(int))(&Entity::GetComponent), return_internal_reference<>());
    def("GetNewId", &ClassManager::GetNewId);

    iterable_converter()
        .from_python<std::vector<int>>();       // Additionally register std::vector<int> for support System's AddSupportedComponents method

    class_<SystemPythonWrap, boost::noncopyable>("System")
        .def("Init", &System::Init, &SystemPythonWrap::default_Init)
        .def("Update", &System::Update, &SystemPythonWrap::default_Update)
        .def("Render", &System::Render, &SystemPythonWrap::default_Render)
        .def("CleanUp", &System::CleanUp, &SystemPythonWrap::default_CleanUp)
        .def("AddEntity", &System::AddEntity)
        .def("RemoveEntity", &System::RemoveEntity)
        .def("GetEntitiesCount", &System::GetEntitiesCount)
        .def("GetEntity", &System::GetEntity, return_internal_reference<>())
        .def("AddComponentType", &System::AddComponentType)
        .def("AddComponentTypes", &System::AddComponentTypes);

    def("AddSystem", &AddSystem);
    def("GetSystemsCount", &GetSystemsCount);
    def("GetSystem", &GetSystem, return_value_policy<reference_existing_object>());
}

std::vector<System*> systems;
void AddSystem(System* system) { systems.push_back(system); }
size_t GetSystemsCount() { return systems.size(); }
System* GetSystem(size_t index) { return systems[index]; }

void InitEngine()
{
     PyImport_AppendInittab("Engine", PyInit_Engine);
     Py_Initialize();

     EngineNamespace = import("Engine").attr("__dict__");
     MainNamespace = import("__main__").attr("__dict__");
     
     // Register method to register Python Component class
     char str[] =
         "import Engine\n"
         "def RegisterComponent(compClass):\n"
         "    compClass.id = Engine.GetNewId()\n"
         "    compClass.GetId = lambda self: compClass.id\n";


     exec(str, MainNamespace, EngineNamespace);
}
