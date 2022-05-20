#include "World.h"

World::World()
{
    //this->rooms.insert({ getSampleRoom1().getName(), getSampleRoom1() });
    //this->rooms.insert({ getSampleRoom2().getName(), getSampleRoom2() });
    this->rooms.insert({ getOutsideEntrance().getName(), getOutsideEntrance() });
    this->rooms.insert({ getAntechamber().getName(), getAntechamber() });
    this->rooms.insert({ getEventHorizon().getName(), getEventHorizon() });
    this->rooms.insert({ getFirstRoom().getName(), getFirstRoom() });
    this->rooms.at("Outside Entrance").setExits(&this->rooms.at("Antechamber"), NULL, NULL,
        NULL, NULL, NULL);
    this->rooms.at("Outside Entrance").setRoomContained(&this->rooms.at("Antechamber"));
    this->rooms.at("Antechamber").setExits(NULL, NULL, &this->rooms.at("Outside Entrance"),
        NULL, NULL, &this->rooms.at("Event Horizon"));
    this->rooms.at("Event Horizon").setExits(NULL, NULL, NULL, NULL, &this->rooms.at("Antechamber"),
        &this->rooms.at("First Room"));
    this->rooms.at("First Room").setExits(NULL, NULL, NULL, NULL, NULL, NULL);
    //this->rooms.at("Sample Room 1").setExits(&(this->rooms.at("Sample Room 2")), NULL,
    //    NULL, NULL, NULL, NULL);
    //this->rooms.at("Sample Room 2").setExits(NULL, NULL, &(this->rooms.at("Sample Room 1")),
    //    NULL, NULL, NULL);
    this->currentRoom = &(this->rooms.at("Outside Entrance"));
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
        "An open passage lies on the North side of the room.",
        false
    );
    this->objects.insert({ egg.getName(), egg });
    //this->sampleObject1 = egg;
    sampleRoom.addObject(&this->objects.at("egg"));
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
        "The only exit lies to the south.",
        false
    );
    //sampleRoom2.addObject(&nest);
    return sampleRoom2;
}

Room World::getOutsideEntrance()
{
    GameObject entrance(
        "entrance",     
        "The entranceway is about six and a half feet tall, three feet wide. There is no sign that it ever included a door. The little light in the forest barely illuminates the inside.",
        "On its front is a tall opening with no door. It looks dark inside.",
        false
    );
    Room outsideEntrance(
        "Outside Entrance",
        "You're in a dark forest. Before you is a concrete cubic structure, about the size of the garage at your parents house.",
        true
    );
    this->objects.insert({ entrance.getName(), entrance });
    outsideEntrance.addObject(&this->objects.at("entrance"));
    return outsideEntrance;
}

Room World::getAntechamber()
{
    GameObject hole(
        "hole",
        "You cannot see its bottom. The rope descends further than your vision.",
        "In the middle of the floor is a small square hole with a metal ring fixed into the concrete floor on one of its sides. Attached to the ring, a rope hangs, descending into the darkness below.",
        false
    );
    Room antechamber(
        "Antechamber",
        "Leaves that have blown in from the forest outside scatter the floor.",
        true
    );
    this->objects.insert({ hole.getName(), hole });
    antechamber.addObject(&this->objects.at("hole"));
    return antechamber;
}

Room World::getEventHorizon()
{
    Room eventHorizon(
        "Event Horizon",
        "You're hanging on the end of a rope, submerged in darkness. You're not sure how far above the floor you are, but the rope has stopped.",
        false
    );
    return eventHorizon;
}

Room World::getFirstRoom()
{
    GameObject corpse(
        "corpse",
        "Looking more closely at the corpse, you see that its face and body are identical to yours. Its expression is twisted into a look of terror.",
        "A body lies on the floor, a knife sticking out of its back.",
        false
    );
    GameObject writing(
        "writing",
        "The words read, \'you have to find and kill your shadowself\'. It's in your own handwriting.",
        "Above the corpse on the south wall, some writing is scribbled.",
        false
    );
    Room firstRoom(
        "First Room",
        "Your feet touch the ground after a short drop, and the darkness disappears in an instant as two torches light up on the western side of this small room, seemingly by themselves. Between them is a door.",
        false
    );
    this->objects.insert({ corpse.getName(), corpse });
    this->objects.insert({ writing.getName(), writing });
    firstRoom.addObject(&this->objects.at("corpse"));
    firstRoom.addObject(&this->objects.at("writing"));
    return firstRoom;
}
