import Engine

# Custom component class built in python
class MyComponent(Engine.Component):
    def Hello(self):
        print("hello")

# Register MyComponent as Component
Engine.RegisterComponent(MyComponent)


# Custom system built in python
class MySystem(Engine.System):
    def __init__(self):
        Engine.System.__init__(self)
        Engine.System.AddComponentTypes(self, [Engine.A.id, MyComponent.id])  # System's components are A and MyComponent

    def Init(self):
        for i in range(0, self.GetEntitiesCount()):
            ent = self.GetEntity(i)
            ent.Get(MyComponent.id).Hello()
            ent.Get(Engine.A.id).Show()

# Create components of each type: A, B and MyComponent
b = Engine.A()
a = Engine.B()
c = MyComponent()

# Create a entity and add above components
en = Engine.Entity()
en.Add(a)
en.Add(b)
en.Add(c)
en.Display()

# Add a new system and add the entity to it
sys = MySystem()
Engine.AddSystem(sys)
sys.AddEntity(en)

