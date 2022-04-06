#include <iostream>
//#include "IAudioObjectManager.h"
#include "AudioObject.h"
#include "AudioObjectManager.h"

using namespace holoplot;
int main(int, char**) {
    IAudioObjectManager* audioObjectManager = AudioObjectManager::getInstancePtr();

    /*
    Add object with first id and position A
    Add object with second id and position B
    Change position of object with first id to position C
    Add object with third id and position D
    Change position of object with second id to position E
    Remove object with first id
    Change position of object with third id to position F
    Change position of object with third id to position G
    Undo
    Undo
    */

    //Add object with first id and position A
    Id id1{}; 
    Position positionA{1,1,1};
    AudioObject obj1{id1, positionA};
    audioObjectManager->add(obj1);

    //Add object with second id and position B
    Id id2{}; 
    Position positionB{2,2,2};
    AudioObject obj2{id2, positionB};
    audioObjectManager->add(obj2);

    //Change position of object with first id to position C
    Position positionC{3,3,3};
    audioObjectManager->changePosition(id1, positionC);

    //Add object with third id and position D
    Id id3{}; 
    Position positionD{4,4,4};
    AudioObject obj3{id3, positionD};
    audioObjectManager->add(obj3);

    //Change position of object with second id to position E
    Position positionE{5,5,5};
    audioObjectManager->changePosition(obj2.getObjectId(), positionE);

    //Remove object with first id
    audioObjectManager->remove(id1);

    //Change position of object with third id to position F
    Position positionF{6,6,6};
    audioObjectManager->changePosition(obj3.getObjectId(), positionF);

    //Change position of object with third id to position G
    Position positionG{7,7,7};
    audioObjectManager->changePosition(obj3.getObjectId(), positionG);

    //Undo
    audioObjectManager->undo();

    //Undo
    audioObjectManager->undo();

    //Remove object with first id
    audioObjectManager->remove(id1);

    //Redo
    audioObjectManager->redo();

    //Redo
    audioObjectManager->redo();

    //Redo
    audioObjectManager->redo();

    //Undo
    audioObjectManager->undo();

    //Undo
    //audioObjectManager->undo();

    //Print all objects
    audioObjectManager->printAll();
}
