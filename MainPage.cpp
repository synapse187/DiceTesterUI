#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
#include "CharacterTools.h"
#include "DiceRoller.h"
#include <string>
#include <cctype>

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::DiceTesterUI::implementation
{
    std::vector<charSheet> g_Players = { charSheet("Fulkan", 2), charSheet("LoFat", 3) };
    MainPage::MainPage()
    {
        InitializeComponent();
    }

    DiceTesterUI::CharacterSheet MainPage::CharSheet()
    {
        return m_ViewModel;
    }

    int32_t MainPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainPage::RefreshStatsPools()
    {
        //Player 1
        for (charSheet& i : g_Players)
        {
            i.setSecondaryStats();
            i.setPools();
        }
    }
    
    void MainPage::RefreshStatsBody()
    {
        p1PhysicalPool().Text(to_hstring(g_Players[0].pool.Physical));
        p1Body().Text(to_hstring(g_Players[0].Stats.Physical.Body));
    }
    
    void MainPage::RefreshStatsAgility()
    {
        p1PhysicalPool().Text(to_hstring(g_Players[0].pool.Physical));
        p1Agility().Text(to_hstring(g_Players[0].Stats.Physical.Agility));
    }

    void MainPage::RefreshStatsMind()
    {
        p1MentalPool().Text(to_hstring(g_Players[0].pool.Mental));
        p1Mind().Text(to_hstring(g_Players[0].Stats.Mental.Mind));
    }
    void MainPage::RefreshStatsWillpower()
    {
        p1MentalPool().Text(to_hstring(g_Players[0].pool.Mental));
        p1Willpower().Text(to_hstring(g_Players[0].Stats.Mental.Willpower));
    }
    void MainPage::RefreshStatsPower()
    {
        p1CastPool().Text(to_hstring(g_Players[0].pool.Cast));
        p1Power().Text(to_hstring(g_Players[0].Stats.Meta.Power));
    }
    void MainPage::RefreshStatsControl()
    {
        p1CastPool().Text(to_hstring(g_Players[0].pool.Cast));
        p1Control().Text(to_hstring(g_Players[0].Stats.Meta.Control));
    }


    void MainPage::GetStepSettings(DiceRoller::UIdata& settings)
    {
    }

    void MainPage::GetSimSettings(DiceRoller::UIdata& settings)
    {
        settings.GeneralSettings.useStatsP1 = P1UseStatsToggleSwitch().IsOn();
        settings.GeneralSettings.itter = std::stoi(TextBoxItterations().Text().c_str());
        settings.GeneralSettings.steps = std::stoi(TextBoxSteps().Text().c_str());
        settings.GeneralSettings.combat = ToggleSwitchRunRoundCombat().IsOn();
        settings.OutputSettings.outStep = CheckBoxOutStep().IsChecked().GetBoolean();
        settings.OutputSettings.outRound = CheckBoxOutRound().IsChecked().GetBoolean();
        settings.outputBox = TextBoxOutputWindow();
    }

    void MainPage::RunSim(IInspectable const&, RoutedEventArgs const&)
    {
        DiceRoller::UIdata UISettings;
        GetSimSettings(UISettings);
        GetStepSettings(UISettings);
        DiceRoller::RunSim(UISettings, g_Players);
    }
}

void winrt::DiceTesterUI::implementation::MainPage::ButtonClearOutput_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
    TextBoxOutputWindow().Text(to_hstring(CharSheet().Strength()));
}



void winrt::DiceTesterUI::implementation::MainPage::VerifyNumberBoxes(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e)
{
    Controls::TextBox curBox{ sender.as<Controls::TextBox>() };
    std::string curText = to_string(curBox.Text());
    if (curText.size() != 0)
    {
        for (int i = 0; i < curText.size(); i++)
        {
            if (!std::isdigit(curText[i]))
            {
                curText.pop_back();
                curBox.Text(to_hstring(curText));
                curBox.SelectionStart(i);
            }
        }
    }
    else
    {
        curBox.Text(L"0");
        curBox.SelectionStart(1);
    }
}


void winrt::DiceTesterUI::implementation::MainPage::EventToggleStats(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
    winrt::Windows::UI::Xaml::Controls::ToggleSwitch curSwitch = sender.as<winrt::Windows::UI::Xaml::Controls::ToggleSwitch>();
    winrt::Windows::UI::Xaml::Visibility VisOn = winrt::Windows::UI::Xaml::Visibility::Visible;
    winrt::Windows::UI::Xaml::Visibility VisOff = winrt::Windows::UI::Xaml::Visibility::Collapsed;
    if (curSwitch.Tag().as<hstring>() == L"p1")
    {
        if (!curSwitch.IsOn())
        {
            P1QuickStatsPanel().Visibility(VisOn);
            P1StandardStatsPanel().Visibility(VisOff);
        }
        if (curSwitch.IsOn())
        {
            P1QuickStatsPanel().Visibility(VisOff);
            P1StandardStatsPanel().Visibility(VisOn);
        }
    }
}

