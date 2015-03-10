# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ifeq ($(TARGET_ARCH_ABI), armeabi-v7a)
    LOCAL_ARM_MODE := arm
endif

LOCAL_MODULE := juce_jni
LOCAL_SRC_FILES := \
  ../../../Source/Main.cpp\
  ../../../../Juce/juce_audio_basics/juce_audio_basics.cpp\
  ../../../../Juce/juce_audio_devices/juce_audio_devices.cpp\
  ../../../../Juce/juce_audio_formats/juce_audio_formats.cpp\
  ../../../../Juce/juce_audio_processors/juce_audio_processors.cpp\
  ../../../../Juce/juce_core/juce_core.cpp\
  ../../../../Juce/juce_cryptography/juce_cryptography.cpp\
  ../../../../Juce/juce_data_structures/juce_data_structures.cpp\
  ../../../../Juce/juce_events/juce_events.cpp\
  ../../../../Juce/juce_graphics/juce_graphics.cpp\
  ../../../../Juce/juce_gui_basics/juce_gui_basics.cpp\
  ../../../../Juce/juce_gui_extra/juce_gui_extra.cpp\
  ../../../../Juce/juce_opengl/juce_opengl.cpp\
  ../../../../Juce/juce_video/juce_video.cpp\

ifeq ($(NDK_DEBUG),1)
  LOCAL_CPPFLAGS += -fsigned-char -fexceptions -frtti -g -I "../../JuceLibraryCode" -I "../../../Juce" -O0 -std=c++11 -std=gnu++11 -D "JUCE_ANDROID=1" -D "JUCE_ANDROID_API_VERSION=8" -D "JUCE_ANDROID_ACTIVITY_CLASSNAME=com_yourcompany_kentdaw_KentDAW" -D JUCE_ANDROID_ACTIVITY_CLASSPATH=\"com/yourcompany/kentdaw/KentDAW\" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_ANDROID_7F0E4A25=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000"
  LOCAL_LDLIBS := -llog -lGLESv2
  LOCAL_CFLAGS += -fsigned-char -fexceptions -frtti -g -I "../../JuceLibraryCode" -I "../../../Juce" -O0 -std=c++11 -std=gnu++11 -D "JUCE_ANDROID=1" -D "JUCE_ANDROID_API_VERSION=8" -D "JUCE_ANDROID_ACTIVITY_CLASSNAME=com_yourcompany_kentdaw_KentDAW" -D JUCE_ANDROID_ACTIVITY_CLASSPATH=\"com/yourcompany/kentdaw/KentDAW\" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_ANDROID_7F0E4A25=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000"
  LOCAL_LDLIBS := -llog -lGLESv2
else
  LOCAL_CPPFLAGS += -fsigned-char -fexceptions -frtti -I "../../JuceLibraryCode" -I "../../../Juce" -Os -std=c++11 -std=gnu++11 -D "JUCE_ANDROID=1" -D "JUCE_ANDROID_API_VERSION=8" -D "JUCE_ANDROID_ACTIVITY_CLASSNAME=com_yourcompany_kentdaw_KentDAW" -D JUCE_ANDROID_ACTIVITY_CLASSPATH=\"com/yourcompany/kentdaw/KentDAW\" -D "NDEBUG=1" -D "JUCER_ANDROID_7F0E4A25=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000"
  LOCAL_LDLIBS := -llog -lGLESv2
  LOCAL_CFLAGS += -fsigned-char -fexceptions -frtti -I "../../JuceLibraryCode" -I "../../../Juce" -Os -std=c++11 -std=gnu++11 -D "JUCE_ANDROID=1" -D "JUCE_ANDROID_API_VERSION=8" -D "JUCE_ANDROID_ACTIVITY_CLASSNAME=com_yourcompany_kentdaw_KentDAW" -D JUCE_ANDROID_ACTIVITY_CLASSPATH=\"com/yourcompany/kentdaw/KentDAW\" -D "NDEBUG=1" -D "JUCER_ANDROID_7F0E4A25=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000"
  LOCAL_LDLIBS := -llog -lGLESv2
endif

include $(BUILD_SHARED_LIBRARY)
