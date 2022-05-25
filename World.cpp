#include "World.h"

World::World()
{
    this->rooms.insert({ getOutsideEntrance().getName(), getOutsideEntrance() });
    this->rooms.insert({ getAntechamber().getName(), getAntechamber() });
    this->rooms.insert({ getEventHorizon().getName(), getEventHorizon() });
    this->rooms.insert({ getFirstRoom().getName(), getFirstRoom() });
    this->rooms.insert({ getFountainRoom().getName(), getFountainRoom() });
    this->rooms.insert({ getStableRoom().getName(), getStableRoom() });
    this->rooms.insert({ getTempleRoom().getName(), getTempleRoom() });
    this->rooms.insert({ getShroomRoom().getName(), getShroomRoom() });
    this->rooms.insert({ getLibrary().getName(), getLibrary() });
    this->rooms.at("Outside Entrance").setExits(&this->rooms.at("Antechamber"), NULL, NULL, NULL,
        NULL, NULL, NULL);
    this->rooms.at("Antechamber").setExits(NULL, NULL, NULL, &this->rooms.at("Outside Entrance"),
        NULL, NULL, &this->rooms.at("Event Horizon"));
    this->rooms.at("Event Horizon").setExits(NULL, NULL, NULL, NULL, NULL, &this->rooms.at("Antechamber"),
        &this->rooms.at("First Room"));
    this->rooms.at("First Room").setExits(NULL, &this->rooms.at("Fountain Room"), NULL, NULL, NULL,
        NULL, NULL);
    this->rooms.at("Fountain Room").setExits(NULL, NULL, &this->rooms.at("Temple Room"), &this->rooms.at("First Room"),
        &this->rooms.at("Stable Room"), NULL, NULL);
    this->rooms.at("Stable Room").setExits(NULL, NULL, &this->rooms.at("Fountain Room"), NULL, NULL,
        NULL, NULL);
    this->rooms.at("Temple Room").setExits(NULL, &this->rooms.at("Shroom Room"), &this->rooms.at("Library"), NULL,
        &this->rooms.at("Fountain Room"), NULL, NULL);
    this->rooms.at("Shroom Room").setExits(NULL, NULL, NULL, &this->rooms.at("Temple Room"), NULL,
        NULL, NULL);
    this->rooms.at("Library").setExits(NULL, NULL, NULL, NULL, &this->rooms.at("Temple Room"),
        NULL, NULL);
    this->currentRoom = &(this->rooms.at("Outside Entrance"));
}

void World::setCurrentRoom(Room* roomToSet)
{
    this->currentRoom = roomToSet;
}

Room World::getOutsideEntrance()
{
    GameObject entrance(
        "entrance",     
        "The entranceway is about six and a half feet tall, three feet wide. There is no sign that it ever included a door. The little light in the forest barely illuminates the inside.",
        "On its front is a tall opening with no door. It looks dark inside.\n",
        false
    );
    Room outsideEntrance(
        "Outside Entrance",
        "You're in a dark forest. Before you is a concrete cubic structure, about the size of the garage at your parents house."
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
        "In the middle of the floor is a small square hole with a metal ring fixed into the concrete floor on one of its sides. Attached to the ring, a rope hangs, descending into the darkness below.\n",
        false
    );
    Room antechamber(
        "Antechamber",
        "Leaves that have blown in from the forest outside scatter the floor."
    );
    this->objects.insert({ hole.getName(), hole });
    antechamber.addObject(&this->objects.at("hole"));
    return antechamber;
}

Room World::getEventHorizon()
{
    Room eventHorizon(
        "Event Horizon",
        "You're hanging on the end of a rope, submerged in darkness. You're not sure how far above the floor you are, but the rope has stopped."
    );
    return eventHorizon;
}

Room World::getFirstRoom()
{
    GameObject corpse(
        "corpse",
        "Looking more closely at the corpse, you see that its face and body are identical to yours. Its expression is twisted into a look of terror.",
        "A body lies on the floor.\n",
        false
    );
    GameObject writing(
        "writing",
        "The words read, \'you have to find and kill your shadowself\'. It's in your own handwriting.",
        "Above the corpse on the south wall, some writing is scribbled.\n",
        false
    );
    GameObject knife(
        "knife",
        "It looks like a hunting knife.",
        "A knife sticks out of the back of the corpse.\n",
        true
    );
    Room firstRoom(
        "First Room",
        "Your feet touch the ground after a short drop, and the darkness disappears in an instant as two torches light up on the northern side of this small room, seemingly by themselves. Between them is a door."
    );
    this->objects.insert({ corpse.getName(), corpse });
    this->objects.insert({ writing.getName(), writing });
    this->objects.insert({ knife.getName(), knife });
    firstRoom.addObject(&this->objects.at("corpse"));
    firstRoom.addObject(&this->objects.at("writing"));
    firstRoom.addObject(&this->objects.at("knife")); 
    return firstRoom;
}

