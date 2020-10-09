#include "Dungeon.h"
#include "Player.h"
#include <iostream>
using namespace std;
Dungeon::Dungeon(Player p)
{
    player = p;
}
void Dungeon::handleEmptyRoom(Room *room){
    cout << "You enter the room, and see that its empty!\n";
    string actions[] ={"a. Move to another room"};
    while(true) {
        printActions(1, actions);
        string input;
        cin >> input;
        if (input =="a"){
            //move actions
            return;
        }
        else{
            cout << "Wrong input!\n";
        }
    }
}
void Dungeon::handleLootActions(Room *room){
    Item item=room->items.front();
    int size =room->items.size();
    player.lootRoom(room);
    room->clearLoot();
    for (int i=0;i <size;i++){
        cout <<"you open the chest and find a " <<item.name <<".\n";
        cout << "Your health is now " << player.currentHealth;
        cout << ", your attack is now " << player.attack;
        cout << ", and your defence is now " << player.defense << "\n";
        
}
}
void Dungeon::handleFightActions(GameCharacter *enemy){
    //fighting
    string actions[] = {
        "a. Attack ",
        "b. Retreat"};

    while(true) {
        printActions(2, actions);
        string input;
        cin >> input;
        //handle player actions
        if (input =="a"){
            //fight
            int damage = enemy->takeDamage(player.attack);
            cout << "Your attack does "<< damage<<" damage.\n";

            
        }
        else if (input == "b"){
            //move to previous room
            player.changeRooms(player.previousRoom);
            enterRoom(player.currentRoom);
            return;
        }
        else{
            cout << "Wrong input!\n";
        }
        //check if enemy is dead
        if (enemy->checkIsDead()){
            cout << "Your win! You have defeated the "<< enemy->name <<".\n";
            player.increaseStats(10,5,5);
            player.currentRoom->clearEnemies();
            return;
        }

        //handle enemy actions
        int damage = player.takeDamage(enemy->attack);
        cout <<enemy->name<<"'s attack does "<<damage<<" damage.\n";
        cout << "You now have " << player.currentHealth << " health.\n";

        if (player.checkIsDead()){
            cout<<"You died!";
            return;
        }
        
        
    }
    

}
void Dungeon::handleRoomWithEnemy(Room *room) {
    GameCharacter enemy=room->enemies.front();
    cout << "You enter the room, and see a " << enemy.name<<".\n";
    string actions[] = {
        "a. Attack the " + enemy.name,
        "b. Go back to previous room"};

    while(true) {
        printActions(1, actions);
        string input;
        cin >> input;
        if (input =="a"){
            //fight
            handleFightActions(&enemy);
            return;
        }

        else if (input == "b"){
            //move to previous room
            player.changeRooms(player.previousRoom);
            enterRoom(player.currentRoom);
            return;
        }
        else{
            cout << "Wrong input!\n";
        }
    }
}

void Dungeon::handleRoomWithChest(Room *room){
    cout << "You enter the room, and see a large chest in the middle!\n";
    string actions[] =    {"a. Loot the chest","b. Move to another room"};

    while(true) {
        printActions(1, actions);
        string input;
        cin >> input;
        if (input =="a"){
            //loot chest
            handleLootActions(room);
            return;
        }
        else if (input == "b"){
            //move to another room
            return;
        }
        else{
            cout << "Wrong input!\n";
        }
    }
}
void Dungeon::handleMovementActions(Room * room){
    while(true){

    if (room->pos==0){
        string actions[] = {"a.Move right","b. Move down"};
        printActions(2, actions);
        string input;
        cin >> input;
        if (input=="a"){
            player.changeRooms(&rooms[1]);
            return;
        }
        else if (input=="b"){
            player.changeRooms(&rooms[2]);
            return;
        }else{
           cout << "Wrong input!\n"; 
        }
        }

    else if (room->pos==1){
        string actions[] = {"a.Move left"};
        printActions(1, actions);
        string input;
        cin >> input;
        if (input=="a"){
            player.changeRooms(&rooms[0]);
            return;
        }
        else{
           cout << "Wrong input!\n"; 
        }
    }

    else if (room->pos==2){
        string actions[] = {"a.Move up","b. Move right"};
        printActions(2,actions);
        string input;
        cin >> input;
        if (input=="a"){
            player.changeRooms(&rooms[0]);
            return;
        }
        else if (input=="b"){
            player.changeRooms(&rooms[3]);
            return;
        }else{
           cout << "Wrong input!\n"; 
        }
    }
    else{    
        string actions[] = {"a.Move left"};
        printActions(1, actions);
        string input;
        cin >> input;
        if (input=="a"){
            player.changeRooms(&rooms[2]);
            return;
        }
        else{
           cout << "Wrong input!\n"; 
        }

    }
    }

}
void Dungeon::printActions(int numActions, string actions[]){
    cout << "Choose an action: \n";
    for (int i=0; i<numActions; i++){
        cout << actions[i] << "\n";
    }
}
void Dungeon::enterRoom(Room * room)
{
    if(room->enemies.size()!=0){
        //handle room with enemy
        handleRoomWithEnemy(room);
    }
    else if(room->items.size()!=0){
        //handle room with items
        handleRoomWithChest(room);
    }
    else{
        // empty room
        handleEmptyRoom(room);
    }
}
int Dungeon::performEndGameLogic(){
    string actions[]={"a. Yes","b. No"};
    while(true){
        printActions(2, actions);
        string input;
        cin>>input;
        if (input == "a"){
            return 1;
        }
        else if (input =="b"){
            return 0;
        }
        else{
            cout << "Wrong input!\n";
        }
    }

    
}
int Dungeon::runDungeon() {
    cout << "Welcome to the Dungeon! It's a dangerous place!\n";
    player.currentRoom = &rooms[0];
    player.previousRoom = &rooms[0];
    while(true){
        //enter room
        enterRoom(player.currentRoom);
        if (player.checkIsDead()){
            //lose the game
            cout << "Game over! Try again?\n";
            return performEndGameLogic();

        }
        else{
            if (player.currentRoom->isExit){
                if (player.currentRoom->enemies.size() == 0){
                    //win
                    cout << "You win! Play again?\n";
                    return performEndGameLogic();
                }
            }
        }
        //present action
        //take action -enter seq
        //check if dead
        //movement options
        handleMovementActions(player.currentRoom);
    }
}