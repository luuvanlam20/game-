#include <iostream>
#include "Hamchung.h"
#include "Hamcoso.h"
#include "bando.h"
#include "NVchinh.h"
#include "Enemy.h"
#include "time.h"
#include "explo.h"

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
std::vector<Enemy*> MakeEnemyList()
{
    std::vector<Enemy*> enemy_list;

    Enemy* enemy_obj_move = new Enemy[20];
    for (int i = 0; i < 20; i++)
    {
        Enemy* p_enemy = (enemy_obj_move + i);
        if (p_enemy != NULL)
        {
            p_enemy->LoadImg("hinh//threat_left.png", g_screen);
            p_enemy->set_clip();
            p_enemy->set_type_move(Enemy::move_in_space);
            p_enemy->set_x_pos(500 + i * 500);
            p_enemy->set_y_pos(200);

            int pos1 = p_enemy->get_x_pos() - 60;
            int pos2 = p_enemy->get_x_pos() + 60;

            p_enemy->set_enemy_pos(pos1, pos2);

            p_enemy->set_input_left(1);

            enemy_list.push_back(p_enemy);

        }
    }

    Enemy* enemy_obj = new Enemy[20];
    for (int i = 0; i < 20; i++)
    {
        Enemy* p_enemy = (enemy_obj + i);
        if (p_enemy != NULL)
        {
            p_enemy->LoadImg("hinh//threat_level.png", g_screen);
            p_enemy->set_clip();
            p_enemy->set_x_pos(700+i*1200);
            p_enemy->set_y_pos(250);
            p_enemy->set_type_move(Enemy::static_enemy);

            Bullet* p_bullet = new Bullet();
            p_enemy->InitBullet(p_bullet, g_screen);


            enemy_list.push_back(p_enemy);

        }
    }
    return enemy_list;
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

    std::vector<Enemy*> enemy_list = MakeEnemyList();

    EXPLO exp_enemy;
    bool tRet = exp_enemy.LoadImg("hinh//exp3.png", g_screen);
    if (!tRet) 
    {
        return -1;
    }
    exp_enemy.set_clip();

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

        for (int i = 0; i < enemy_list.size(); i++)
        {
            Enemy* p_enemy = enemy_list.at(i);
            if (p_enemy != NULL)
            {
                p_enemy->SetMapXY(map_data.stratX, map_data.stratY);
                p_enemy->ImgMoveType(g_screen);
                p_enemy->doEnemy(map_data);
                p_enemy->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                p_enemy->show(g_screen);

                SDL_Rect rect_player = player.GetRectFrame();
                bool bCol1 = false;
                std::vector<Bullet*> tbullet = p_enemy->get_bullet_list();
                for(int k = 0; k < tbullet.size(); k++)
                {
                    Bullet* enemy_bullet = tbullet.at(k);
                    if (enemy_bullet)
                    {
                        bCol1 = SDLCommonFuc::checkColisision(enemy_bullet->GetRect(), rect_player);
                        if (bCol1)
                        {
                            p_enemy->RemoveBullet(k);
                            break;
                        }
                    }
                }

                SDL_Rect rect_enemy = p_enemy->GetRectFrame();
                bool bCol2;
                bCol2 = SDLCommonFuc::checkColisision(rect_player, rect_enemy);

                if (bCol1 || bCol2)
                {
                    if (MessageBox(NULL, L"Game Over!",L"Infor", MB_OK | MB_ICONSTOP) == IDOK)
                    {
                        player.Free();
                        close();
                        SDL_Quit();
                        return 0;
                    }
                }

            }
        }

        int frame_exp_width = exp_enemy.get_frame_width();
        int frame_exp_height = exp_enemy.get_frame_height();

        std::vector<Bullet*> bullet_arr = player.get_bullet_list();
        for (int bl = 0; bl < bullet_arr.size(); bl++)
        {
            Bullet* p_bullet = bullet_arr.at(bl);
            if (p_bullet != NULL)
            {
                for (int t = 0; t < enemy_list.size(); t++)
                {
                    Enemy* obj_enemy = enemy_list.at(t);
                    if (obj_enemy != NULL)
                    {
                        SDL_Rect tRect;

                        tRect.x = obj_enemy->GetRect().x;
                        tRect.y = obj_enemy->GetRect().y;
                        tRect.w = obj_enemy->get_width_frame();
                        tRect.h = obj_enemy->get_height_frame();

                        SDL_Rect bRect;
                        bRect = p_bullet->GetRect();

                        bool bCol = SDLCommonFuc::checkColisision(bRect,tRect);

                        if (bCol)
                        {
                            for (int ex = 0; ex < Num_EX_frame; ex++)
                            {
                                int x_pos = p_bullet->GetRect().x-frame_exp_width*0.5;
                                int y_pos = p_bullet->GetRect().y - frame_exp_height * 0.5;
                                exp_enemy.set_frame(ex);
                                exp_enemy.SetRect(x_pos, y_pos);
                                exp_enemy.show(g_screen);

                            }

                            player.RemoveBullet(bl);
                            obj_enemy->Free();
                            enemy_list.erase(enemy_list.begin() + t);
                        }

                    }
                }
            }
        }


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
    for (int i = 0; i < enemy_list.size(); i++)
    {
        Enemy* p_enemy = enemy_list.at(i);
        if (p_enemy)
        {
            p_enemy->Free();
            p_enemy = NULL;
        }
    }
    enemy_list.clear();
    close();
    return 0;
}
