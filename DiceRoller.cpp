#include "pch.h"
#include "MainPage.h"
#include "DiceRoller.h"
#include "CharacterTools.h"
#include <string>
#include <sstream>
#include <iomanip>
using namespace winrt;
using namespace Windows::UI::Xaml;


void OutputToWindow(DiceRoller::UIdata &settings, hstring strToAdd)
{
	hstring origText = settings.outputBox.Text();
	settings.outputBox.Text(origText + strToAdd);
}

void OutputCombat(DiceRoller::UIdata& settings, std::vector<charSheet>& players)
{

}

void OutputRound(DiceRoller::UIdata& settings, std::vector<charSheet>& players)
{
	std::ostringstream oStr;
	for (int i = 0; i < players.size(); i++)
	{
		oStr << players[i].bio.charName << "\n";
		oStr << "Target Number: " << players[i].cStats.CurrentTarget << " |--| ";
		oStr << "Pool: " << players[i].cStats.CurrentPool << "\n";
		oStr << "Rolls: " << "\n|";
		//output rolls
		for (int j = 0; j < players[i].cStats.CurrentPool; j++)
		{
			oStr << players[i].cData.poolArr[j] << "|";
		}
		oStr << "\n";
		oStr << "Successes: " << players[i].cData.curSuc << "\n";
	}
	oStr << "Winner: " << players[settings.StatsData.curWiner].bio.charName << "|--|";
	oStr << "Won By: " << (players[settings.StatsData.curWiner].cData.curSuc - players[!settings.StatsData.curWiner].cData.curSuc) << "\n";
	oStr << "Damage Done: " << players[0].cData.damDone << "\n\n";
	OutputToWindow(settings, to_hstring(oStr.str()));
}


void OutputStep(DiceRoller::UIdata& settings, std::vector<charSheet>& players)
{
	std::ostringstream os2;
	os2 << "----------|Step # " << settings.StatsData.totalSteps << "|----------\n";
	for (int i = 0; i < players.size(); i++)
	{
		float winPerc = 0.00;
		float winAvg = 0.00;
		float avgSuc = (players[i].cData.totSuc / (settings.StatsData.totalIter + settings.StatsData.totalRounds));
		if (players[i].cData.wonByTotal > 0)
		{
			winAvg = players[i].cData.wonByTotal / players[i].cData.wins;
		}
		if (players[i].cData.wins > 0)
		{
			winPerc = ((float(players[i].cData.wins) / (settings.StatsData.totalIter + settings.StatsData.totalRounds)) * 100.00);
		}
		if (players[i].cData.totDam > 0)
		{
			winPerc = ((float(players[i].cData.totDam) / (settings.StatsData.totalIter + settings.StatsData.totalRounds)) * 100.00);
		}
		os2 << "---|Player: " + players[i].bio.charName + "|---\n";
		os2 << "|Pool||Target||Avg Suc||Win Avg||Win %|\n";
		os2 << std::setw(6) << players[i].cStats.CurrentPool;
		os2 << std::setw(8) << players[i].cStats.CurrentTarget;
		os2 << std::setprecision(3);
		os2 << std::setw(9) << avgSuc;
		os2 << std::setw(9) << winAvg;
		os2 << std::setw(5) << "%" << winPerc << "\n" << std::endl;
	}
	OutputToWindow(settings, to_hstring(os2.str()));
}

void SetStatsQuick(DiceRoller::UIdata& settings, std::vector<charSheet>& players)
{
	int quickStatArray[2][8] = {
		{
			settings.QuickStats.Player01.Health,
			settings.QuickStats.Player01.Endurance,
			settings.QuickStats.Player01.Pool,
			settings.QuickStats.Player01.Target,
			settings.QuickStats.Player01.Accuracy,
			settings.QuickStats.Player01.Damage,
			settings.QuickStats.Player01.OffenceType,
			settings.QuickStats.Player01.DefenceType,
		},
		{
			settings.QuickStats.Player02.Health,
			settings.QuickStats.Player02.Endurance,
			settings.QuickStats.Player02.Pool,
			settings.QuickStats.Player02.Target,
			settings.QuickStats.Player02.Accuracy,
			settings.QuickStats.Player02.Damage,
			settings.QuickStats.Player02.OffenceType,
			settings.QuickStats.Player02.DefenceType,
		}
	};
	for (int i = 0; i < players.size(); i++)
	{
		players[i].cStats.CurrentHealth = quickStatArray[i][0];
		players[i].cStats.CurrentEndurance = quickStatArray[i][1];
		players[i].cStats.CurrentPool = quickStatArray[i][2];
		players[i].cStats.CurrentTarget = quickStatArray[i][3];
		players[i].cStats.CurrentAccuracy = quickStatArray[i][4];
		players[i].cStats.CurrentDamage = quickStatArray[i][5];
		players[i].cStats.CurrentOffence = quickStatArray[i][6];
		players[i].cStats.CurrentDefence = quickStatArray[i][7];
	}
}

