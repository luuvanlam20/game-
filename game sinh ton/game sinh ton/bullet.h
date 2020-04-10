#ifndef BULLET_H_
#define BULLET_H_

#include "Hamchung.h"
#include "Hamcoso.h"

class Bullet:public Hamcoso
{
public:
	Bullet();
	~Bullet();
	enum BulletDir
	{
		dir_right = 20,
		dir_left = 21,
		dir_up = 22,
		dir_down = 23,
		dir_up_left = 24,
		dir_up_right = 25,
		dir_down_left = 26,
		dir_down_right = 27,
	};
	enum
	{
		bigger_bullet = 10,
		lazer_bullet = 11,
		bomb_bullet = 12,
	};
	void set_x_val(const int& xVAL) { x_val_ = xVAL; }
	void set_y_val(const int& yVAL) { y_val_ = yVAL; }
	int get_x_val()const { return x_val_; }
	int get_y_val()const { return y_val_; }
	void set_is_move(const bool& isMov) { is_move = isMov; }
	bool get_is_move()const { return is_move; }
	void set_bullet_type(const int& bulletTYPE) { bullet_type = bulletTYPE; }
	int get_bullet_type()const { return bullet_type; }
	void set_bullet_dir(const unsigned int& bulletDIR) { bullet_dir = bulletDIR; }
	unsigned int get_bullet_dir()const { return bullet_dir; }
	void hand_Move(const int& x_bor, const int& y_bor);
	bool loadImgBullet(SDL_Renderer* des);
private:
	int x_val_;
	int y_val_;
	bool is_move;
	unsigned int bullet_dir;
	int bullet_type;

};

#endif // !BULLET_H_

