#include <iostream>
#include "Dungeon.cpp"
#include "Player.cpp"
#include "Gamecharacter.cpp"
#include "item.cpp"
#include "Room.cpp"


int main()
{
 cout<< "Welcome to Petr's Dungeon game. Please enter your name:\n";
 string PlayerName;
 cin>>PlayerName;
 Player player = Player(PlayerName,100,20,10);
 // first room
 Room firstRoom = Room(0,false,vector<Item>(),vector<GameCharacter>());
 //set up the second room
 Item sword = Item("Sword",0,20,0);
 vector<Item> secondRoomItems;
 secondRoomItems.push_back(sword);
 Room secondRoom = Room(1,false,secondRoomItems,vector<GameCharacter>());
 //third room
 GameCharacter slime = GameCharacter("slime",50,15,5);
 vector<GameCharacter> thirdRoomEnemies;
 thirdRoomEnemies.push_back(slime);
 Room thirdRoom = Room(2,false,vector<Item>(),thirdRoomEnemies);
 //fourth room
 GameCharacter boss=GameCharacter("Skeleton", 100,20,10);
 vector<GameCharacter> fourthRoomEnemies;
 fourthRoomEnemies.push_back(boss);
 Room fourthRoom = Room(3, true,vector<Item>(),fourthRoomEnemies);
 Dungeon dungeon = Dungeon(player);
 dungeon.rooms[0] = firstRoom;
 dungeon.rooms[1] = secondRoom;
 dungeon.rooms[2] = thirdRoom;
 dungeon.rooms[3] = fourthRoom;
 

 while(true){
     int result = dungeon.runDungeon();
     if (result==0){
         
         break;
     }
 }
 cout << "Goodbye! Thank you for playing!";
}