#pragma once

#include <Utilities/Template.h>

struct ILifetime
{
	bool HasLifetime = false;
	CDTimerClass LifetimeTimer;

	inline bool IsLifetimeOut() const
	{
		return HasLifetime && LifetimeTimer.Completed();
	}
};
