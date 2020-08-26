#pragma once
#include "CharacterSheet.g.h"

namespace winrt::DiceTesterUI::implementation
{
    struct CharacterSheet : CharacterSheetT<CharacterSheet>
    {
    public:
        CharacterSheet()
        {
            Stats.Physical.Strength = 10;
        }

        //Stats Construct
        struct Stats
        {
            //Physical Stats
            struct Physical
            {
                //Body = Strengh + Toughness
                int Body = 10;
                double Strength = 10;
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

        float Strength();
        void Strength(float const& value);
        winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}
namespace winrt::DiceTesterUI::factory_implementation
{
    struct CharacterSheet : CharacterSheetT<CharacterSheet, implementation::CharacterSheet>
    {
    };
}
