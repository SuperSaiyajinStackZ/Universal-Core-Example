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

#include "init.hpp"
#include "gfx.hpp"
#include "gui.hpp"
#include "screenCommon.hpp" // For the "ScreenTarget" definitions.

bool exiting = false;
touchPosition touch;

C2D_SpriteSheet sprites;

Result Init::Initialize() {
	gfxInitDefault();
	romfsInit();
	Gui::init();
	Gui::loadSheet("romfs:/gfx/sprites.t3x", sprites);
	sdmcInit();
	cfguInit();
	osSetSpeedupEnable(true);	// Enable speed-up for New 3DS users
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
		hidTouchRead(&touch);
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
		C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
		Gui::clearTextBufs(); // Clear Text Buffer before.

		// Draw Something on the Top Screen.
		Gui::ScreenDraw(Top);
		Gui::Draw_Rect(0, 0, 400, 30, C2D_Color32(0, 160, 160, 255));
		Gui::Draw_Rect(0, 30, 400, 180, C2D_Color32(0, 120, 120, 255));
		Gui::Draw_Rect(0, 210, 400, 30, C2D_Color32(0, 160, 160, 255));
		Gui::DrawStringCentered(0, 0, 0.7f, C2D_Color32(255, 255, 255, 255), "Universal-Core Example");
		// Draw Sprite example.
		GFX::DrawSprite(sprites_test_idx, 27, 33);

		// Draw Something on the Bottom Screen.
		Gui::ScreenDraw(Bottom);
		Gui::Draw_Rect(0, 0, 320, 30, C2D_Color32(0, 160, 160, 255));
		Gui::Draw_Rect(0, 30, 320, 180, C2D_Color32(0, 120, 120, 255));
		Gui::Draw_Rect(0, 210, 320, 30, C2D_Color32(0, 160, 160, 255));

		C3D_FrameEnd(0);

		if (hDown & KEY_START) {
			exiting = true; // Exit the app by pressing Start.
		}
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