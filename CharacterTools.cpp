#include "pch.h"
#include <iostream>
#include <string>
#include "CharacterTools.h"

charSheet::charSheet(std::string name, int inID)
{
    bio.charName = name;
    ID = inID;
    Stats.Physical.Strength = 10;
    Stats.Physical.Toughness = 10;
    Stats.Physical.Reflexes = 10;
    Stats.Physical.Coordination = 10;
    Stats.Mental.Intelligence = 10;
    Stats.Mental.Ego = 10;
    Stats.Mental.SelfDiscipline = 10;
    Stats.Mental.Knowledge = 10;
    Stats.Meta.Force = 10;
    Stats.Meta.Channeling = 10;
    Stats.Meta.Manipulation = 10;
    Stats.Meta.Reserve = 10;
}


void charSheet::setSecondaryStats()
{
    Stats.Physical.Body =    (Stats.Physical.Strength + Stats.Physical.Toughness) / 2;
    Stats.Physical.Agility = (Stats.Physical.Reflexes + Stats.Physical.Coordination) / 2;
    Stats.Mental.Mind =      (Stats.Mental.Intelligence + Stats.Mental.Ego) / 2;
    Stats.Mental.Willpower = (Stats.Mental.SelfDiscipline + Stats.Mental.Knowledge) / 2;
    Stats.Meta.Control =     (Stats.Meta.Manipulation + Stats.Meta.Reserve) / 2;
    Stats.Meta.Power =       (Stats.Meta.Force + Stats.Meta.Channeling) / 2;
    Stats.Inititive =        (Stats.Physical.Agility + Stats.Mental.Mind);
    Health.Energy =          (Stats.Physical.Body + Stats.Mental.Mind);
    Health.Hits =            (Stats.Physical.Toughness + Stats.Mental.SelfDiscipline);

    //set bonuses
    int BonusDevisor = 4;
    statBonus.Physical.BodyBonus = Stats.Physical.Body / BonusDevisor;
    statBonus.Physical.StrengthBonus = Stats.Physical.Strength / BonusDevisor;
    statBonus.Physical.ToughnessBonus = Stats.Physical.Toughness / BonusDevisor;

    statBonus.Physical.AgilityBonus = Stats.Physical.Agility / BonusDevisor;
    statBonus.Physical.ReflexesBonus = Stats.Physical.Reflexes / BonusDevisor;
    statBonus.Physical.CoordinationBonus = Stats.Physical.Coordination / BonusDevisor;

    statBonus.Mental.MindBonus = Stats.Mental.Mind / BonusDevisor;
    statBonus.Mental.IntelligenceBonus = Stats.Mental.Intelligence / BonusDevisor;
    statBonus.Mental.EgoBonus = Stats.Mental.Ego / BonusDevisor;

    statBonus.Mental.WillpowerBonus = Stats.Mental.Willpower / BonusDevisor;
    statBonus.Mental.SelfDisciplineBonus = Stats.Mental.SelfDiscipline / BonusDevisor;
    statBonus.Mental.KnowledgeBonus = Stats.Mental.Knowledge / BonusDevisor;

    statBonus.Meta.PowerBonus = Stats.Meta.Power / BonusDevisor;
    statBonus.Meta.ChannelingBonus = Stats.Meta.Channeling / BonusDevisor;
    statBonus.Meta.ForceBonus = Stats.Meta.Force / BonusDevisor;

    statBonus.Meta.ControlBonus = Stats.Meta.Control / BonusDevisor;
    statBonus.Meta.ManipulationBonus = Stats.Meta.Manipulation / BonusDevisor;
    statBonus.Meta.RestraintBonus = Stats.Meta.Reserve / BonusDevisor;

}

void charSheet::setSkills(int skillsToUse[2])
{
    skill.Combat.Melee.Brawl = skillsToUse[0];
    skill.Combat.Ranged.Pistols = skillsToUse[1];
}

void charSheet::setCombatStats()
{
    //Att
    CombatStats.StrikeTar = statBonus.Physical.StrengthBonus;
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
    CombatStats.BlockTar = statBonus.Physical.ToughnessBonus;
    CombatStats.BlockPool = skill.Combat.Melee.Brawl;

}

void charSheet::setCstats()
{
    cStats.CurrentHealth = Health.Hits;
    cStats.CurrentEndurance = Health.Energy;
    cStats.CurrentPool = CombatStats.Strike.Melee.PoolMod;
    cStats.CurrentTarget = CombatStats.Strike.Melee.TargetMod;
}

void charSheet::setPools()
{
    int poolDevisor = 4;
    pool.Physical = (Stats.Physical.Body + Stats.Physical.Agility) / poolDevisor;
    pool.Mental = (Stats.Mental.Mind + Stats.Mental.Willpower) / poolDevisor;
    pool.Cast = (Stats.Meta.Power + Stats.Meta.Control) / poolDevisor;
}

void charSheet::rollPool()
{
    for (int i = 0; i < cStats.CurrentPool; i++)
    {
        cData.poolArr[i] = rand() % 20 + 1;
    }
}


void charSheet::countSuccesses()
{
    cData.curSuc = 0;
    for (int i = 0; i < cStats.CurrentPool; i++)
    {
        if (cData.poolArr[i] >= cStats.CurrentTarget)
        {
            cData.curSuc++;
            cData.totSuc++;
        }
    }
}

void charSheet::rollInititive()
{
    int initRoll = (
        (rand() % 6 + 1) + (rand() % 6 + 1) + (rand() % 6 + 1) + Stats.Inititive
        );
    cStats.CurrentInititive = initRoll;
}

void charSheet::setWeapon(int* pWeapon)
{
    curWeapon.Accuracy = pWeapon[0];
    curWeapon.Damage = pWeapon[1];
    curWeapon.Reload = pWeapon[2];
    curWeapon.DrawSpeed = pWeapon[3];
}

void charSheet::Strength_GetSet(int curValue)
{
    Stats.Physical.Strength = curValue;
}
int charSheet::Strength_GetSet()
{
    return Stats.Physical.Strength;
}

void charSheet::Toughness_GetSet(int curValue)
{
    Stats.Physical.Toughness = curValue;
}
int charSheet::Toughness_GetSet()
{
    return Stats.Physical.Toughness;
}

void charSheet::Reflexes_GetSet(int curValue)
{
    Stats.Physical.Reflexes = curValue;
}
int charSheet::Reflexes_GetSet()
{
    return Stats.Physical.Reflexes;
}

void charSheet::Coordination_GetSet(int curValue)
{
    Stats.Physical.Coordination = curValue;
}
int charSheet::Coordination_GetSet()
{
    return Stats.Physical.Coordination;
}