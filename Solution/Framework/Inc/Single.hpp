/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

namespace con
{
/* For classes that shouldn't be instantiated more than once (Logger, Time).
*/
template <typename T>
class Single
{
public:
	Single()
	{
		if ( !isInstantiated() )
			isInstantiated() = true;
	}
	virtual ~Single()
	{
		if ( isInstantiated() )
			isInstantiated() = false;
	}

	Single( const Single& ) = delete;
	Single( Single&& ) = delete;

private:
	// Todo: change to static inline field.
	static bool& isInstantiated()
	{
		static bool val = false;
		return val;
	}
};
}