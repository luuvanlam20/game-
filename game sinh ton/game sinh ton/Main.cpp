#include <iostream>
#include "Hamchung.h"
#include "Hamcoso.h"
#include "bando.h"
#include "NVchinh.h"
#include "time.h"

Hamcoso g_background;
// tao windown
bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    g_window = SDL_CreateWindow("GAME SINH TON", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL)
        success = false;
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
            success = false;
        else
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        int ImgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(ImgFlags) && ImgFlags))
        {
            success = false;
        }
    }
    return success;
}
//load anh nen
bool LoadBackGround()
{
    bool ret = g_background.LoadImg("hinh//thac.png", g_screen);
    if (ret == false)
        return false;
    return true;
}
//dong ctrinhk
void close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    impTime fps_times;


    if (InitData() == false)
        return -1;
    if (LoadBackGround() == false)
        return -1;


    //map
    bando game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTile(g_screen);

    //nhan vat
    NVchinh player;

    player.LoadImg("hinh//player_right.png", g_screen);
    player.SETNVchinh_clip();

    bool is_quit = false;
    while (!is_quit)
    {
        fps_times.start();
       //nhan vao khi nhap
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            player.HandInputAction(g_event, g_screen);
        }
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        //anh nen
        g_background.Render(g_screen, NULL);
        //map
        map map_data = game_map.getMap();
        //nhan vat
        player.HandleBullet(g_screen);
        player.SetMapXY(map_data.stratX, map_data.stratY);
        player.dichuyen(map_data);
        player.show(g_screen);
        //map
        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);

        SDL_RenderPresent(g_screen);
        //delay
        int real_impTime = fps_times.get_tick();
        int time_one_frame = 1000 / FRAME_PER_SECOND;
        if (real_impTime < time_one_frame)
        {
            int delay_time = time_one_frame - real_impTime;
            if(delay_time>=0)
                SDL_Delay(delay_time);
                
        }
    }
    close();
    return 0;
}
