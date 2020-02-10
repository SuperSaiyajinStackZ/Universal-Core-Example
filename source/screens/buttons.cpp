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

#include "buttons.hpp"

extern bool touching(touchPosition touch, Structs::ButtonPos button);

void Buttons::Draw(void) const
{
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 2, 0.8f, WHITE, "Universal-Core Example -> Buttons", 400);
	GFX::DrawBottom();
	// Draw Buttons.
	for (int i = 0; i < (int)buttons.size(); i++) {
		if (Selection == i) {
			Gui::Draw_Rect(buttons[i].x, buttons[i].y, buttons[i].w, buttons[i].h, C2D_Color32(0, 170, 170, 255));
		} else {
			Gui::Draw_Rect(buttons[i].x, buttons[i].y, buttons[i].w, buttons[i].h, C2D_Color32(0, 170, 100, 255));
		}
	}
}


void Buttons::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_B) {
		Gui::screenBack();
		return;
	}

	if (hDown & KEY_DOWN) {
		if (Selection < (int)buttons.size()/2-1 || Selection < (int)buttons.size()-1)	Selection++;
	}

	if (hDown & KEY_RIGHT) {
		if (Selection < (int)buttons.size()/2)	Selection += 3;
	}

	if (hDown & KEY_LEFT) {
		if (Selection > (int)buttons.size()/2-1)	Selection -= 3;
	}

	if (hDown & KEY_UP) {
		if (Selection > 0)	Selection--;
	}
}