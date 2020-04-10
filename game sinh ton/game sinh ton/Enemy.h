#ifndef ENEMY_H_
#define ENEMY_H_

#include <iostream>
#include "Hamchung.h"
#include "Hamcoso.h"
#include "bullet.h"


#define number_frame 8

class Enemy :public Hamcoso
{
public:
	Enemy();
	~Enemy();

	enum type_move
	{
		static_enemy = 0,
		move_in_space = 1,
	};

	void set_x_val(const float& xVAL) { x_val_ = xVAL; }
	void set_y_val(const float& yVAL) { y_val_ = yVAL; }

	void set_x_pos(const float& xPOS) { x_pos_ = xPOS; }
	void set_y_pos(const float& yPOS) { y_pos_ = yPOS; }
	float get_x_pos()const { return x_pos_; }
	float get_y_pos()const { return y_pos_; }
	void SetMapXY(const int& mp_x, const int& mp_y) { map_x = mp_x; map_y = mp_y; }

	void set_clip();
	bool LoadImg ( std::string path , SDL_Renderer* screen);
	void show(SDL_Renderer* des);
	int get_width_frame()const { return width_pic; }
	int get_height_frame()const { return height_pic; }
	void doEnemy(map& gMap);
	void vacham(map& gMap);
	void InitEnemy();
	void set_type_move(const int& TYPE) { type_move = TYPE; }
	void set_enemy_pos(const int& Ea, const int& Eb) { enemy_a = Ea; enemy_b = Eb; }
	void set_input_left(const int& ipleft) { input_type.left = ipleft; }
	void ImgMoveType(SDL_Renderer* screen);

	SDL_Rect GetRectFrame();

	std::vector<Bullet*> get_bullet_list()const { return bullet_list_; }
	void set_bullet_list(const std::vector<Bullet*> bl_list) { bullet_list_ = bl_list; }
	void InitBullet(Bullet* p_bullet, SDL_Renderer* screen);
	void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit);
	void RemoveBullet(const int& id);
	

private:
	int map_x;
	int map_y;
	bool on_ground;
	int come_back;
	float x_pos_;
	float y_pos_;
	float x_val_;
	float y_val_;
	SDL_Rect pic_clip[8];
	int frame_;
	int width_pic;
	int height_pic;

	int type_move;
	int enemy_a;
	int enemy_b;
	input input_type;

	std::vector<Bullet*> bullet_list_;

};


#endif
