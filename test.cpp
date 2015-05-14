#include "common.h"
#include "ecs.h"

// Test component classes
class A : public ComponentBase<A>
{
public:
    void Show()
    {
        std::cout << "AAALLOOOOO" << std::endl;
    }
};

class B : public ComponentBase<B>
{
public:
};


int main()
{
    try {
        InitEngine();

        // Register custom component classes for Python
        EngineNamespace["A"] = RegisterComponent<A>("A")
                                .def("Show", &A::Show);
        EngineNamespace["B"] = RegisterComponent<B>("B");
        
        // Run a python script
        exec_file("script.py", MainNamespace);

        // Execute Init() method of each system
        for (size_t i=0; i<GetSystemsCount(); ++i)
        {
            System* sys = GetSystem(i);
            sys->Init();
        }

    } catch(error_already_set) {
        PyErr_Print();
    }
    return 0;
}
