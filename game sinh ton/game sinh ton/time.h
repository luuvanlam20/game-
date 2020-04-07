#ifndef TIME_H_
#define TIME_H_

class impTime
{
public:
	impTime() ;
	~impTime() ;
	void start();
	void stop();
	void pause();
	void un_pausel();
	int get_tick();
	bool is_started();
	bool is_paused();


private:
	int start_tick_;
	int pause_tick_;

	bool is_paused_;
	bool is_started_;
};



#endif
