#include "endgame.h"
#include <windows.h> 

EndGame::EndGame(int result)
{
    //3 different options for end screen WIN, LOSS, SELECT FOR MENU
    gameResult = result;
}

EndGame::~EndGame()
{
}

void EndGame::update()
{
    //checks the buttons are hovered or pressed
    graphics::MouseState mouse;
    graphics::getMouseState(mouse);
    if (mouse.cur_pos_x >= 530 && mouse.cur_pos_x <= 680 && mouse.cur_pos_y >= 380 && mouse.cur_pos_y <= 400)
    {
        if (mouse.button_left_pressed)
            state = 1;
    }
}

void EndGame::draw()
{
    //draw logo, buttons, help
    graphics::Brush br;
    graphics::MouseState mouse;
    graphics::getMouseState(mouse);

    //logo-background
    br.texture = std::string(ASSET_PATH) + "space.png";
    br.outline_opacity = 0.0;
    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

    if (gameResult == 1)
    {
        br.texture = std::string(ASSET_PATH) + "gameover.png";
        graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 3, 410, 185, br);
    }
    else if (gameResult == 0)
    {
        br.texture = std::string(ASSET_PATH) + "winLogo.png";
        graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 3, 410, 185, br);
    }

    //buttons
    br.texture = "";
    br.fill_color[0] = 0.0f;
    br.fill_color[1] = 0.0f;
    br.fill_color[2] = 0.0f;

    graphics::drawText(CANVAS_WIDTH / 2 - 60, CANVAS_HEIGHT * 2 / 3, 20, "RESTART GAME", br);
    graphics::drawText(CANVAS_WIDTH / 2 - 42, CANVAS_HEIGHT * 2 / 3 + 70, 20, "EXIT GAME", br);

    if (mouse.cur_pos_x >= 530 && mouse.cur_pos_x <= 680 && mouse.cur_pos_y >= 380 && mouse.cur_pos_y <= 400)
    {
        br.fill_color[0] = 1.0f;
        br.fill_color[1] = 0.25f;
        br.fill_color[2] = 0.1f;
        graphics::drawText(CANVAS_WIDTH / 2 - 60, CANVAS_HEIGHT * 2 / 3, 20, "RESTART GAME", br);
    }
    else if (mouse.cur_pos_x >= 550 && mouse.cur_pos_x <= 650 && mouse.cur_pos_y >= 465 && mouse.cur_pos_y <= 485)
    {
        br.fill_color[0] = 1.0f;
        br.fill_color[1] = 0.25f;
        br.fill_color[2] = 0.1f;
        graphics::drawText(CANVAS_WIDTH / 2 - 42, CANVAS_HEIGHT * 2 / 3 + 70, 20, "EXIT GAME", br);

        br.fill_color[0] = 1.0f;
        br.fill_color[1] = 1.0f;
        br.fill_color[2] = 1.0f;
        br.fill_opacity = 0.5;
        graphics::drawText(CANVAS_WIDTH / 2 - 20, CANVAS_HEIGHT * 2 / 3 + 85, 10, "PRESS ESC", br);
        br.fill_opacity = 1.0f;
    }
    //help
    br.texture = "";
    br.fill_color[0] = 1.0f;
    br.fill_color[1] = 1.0f;
    br.fill_color[2] = 1.0f;
    graphics::drawText(CANVAS_WIDTH - 100, CANVAS_HEIGHT - 30 + 15, 12, "MOUSE: Select", br);
}

void EndGame::init()
{
}