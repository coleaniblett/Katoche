#include "World.h"

World::World()
{
    this->rooms.insert({ getOutsideEntrance()->getName(), getOutsideEntrance() });
    this->rooms.insert({ getAntechamber()->getName(), getAntechamber() });
    this->rooms.insert({ getEventHorizon()->getName(), getEventHorizon() });
    this->rooms.insert({ getFirstRoom()->getName(), getFirstRoom() });
    this->rooms.insert({ getFountainRoom()->getName(), getFountainRoom() });
    this->rooms.insert({ getStableRoom()->getName(), getStableRoom() });
    this->rooms.insert({ getTempleRoom()->getName(), getTempleRoom() });
    this->rooms.insert({ getShroomRoom()->getName(), getShroomRoom() });
    this->rooms.insert({ getLibrary()->getName(), getLibrary() });
    this->rooms.insert({ getYourBedroom()->getName(), getYourBedroom() });
    this->rooms.insert({ getInfinityRoom()->getName(), getInfinityRoom() });
    this->rooms.insert({ getArmory()->getName(), getArmory() });
    this->rooms.insert({ getGraveyardRoom()->getName(), getGraveyardRoom() });
    this->rooms.insert({ getNeverRoom()->getName(), getNeverRoom() });
    this->rooms.insert({ getForeverRoom()->getName(), getForeverRoom() });
    this->rooms.insert({ getFinalRoom()->getName(), getFinalRoom() });
    this->rooms.insert({ getForest()->getName(), getForest() });
    this->rooms.insert({ getOutsideExit()->getName(), getOutsideExit() });
    this->rooms.at("Outside Entrance")->setExits(this->rooms.at("Antechamber"), this->rooms.at("Forest"), 
        this->rooms.at("Forest"), this->rooms.at("Forest"), this->rooms.at("Forest"), NULL, NULL);
    this->rooms.at("Antechamber")->setExits(NULL, NULL, NULL, this->rooms.at("Outside Entrance"),
        NULL, NULL, this->rooms.at("Event Horizon"));
    this->rooms.at("Event Horizon")->setExits(NULL, NULL, NULL, NULL, NULL, this->rooms.at("Antechamber"),
        this->rooms.at("First Room"));
    this->rooms.at("First Room")->setExits(NULL, this->rooms.at("Fountain Room"), NULL, NULL, NULL,
        NULL, NULL);
    this->rooms.at("Fountain Room")->setExits(NULL, this->rooms.at("Infinity Room"), 
        this->rooms.at("Temple Room"), this->rooms.at("First Room"), this->rooms.at("Stable Room"), NULL, NULL);
    this->rooms.at("Stable Room")->setExits(NULL, this->rooms.at("Armory"), this->rooms.at("Fountain Room"),
        NULL, NULL, NULL, NULL);
    this->rooms.at("Temple Room")->setExits(NULL, this->rooms.at("Shroom Room"), this->rooms.at("Library"), NULL,
        this->rooms.at("Fountain Room"), NULL, NULL);
    this->rooms.at("Shroom Room")->setExits(NULL, NULL, NULL, this->rooms.at("Temple Room"), NULL,
        NULL, NULL);
    this->rooms.at("Library")->setExits(NULL, NULL, NULL, this->rooms.at("Your Bedroom"), this->rooms.at("Temple Room"),
        NULL, NULL);
    this->rooms.at("Your Bedroom")->setExits(NULL, this->rooms.at("Library"), NULL, NULL, NULL,
        NULL, NULL);
    this->rooms.at("Infinity Room")->setExits(NULL, this->rooms.at("Graveyard Room"), NULL, 
        this->rooms.at("Fountain Room"), NULL, NULL, NULL);
    this->rooms.at("Armory")->setExits(NULL, NULL, NULL, this->rooms.at("Stable Room"), NULL,
        NULL, NULL);
    this->rooms.at("Graveyard Room")->setExits(NULL, this->rooms.at("Never Room"), NULL, 
        this->rooms.at("Infinity Room"), NULL, NULL, NULL);
    this->rooms.at("Never Room")->setExits(NULL, this->rooms.at("Final Room"), NULL, 
        this->rooms.at("Graveyard Room"), NULL, NULL, NULL);
    this->rooms.at("Final Room")->setExits(NULL, this->rooms.at("Outside Exit"), NULL, this->rooms.at("Never Room"), NULL,
        NULL, NULL);
    this->rooms.at("Outside Exit")->setExits(NULL, this->rooms.at("Forest"), this->rooms.at("Forest"),
        this->rooms.at("Forest"), this->rooms.at("Forest"), NULL, NULL);
    this->currentRoom = (this->rooms.at("Outside Entrance"));
    this->magicRings.reset(new MagicRings());
}

