#pragma once
#include "pch.h"
#include "CharacterTools.h"

namespace DiceRoller
{
	struct UIdata
	{
		struct GeneralSettings
		{
			int itter;
			int steps;
			bool combat;
			bool useStatsP1;
			bool useStatsP2;
		}GeneralSettings;
		struct QuickStats
		{
			struct Player01
			{
				int Health = 0;
				int Endurance = 0;
				int Pool = 0;
				int Target = 0;
				int Accuracy = 0;
				int Damage = 0;
				int OffenceType = 0;
				int DefenceType = 0;
			}Player01;
			struct Player02
			{
				int Health = 0;
				int Endurance = 0;
				int Pool = 0;
				int Target = 0;
				int Accuracy = 0;
				int Damage = 0;
				int OffenceType = 0;
				int DefenceType = 0;
			}Player02;
		}QuickStats;
		struct StepSettings
		{
			struct QuickStats
			{
				struct Player01
				{
					int StepUpDown[4][2]{ {0,0},{0,0},{0,0},{0,0} };
					int OffenceType = 0;
					int DefenceType = 0;
				}Player01;
				struct Player02
				{
					int StepUpDown[4][2]{ {0,0},{0,0},{0,0},{0,0} };
					int OffenceType = 0;
					int DefenceType = 0;
				}Player02;
			}QuickStats;
		}StepSettings;
		struct StatsData
		{
			int curWiner = 0;
			int totalSteps = 0;
			int totalIter = 0;
			int totalRounds = 0;
		}StatsData;
		struct OutputSettings
		{
			bool outStep;
			bool outRound;
		}OutputSettings;
		winrt::Windows::UI::Xaml::Controls::TextBox outputBox;
	};
	void RunSim(DiceRoller::UIdata& settings, std::vector<charSheet>& players);
}