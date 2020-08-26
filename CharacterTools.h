#pragma once
#include "pch.h"
#include <string>
#include "Gear.h"

class charSheet
{
public:
    int ID;
    //Basic Character Info
    struct bio
    {
        std::string charName;
        std::string race;
        std::string height;
        std::string weight;
        std::string hair;
        std::string eyes;
        std::string description;
    }bio;

    //Stats Construct
    struct Stats
    {
        //Physical Stats
        struct Physical
        {
            //Body = Strengh + Toughness
            int Body = 10;
            int Strength = 10;
            int Toughness = 10;

            //Agility = Reflexes + Coordination
            int Agility = 10;
            int Reflexes = 10;
            int Coordination = 10;
        }Physical;
        //Mental Stats
        struct Mental
        {
            //Mind = Intelligence + Ego
            int Mind = 10;
            int Intelligence = 10;
            int Ego = 10;

            //Willpower = Self Discipline + Knowledge
            int Willpower = 10;
            int SelfDiscipline = 10;
            int Knowledge = 10;
        }Mental;
        //Meta Stats
        struct Meta
        {
            //Power = Force + Channeling
            int Power = 10;
            int Force = 10;
            int Channeling = 10;

            //Control = Manipulation + Reserve
            int Control = 10;
            int Manipulation = 10;
            int Reserve = 10;
        }Meta;
        //Terciary Stats
        int Inititive;
        int Looks;
    }Stats;
    
    struct statBonus
    {
        //Physical Stats
        struct Physical
        {
            int BodyBonus;
            int StrengthBonus;
            int ToughnessBonus;
 
            int AgilityBonus;
            int ReflexesBonus;
            int CoordinationBonus;
        }Physical;

        //Mental Stats
        struct Mental
        {
            int MindBonus;
            int IntelligenceBonus;
            int EgoBonus;

            int WillpowerBonus;
            int SelfDisciplineBonus;
            int KnowledgeBonus;
        }Mental;

        struct Meta
        {
            int ControlBonus;
            int ManipulationBonus;
            int RestraintBonus;

            int PowerBonus;
            int ChannelingBonus;
            int ForceBonus;
        }Meta;
        //Magic Stats

        //Terciary Stats
        int LooksBonus;
    }statBonus;

    //Dice pool construct
    struct pool
    {
        //Physical Pool
        //Body + Agility / 2
        int Physical = 5;
        //Mental Pool
        //Mind + Willpower / 2
        int Mental = 5;
        //Casting Pool
        //Control + Power / 2
        int Cast = 5;
    }pool;

    //Damage and stuff
    struct Health
    {
        int Energy = 0;
        int Hits = 0;
    }Health;

    //Current Maths For Attacks and Defence
    struct CombatStats
    {
        struct Strike
        {
            struct Melee
            {
                int TargetMod = 0;
                int PoolMod = 0;
            }Melee;
            struct Ranged
            {
                int TargetMod = 0;
                int PoolMod = 0;
            }Ranged;
        }Strike;

        struct Block
        {
            int TargetMod = 0;
            int PoolMod = 0;
        }Block;

        //Attack
        int StrikeTar;
        int StrikePool;
        int GrappleTar;
        int GrapplePool;
        int CastTar;
        int CastPool;
        //Defense
        int DodgeTar;
        int DodgePool;
        int ParryTar;
        int ParryPool;
        int BlockTar;
        int BlockPool;
    }CombatStats;

    //Skills construct
    struct skill
    {
        struct Combat
        {
            struct Melee
            {
                int Brawl;
                int Swords;
                int Knives;
            }Melee;
            struct Ranged
            {
                int Pistols;
                int SMGs;
                int Rifles;
                int Bow;
            }Ranged;
            struct Cast
            {
                int PointBlank;
                int Blast;
                int Ray;
                int Cone;
            }Cast;
        }Combat;
        struct active
        {
            //Physical Skills
            int powerLifting;
            //Agility Skills
            int slightOfHand;
            //Mental Skills
            int bluff;
            //Social Skills
            int mingle;
            //Magic Skills;
            int kinetomancy;
        }active;
        struct passive
        {
            //Knowledge skills mostly, things that are intangable maybe.
        };
    }skill;

    struct cStats {
        int CurrentEndurance = 0;
        int CurrentHealth = 0;
        int CurrentTarget = 0;
        int CurrentPool = 0;
        int CurrentAccuracy = 0;
        int CurrentDamage = 0;
        int CurrentOffence = 0;
        int CurrentDefence = 0;
        int CurrentInititive = 0;
    }cStats;

    struct cData
    {
        int poolArr[50]{};
        int curSuc = 0;
        float totSuc = 0.00f;
        int wins = 0;
        int wonBy = 0;
        int damDone = 0;
        float totDam = 0.00f;
        float wonByTotal = 0.00f;
        int kills = 0;
    }cData;

    struct cPools {
        int curPhys;
        int curMen;
        int curCast;
    }cPools;

    Weapon curWeapon;
    
    charSheet(std::string name, int inID);

    //Get Set//

    int Strength_GetSet();
    void Strength_GetSet(int curValue);
    int Toughness_GetSet();
    void Toughness_GetSet(int curValue);
    int Reflexes_GetSet();
    void Reflexes_GetSet(int curValue);
    int Coordination_GetSet();
    void Coordination_GetSet(int curValue);

    void setSkills(int skillsToUse[2]);
    void setCstats();
    void setCombatStats();
    void setSecondaryStats();
    void setPools();

    void setWeapon(int* pWeapon);

    void rollInititive();
    void rollPool();
    void countSuccesses();

};