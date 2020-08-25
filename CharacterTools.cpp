#include "pch.h"
#include <iostream>
#include <string>
#include "CharacterTools.h"

charSheet::charSheet(std::string name, int inID, int inDie)
{
    bio.charName = name;
    ID = inID;
    cStats.curDie = inDie;
}


void charSheet::setSecondaryStats()
{
    stat.Body = (stat.Strength + stat.Toughness) / 2;
    stat.Agility = (stat.Reflexes + stat.Coordination) / 2;
    stat.Mind = (stat.Intelligence + stat.Ego) / 2;
    stat.Willpower = (stat.SelfDiscipline + stat.Knowledge) / 2;
    stat.Control = (stat.Manipulation + stat.Reserve) / 2;
    stat.Power = (stat.Force + stat.Channeling) / 2;
    stat.Inititive = (stat.Agility + stat.Mind);
    health.Energy = (stat.Body + stat.Mind);
    health.Hits = stat.Toughness + stat.SelfDiscipline;

    //set bonuses
    int BonusDevisor = 4;
    statBonus.BodyB = stat.Body / BonusDevisor;
    statBonus.StrengthB = stat.Strength / BonusDevisor;
    statBonus.ToughnessB = stat.Toughness / BonusDevisor;

    statBonus.AgilityB = stat.Agility / BonusDevisor;
    statBonus.ReflexesB = stat.Reflexes / BonusDevisor;
    statBonus.CoordinationB = stat.Coordination / BonusDevisor;

    statBonus.MindB = stat.Mind / BonusDevisor;
    statBonus.IntelligenceB = stat.Intelligence / BonusDevisor;
    statBonus.PersoaB = stat.Ego / BonusDevisor;

    statBonus.WillpowerB = stat.Willpower / BonusDevisor;
    statBonus.SelfDisciplineB = stat.SelfDiscipline / BonusDevisor;
    statBonus.KnowledgeB = stat.Knowledge / BonusDevisor;

    statBonus.PowerB = stat.Power / BonusDevisor;
    statBonus.ChannelingB = stat.Channeling / BonusDevisor;
    statBonus.ForceB = stat.Force / BonusDevisor;

    statBonus.ControlB = stat.Control / BonusDevisor;
    statBonus.ManipulationB = stat.Manipulation / BonusDevisor;
    statBonus.RestraintB = stat.Reserve / BonusDevisor;

}

void charSheet::setSkills(int skillsToUse[2])
{
    skill.Combat.Melee.Brawl = skillsToUse[0];
    skill.Combat.Ranged.Pistols = skillsToUse[1];
}

void charSheet::setCombatStats()
{
    //Att
    CombatStats.StrikeTar = statBonus.StrengthB;
    CombatStats.StrikePool = skill.Combat.Melee.Brawl;

    CombatStats.GrappleTar = 0;
    CombatStats.GrapplePool = 0;

    CombatStats.CastTar = 0;
    CombatStats.CastPool = 0;
    //Def
    //Strength + reaction + Skill
    CombatStats.DodgeTar = 0;
    CombatStats.DodgePool = 0;
    //coordination + Strength + Skill
    CombatStats.ParryTar = 0;
    CombatStats.ParryPool = 0;
    //Toughness + Reaction + Skill
    CombatStats.BlockTar = statBonus.ToughnessB;
    CombatStats.BlockPool = skill.Combat.Melee.Brawl;

}

void charSheet::setPools()
{
    int poolDevisor = 4;
    pool.Physical = (stat.Body + stat.Agility) / poolDevisor;
    pool.Mental = (stat.Intelligence + stat.Ego) / poolDevisor;
    pool.Cast = (stat.Power + stat.Control) / poolDevisor;
}

void charSheet::rollPool()
{
    for (int i = 0; i < cStats.curPool; i++)
    {
        cStats.poolArr[i] = rand() % cStats.curDie + 1;
    }
}


void charSheet::countSuccesses()
{
    cStats.curSuc = 0;
    for (int i = 0; i < cStats.curPool; i++)
    {
        if (cStats.poolArr[i] >= cStats.curTargNum)
        {
            cStats.curSuc++;
            cStats.totSuc++;
        }
    }
}

void charSheet::rollInititive()
{
    int initRoll = (
        (rand() % 6 + 1) + (rand() % 6 + 1) + (rand() % 6 + 1) + stat.Inititive
        );
    cStats.curInit = initRoll;
}

void charSheet::setWeapon(int* pWeapon)
{
    curWeapon.Accuracy = pWeapon[0];
    curWeapon.Damage = pWeapon[1];
    curWeapon.Reload = pWeapon[2];
    curWeapon.DrawSpeed = pWeapon[3];
}
