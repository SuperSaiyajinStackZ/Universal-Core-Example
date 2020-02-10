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
// Screens.
#include "buttons.hpp"
#include "fileList.hpp"
#include "mainMenu.hpp"

extern bool touching(touchPosition touch, Structs::ButtonPos button);
extern bool exiting;

void MainMenu::Draw(void) const
{
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 2, 0.8f, WHITE, "Universal-Core Example -> MainMenu", 400);
	GFX::DrawSprite(sprites_test_idx, 27, 33);
	GFX::DrawBottom();
	// Draw Buttons. ;P
	for (int i = 0; i < (int)mainButtons.size(); i++) {
		if (Selection == i) {
			Gui::Draw_Rect(mainButtons[i].x, mainButtons[i].y, mainButtons[i].w, mainButtons[i].h, C2D_Color32(0, 170, 170, 255));
		} else {
			Gui::Draw_Rect(mainButtons[i].x, mainButtons[i].y, mainButtons[i].w, mainButtons[i].h, C2D_Color32(0, 170, 100, 255));
		}
	}
	Gui::DrawStringCentered(0, mainButtons[0].y+10, 0.6f, WHITE, "FileList Example");
	Gui::DrawStringCentered(0, mainButtons[1].y+10, 0.6f, WHITE, "Buttons Example");
	Gui::DrawStringCentered(0, mainButtons[2].y+10, 0.6f, WHITE, "?");
}


void MainMenu::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	// Press Start to exit the app.
	if (hDown & KEY_START) {
		exiting = true;
	}

	// Press <A> on a Button to enter example screen.
	if (hDown & KEY_A) {
		if (Selection == 0) {
			Gui::setScreen(std::make_unique<FileList>());
		} else if (Selection == 1) {
			Gui::setScreen(std::make_unique<Buttons>());
		}
	}

	// Touch the button to enter example screen.
	if (hDown & KEY_TOUCH) {
		if (touching(touch, mainButtons[0])) {
			Gui::setScreen(std::make_unique<FileList>());
		} else if (touching(touch, mainButtons[1])) {
			Gui::setScreen(std::make_unique<Buttons>());
		}
	}

	// Press Down to go one entry down. - 1 -> Because we don't want to go one Entry after the actual Buttons.
	if (hDown & KEY_DOWN) {
		if (Selection < (int)mainButtons.size() - 1)	Selection++;
	}

	// Press Up to go one entry up.
	if (hDown & KEY_UP) {
		if (Selection > 0)	Selection--;
	}
}