#pragma once

typedef long long unsigned uint64;
#include <iostream>


class Event {
public:

};

class iRuntimeLayer {
public:
	iRuntimeLayer() = default;
	virtual ~iRuntimeLayer() = default;

	virtual uint64 Initilize() = 0;
	virtual uint64 Tick() = 0;
	virtual uint64 Shutdown() = 0;
};