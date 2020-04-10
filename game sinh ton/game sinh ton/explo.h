#ifndef EXPLO_H_
#define EXPLO_H_

#include "Hamchung.h"
#include "Hamcoso.h"

#define Num_EX_frame 8


class EXPLO : public Hamcoso
{
public:
	EXPLO();
	~EXPLO();

public:
	void set_clip();
	void set_frame(const int& fr) { frame_ = fr; }
	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	void show(SDL_Renderer* screen);
	int get_frame_width()const { return width_pic; }
	int get_frame_height()const { return height_pic; }
private:
	int width_pic;
	int height_pic;
	unsigned int frame_;
	SDL_Rect pic_clip[8];

};


#endif // !EXPLO_H_

