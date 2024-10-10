#pragma once

#include <TeamClass.h>

#include "extension.abstract.hpp"

#include <vector>

template<> class Extension<TeamClass> : public Extension<AbstractClass>
{
	__EXTENSION_BODY(TeamClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
public:
	constexpr Extension(base_type& base) : parent_type(base)
		, WaitNoTargetAttempts { 0 }
		, NextSuccessWeightAward { 0 }
		, IdxSelectedObjectFromAIList { -1 }
		, CloseEnough { -1 }
		, Countdown_RegroupAtLeader { -1 }
		, MoveMissionEndMode { 0 }
		, WaitNoTargetCounter { 0 }
		, WaitNoTargetTimer { }
		, ForceJump_Countdown { }
		, ForceJump_InitialCountdown { -1 }
		, ForceJump_RepeatMode { false }
		, TeamLeader { nullptr }
		, PreviousScriptList { }
	{ }

	int WaitNoTargetAttempts;
	double NextSuccessWeightAward;
	int IdxSelectedObjectFromAIList;
	double CloseEnough;
	int Countdown_RegroupAtLeader;
	int MoveMissionEndMode;
	int WaitNoTargetCounter;
	CDTimerClass WaitNoTargetTimer;
	CDTimerClass ForceJump_Countdown;
	int ForceJump_InitialCountdown;
	bool ForceJump_RepeatMode;
	FootClass* TeamLeader;
	std::vector<ScriptClass*> PreviousScriptList;
};

template<> struct Proxy<TeamClass> : public TeamClass
{
	__PROXY_BODY(TeamClass)
	__PROXY_MEMORY_MANAGEMENT
};

