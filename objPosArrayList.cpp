#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; // 256 elements on the heap
    listSize = 0; // no valid element in the list upon startup
    arrayCapacity = ARRAY_MAX_CAP; // array capacity should be max
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList; // remember to use delete[] to call the destructors of all instances in the array
    // otherwise, only the first element will be properly deleted, leading to leak
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // still need error check - what if listSize is at capacity?
    // - check if listSize is equal to arrayCapacity. If yes, at capacity, dont insert.
    
    // At capacity, don't insert.
    if (listSize == arrayCapacity) 
    {
        return;
    }

    for(int i = listSize; i > 0; i--)
    {
        aList[i].setObjPos(aList[i-1]); // this will shuffle all elements towards the tail
    }

    aList[0].setObjPos(thisPos);
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize == arrayCapacity)
    {
        return;
    }

    for (int i = listSize - 1; i >= 0; i--)
    {
        aList[i + 1].setObjPos(aList[i]);
    }

    // Insert the new element at the tail.
    aList[listSize].setObjPos(thisPos);
    listSize++;
}

void objPosArrayList::removeHead()
{
    // if the list is empty, do nothing.
    if (listSize == 0)
    {
        return;
    }

    // Shift all elements towards the head to remove the head element.
    for (int i = 0; i < listSize - 1; i++)
    {
        aList[i].setObjPos(aList[i + 1]);
    }

    // Decrement the list size.
    listSize--;
}

void objPosArrayList::removeTail()
{
    // if the list is empty, do nothing.
    if (listSize == 0)
    {
        return;
    }

    // Decrement the list size to exclude the last element (remove the tail).
    listSize--;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    if(listSize > 0)
        returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    if(listSize > 0)
        returnPos.setObjPos(aList[listSize - 1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index) const
{
    if (index >= 0 && index < listSize)
        returnPos.setObjPos(aList[index]);
}

// when all test cases pass for objPosArrayList, copy all contents into project files
