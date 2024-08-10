#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

constexpr int SCREEN_WIDTH = 1280;
constexpr char VERSION_NUMBER[] = "v1.5";

constexpr float ASPECT_RATIO = 1.6f;
constexpr int SCREEN_HEIGHT = static_cast<int>(SCREEN_WIDTH / ASPECT_RATIO);

constexpr float SCALE_FACTOR = (int)SCREEN_WIDTH / 640;

#define COLOR_CYAN sf::Color(203, 251, 251, 255)
#define COLOR_LIGHT_YELLOW sf::Color(231, 231, 147, 255)
#define COLOR_STONE_BLUE sf::Color(0, 127, 163, 255)

constexpr float SPLASH_STATE_SHOW_TIME = 2.5f;

constexpr int TILE_SIZE = int(SCREEN_WIDTH / 40);

constexpr const float TRANSTION_TIME = 0.05f;

// Fonts
constexpr char FONT_MICROGRAMMA[] = "resources/fonts/MicrogrammaDExtendedBold.otf";
constexpr char FONT_THOMSON[] = "resources/fonts/Thomson.ttf";
constexpr char FONT_LODE_RUNNER[] = "resources/fonts/Lode_Runner_(C64).ttf";

// Textures
constexpr char SPRITESHEET[] = "resources/spritesheet.png";

// Sounds
constexpr char SOUND_BEEP[] = "resources/sfx/beep.wav";
constexpr char SOUND_HIT[] = "resources/sfx/hit.wav";
constexpr char SOUND_TICK[] = "resources/sfx/tick.wav";
constexpr char SOUND_WIN[] = "resources/sfx/win.wav";
constexpr char SOUND_BONUS[] = "resources/sfx/bonus.wav";
constexpr char SOUND_DIG[] = "resources/sfx/dig.wav";

#endif // !_DEFINITIONS_H_
