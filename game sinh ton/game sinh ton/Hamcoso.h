#ifndef HAM_CO_SO_H_
#define HAM_CO_SO_H_

#include "Hamchung.h"

class Hamcoso
{
public:
	Hamcoso();
	~Hamcoso();
	void SetRect(const int& x, const int& y) { rect_.x = x; rect_.y = y; }//dat toa đo
	SDL_Rect GetRect() const { return rect_; }//tra ve toa do
	SDL_Texture* GetObject()const { return p_object_; } //tra ve texture
	virtual bool LoadImg(std::string path, SDL_Renderer* screen);//load anh
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);//ve
	void Free();//giai phong
protected:
	SDL_Texture* p_object_;
	SDL_Rect rect_;
};

#endif // !HAM_CO_SO_H_

