#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
#include "CharacterTools.h"
#include "DiceRoller.h"
#include <string>
#include <cctype>

using namespace winrt;
using namespace Windows::UI::Xaml;
std::vector<charSheet> g_Players = { charSheet("Fulkan", 2, 20), charSheet("LoFat", 3, 20) };

namespace winrt::DiceTesterUI::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
    }

    int32_t MainPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainPage::RefreshStats()
    {
        //Player 1
        for (charSheet& i : g_Players)
        {
            i.setSecondaryStats();
            i.setPools();
        }

        p1PhysicalPool().Text(to_hstring(g_Players[0].pool.Physical));

        p1Body().Text(to_hstring(g_Players[0].stat.Body));
        p1Strength().Text(to_hstring(g_Players[0].stat.Strength));
        p1Toughness().Text(to_hstring(g_Players[0].stat.Toughness));

        p1Agility().Text(to_hstring(g_Players[0].stat.Agility));
        p1Reflexes().Text(to_hstring(g_Players[0].stat.Reflexes));
        p1Coordination().Text(to_hstring(g_Players[0].stat.Coordination));

        p1MentalPool().Text(to_hstring(g_Players[0].pool.Mental));

        p1Mind().Text(to_hstring(g_Players[0].stat.Mind));
        p1Intelligence().Text(to_hstring(g_Players[0].stat.Intelligence));
        p1Ego().Text(to_hstring(g_Players[0].stat.Ego));

        p1Willpower().Text(to_hstring(g_Players[0].stat.Willpower));
        p1Knowledge().Text(to_hstring(g_Players[0].stat.Knowledge));
        p1SelfDiscipline().Text(to_hstring(g_Players[0].stat.SelfDiscipline));


        p1CastPool().Text(to_hstring(g_Players[0].pool.Cast));

        p1Power().Text(to_hstring(g_Players[0].stat.Power));
        p1Force().Text(to_hstring(g_Players[0].stat.Force));
        p1Channeling().Text(to_hstring(g_Players[0].stat.Channeling));

        p1Control().Text(to_hstring(g_Players[0].stat.Control));
        p1Manipulation().Text(to_hstring(g_Players[0].stat.Manipulation));
        p1Reserve().Text(to_hstring(g_Players[0].stat.Reserve));

    }

    void MainPage::GetStepSettings(DiceRoller::UIdata& settings)
    {
        settings.StepSettings.quickP1[0][0] = trgP1StpUp().IsOn();
        settings.StepSettings.quickP1[0][1] = trgP1StpDn().IsOn();
        settings.StepSettings.quickP1[1][0] = trgP2StpUp().IsOn();
        settings.StepSettings.quickP1[1][1] = trgP2StpDn().IsOn();
    }

    void MainPage::RunSim(IInspectable const&, RoutedEventArgs const&)
    {
        int defTargP1 = std::stoi(TextBoxP1DefTarg().Text().c_str());
        int defPoolP1 = std::stoi(to_string(TextBoxP1DefPool().Text()));
        int defTargP2 = std::stoi(to_string(TextBoxP2DefTarg().Text()));
        int defPoolP2 = std::stoi(to_string(TextBoxP2DefPool().Text()));
        int defItter = std::stoi(to_string(TextBoxItterations().Text()));
        int defStep = std::stoi(to_string(TextBoxSteps().Text()));
        Controls::ComboBoxItem dieUsed = ComboBoxDieSelect().SelectedItem().as<Controls::ComboBoxItem>();
        int dieToUse = std::stoi(to_string(dieUsed.Tag().as<hstring>()));
        bool rndComSwitch = ToggleSwitchRunRoundCombat().IsOn();
        bool outputSteps =  CheckBoxOutStep().IsChecked().GetBoolean();
        bool outputRound = CheckBoxOutRound().IsChecked().GetBoolean();
        DiceRoller::UIdata UISettings;
        GetStepSettings(UISettings);
        UISettings.GeneralSettings.useStatsP1 = ToggleUseStatsP1().IsOn();
        UISettings.GeneralSettings.useStatsP2 = ToggleUseStatsP2().IsOn();
        UISettings.GeneralSettings.die = dieToUse;
        UISettings.PlayerData.P1.tar = defTargP1;
        UISettings.PlayerData.P1.pool = defPoolP1;
        UISettings.PlayerData.P2.tar = defTargP2;
        UISettings.PlayerData.P2.pool = defPoolP2;
        UISettings.GeneralSettings.itter = defItter;
        UISettings.GeneralSettings.steps = defStep;
        UISettings.GeneralSettings.combat = rndComSwitch;
        UISettings.OutputSettings.outStep = outputSteps;
        UISettings.OutputSettings.outRound = outputRound;
        UISettings.outputBox = TextBoxOutputWindow();
        DiceRoller::RunSim(UISettings, g_Players);
    }
}

void winrt::DiceTesterUI::implementation::MainPage::ButtonClearOutput_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
    TextBoxOutputWindow().Text(L"");
}



