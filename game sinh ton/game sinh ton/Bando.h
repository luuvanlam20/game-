#ifndef BAN_DO_H_
#define BAN_DO_H_

#include "Hamchung.h"
#include "Hamcoso.h"
#define MAXTILE 20
class TileMap : public Hamcoso//ke thua ham co so
{
public:
	TileMap() { ; }
	~TileMap() { ; }

};

typedef class bando
{
public:
	bando() { ; }
	~bando() { ; }
	void LoadMap(const char* nap);//load ban đo
	void LoadTile(SDL_Renderer* screen);//load mat xich ban do
	void DrawMap(SDL_Renderer* screen);//ve ban do
	map getMap()const { return ban_do; };//lay ban do
	void SetMap(map& map_data) { ban_do = map_data; }//cai dat ban do
private:
	map ban_do;
	TileMap tile_map[MAXTILE];
};

#endif

