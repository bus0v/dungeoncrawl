#include <vector>
#include "Item.h"
#include "gamecharacter.h"

#ifndef ROOM_H
#define ROOM_H

class Room{
    //position list of items and enemies
public:
    int pos;
    bool isExit;
    vector<Item> items;
    vector<GameCharacter> enemies;
    Room(int=0,bool=false,vector<Item> = vector<Item>(),vector<GameCharacter> = vector<GameCharacter>());
    void clearLoot();
    void clearEnemies();
};

#endif