Room World::getFountainRoom()
{
    GameObject bowAndQuiver(
        "bow and quiver",
        "The bow is a simple short bow, about three feet long. The quiver looks full with arrows.",
        "Around the gargoyle's head hangs a bow and a quiver of arrows. It looks to be out of reach.\n",
        false
    );
    GameObject fountain(
        "fountain",
        "The bottom of the fountain is filled with coins.",
        "A massive fountain sits at the center. The water flows backwards, out of the fountain and into the mouth of a gargoyle that hangs from the ceiling.",
        false
    );
    Room fountainRoom(
        "Fountain Room",
        "You find yourself in a circular room."
    );
    this->objects.insert({ bowAndQuiver.getName(), bowAndQuiver });
    this->objects.insert({ fountain.getName(), fountain });
    fountainRoom.addObject(&this->objects.at("bow and quiver"));
    fountainRoom.addObject(&this->objects.at("fountain"));
    return fountainRoom;
}

Room World::getStableRoom()
{
    GameObject horse(
        "horse",
        "The horse appears calm, but when you look into its eyes you see what looks like remarkable awareness. But then again, you've never spent much time around horses. Have you?",
        "In one of the stalls stands a tall bay horse.\n",
        false
    );
    GameObject shovel(
        "shovel",
        "It's pretty much an ordinary shovel.",
        "A shovel rests against the wall.\n",
        true
    );
    Room stableRoom(
        "Stable Room",
        "Straw lies strewn across the ground of this long room. To the right, five stalls line the room."
    );
    this->objects.insert({ horse.getName(), horse });
    this->objects.insert({ shovel.getName(), shovel });
    stableRoom.addObject(&this->objects.at("horse"));
    stableRoom.addObject(&this->objects.at("shovel"));
    return stableRoom;
}

Room World::getTempleRoom()
{
    GameObject statue(
        "statue",
        "He looks peaceful. You feel a strong contentmen looking at him.",
        "Atop the stage sits a statue of a bearded man, head draped and hands cupped.\n",
        false
    );
    Room templeRoom(
        "Temple Room",
        "This tall room leads to a short stage."
    );
    this->objects.insert({ statue.getName(), statue });
    templeRoom.addObject(&this->objects.at("statue"));
    return templeRoom;
}

Room World::getShroomRoom()
{
    GameObject brownMushroom(
        "brown mushroom",
        "It's a pretty ordinary looking mushroom, like the kind you'd see on lawns in the winter.",
        "",
        true
    );
    GameObject redMushroom(
        "red mushroom",
        "The mushroom is red, with white spots. It reminds you of a video game you used to play as a kid.",
        "A red mushroom grows in the middle, shorter than the rest but visible by its bright color.\n",
        true
    );
    GameObject purpleMushroom(
        "purple mushroom",
        "It's a sickly purple color.",
        "A few purple mushrooms sit in the corner.\n",
        true
    );
    Room shroomRoom(
        "Shroom Room",
        "This strange room is filled with mushrooms, mostly brown."
    );
    this->objects.insert({ brownMushroom.getName(), brownMushroom });
    this->objects.insert({ redMushroom.getName(), redMushroom });
    this->objects.insert({ purpleMushroom.getName(), purpleMushroom });
    shroomRoom.addObject(&this->objects.at("brown mushroom"));
    shroomRoom.addObject(&this->objects.at("red mushroom"));
    shroomRoom.addObject(&this->objects.at("brown mushroom"));
    return shroomRoom;
}

Room World::getLibrary()
{
    GameObject book(
        "book",
        "The leather cover shows the outline of a feathered serpent. The pages are written in English.",
        "One book sits in the middle of an otherwise empty shelf.\n",
        true
    );
    Room library(
        "Library",
        "Shelves line the walls, but they look to have been stripped bare."
    );
    this->objects.insert({ book.getName(), book });
    library.addObject(&this->objects.at("book"));
    return library;
}