void World::setCurrentRoom(std::shared_ptr<Room> roomToSet)
{
    this->currentRoom = roomToSet;
}

std::shared_ptr<Room> World::getOutsideEntrance()
{
    std::shared_ptr<GameObject> entrance( new GameObject(
        "entrance",     
        "The entranceway is about six and a half feet tall, three feet wide. There is no sign that it ever included a door. The little light in the forest barely illuminates the inside.",
        "On its front is a tall opening with no door. It looks dark inside.\n",
        false
    ));
    std::shared_ptr<Room> outsideEntrance( new Room(
        "Outside Entrance",
        "You're in a dark forest. Before you is a concrete cubic structure, about the size of the garage at your parents house.\n"
    ));
    outsideEntrance->addObject(entrance);
    return outsideEntrance;
}

std::shared_ptr<Room> World::getAntechamber()
{
    std::shared_ptr<GameObject> hole( new GameObject(
        "hole",
        "You cannot see its bottom. The rope descends further than your vision.",
        "In the middle of the floor is a small square hole with a metal ring fixed into the concrete floor on one of its sides. Attached to the ring, a rope hangs, descending into the darkness below.\n",
        false
    ));
    std::shared_ptr<GameObject> rope(new GameObject(
        "rope",
        "It looks thick and sturdy, like it would support your bodyweight.",
        "",
        false
    ));
    std::shared_ptr<Room> antechamber( new Room(
        "Antechamber",
        "Leaves that have blown in from the forest outside scatter the floor.\n"
    ));
    antechamber->addObject(hole);
    antechamber->addObject(rope);
    return antechamber;
}

std::shared_ptr<Room> World::getEventHorizon()
{
    std::shared_ptr<Room> eventHorizon( new Room(
        "Event Horizon",
        "You're hanging on the end of a rope, submerged in darkness. You're not sure how far above the floor you are, but the rope has stopped.\n"
    ));
    return eventHorizon;
}

std::shared_ptr<Room> World::getFirstRoom()
{
    std::shared_ptr<GameObject> corpse( new SearchableObject (
        "corpse",
        "Looking more closely at the corpse, you see that its face and body are identical to yours. Its expression is twisted into a look of terror.",
        "A body lies on the floor.\n",
        false
    ));
    std::shared_ptr<GameObject> magicRing1(new GameObject(
        "ring",
        "It's made of silver. It looks... precious.",
        "",
        true
    ));
    std::dynamic_pointer_cast<SearchableObject>(corpse)->addObject(magicRing1);
    std::shared_ptr<GameObject> writing ( new GameObject (
        "writing",
        "The words read, \'you have to find and kill your shadow self\'. It's in your own handwriting.\n",
        "Above the corpse on the south wall, some writing is scribbled.\n",
        false
    ));
    std::shared_ptr<GameObject> knife( new GameObject (
        "knife",
        "It looks like a hunting knife.",
        "A knife sticks out of the back of the corpse.\n",
        true
    ));
    std::shared_ptr<Room> firstRoom( new Room(
        "First Room",
        ""
    ));
    firstRoom->addObject(corpse);
    firstRoom->addObject(writing);
    firstRoom->addObject(knife); 
    return firstRoom;
}

std::shared_ptr<Room> World::getFountainRoom()
{
    std::shared_ptr<GameObject> bowAndQuiver( new GameObject(
        "bow and quiver",
        "The bow is a simple short bow, about three feet long. The quiver looks full with arrows.",
        "Around the gargoyle's head hangs a bow and a quiver of arrows. It looks to be out of reach.\n",
        false
    ));
    std::shared_ptr<GameObject> fountain( new GameObject(
        "fountain",
        "The bottom of the fountain is filled with coins.",
        "",
        false
    ));
    std::shared_ptr<GameObject> gargoyle( new GameObject(
        "gargoyle",
        "It has a long neck, a small pair of wings, and a pair of arms tucked into its sides. It looks pretty well crafted.",
        "",
        false
    ));
    std::shared_ptr<GameObject> magicRing2(new GameObject(
        "ring",
        "It's made of silver. It looks... precious.",
        "",
        true
    ));
    std::shared_ptr<GameObject> coins( new SearchableObject(
        "coins",
        "They are mostly copper, but some look like they may be made of silver, and you even see a few gold.",
        "",
        false
    ));
    std::dynamic_pointer_cast<SearchableObject>(coins)->addObject(magicRing2);
    std::shared_ptr<Room> fountainRoom( new Room(
        "Fountain Room",
        "You find yourself in a circular room. A massive fountain sits at the center. The water flows backwards, out of the fountain and into the mouth of a gargoyle that hangs from the ceiling.\n"
    ));
    fountainRoom->addObject(fountain);
    fountainRoom->addObject(bowAndQuiver);
    fountainRoom->addObject(coins);
    fountainRoom->addObject(gargoyle);
    return fountainRoom;
}

