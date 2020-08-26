#pragma once
#include <string>
struct Weapon
{
    std::string Name;
    int Accuracy = 0;
    int Damage = 0;
    int Reload = 0;
    int DrawSpeed = 0;
};

struct Armor
{
    std::string Name;
    int DamageReduction = 0;
    int OtherStat = 0;
};


struct Barretta : public Weapon
{
    std::string Name = "Baretta";
    int Accuracy = 5;
    int Damage = 5;
    int Reload = 5;
    int DrawSpeed = 5;
};

struct BasicArmor : public Armor
{
    std::string Name = "Basic Armor";
    int DamageReduction = 2;
    int OtherStat = 0;
};