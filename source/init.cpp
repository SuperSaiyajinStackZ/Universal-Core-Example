/*
*   This file is part of Universal-Core-Example
*   Copyright (C) 2020 StackZ
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#include "common.hpp"
#include "init.hpp"
#include "mainMenu.hpp"
#include "structs.hpp"

bool exiting = false;
touchPosition touch;

C2D_SpriteSheet sprites;

// If button Position pressed -> Do something.
bool touching(touchPosition touch, Structs::ButtonPos button) {
	if (touch.px >= button.x && touch.px <= (button.x + button.w) && touch.py >= button.y && touch.py <= (button.y + button.h))
		return true;
	else
		return false;
}

Result Init::Initialize() {
	gfxInitDefault();
	romfsInit();
	Gui::init();
	Gui::loadSheet("romfs:/gfx/sprites.t3x", sprites);
	sdmcInit();
	cfguInit();
	osSetSpeedupEnable(true);	// Enable speed-up for New 3DS users
	// Set Screen.
	Gui::setScreen(std::make_unique<MainMenu>());
    return 0;
}

Result Init::MainLoop() {
    // Initialize everything.
    Initialize();

	// Loop as long as the status is not exiting.
	while (aptMainLoop() && !exiting)
	{
		hidScanInput();
		u32 hDown = hidKeysDown();
		u32 hHeld = hidKeysHeld();
		hidTouchRead(&touch);
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
		C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
		Gui::clearTextBufs(); // Clear Text Buffer before.
		Gui::mainLoop(hDown, hHeld, touch);
		C3D_FrameEnd(0);
	}
    // Exit all services and exit the app.
    Exit();
    return 0;
}

Result Init::Exit() {
	Gui::exit();
	Gui::unloadSheet(sprites);
	gfxExit();
	cfguExit();
	romfsExit();
	sdmcExit();
	return 0;
}