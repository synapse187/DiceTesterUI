#pragma once
#include "pch.h"
#include "CharacterTools.h"

namespace DiceRoller
{
	struct UIdata
	{
		struct GeneralSettings
		{
			int die;
			int itter;
			int steps;
			bool combat;
			bool useStatsP1;
			bool useStatsP2;
		}GeneralSettings;
		struct StepSettings
		{
			int quickP1[2][2] = { { 0,0 }, { 0,0 } };
			int quickP2[2][2] = { { 0,0 }, { 0,0 } };
		}StepSettings;
		struct StatsData
		{
			int curWiner = 0;
			int totalSteps = 0;
			int totalIter = 0;
			int totalRounds = 0;
		}StatsData;
		struct PlayerData
		{
			struct P1
			{
				std::vector<int> statsP1Vec;
				int tar = 0;
				int pool = 0;
			}P1;
			struct P2
			{
				std::vector<int> statsP2Vec;
				int tar = 0;
				int pool = 0;
			}P2;
		}PlayerData;
		struct OutputSettings
		{
			bool outStep;
			bool outRound;
		}OutputSettings;
		winrt::Windows::UI::Xaml::Controls::TextBox outputBox;
	};
	void RunSim(DiceRoller::UIdata& settings, std::vector<charSheet>& players);
}