#pragma once

struct EntityUniqueID
{
	long long id;

	bool operator <(const EntityUniqueID& rhs) const
	{
		return id < rhs.id;
	}
};
