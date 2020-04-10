#include "bullet.h"

Bullet::Bullet()
{
	x_val_ = 0;
	y_val_ = 0;
	is_move = false;

}

Bullet::~Bullet()
{

}
bool Bullet::loadImgBullet(SDL_Renderer* des)
{
	bool rec = false;
	if(bullet_type==bigger_bullet)
	{
		rec=LoadImg("hinh//bigger_bullet.png", des);
	}
	else if(bullet_type == lazer_bullet)
	{
		rec=LoadImg("hinh//lazer_bullet.png", des);
	}
	else if(bullet_type == bomb_bullet)
	{
		rec=LoadImg("hinh//bomb_bullet.png", des);
	}
	return rec;
}
void Bullet::hand_Move(const int& x_bor,const int & y_bor)
{
	if (bullet_dir == dir_right)
	{
		rect_.x += x_val_;
		if (rect_.x > x_bor)
		{
			is_move = false;
		}
	}
	else if (bullet_dir == dir_left)
	{
		rect_.x -= x_val_;
		if (rect_.x < 0)
		{
			is_move = false;
		}
	}
	else if (bullet_dir == dir_up)
	{
		rect_.y -= y_val_;
		if (rect_.y < 0)
		{
			is_move = false;
		}
	}
	else if (bullet_dir == dir_down)
	{
		rect_.y += y_val_;
		if (rect_.y > y_bor)
		{
			is_move = false;
		}
	}
	else if (bullet_dir == dir_up_left)
	{
		rect_.x -= x_val_;
		if (rect_.x < 0)
		{
			is_move = false;
		}
		rect_.y -= y_val_;
		if (rect_.y < 0)
		{
			is_move = false;
		}
	}
	else if (bullet_dir == dir_up_right)
	{
		rect_.x += x_val_;
		if (rect_.x > x_bor)
		{
			is_move = false;
		}
		rect_.y -= y_val_;
		if (rect_.y < 0)
		{
			is_move = false;
		}
	}
	else if (bullet_dir == dir_down_left)
	{
		rect_.x -= x_val_;
		if (rect_.x < 0)
		{
			is_move = false;
		}
		rect_.y += y_val_;
		if (rect_.y > y_bor)
		{
			is_move = false;
		}
	}
	else if (bullet_dir == dir_down_right)
	{
		rect_.x += x_val_;
		if (rect_.x > x_bor)
		{
			is_move = false;
		}
		rect_.y += y_val_;
		if (rect_.y > y_bor)
		{
			is_move = false;
		}
	}
}