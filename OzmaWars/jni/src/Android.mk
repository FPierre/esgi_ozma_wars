LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../sdl
# https://www.libsdl.org/projects/SDL_ttf/
# http://www.dinomage.com/2013/05/howto-sdl-on-android-part-3-native-libraries/
SDL_TTF_PATH := ../sdl_ttf
SDL_MIXER_PATH := ../sdl_mixer

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
                    $(LOCAL_PATH)/$(SDL_TTF_PATH) \
                    $(LOCAL_PATH)/$(SDL_MIXER_PATH)

LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
    main.cpp sources/EnemyShip.cpp sources/Game.cpp sources/Window.cpp sources/Rgb.cpp sources/Sprite.cpp sources/Weapon.cpp sources/Ship.cpp sources/GameState.cpp sources/LevelOne.cpp sources/LevelTwo.cpp sources/OwnShip.cpp sources/Meteorite.cpp

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_ttf SDL2_mixer

LOCAL_CFLAGS := -std=c++11

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

LOCAL_EXPORT_C_INCLUDES += $(LOCAL_C_INCLUDES)

include $(BUILD_SHARED_LIBRARY)