std::shared_ptr<Room> World::getStableRoom()
{
    std::shared_ptr<GameObject> horse( new GameObject(
        "horse",
        "The horse appears calm, but when you look into its eyes you see what looks like remarkable awareness. But then again, you've never spent much time around horses. Have you?",
        "In one of the stalls stands a tall bay horse.\n",
        false
    ));
    std::shared_ptr<GameObject> shovel( new GameObject(
        "shovel",
        "It's pretty much an ordinary shovel.",
        "A shovel rests against the wall.\n",
        true
    ));
    std::shared_ptr<GameObject> straw(new SearchableObject(
        "straw",
        "It's straw. Or is it hay? You never learned the difference.",
        "",
        false
    ));
    std::shared_ptr<GameObject> magicRing3(new GameObject(
        "ring",
        "It's made of silver. It looks... precious.",
        "",
        true
    ));
    std::dynamic_pointer_cast<SearchableObject>(straw)->addObject(magicRing3);
    std::shared_ptr<Room> stableRoom( new Room(
        "Stable Room",
        "Straw lies strewn across the ground of this long room. To the right, five stalls line the room.\n"
    ));
    stableRoom->addObject(horse);
    stableRoom->addObject(shovel);
    return stableRoom;
}

std::shared_ptr<Room> World::getTempleRoom()
{
    std::shared_ptr<GameObject> statue( new GameObject(
        "statue",
        "He looks peaceful. You feel a strong contentment looking at him.",
        "Atop the stage sits a statue of a bearded man, head draped and hands cupped.\n",
        false
    ));
    std::shared_ptr<Room> templeRoom( new Room(
        "Temple Room",
        "This tall room leads to a short stage.\n"
    ));
    templeRoom->addObject(statue);
    return templeRoom;
}

std::shared_ptr<Room> World::getShroomRoom()
{
    std::shared_ptr<GameObject> brownMushroom( new GameObject(
        "brown mushroom",
        "It's a pretty ordinary looking mushroom, like the kind you'd see on lawns in the winter.",
        "",
        true
    ));
    std::shared_ptr<GameObject> redMushroom( new GameObject(
        "red mushroom",
        "The mushroom is red, with white spots. It reminds you of a video game you used to play as a kid.",
        "A red mushroom grows in the middle, shorter than the rest but visible by its bright color.\n",
        true
    ));
    std::shared_ptr<GameObject> purpleMushroom( new GameObject(
        "purple mushroom",
        "It's a sickly purple color.",
        "A few purple mushrooms sit in the corner.\n",
        true
    ));
    std::shared_ptr<Room> shroomRoom( new Room(
        "Shroom Room",
        "This strange room is filled with mushrooms, mostly brown.\n"
    ));
    shroomRoom->addObject(brownMushroom);
    shroomRoom->addObject(redMushroom);
    shroomRoom->addObject(brownMushroom);
    return shroomRoom;
}

std::shared_ptr<Room> World::getLibrary()
{
    std::shared_ptr<GameObject> book( new GameObject(
        "book",
        "The leather cover shows the outline of a feathered serpent. The pages are written in English.",
        "One book sits in the middle of an otherwise empty shelf.\n",
        true
    ));
    std::shared_ptr<Room> library( new Room(
        "Library",
        "Shelves line the walls, but they look to have been stripped bare.\n"
    ));
    library->addObject(book);
    return library;
}

