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

C2D_SpriteSheet sprites;

// If button Position pressed -> Do something.
bool touching(touchPosition touch, Structs::ButtonPos button) {
	if (touch.px >= button.x && touch.px <= (button.x + button.w) && touch.py >= button.y && touch.py <= (button.y + button.h))	return true;
	else	return false;
}

Result Init::Initialize() {
	// Here we set the fade effect for fadein.
	fadealpha = 255;
	fadein = true;

	gfxInitDefault();
	romfsInit();
	Gui::init();
	Gui::loadSheet("romfs:/gfx/sprites.t3x", sprites);
	cfguInit();
	osSetSpeedupEnable(true);	// Enable speed-up for New 3DS users
	// Set Screen.
	Gui::setScreen(std::make_unique<MainMenu>(), false); // Set the screen initially as MainMenu.
	return 0;
}

Result Init::MainLoop() {
	// Initialize everything.
	Init::Initialize();

	// Loop as long as the status is not exiting.
	while (aptMainLoop()) {
		// Scan the input.
		hidScanInput();
		u32 hDown = hidKeysDown();
		u32 hHeld = hidKeysHeld();
		touchPosition touch;
		hidTouchRead(&touch);

		Gui::clearTextBufs(); // Clear Text Buffer before.
		C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
		C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));

		if (!exiting) {
			// Screen Logic & Draw.
			C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
			Gui::DrawScreen();
			Gui::ScreenLogic(hDown, hHeld, touch, true);
			C3D_FrameEnd(0);
		} else {
			C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
			Gui::ScreenDraw(Top);
			if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect
			Gui::ScreenDraw(Bottom);
			if (fadealpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha)); // Fade in/out effect
			C3D_FrameEnd(0);

			if (fadeout == false) {
				break;
			}
		}

		// Call the fade effects here. :D
		Gui::fadeEffects();
	}
	// Exit all services and exit the app.
	Init::Exit();
	return 0;
}

Result Init::Exit() {
	Gui::exit();
	Gui::unloadSheet(sprites);
	gfxExit();
	cfguExit();
	romfsExit();
	return 0;
}