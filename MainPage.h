#pragma once
#include "CharacterSheet.h"
#include "DiceRoller.h"
#include "MainPage.g.h"

namespace winrt::DiceTesterUI::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
    public:
        MainPage();
        DiceTesterUI::CharacterSheet CharSheet();
        int32_t MyProperty();
        void MyProperty(int32_t value);

        void RefreshStatsPools();
        void RefreshStatsBody();
        void RefreshStatsAgility();
        void RefreshStatsMind();
        void RefreshStatsWillpower();
        void RefreshStatsPower();
        void RefreshStatsControl();
        void GetSimSettings(DiceRoller::UIdata& settings);
        void GetStepSettings(DiceRoller::UIdata& settings);
        void RunSim(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void ButtonClearOutput_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void VerifyNumberBoxes(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e);
        void SettingsButtonChange(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void EventToggleStats(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void Player1StatChange(winrt::Microsoft::UI::Xaml::Controls::NumberBox const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args);
        void StepMenuFlyoutItem_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void p1QuickHealth_ValueChanged(winrt::Microsoft::UI::Xaml::Controls::NumberBox const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args);
    private:
        DiceTesterUI::CharacterSheet m_ViewModel{ nullptr };
        Windows::Foundation::Collections::IObservableVector<DiceTesterUI::CharacterSheet>CharacterSheets();
    };
}

namespace winrt::DiceTesterUI::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
        std::vector<charSheet> g_Players;
    };
}
