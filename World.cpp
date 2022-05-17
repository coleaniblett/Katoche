#include "World.h"

World::World()
{
    this->rooms.insert({ getSampleRoom1().getName(), getSampleRoom1() });
    this->rooms.insert({ getSampleRoom2().getName(), getSampleRoom2() });
    this->rooms.at("Sample Room 1").setExits(&(this->rooms.at("Sample Room 2")), NULL,
        NULL, NULL, NULL, NULL);
    this->rooms.at("Sample Room 2").setExits(NULL, NULL, &(this->rooms.at("Sample Room 1")),
        NULL, NULL, NULL);
    this->currentRoom = &(this->rooms.at("Sample Room 1"));
}

void World::setCurrentRoom(Room* roomToSet)
{
    this->currentRoom = roomToSet;
}

Room World::getSampleRoom1()
{
    GameObject egg(
        "egg",
        "It's a regular egg, presumably from a hen.",
        "A small egg is sitting in the middle of the room.",
        true
    );
    Room sampleRoom(
        "Sample Room 1",
        "An open passage lies on the North side of the room."
    );
    this->sampleObject1 = egg;
    sampleRoom.addObject(&sampleObject1);
    return sampleRoom;
}

Room World::getSampleRoom2()
{
    GameObject nest(
        "nest",
        "The nest is made of small twigs, and the center is covered with dead grass.",
        "A nest lies in the corner.",
        true
    );
    Room sampleRoom2(
        "Sample Room 2",
        "The only exit lies to the south."
    );
    //sampleRoom2.addObject(&nest);
    return sampleRoom2;
}
