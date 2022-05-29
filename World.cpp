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
    this->rooms.insert({ getYourBedroom().getName(), getYourBedroom() });
    this->rooms.insert({ getInfinityRoom().getName(), getInfinityRoom() });
    this->rooms.insert({ getArmory().getName(), getArmory() });
    this->rooms.insert({ getGraveyardRoom().getName(), getGraveyardRoom() });
    this->rooms.insert({ getNeverRoom().getName(), getNeverRoom() });
    this->rooms.insert({ getForeverRoom().getName(), getForeverRoom() });
    this->rooms.insert({ getFinalRoom().getName(), getFinalRoom() });
    this->rooms.insert({ getForest().getName(), getForest() });
    this->rooms.insert({ getOutsideExit().getName(), getOutsideExit() });
    this->rooms.at("Outside Entrance").setExits(&this->rooms.at("Antechamber"), &this->rooms.at("Forest"), 
        &this->rooms.at("Forest"), &this->rooms.at("Forest"), &this->rooms.at("Forest"), NULL, NULL);
    this->rooms.at("Antechamber").setExits(NULL, NULL, NULL, &this->rooms.at("Outside Entrance"),
        NULL, NULL, &this->rooms.at("Event Horizon"));
    this->rooms.at("Event Horizon").setExits(NULL, NULL, NULL, NULL, NULL, &this->rooms.at("Antechamber"),
        &this->rooms.at("First Room"));
    this->rooms.at("First Room").setExits(NULL, &this->rooms.at("Fountain Room"), NULL, NULL, NULL,
        NULL, NULL);
    this->rooms.at("Fountain Room").setExits(NULL, &this->rooms.at("Infinity Room"), 
        &this->rooms.at("Temple Room"), &this->rooms.at("First Room"), &this->rooms.at("Stable Room"), NULL, NULL);
    this->rooms.at("Stable Room").setExits(NULL, &this->rooms.at("Armory"), &this->rooms.at("Fountain Room"),
        NULL, NULL, NULL, NULL);
    this->rooms.at("Temple Room").setExits(NULL, &this->rooms.at("Shroom Room"), &this->rooms.at("Library"), NULL,
        &this->rooms.at("Fountain Room"), NULL, NULL);
    this->rooms.at("Shroom Room").setExits(NULL, NULL, NULL, &this->rooms.at("Temple Room"), NULL,
        NULL, NULL);
    this->rooms.at("Library").setExits(NULL, NULL, NULL, &this->rooms.at("Your Bedroom"), &this->rooms.at("Temple Room"),
        NULL, NULL);
    this->rooms.at("Your Bedroom").setExits(NULL, &this->rooms.at("Library"), NULL, NULL, NULL,
        NULL, NULL);
    this->rooms.at("Infinity Room").setExits(NULL, &this->rooms.at("Graveyard Room"), NULL, 
        &this->rooms.at("Fountain Room"), NULL, NULL, NULL);
    this->rooms.at("Armory").setExits(NULL, NULL, NULL, &this->rooms.at("Stable Room"), NULL,
        NULL, NULL);
    this->rooms.at("Graveyard Room").setExits(NULL, &this->rooms.at("Never Room"), NULL, 
        &this->rooms.at("Infinity Room"), NULL, NULL, NULL);
    this->rooms.at("Never Room").setExits(NULL, &this->rooms.at("Final Room"), NULL, 
        &this->rooms.at("Graveyard Room"), NULL, NULL, NULL);
    this->rooms.at("Final Room").setExits(NULL, NULL, NULL, &this->rooms.at("Never Room"), NULL,
        NULL, NULL);
    this->rooms.at("Outside Exit").setExits(NULL, &this->rooms.at("Forest"), &this->rooms.at("Forest"),
        &this->rooms.at("Forest"), &this->rooms.at("Forest"), NULL, NULL);
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
        "You're in a dark forest. Before you is a concrete cubic structure, about the size of the garage at your parents house.\n"
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
        "Leaves that have blown in from the forest outside scatter the floor.\n"
    );
    this->objects.insert({ hole.getName(), hole });
    antechamber.addObject(&this->objects.at("hole"));
    return antechamber;
}

Room World::getEventHorizon()
{
    Room eventHorizon(
        "Event Horizon",
        "You're hanging on the end of a rope, submerged in darkness. You're not sure how far above the floor you are, but the rope has stopped.\n"
    );
    return eventHorizon;
}

