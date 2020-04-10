#include "explo.h"


EXPLO::EXPLO()
{
	width_pic = 0;
	height_pic = 0;
	frame_ = 0;
}

EXPLO::~EXPLO()
{

}

bool EXPLO::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = Hamcoso::LoadImg(path, screen);
	if (ret)
	{
		width_pic = rect_.w / Num_EX_frame;
		height_pic = rect_.h;
	}
	return ret;
}

void EXPLO::set_clip()
{
	if (width_pic > 0 && height_pic > 0)
	{
		pic_clip[0].x = 0;
		pic_clip[0].y = 0;
		pic_clip[0].w = width_pic;
		pic_clip[0].h = height_pic;

		pic_clip[1].x = width_pic;
		pic_clip[1].y = 0;
		pic_clip[1].w = width_pic;
		pic_clip[1].h = height_pic;

		pic_clip[2].x = 2 * width_pic;
		pic_clip[2].y = 0;
		pic_clip[2].w = width_pic;
		pic_clip[2].h = height_pic;

		pic_clip[3].x = 3 * width_pic;
		pic_clip[3].y = 0;
		pic_clip[3].w = width_pic;
		pic_clip[3].h = height_pic;

		pic_clip[4].x = 4 * width_pic;
		pic_clip[4].y = 0;
		pic_clip[4].w = width_pic;
		pic_clip[4].h = height_pic;

		pic_clip[5].x = 5 * width_pic;
		pic_clip[5].y = 0;
		pic_clip[5].w = width_pic;
		pic_clip[5].h = height_pic;

		pic_clip[6].x = 6 * width_pic;
		pic_clip[6].y = 0;
		pic_clip[6].w = width_pic;
		pic_clip[6].h = height_pic;

		pic_clip[7].x = 7 * width_pic;
		pic_clip[7].y = 0;
		pic_clip[7].w = width_pic;
		pic_clip[7].h = height_pic;
	}
}
void EXPLO::show(SDL_Renderer* screen)
{
		SDL_Rect* clipHT = &pic_clip[frame_];
		SDL_Rect rederquad = { rect_.x,rect_.y,width_pic,height_pic };

		if (clipHT != NULL)
		{
			rederquad.w = clipHT->w;
			rederquad.h = clipHT->h;
		}

		SDL_RenderCopy(screen, p_object_, clipHT, &rederquad);
}