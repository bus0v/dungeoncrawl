#include "gamecharacter.h"

GameCharacter::GameCharacter(string n, int h,int a, int d){
    name =n;
    maxHealth=h;
    currentHealth=h;
    attack=a;
    defense=d;

}

int GameCharacter::takeDamage(int amount){
    int damage=amount-defense;
    if (damage <0){
        damage=0;
    }
    currentHealth -=damage;
    return damage;

}

bool GameCharacter::checkIsDead()
{
    return currentHealth<=0;
}