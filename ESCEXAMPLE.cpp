#include <vector>
    using std::vector;
#include <iostream>
#include <map>
    using std::map;

//create a class that can be used so everything can derive from it
class Component
{
    public:
        Component(int id = -1) {this->id = id;};

        int getID() {return id;};
        void setID(int newID) {id = newID;};

    private:
        int id;
};

//a struct that inherits the componet class which acts more as a tag
struct Stats : Component
{
    public:
        Stats(int h, int mh, int d, int s)
        {
            setID(0);
            hp = h;
            maxHp = mh;
            dex = d;
            str = s;
        };

    private:
	    int hp, maxHp, dex, str;
};

//a struct that inherits the componet class which acts more as a tag
struct Inventory: Component
{
	//map for the inventory
};

//a struct that inherits the componet class which acts more as a tag
struct Attacks: Component
{
	//vector for spells
	//vector for attacks
	//vector that contains all
};

//Entities that you put componesnts inside of
class Entity
{
    public:
        /**
         * @brief Adds a new component into the entities map
         * 
         * @param newComponent The new Component
         */
        void addComponent(Component* newComponent)
        {
            if(!hasComponent(newComponent->getID()))
            {
                if(newComponent->getID() >= 0)
                {
                    components[newComponent->getID()] = newComponent;
                }
            }

            else 
            {
                std::cout << "Component Already Added to me!\n";
            }
            
        };

        /**
         * @brief Checks if the entitiy has a component in their map
         * 
         * @param checkComponent The component to check
         * @return True if they have the component
         */
        bool hasComponent(int id)
        {
            return components.find(id) != components.end();
        }

    private:
	    map<int, Component*> components;
};


int loop()
{
    Entity Player;

    Stats* stats = new Stats(5, 10, 5, 5);

    Player.addComponent(stats);
    Player.addComponent(stats);
    Player.addComponent(stats);

    delete stats;

    return 0;
}


/*
    They way that i understood the ECS from what I had watched and read made it kinda seem like
        Enitys, Components, and Systems were all "Tags" that were used to then create components
        and what not.
    
    So I figured that I would make a base class of each, and from their if I needed differnt methods
        I would define them inside of the struct that inherits from the base class


    All Components have an ID which would sit inside the base class, anything extra would be defined
        in the components

    All Entities would have an ID and a components map, and functiosn respecive to that
        addComponent(), removeComponent(), hasComponent,



*/

