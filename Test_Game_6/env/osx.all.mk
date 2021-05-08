CC := clang++
CFLAGS := $(CFLAGS:-s=)

LIB_DIRS := \
	/usr/local/lib

INCLUDE_DIRS := \
	/usr/local/include

BUILD_FLAGS :=

MACOS_FRAMEWORK_PATHS := \
	/Library/Frameworks

# Name, no extension (eg. CoreFoundation, ogg)
MACOS_FRAMEWORKS := \
	CoreFoundation

# Icon .png
PRODUCTION_MACOS_ICON := sfml

PRODUCTION_DEPENDENCIES := \
	$(PRODUCTION_DEPENDENCIES)

PRODUCTION_MACOS_BUNDLE_DEVELOPER := iCoder
PRODUCTION_MACOS_BUNDLE_DISPLAY_NAME := Test_Game_6
PRODUCTION_MACOS_BUNDLE_NAME := Test_Game_6
PRODUCTION_MACOS_MAKE_DMG := true
PRODUCTION_MACOS_BACKGROUND := dmg-background

PRODUCTION_MACOS_DYLIBS := \
	/usr/local/lib/libsfml-graphics.2.5 \
	/usr/local/lib/libsfml-audio.2.5 \
	/usr/local/lib/libsfml-network.2.5 \
	/usr/local/lib/libsfml-window.2.5 \
	/usr/local/lib/libsfml-system.2.5

# Path, no extension (eg. /Library/Frameworks/ogg)
PRODUCTION_MACOS_FRAMEWORKS := \
	/Library/Frameworks/freetype \
	/Library/Frameworks/OpenAL \
	/Library/Frameworks/vorbis \
	/Library/Frameworks/vorbisfile \
	/Library/Frameworks/vorbisenc \
	/Library/Frameworks/ogg \
	/Library/Frameworks/FLAC

