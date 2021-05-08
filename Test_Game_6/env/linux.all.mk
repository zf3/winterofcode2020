CC := g++
CFLAGS := $(CFLAGS) -fpic

LIB_DIRS := \
	/usr/local/lib

INCLUDE_DIRS := \
	/usr/local/include

BUILD_FLAGS := \
	$(BUILD_FLAGS) \
	-pthread

LINK_LIBRARIES := \
	$(LINK_LIBRARIES) \
	stdc++fs \
	X11

PRODUCTION_LINUX_ICON := sfml

PRODUCTION_LINUX_APP_NAME := Test_Game_6
PRODUCTION_LINUX_APP_COMMENT := My SFML Game
