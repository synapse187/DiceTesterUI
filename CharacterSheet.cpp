#include "pch.h"
#include "CharacterSheet.h"
#include "CharacterSheet.g.cpp"

namespace winrt::DiceTesterUI::implementation
{
    float CharacterSheet::Strength()
    {
        return Stats.Physical.Strength;
    }
    void CharacterSheet::Strength(float const& value)
    {
        Stats.Physical.Strength = value;
    }
    winrt::event_token CharacterSheet::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }
    void CharacterSheet::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }
}
