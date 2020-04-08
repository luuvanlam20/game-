#include "Enemy.h"

#define tocdoroi 1
#define tocdomax 10
#define tocdochay 10
#define lucnhay 18

Enemy::Enemy()
{
	width_pic = 0;
	height_pic = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	on_ground = false;
	come_back = 0;
	frame_ = 0;

	enemy_a = 0;
	enemy_b = 0;
	input_type.left = 0;
	type_move = static_enemy;
}
Enemy::~Enemy()
{

}
bool Enemy::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = Hamcoso::LoadImg(path, screen);
	if (ret == true)
	{
		width_pic = rect_.w / 8;
		height_pic = rect_.h;

	}
	return ret;
}
void Enemy::set_clip()
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
void Enemy::show(SDL_Renderer* des)
{
	if (come_back == 0)
	{
		rect_.x = x_pos_ - map_x;
		rect_.y = y_pos_ - map_y;
		frame_++;
		if (frame_ >= 8)
		{
			frame_ = 0;
		}
		SDL_Rect* clipHT = &pic_clip[frame_];
		SDL_Rect rederquad = { rect_.x,rect_.y,width_pic,height_pic };
		SDL_RenderCopy(des, p_object_, clipHT, &rederquad);
	}
}

void Enemy::doEnemy(map& gMap)
{
	if (come_back == 0) {
		x_val_ = 0;
		y_val_ += tocdoroi;
		if (y_val_ >= tocdomax)
		{
			y_val_ = tocdomax;
		}
		if (input_type.left == 1)
		{
			x_val_ -= tocdochay;
		}
		
		if (input_type.right == 1)
		{
			x_val_ += tocdochay;
		}
		/*if (input_type.jump == 1)
		{
			if (on_groud == true)
			{
				y_val = -lucnhay;
				on_groud = false;
			}

			input_type.jump = 0;
		}*/
		vacham(gMap);
	}
	else
	{
		come_back--;
		if (come_back == 0)
		{
			InitEnemy();
		}

	}
}

void Enemy::InitEnemy()
{
	x_pos_ = 0;
	y_pos_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	come_back = 0;
	input_type.left = 1;
}

void Enemy::vacham(map& gMap)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;


	//kt chieu cao
	int height_min = height_pic < TILE_SIZE ? height_pic : TILE_SIZE;

	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_pic - 1) / TILE_SIZE;

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAPMAX_X && y1 >= 0 && y2 < MAPMAX_Y)
	{
		if (x_val_ > 0)//di chuyen sang ngang
		{
			int val1 = gMap.tile[y1][x2];
			int val2 = gMap.tile[y2][x2];

			if (val1 != chotrong && val1 != tien || val2 != chotrong && val2 != tien)
			{
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= (width_pic + 1);
				x_val_ = 0;
			}
			else if (gMap.tile[y1][x2] == chotrong && gMap.tile[y2 + 1][x2] == chotrong && gMap.tile[y1][x2] == chotrong && gMap.tile[y2][x2] == chotrong)
				on_ground = false;
		}

		else if (x_val_ < 0)
		{
			int val1 = gMap.tile[y1][x1];
			int val2 = gMap.tile[y2][x1];
			
			if (val1 != chotrong && val1 != tien || val2 != chotrong && val2 != tien)
			{
				x_pos_ = (x1 + 1) * TILE_SIZE;
				//x_pos += width_pic ;
				x_val_ = 0;
			}
			else if (gMap.tile[y1 + 1][x1] == chotrong && gMap.tile[y2 + 1][x1] == chotrong && gMap.tile[y1][x1] == chotrong && gMap.tile[y2][x1] == chotrong)
				on_ground = false;


		}
	}
	int width_min = width_pic < TILE_SIZE ? width_pic : TILE_SIZE;

	x1 = (x_pos_) / TILE_SIZE;
	x2 = (x_pos_ + width_min - 1) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_pic - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAPMAX_X && y1 >= 0 && y2 < MAPMAX_Y)
	{
		if (y_val_ > 0)
		{
			int val1 = gMap.tile[y2][x1];
			int val2 = gMap.tile[y2][x2];
			
			if (val1 != chotrong && val1 != tien || val2 != chotrong && val2 != tien)
			{
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= height_pic + 1;
				y_val_ = 0;
				on_ground = true;
			}


		}
		else if (y_val_ < 0)
		{
			int val1 = gMap.tile[y1][x1];
			int val2 = gMap.tile[y1][x2];
			
			if (val1 != chotrong && val1 != tien || val2 != chotrong && val2 != tien)
			{
				y_pos_ = (y1 + 1) * TILE_SIZE;
				//x_pos += width_pic ;
				y_val_ = 0;
			}

		}
	}
	x_pos_ += x_val_;
	y_pos_ += y_val_;
	if (x_pos_ < 0)
	{
		x_pos_ = 0;
	}
	else if (x_pos_ + width_pic > gMap.max_X)
	{
		x_pos_ = gMap.max_X - width_pic - 1;
	}
	if (y_pos_ < 0)
	{
		y_pos_ = 0;
	}
	else if (y_pos_ + height_pic > gMap.max_Y)
	{
		come_back = 10;
		//y_pos = map_data.max_Y - height_pic - 1;
		on_ground = false;
		//status = -1;
	}
}

void Enemy::ImgMoveType(SDL_Renderer* screen)
{
	if (type_move == static_enemy)
	{
		;
	}
	else
	{
		if (on_ground == true)
		{
			if (x_pos_ > enemy_b)
			{
				input_type.left = 1;
				input_type.right = 0;
				LoadImg("hinh//threat_left.png", screen);
			}
			else
			{
				if (x_pos_ < enemy_a)
				{
					input_type.left = 0;
					input_type.right = 1;
					
					LoadImg("hinh//threat_right.png", screen);
				}
			}
		}
		else
		{
			if (input_type.left == 1)
			{
				LoadImg("hinh//threat_left.png", screen);
			}
		}
	}
}