namespace winrt::DiceTesterUI::implementation
{
    void winrt::DiceTesterUI::implementation::MainPage::Player1StatChange(winrt::Microsoft::UI::Xaml::Controls::NumberBox const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args)
    {
        enum class statSent
        {
            Str, Tgh, Ref, Cor, Int, Ego, Kno, SDc, For, Cha, Man, Res
        };
        switch (statSent(std::stoi(sender.AccessKey().c_str())))
        {
            //Body
        case statSent::Str:
        {
            g_Players[0].Stats.Physical.Strength = sender.Value();
            RefreshStatsPools();
            RefreshStatsBody();
            break;
        }
        case statSent::Tgh:
        {
            g_Players[0].Stats.Physical.Toughness = sender.Value();
            RefreshStatsPools();
            RefreshStatsBody();
            break;
        }
        //Body End
        //Agility
        case statSent::Ref:
        {
            g_Players[0].Stats.Physical.Reflexes = sender.Value();
            RefreshStatsPools();
            RefreshStatsAgility();
            break;
        }
        case statSent::Cor:
        {
            g_Players[0].Stats.Physical.Coordination = sender.Value();
            RefreshStatsPools();
            RefreshStatsAgility();
            break;
        }
        //Agility End
        //Mind
        case statSent::Int:
        {
            g_Players[0].Stats.Mental.Intelligence = sender.Value();
            RefreshStatsPools();
            RefreshStatsMind();
            break;
        }
        case statSent::Ego:
        {
            g_Players[0].Stats.Mental.Ego = sender.Value();
            RefreshStatsPools();
            RefreshStatsMind();
            break;
        }
        //Mind End
        //Willpower
        case statSent::Kno:
        {
            g_Players[0].Stats.Mental.Knowledge = sender.Value();
            RefreshStatsPools();
            RefreshStatsWillpower();
            break;
        }
        case statSent::SDc:
        {
            g_Players[0].Stats.Mental.SelfDiscipline = sender.Value();
            RefreshStatsPools();
            RefreshStatsWillpower();
            break;
        }
        //Willpower End
        //Power
        case statSent::For:
        {
            g_Players[0].Stats.Meta.Force = sender.Value();
            RefreshStatsPools();
            RefreshStatsPower();
            break;
        }
        case statSent::Cha:
        {
            g_Players[0].Stats.Meta.Channeling = sender.Value();
            RefreshStatsPools();
            RefreshStatsPower();
            break;
        }
        //Power End
        //Control
        case statSent::Man:
        {
            g_Players[0].Stats.Meta.Manipulation = sender.Value();
            RefreshStatsPools();
            RefreshStatsControl();
            break;
        }
        case statSent::Res:
        {
            g_Players[0].Stats.Meta.Reserve = sender.Value();
            RefreshStatsPools();
            RefreshStatsControl();
            break;
        }
        //Control End
        default:
            break;
        }
    }
}


void winrt::DiceTesterUI::implementation::MainPage::StepMenuFlyoutItem_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
    winrt::Windows::UI::Xaml::Controls::MenuFlyoutItem curFlyoutItem = sender.as<winrt::Windows::UI::Xaml::Controls::MenuFlyoutItem>();
    enum setStepToEnum
    {
        noStep,stepUp,stepDown
    };

    switch (setStepToEnum(std::stoi(curFlyoutItem.Tag().as<hstring>().c_str())))
    {
    case noStep:
    {
        curFlyoutItem.Parent().as<winrt::Windows::UI::Xaml::Controls::Button>().Content(winrt::box_value(L"D"));
    }
    default:
        break;
    }
}


void winrt::DiceTesterUI::implementation::MainPage::p1QuickHealth_ValueChanged(winrt::Microsoft::UI::Xaml::Controls::NumberBox const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args)
{
    //int curNumber = CharSheet().Strength_GetSet();
    //TextBoxOutputWindow().Text(L"D");
}

Windows::Foundation::Collections::IObservableVector<DiceTesterUI::CharacterSheet> winrt::DiceTesterUI::implementation::MainPage::CharacterSheets()
{
    Windows::Foundation::Collections::IObservableVector<DiceTesterUI::CharacterSheet> Players;
    DiceTesterUI::CharacterSheet Player01;
    DiceTesterUI::CharacterSheet Player02;
    Players.Append(Player01);
    Players.Append(Player02);
    return Players;
}