void winrt::DiceTesterUI::implementation::MainPage::VerifyNumberBoxes(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e)
{
    Controls::TextBox curBox{ sender.as<Controls::TextBox>() };
    std::string curText = to_string(curBox.Text());
    int curSize = curText.size();
    if (curSize != 0)
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


void winrt::DiceTesterUI::implementation::MainPage::StatButtonChange(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
    Controls::Button curButton = sender.as<Controls::Button>();
    enum statSel
    {
        StrU = 0,StrD,TghU,TghD,RefU, RefD,CorU, CorD,IntU, IntD,EgoU, EgoD,KnoU, KnoD,SDcU, SDcD,ForU, ForD,ChaU, ChaD,ManU, ManD,ResU, ResD
    };
    int butSel = std::stoi(to_string(curButton.AccessKey()));
    statSel stsel = statSel(butSel);
    switch (stsel)
    {
    //Body
    case StrU:
    {
        g_Players[0].stat.Strength++;
        break;
    }
    case StrD:
    {
        g_Players[0].stat.Strength--;
        break;
    }
    case TghU:
    {
        g_Players[0].stat.Toughness++;
        break;
    }
    case TghD:
    {
        g_Players[0].stat.Toughness--;
        break;
    }
    //Body End
    //Agility
    case RefU:
    {
        g_Players[0].stat.Reflexes++;
        break;
    }
    case RefD:
    {
        g_Players[0].stat.Reflexes--;
        break;
    }
    case CorU:
    {
        g_Players[0].stat.Coordination++;
        break;
    }
    case CorD:
    {
        g_Players[0].stat.Coordination--;
        break;
    }
    //Agility End
    //Mind
    case IntU:
    {
        g_Players[0].stat.Intelligence++;
        break;
    }
    case IntD:
    {
        g_Players[0].stat.Intelligence--;
        break;
    }
    case EgoU:
    {
        g_Players[0].stat.Ego++;
        break;
    }
    case EgoD:
    {
        g_Players[0].stat.Ego--;
        break;
    }
    //Mind End
    //Willpower
    case KnoU:
    {
        g_Players[0].stat.Knowledge++;
        break;
    }
    case KnoD:
    {
        g_Players[0].stat.Knowledge--;
        break;
    }
    case SDcU:
    {
        g_Players[0].stat.SelfDiscipline++;
        break;
    }
    case SDcD:
    {
        g_Players[0].stat.SelfDiscipline--;
        break;
    }
    //Willpower End
    //Power
    case ForU:
    {
        g_Players[0].stat.Force++;
        break;
    }
    case ForD:
    {
        g_Players[0].stat.Force--;
        break;
    }
    case ChaU:
    {
        g_Players[0].stat.Channeling++;
        break;
    }
    case ChaD:
    {
        g_Players[0].stat.Channeling--;
        break;
    }
    //Power End
    //Control
    case ManU:
    {
        g_Players[0].stat.Manipulation++;
        break;
    }
    case ManD:
    {
        g_Players[0].stat.Manipulation--;
        break;
    }
    case ResU:
    {
        g_Players[0].stat.Reserve++;
        break;
    }
    case ResD:
    {
        g_Players[0].stat.Reserve--;
        break;
    }
    //Control End
    default:
        break;
    }
    RefreshStats();
}


void winrt::DiceTesterUI::implementation::MainPage::SettingsButtonChange(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
    Controls::Button curButton = sender.as<Controls::Button>();
    enum setSel
    {
        p1TarUp, p1TarDn, p1PoolUp, p1PoolDn, p2TarUp, p2TarDn, p2PoolUp, p2PoolDn
    };
    int butSel = std::stoi(to_string(curButton.AccessKey()));
    setSel stsel = setSel(butSel);
    switch (stsel)
    {
        //Player 1 Targ
    case p1TarUp:
    {
        TextBoxP1DefTarg().Text(to_hstring(std::stoi(TextBoxP1DefTarg().Text().c_str()) + 1));
        break;
    }
    case p1TarDn:
    {
        TextBoxP1DefTarg().Text(to_hstring(std::stoi(TextBoxP1DefTarg().Text().c_str()) - 1));
        break;
    }
    //Player 1 Pool
    case p1PoolUp:
    {
        TextBoxP1DefPool().Text(to_hstring(std::stoi(TextBoxP1DefPool().Text().c_str()) + 1));
        break;
    }
    case p1PoolDn:
    {
        TextBoxP1DefPool().Text(to_hstring(std::stoi(TextBoxP1DefPool().Text().c_str()) - 1));
        break;
    }
    //Player 2 Targ
    case p2TarUp:
    {
        TextBoxP2DefTarg().Text(to_hstring(std::stoi(TextBoxP2DefTarg().Text().c_str()) + 1));
        break;
    }
    case p2TarDn:
    {
        TextBoxP2DefTarg().Text(to_hstring(std::stoi(TextBoxP2DefTarg().Text().c_str()) - 1));
        break;
    }
    //Player 2 Pool
    case p2PoolUp:
    {
        TextBoxP2DefPool().Text(to_hstring(std::stoi(TextBoxP2DefPool().Text().c_str()) + 1));
        break;
    }
    case p2PoolDn:
    {
        TextBoxP2DefPool().Text(to_hstring(std::stoi(TextBoxP2DefPool().Text().c_str()) - 1));
        break;
    }
    default:
        break;
    }
}


void winrt::DiceTesterUI::implementation::MainPage::EventToggleStats(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
    Controls::ToggleSwitch curSwitch = sender.as<Controls::ToggleSwitch>();
    if (curSwitch.Tag().as<hstring>() == L"p1")
    {
        ContentControlP1Settings().IsEnabled(!curSwitch.IsOn());
        ContentControlP1Stats().IsEnabled(curSwitch.IsOn());
    }
    if (curSwitch.Tag().as<hstring>() == L"p2")
    {
        //ContentControlP2Settings().IsEnabled(!curSwitch.IsOn());
        //ContentControlP2Stats().IsEnabled(curSwitch.IsOn());
    }
}