std::shared_ptr<Room> World::getYourBedroom()
{
    std::shared_ptr<GameObject> blinds( new GameObject(
        "blinds",
        "They're closed.",
        "The blinds are drawn on your bedroom window.\n",
        false
    ));
    std::shared_ptr<GameObject> bed( new GameObject(
        "bed",
        "It has the same green and brown bedspread you've had for years.",
        "In front of you is your bed, the one you fall asleep in every night.\n",
        false
    ));
    std::shared_ptr<GameObject> magicRing3(new GameObject(
        "ring",
        "It's made of silver. It looks... precious.",
        "",
        true
    ));
    std::shared_ptr<GameObject> dresser( new SearchableObject(
        "dresser",
        "It has six drawers, probably filled with your clothes.",
        "Your dresser stands against the wall.\n",
        false
    ));
    std::dynamic_pointer_cast<SearchableObject>(dresser)->addObject(magicRing3);
    std::shared_ptr<Room> yourBedroom( new Room(
        "Your Bedroom",
        "It's the strangest thing... This room is your bedroom.\n"
    ));
    yourBedroom->addObject(blinds);
    yourBedroom->addObject(bed);
    yourBedroom->addObject(dresser);
    return yourBedroom;
}

std::shared_ptr<Room> World::getInfinityRoom()
{
    std::shared_ptr<GameObject> shadowSelf( new GameObject(
        "shadow self",
        "His movements seem to mirror yours.",
        "The figure appears to be you.\n",
        false
    ));
    std::shared_ptr<Room> infinityRoom( new Room(
        "Infinity Room",
        "As you stand in the open doorway of this room, you see another figure standing in a doorway on the opposite side, his back to you.\n"
    ));
    infinityRoom->addObject(shadowSelf);
    return infinityRoom;
}

std::shared_ptr<Room> World::getArmory()
{
    std::shared_ptr<GameObject> chest( new ContainerObject(
        "chest",
        "It's made of dark wood with no ornamentation. The opening has a clasp, but there is no lock.",
        "",
        false
    ));
    std::shared_ptr<GameObject> candle( new GameObject(
        "candle",
        "A short, wide candle. It looks like most of it has probably been used.",
        "A candle sits on the ground",
        true
    ));
    std::dynamic_pointer_cast<ContainerObject>(chest)->addObject(candle);
    std::shared_ptr<GameObject> sword( new GameObject(
        "sword",
        "It's a longsword, a bit aged by the look of it.",
        "Above the chest hangs a sword.\n",
        true
    ));
    std::shared_ptr<Room> armory( new Room(
        "Armory",
        "A chest sits in this small room.\n"
    ));
    armory->addObject(chest);
    armory->addObject(sword);
    return armory;
}

std::shared_ptr<Room> World::getGraveyardRoom()
{
    std::shared_ptr<GameObject> headstone( new GameObject(
        "headstone",
        "It has your name on it.",
        "A headstone stands erect in the middle of the room.\n",
        false
    ));
    std::shared_ptr<GameObject> grave(new SearchableObject(
        "grave",
        "The ground seems to have been packed tight.",
        "",
        false
    ));
    std::shared_ptr<GameObject> magicRing4(new GameObject(
        "ring",
        "It's made of silver. It looks... precious.",
        "",
        true
    ));
    std::dynamic_pointer_cast<SearchableObject>(grave)->addObject(magicRing4);
    std::shared_ptr<Room> graveyardRoom( new Room(
        "Graveyard Room",
        "The floor is made of dirt, and the illumination is a bit darker than the other rooms you've seen.\n"
    ));
    graveyardRoom->addObject(grave);
    graveyardRoom->addObject(headstone);
    return graveyardRoom;
}

std::shared_ptr<Room> World::getNeverRoom()
{
    std::shared_ptr<Room> neverRoom( new Room(
        "Never Room",
        "There's something wrong with this room. You don't like this room. You have a powerful urge to leave.\n"
    ));
    return neverRoom;
}

std::shared_ptr<Room> World::getForeverRoom()
{
    std::shared_ptr<Room> foreverRoom( new Room(
        "Forever Room",
        "You feel a profound tranquility here. A sense that you coud live out eternity, just existing in this room.\n"
    ));
    return foreverRoom;
}

std::shared_ptr<Room> World::getFinalRoom()
{
    std::shared_ptr<Room> finalRoom( new Room(
        "Final Room",
        "This room is small and completely empty. A pair of stairs lead up to a slanted door on the opposite side of the room.\n"
    ));
    return finalRoom;
}

std::shared_ptr<Room> World::getForest()
{
    std::shared_ptr<Room> forest( new Room(
        "Forest",
        "You're in the forest. The trees are thin, leafless, and almost branchless.\n"
    ));
    return forest;
}

std::shared_ptr<Room> World::getOutsideExit()
{
    std::shared_ptr<Room> outsideExit( new Room(
        "Outside Exit",
        "You're outside. An oblique door like that of a storm cellar emerges from the ground.\n"
    ));
    return outsideExit;
}