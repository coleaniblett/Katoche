#include "World.h"

void World::setRooms()
{
    Room sampleRoom1 = getSampleRoom1();
    Room sampleRoom2 = getSampleRoom2();
    sampleRoom1.setExits(&sampleRoom2, NULL, NULL,
        NULL, NULL, NULL);
    sampleRoom2.setExits(NULL, NULL, &sampleRoom1,
        NULL, NULL, NULL);
    this->rooms.push_back(&sampleRoom1);
    this->rooms.push_back(&sampleRoom2);
    setCurrentRoom(&sampleRoom1);
    this->testRooms();
}

void World::testRooms()
{
    std::cout << "TESTING ROOMS" << std::endl;
    for (Room* roomToTest : this->rooms)
    {
        roomToTest->printDescription();
    }
}

//void World::initializeFirstRoom()
//{
//    delete this->currentRoom;
//    this->currentRoom = this->rooms[0];
//}

void World::setCurrentRoom(Room* roomToSet)
{
    this->currentRoom = roomToSet;
}

Room World::getSampleRoom1()
{
    //GameObject egg(
    //    "egg",
    //    "item",
    //    "It's a regular egg, presumably from a hen.\n",
    //    " A small egg is sitting in the middle of the room.",
    //    true,
    //    false,
    //    true
    //);
    //std::vector<GameObject> sampleRoomContents = { egg };
    Room sampleRoom(
        "Sample Room 1",
        "An open passage lies on the North side of the room."
    );
    return sampleRoom;
}

Room World::getSampleRoom2()
{
    //GameObject nest(
    //    "nest",
    //    "item",
    //    "The nest is made of small twigs, and the center is covered with dead grass.",
    //    " A nest lies in the corner.",
    //    false,
    //    false,
    //    true
    //);
    //std::vector<GameObject> sampleRoom2Contents = { nest };
    Room sampleRoom2(
        "Sample Room 2",
        "The only exit lies to the south."
    );
    return sampleRoom2;
}
