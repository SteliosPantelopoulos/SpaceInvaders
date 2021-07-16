#include "settings.h"

#include <string>  

Settings::Settings()
{
}

Settings::~Settings()
{
}

void Settings::update()
{
	//update settings of the game if buttons were pressed
	graphics::Brush br;
	graphics::MouseState mouse;
	graphics::getMouseState(mouse);

	if (mouse.cur_pos_x >= (530 - 15) && mouse.cur_pos_x <= (530 + 15) && mouse.cur_pos_y >= (350 - 15) && mouse.cur_pos_y <= (350 + 15))
		if (mouse.button_left_pressed)
				audioChoise = !audioChoise;

	if (mouse.cur_pos_x >= (540 - 40) && mouse.cur_pos_x <= (540 + 40) && mouse.cur_pos_y >= (230 - 22) && mouse.cur_pos_y <= (230 + 22))
		if (mouse.button_left_pressed)
			controlsChoise = true;
	
	if (mouse.cur_pos_x >= (660 - 40) && mouse.cur_pos_x <= (660 + 40) && mouse.cur_pos_y >= (230 - 22) && mouse.cur_pos_y <= (230 + 22))
			if (mouse.button_left_pressed)
				controlsChoise = false;

	if (graphics::getKeyState(graphics::SCANCODE_RIGHT))
		state = 1;
}

void Settings::draw()
{
	graphics::Brush br;
	//background
	br.texture = std::string(ASSET_PATH) + "space.png";
	br.outline_opacity = 0.0;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	//if buttons for controls are hovered create a rectangle
	br.texture = "";
	br.outline_opacity = 1.0f;
	br.outline_color[0] = 1.0f;
	br.outline_color[1] = 1.0f;
	br.outline_color[2] = 1.0f;
	br.fill_opacity = 0.0f;
	if (controlsChoise)
		graphics::drawRect(450, 190, 80, 55, br);
	else
		graphics::drawRect(550, 190, 80, 55, br);
	
	br.outline_opacity = 0.0f;
	br.fill_opacity = 1.0f;
	//change audio icon if audio is ON/OFF
	if (!audioChoise)
	{
		br.texture = std::string(ASSET_PATH) + "soundOff.png";
		graphics::drawRect(450, 290, 35, 35, br);
	}
	else
	{
		br.texture = std::string(ASSET_PATH) + "soundOn.png";
		graphics::drawRect(450, 290, 35, 35, br);
	}

	//icons for controls
	br.texture = std::string(ASSET_PATH) + "wasd.png";
	graphics::drawRect(450, 190, 80, 55, br);
	br.texture = std::string(ASSET_PATH) + "arrows.png";
	graphics::drawRect(550, 190, 80, 55, br);
	//settings and help
	br.texture = "";
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	graphics::drawText(CANVAS_WIDTH / 2 - 80, 100, 40, "SETTINGS", br);
	graphics::drawText(250, 200, 30, "Controls", br);
	graphics::drawText(250, 300, 30, "Audio", br);
	br.texture = "";
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	graphics::drawText(CANVAS_WIDTH - 150, CANVAS_HEIGHT - 30, 12, "RIGHT: Returm to menu", br);
	graphics::drawText(CANVAS_WIDTH - 150, CANVAS_HEIGHT - 30 + 15, 12, "MOUSE: Select", br);
}

void Settings::init()
{
}