void SetStatsFull(DiceRoller::UIdata& settings, std::vector<charSheet>& players)
{
	//SET FULL STATS LATER!
}

void SetStats(DiceRoller::UIdata& settings, std::vector<charSheet> &players)
{
	if (!settings.GeneralSettings.useStatsP1)
	{
		SetStatsQuick(settings, players);
	}
	else
	{
		SetStatsFull(settings, players);
	}
}

void StepStats(DiceRoller::UIdata& settings, std::vector<charSheet>& players)
{
	if (!settings.GeneralSettings.useStatsP1)
	{
		//players[0].cStats.CurrentTarget += (settings.StepSettings.quickP1[0][0] - settings.StepSettings.quickP1[0][1]);
		//players[0].cStats.CurrentPool += (settings.StepSettings.quickP1[1][0] - settings.StepSettings.quickP1[1][1]);
	}
	if (!settings.GeneralSettings.useStatsP2)
	{
		//players[1].cStats.CurrentTarget += (settings.StepSettings.quickP2[0][0] - settings.StepSettings.quickP2[0][1]);
		//players[1].cStats.CurrentPool += (settings.StepSettings.quickP2[1][0] - settings.StepSettings.quickP2[1][1]);
	}
	settings.StatsData.totalIter = 0;
	settings.StatsData.totalRounds = 0;
	for (charSheet& i : players)
	{
		i.cData.wins = 0;
		i.cData.totSuc = 0;
		i.cData.wonByTotal = 0;
	}
}

void RunCombat(DiceRoller::UIdata& settings, std::vector<charSheet>& players)
{
	do
	{
		//COMBAT ROUNDS HERE
	} while (false);
}

void GetWinner(DiceRoller::UIdata& settings, std::vector<charSheet>& players)
{
	if (players[0].cData.curSuc >= players[1].cData.curSuc)
	{
		settings.StatsData.curWiner = 0;
		players[0].cData.wins++;
		players[0].cData.wonBy = players[0].cData.curSuc - players[1].cData.curSuc;
		players[0].cData.wonByTotal += players[0].cData.curSuc - players[1].cData.curSuc;
		players[0].cData.damDone = players[0].cData.curSuc - players[1].cData.curSuc;
		players[0].cData.totDam += players[0].cData.curSuc - players[1].cData.curSuc;
	}
	else
	{
		settings.StatsData.curWiner = 1;
		players[1].cData.wins++;
		players[1].cData.wonBy = players[1].cData.curSuc - players[0].cData.curSuc;
		players[1].cData.wonByTotal += players[1].cData.curSuc - players[0].cData.curSuc;
		players[0].cData.damDone = 0;
	}
}

void RunRound(DiceRoller::UIdata& settings, std::vector<charSheet>& players)
{
	//OutputToWindow(settings, L"MADE IT TO RUN ROUND!");
	for (charSheet &i : players)
	{
		i.rollPool();
		i.countSuccesses();
	}
	GetWinner(settings, players);
	if (settings.OutputSettings.outRound)
	{
		OutputRound(settings, players);
	}

}

void RunItter(DiceRoller::UIdata& settings, std::vector<charSheet>& players)
{
	//OutputToWindow(settings, L"MADE IT TO RUN ITERATION!");
	if (!settings.GeneralSettings.combat)
	{
		for (int i = 0; i < settings.GeneralSettings.itter; i++)
		{
			RunRound(settings, players);
			settings.StatsData.totalIter++;
		}
	}
	else
	{
		for (int i = 0; i < settings.GeneralSettings.itter; i++)
		{
			RunCombat(settings, players);
			settings.StatsData.totalIter++;
		}
	}
}

void RunStep(DiceRoller::UIdata& settings, std::vector<charSheet>& players)
{
	//OutputToWindow(settings, L"MADE IT TO RUN STEP!");
	SetStats(settings, players);
	for (int i = 0; i < settings.GeneralSettings.steps; i++)
	{
		RunItter(settings, players);
		settings.StatsData.totalSteps++;
		if (settings.OutputSettings.outStep)
		{
			OutputStep(settings, players);
		}
		StepStats(settings, players);
	};
}

void DiceRoller::RunSim(DiceRoller::UIdata& settings, std::vector<charSheet>& players)
{
	//OutputToWindow(settings, L"MADE IT TO RUN SIM!\n");
	std::srand(time(NULL));
	RunStep(settings, players);
};
