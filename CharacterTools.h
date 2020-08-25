#pragma once
#include <string>


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
    struct stat
    {
        //Physical Stats
        //Body = Strengh + Toughness
        int Body = 10;
        int Strength = 10;
        int Toughness = 10;
        //Agility = Reflexes + Coordination
        int Agility = 10;
        int Reflexes = 10;
        int Coordination = 10;

        //Mental Stats
        //Mind = Intelligence + Ego
        int Mind = 10;
        int Intelligence = 10;
        int Ego = 10;

        int Willpower = 10;
        int SelfDiscipline = 10;
        int Knowledge = 10;

        //Magic Stats
        int Power = 10;
        int Force = 10;
        int Channeling = 10;

        int Control = 10;
        int Manipulation = 10;
        int Reserve = 10;

        //Terciary Stats
        int Inititive;
        int Looks;
    }stat;
    
    struct statBonus
    {
        //Physical Stats
        //Body = Strengh + Toughness
        int BodyB;
        int StrengthB;
        int ToughnessB;

        int AgilityB;
        int ReflexesB;
        int CoordinationB;

        //Mental Stats
        int MindB;
        int IntelligenceB;
        int PersoaB;

        int WillpowerB;
        int SelfDisciplineB;
        int KnowledgeB;

        //Magic Stats
        int ControlB;
        int ManipulationB;
        int RestraintB;

        int PowerB;
        int ChannelingB;
        int ForceB;

        //Terciary Stats
        int LooksB;
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
    struct health
    {
        int Energy = 0;
        int Hits = 0;
    }health;

    //Current Maths For Attacks and Defence
    struct CombatStats
    {
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
        int curEnergy = 0;
        int curHits = 0;
        int curInit = 0;
        int curPool = 0;
        int curTargNum = 0;
        int curDie = 20;
        //attack stats
        std::string curAttType = "Melee";
        int curAttMod = 0;
        int curDamBonus = 0;
        //defence stats
        std::string curDefType = "Block";
        int curDefMod = 0;
        int curDamReduc = 0;
        //storage
        int poolArr[50]{};
        int curSuc = 0;
        float totSuc = 0.00f;
        int wins = 0;
        int wonBy = 0;
        float wonByTotal = 0.00f;
        int kills = 0;
    }cStats;

    struct cPools {
        int curPhys;
        int curMen;
        int curCast;
    }cPools;

    struct curWeapon {
        int Accuracy = 0;
        int Damage = 0;
        int Reload = 0;
        int DrawSpeed = 0;
    }curWeapon;

    struct curArmor {
        int DamageReduction;
        int MoveReduction;
    }curArmor;

    charSheet(std::string name, int inID, int inDie);

    void setSkills(int skillsToUse[2]);
    void setCombatStats();
    void setSecondaryStats();
    void setPools();
    void setStats(int statsToSet[12]);

    void setWeapon(int* pWeapon);

    void rollInititive();
    void rollPool();
    void countSuccesses();

};