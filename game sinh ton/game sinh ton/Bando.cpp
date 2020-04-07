#include <iostream>
#include "bando.h"

void bando::LoadMap(const char* nap)
{
	FILE* fp = NULL;
	fopen_s(&fp, nap, "rb");//doc file
	if (fp == NULL) {
		return;
	}

	ban_do.max_Y = 0;
	ban_do.max_X = 0;

	for (int i = 0; i < MAPMAX_Y; i++)
	{
		for (int j = 0; j < MAPMAX_X; j++)
		{
			fscanf_s(fp, "%d", &ban_do.tile[i][j]);//lay gia tri vao tile
			int  val = ban_do.tile[i][j];
			if (val > 0)
			{
				if (j > ban_do.max_X)
				{
					ban_do.max_X = j;
				}
				if (i > ban_do.max_Y)
				{
					ban_do.max_Y = i;
				}
			}
		}
	}
	ban_do.max_Y = (ban_do.max_Y + 1) * TILE_SIZE;
	ban_do.max_X = (ban_do.max_X + 1) * TILE_SIZE;
	ban_do.stratX = 0;
	ban_do.stratY = 0;
	ban_do.file_name = nap;
	fclose(fp);
}
void bando::LoadTile(SDL_Renderer* screen)
{
	char file_img[30];
	FILE* fp = NULL;
	for (int i = 0; i < MAXTILE; i++)
	{
		sprintf_s(file_img, "map/%d.png", i);//ghi chuoi vao file_img[i]
		fopen_s(&fp, file_img, "rb");
		if (fp == NULL) {
			continue;
		}
		fclose(fp);
		tile_map[i].LoadImg(file_img, screen);
	}
}
void bando::DrawMap(SDL_Renderer* screen)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;
	int map_x = 0;
	int map_y = 0;
	map_x = ban_do.stratX / TILE_SIZE;
	x1 = (ban_do.stratX % TILE_SIZE) * -1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	map_y = ban_do.stratY / TILE_SIZE;
	y1 = (ban_do.stratY % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);
	for (int i = y1; i < y2; i += TILE_SIZE)
	{
		map_x = ban_do.stratX / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE)
		{
			int val = ban_do.tile[map_y][map_x];
			if (val > 0)
			{
				tile_map[val].SetRect(j, i);
				tile_map[val].Render(screen);

			}
			map_x++;
		}
		map_y++;
	}
}
