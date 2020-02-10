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

#include "fileList.hpp"

extern bool touching(touchPosition touch, Structs::ButtonPos button);

std::vector<std::string> exampleVector = {"Entry 1", "Entry 2", "Entry 3", "Entry 4", "Entry 5", "Entry 6", "Entry 7", "Entry 8"};

void FileList::Draw(void) const
{
	std::string fileList;
	GFX::DrawFileBrowseBG();
	Gui::DrawStringCentered(0, 2, 0.8f, WHITE, "Universal-Core Example -> FileList", 400);

	for (int i = (Selection<5) ? 0 : Selection-5;i< (int)exampleVector.size() && i <((Selection<5) ? 6 : Selection+1);i++) {
		if (i == Selection) {
			fileList += "> " + exampleVector[i] + "\n\n";
		} else {
			fileList += exampleVector[i] + "\n\n";
		}
	}
	for (int i=0;i<(((int)exampleVector.size()<6) ? 6-(int)exampleVector.size() : 0);i++) {
		fileList += "\n\n";
	}
	Gui::DrawString(26, 32, 0.52f, WHITE, fileList, 360);
	Gui::DrawStringCentered(0, 216, 0.8f, WHITE, "Entry Amount: " + std::to_string((int)exampleVector.size()), 400);
	GFX::DrawFileBrowseBG(false);
}


void FileList::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_B) {
		Gui::screenBack();
		return;
	}

	if (hDown & KEY_DOWN) {
		if (Selection < (int)exampleVector.size()-1)	Selection++;
	}
	if (hDown & KEY_UP) {
		if (Selection > 0)	Selection--;
	}
}