Room World::getFirstRoom()
{
    GameObject corpse(
        "corpse",
        "Looking more closely at the corpse, you see that its face and body are identical to yours. Its expression is twisted into a look of terror.\n",
        "A body lies on the floor.\n",
        false
    );
    GameObject writing(
        "writing",
        "The words read, \'you have to find and kill your shadow self\'. It's in your own handwriting.",
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
        ""
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
        "",
        false
    );
    GameObject gargoyle(
        "gargoyle",
        "It has a long neck, a small pair of wings, and a pair of arms tucked into its sides. It looks pretty well crafted.",
        "",
        false
    );
    GameObject coins(
        "coins",
        "They are mostly copper, but some look like they may be made of silver, and you even see a few gold.",
        "",
        false
    );
    Room fountainRoom(
        "Fountain Room",
        "You find yourself in a circular room. A massive fountain sits at the center. The water flows backwards, out of the fountain and into the mouth of a gargoyle that hangs from the ceiling.\n"
    );
    this->objects.insert({ bowAndQuiver.getName(), bowAndQuiver });
    this->objects.insert({ fountain.getName(), fountain });
    fountainRoom.addObject(&this->objects.at("fountain"));
    fountainRoom.addObject(&this->objects.at("bow and quiver"));
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
        "Straw lies strewn across the ground of this long room. To the right, five stalls line the room.\n"
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
        "He looks peaceful. You feel a strong contentment looking at him.",
        "Atop the stage sits a statue of a bearded man, head draped and hands cupped.\n",
        false
    );
    Room templeRoom(
        "Temple Room",
        "This tall room leads to a short stage.\n"
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
        "This strange room is filled with mushrooms, mostly brown.\n"
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
        "Shelves line the walls, but they look to have been stripped bare.\n"
    );
    this->objects.insert({ book.getName(), book });
    library.addObject(&this->objects.at("book"));
    return library;
}

Room World::getYourBedroom()
{
    GameObject blinds(
        "blinds",
        "They're closed.",
        "The blinds are drawn on your bedroom window.",
        false
    );
    GameObject bed(
        "bed",
        "It has the same green and brown bedspread you've had for years.",
        "In front of you is your bed, the one you fall asleep in every night.\n",
        false
    );
    GameObject dresser(
        "dresser",
        "It has six drawers, probably filled with your clothes.",
        "Your dresser stands against the wall.\n",
        false
    );
    Room yourBedroom(
        "Your Bedroom",
        "It's the strangest thing... This room is your bedroom.\n"
    );
    this->objects.insert({ blinds.getName(), blinds });
    this->objects.insert({ bed.getName(), bed });
    this->objects.insert({ dresser.getName(), dresser });
    yourBedroom.addObject(&this->objects.at("blinds"));
    yourBedroom.addObject(&this->objects.at("bed"));
    yourBedroom.addObject(&this->objects.at("dresser"));
    return yourBedroom;
}

Room World::getInfinityRoom()
{
    GameObject shadowSelf(
        "shadow self",
        "His movements seem to mirror yours.",
        "The figure appears to be you.\n",
        false
    );
    Room infinityRoom(
        "Infinity Room",
        "As you stand in the open doorway of this room, you see another figure standing in a doorway on the opposite side, his back to you.\n"
    );
    this->objects.insert({ shadowSelf.getName(), shadowSelf });
    infinityRoom.addObject(&this->objects.at("shadow self"));
    return infinityRoom;
}

Room World::getArmory()
{
    GameObject chest(
        "chest",
        "It's made of dark wood with no ornamentation. The opening has a clasp, but there is no lock.",
        "",
        false
    );
    GameObject sword(
        "sword",
        "It's a longsword, a bit aged by the look of it.",
        "Above the chest hangs a sword.\n",
        true
    );
    Room armory(
        "Armory",
        "A chest sits in this small room.\n"
    );
    this->objects.insert({ chest.getName(), chest });
    this->objects.insert({ sword.getName(), sword });
    armory.addObject(&this->objects.at("chest"));
    armory.addObject(&this->objects.at("sword"));
    return armory;
}

Room World::getGraveyardRoom()
{
    GameObject headstone(
        "headstone",
        "It has your name on it.",
        "A headstone stands erect in the middle of the room.\n",
        false
    );
    Room graveyardRoom(
        "Graveyard Room",
        "The floor is made of dirt, and the illumination is a bit darker than the other rooms you've seen.\n"
    );
    this->objects.insert({ headstone.getName(), headstone });
    graveyardRoom.addObject(&this->objects.at("headstone"));
    return graveyardRoom;
}

Room World::getNeverRoom()
{
    Room neverRoom(
        "Never Room",
        "There's something wrong with this room. You don't like this room. You have a powerful urge to leave.\n"
    );
    return neverRoom;
}

Room World::getForeverRoom()
{
    Room foreverRoom(
        "Forever Room",
        "You feel a profound tranquility here. A sense that you coud live out eternity, just existing in this room.\n"
    );
    return foreverRoom;
}

Room World::getFinalRoom()
{
    Room finalRoom(
        "Final Room",
        "This room is small and completely empty. A pair of stairs lead up to a slanted door on the opposite side of the room.\n"
    );
    return finalRoom;
}

Room World::getForest()
{
    Room forest(
        "Forest",
        "You're in the forest. The trees are thin, leafless, and almost branchless.\n"
    );
    return forest;
}

Room World::getOutsideExit()
{
    Room outsideExit(
        "Outside Exit",
        "You're outside. An oblique door like that of a storm cellar emerges from the ground.\n"
    );
    return outsideExit;
}