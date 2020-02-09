# Universal-Core-Example
An example for the use of [Universal-Core](https://github.com/Universal-Team/Universal-Core).

## Adding the Submodule
First of all, you need to do `git submodule add https://github.com/Universal-Team/Universal-Core.git`. This add's the Universal-Core as a submodule to your project.

## What you need?
- Latest devkitARM, Libctru, Citro2D & Citro3D.
- `-std=gnu++17` inside the CXXFLAGS.
- `-D_GNU_SOURCE=1` inside the CFLAGS.

## How to use it
You need at least `Gui::init();` and `Gui::exit();` to use Universal-Core.

I did that inside the `init.cpp` file, because `init.cpp` makes kinda more sense to initialize everything and exit.

You like to use Spritesheets? No problem! Do the following:
```
// Define the Spritesheet here.
C2D_SpriteSheet <SpriteSheetName>;

// Loading the Spritesheet. (Better do it by initializing or so.)
Gui::loadSheet(<Path to the Sheet>, <SpriteSheetName>);

// Of course don't forget to unload the sheet at the end!
Gui::unloadSheet(<SpriteSheetname>);
``` 

More little examples will be added soon.