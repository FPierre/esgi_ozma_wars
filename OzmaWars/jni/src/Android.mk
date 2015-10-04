LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../sdl
# https://www.libsdl.org/projects/SDL_ttf/
# http://www.dinomage.com/2013/05/howto-sdl-on-android-part-3-native-libraries/
SDL_TTF_PATH := ../sdl_ttf

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
                    $(LOCAL_PATH)/$(SDL_TTF_PATH)

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	main.cpp sources/Game.cpp sources/Window.cpp sources/Rgb.cpp sources/Sprite.cpp sources/Weapon.cpp sources/Ship.cpp sources/GameState.cpp sources/LevelOne.cpp sources/LevelTwo.cpp

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_ttf

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
