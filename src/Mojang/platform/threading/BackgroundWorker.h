#pragma once

#include <functional>

class BackgroundWorker
{
public:
	void queue(const std::function<bool()> &, const std::function<void()> &, int);
};