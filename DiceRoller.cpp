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
		oStr << "Target Number: " << players[i].cStats.curTargNum << " |--| ";
		oStr << "Pool: " << players[i].cStats.curPool << "\n";
		oStr << "Rolls: " << "\n|";
		//output rolls
		for (int j = 0; j < players[i].cStats.curPool; j++)
		{
			oStr << players[i].cStats.poolArr[j] << "|";
		}
		oStr << "\n";
		oStr << "Successes: " << players[i].cStats.curSuc << "\n";
	}
	oStr << "Winner: " << players[settings.StatsData.curWiner].bio.charName << "|--|";
	oStr << "Won By: " << (players[settings.StatsData.curWiner].cStats.curSuc - players[!settings.StatsData.curWiner].cStats.curSuc) << "\n\n";
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
		float avgSuc = (players[i].cStats.totSuc / (settings.StatsData.totalIter + settings.StatsData.totalRounds));
		if (players[i].cStats.wonByTotal > 0)
		{
			winAvg = players[i].cStats.wonByTotal / players[i].cStats.wins;
		}
		if (players[i].cStats.wins > 0)
		{
			winPerc = ((float(players[i].cStats.wins) / (settings.StatsData.totalIter + settings.StatsData.totalRounds)) * 100.00);
		}
		os2 << "---|Player: " + players[i].bio.charName + "|---\n";
		os2 << "|Pool||Target||Avg Suc||Win Avg||Win %|\n";
		os2 << std::setw(6) << players[i].cStats.curPool;
		os2 << std::setw(8) << players[i].cStats.curTargNum;
		os2 << std::setprecision(3);
		os2 << std::setw(9) << avgSuc;
		os2 << std::setw(9) << winAvg;
		os2 << std::setw(5) << "%" << winPerc << "\n" << std::endl;
	}
	OutputToWindow(settings, to_hstring(os2.str()));
}

void SetStats(DiceRoller::UIdata& settings, std::vector<charSheet> &players)
{
	if (!settings.GeneralSettings.useStatsP1)
	{
		int tempArr[2][2] = { {settings.PlayerData.P1.tar,settings.PlayerData.P1.pool}, {settings.PlayerData.P2.tar,settings.PlayerData.P2.pool} };
		for (int i = 0; i < players.size(); i++)
		{
			players[i].cStats.curTargNum = tempArr[i][0];
			players[i].cStats.curPool = tempArr[i][1];
		}
	}
	else
	{

	}
}

void StepStats(DiceRoller::UIdata& settings, std::vector<charSheet>& players)
{
	if (!settings.GeneralSettings.useStatsP1)
	{
		players[0].cStats.curTargNum += (settings.StepSettings.quickP1[0][0] - settings.StepSettings.quickP1[0][1]);
		players[0].cStats.curPool += (settings.StepSettings.quickP1[1][0] - settings.StepSettings.quickP1[1][1]);
	}
	if (!settings.GeneralSettings.useStatsP2)
	{
		players[1].cStats.curTargNum += (settings.StepSettings.quickP2[0][0] - settings.StepSettings.quickP2[0][1]);
		players[1].cStats.curPool += (settings.StepSettings.quickP2[1][0] - settings.StepSettings.quickP2[1][1]);
	}
	settings.StatsData.totalIter = 0;
	settings.StatsData.totalRounds = 0;
	for (charSheet& i : players)
	{
		i.cStats.wins = 0;
		i.cStats.totSuc = 0;
		i.cStats.wonByTotal = 0;
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
	if (players[0].cStats.curSuc >= players[1].cStats.curSuc)
	{
		settings.StatsData.curWiner = 0;
		players[0].cStats.wins++;
		players[0].cStats.wonBy = players[0].cStats.curSuc - players[1].cStats.curSuc;
		players[0].cStats.wonByTotal += players[0].cStats.curSuc - players[1].cStats.curSuc;
	}
	else
	{
		settings.StatsData.curWiner = 1;
		players[1].cStats.wins++;
		players[1].cStats.wonBy = players[1].cStats.curSuc - players[0].cStats.curSuc;
		players[1].cStats.wonByTotal += players[1].cStats.curSuc - players[0].cStats.curSuc;
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
