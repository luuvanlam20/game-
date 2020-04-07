#include "time.h"
#include "Hamchung.h"

impTime::impTime()
{
	start_tick_ = 0;
	pause_tick_ = 0;
	is_paused_ = false;
	is_started_ = false;

}
impTime::~impTime()
{


}

void impTime::start()
{
	is_started_ = true;
	is_paused_ = false;
	start_tick_ = SDL_GetTicks();

}
void impTime::stop()
{
	is_paused_ = false;
	is_started_ = false;
}
void impTime::pause()
{
	if (is_started_ ==true && is_paused_ == false)
	{
		is_paused_ = true;
		pause_tick_ = SDL_GetTicks() - start_tick_;
	}
}
void impTime::un_pausel()
{
	if (is_paused_ == true)
	{
		is_paused_ = false;
		start_tick_ = SDL_GetTicks() - pause_tick_;
		pause_tick_ = 0;
	}
}
int impTime::get_tick()
{
	if (is_started_ == true)
	{
		if (is_paused_ == true)
		{
			return pause_tick_;
		}
		else
			return SDL_GetTicks() - start_tick_;
	}
	return 0;
}
bool impTime::is_started()
{
	return is_started_;
}
bool impTime::is_paused()
{
	return is_paused_;
}