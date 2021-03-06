# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../Juce
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS) -std=c++11
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 

  TARGET := KentDAW
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../Juce
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os
  CXXFLAGS += $(CFLAGS) -std=c++11
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 

  TARGET := KentDAW
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/TimelineCursor_14235a1e.o \
  $(OBJDIR)/RegionComponent_16cc4137.o \
  $(OBJDIR)/TrackComponent_467eefee.o \
  $(OBJDIR)/MixerComponent_356b39f0.o \
  $(OBJDIR)/ChannelStripComponent_7b124736.o \
  $(OBJDIR)/MeterComponent_6c7c4a70.o \
  $(OBJDIR)/StatusBar_d572aa4f.o \
  $(OBJDIR)/LeftSidebar_43b7b4a3.o \
  $(OBJDIR)/ArrangeWindow_d578844a.o \
  $(OBJDIR)/BinaryData_6333ce47.o \
  $(OBJDIR)/MainComponent_4eca1cd2.o \
  $(OBJDIR)/TransportComponent_90926750.o \
  $(OBJDIR)/EQProcessor_aabe923f.o \
  $(OBJDIR)/MidiManager_b1275f25.o \
  $(OBJDIR)/AudioTrackFactory_b681268e.o \
  $(OBJDIR)/AudioRegionFactory_43999451.o \
  $(OBJDIR)/ChannelStripProcessor_1de3a096.o \
  $(OBJDIR)/AudioSourceProcessor_d46aa592.o \
  $(OBJDIR)/AudioMixer_72677d64.o \
  $(OBJDIR)/ProjectManager_bb0c2f65.o \
  $(OBJDIR)/SampleAudioRegion_9d0c3739.o \
  $(OBJDIR)/AudioRegion_3ad9a943.o \
  $(OBJDIR)/AudioTrack_62b571a6.o \
  $(OBJDIR)/SettingsManager_9e3ee3.o \
  $(OBJDIR)/AudioEngine_7532591.o \
  $(OBJDIR)/Main_90ebc5c2.o \
  $(OBJDIR)/juce_audio_basics_1e890073.o \
  $(OBJDIR)/juce_audio_devices_25f60471.o \
  $(OBJDIR)/juce_audio_formats_54774e11.o \
  $(OBJDIR)/juce_audio_processors_293bb72b.o \
  $(OBJDIR)/juce_audio_utils_c9347cb1.o \
  $(OBJDIR)/juce_core_978ecf55.o \
  $(OBJDIR)/juce_cryptography_200e03af.o \
  $(OBJDIR)/juce_data_structures_3126551.o \
  $(OBJDIR)/juce_events_a7cf8949.o \
  $(OBJDIR)/juce_graphics_868c9c2d.o \
  $(OBJDIR)/juce_gui_basics_f6dc2529.o \
  $(OBJDIR)/juce_gui_extra_39278cf1.o \
  $(OBJDIR)/juce_opengl_6817b175.o \
  $(OBJDIR)/juce_video_7afe3111.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(RESOURCES)
	@echo Linking KentDAW
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning KentDAW
	@$(CLEANCMD)

strip:
	@echo Stripping KentDAW
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/TimelineCursor_14235a1e.o: ../../Source/utils/TimelineCursor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TimelineCursor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/RegionComponent_16cc4137.o: ../../Source/ui/RegionComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling RegionComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TrackComponent_467eefee.o: ../../Source/ui/TrackComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TrackComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MixerComponent_356b39f0.o: ../../Source/ui/MixerComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MixerComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ChannelStripComponent_7b124736.o: ../../Source/ui/ChannelStripComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ChannelStripComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MeterComponent_6c7c4a70.o: ../../Source/ui/MeterComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MeterComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/StatusBar_d572aa4f.o: ../../Source/ui/StatusBar.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling StatusBar.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LeftSidebar_43b7b4a3.o: ../../Source/ui/LeftSidebar.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LeftSidebar.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ArrangeWindow_d578844a.o: ../../Source/ui/ArrangeWindow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ArrangeWindow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_6333ce47.o: ../../Source/ui/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainComponent_4eca1cd2.o: ../../Source/ui/MainComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TransportComponent_90926750.o: ../../Source/ui/TransportComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TransportComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/EQProcessor_aabe923f.o: ../../Source/core/EQProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling EQProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MidiManager_b1275f25.o: ../../Source/core/MidiManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MidiManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/AudioTrackFactory_b681268e.o: ../../Source/core/AudioTrackFactory.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling AudioTrackFactory.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/AudioRegionFactory_43999451.o: ../../Source/core/AudioRegionFactory.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling AudioRegionFactory.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ChannelStripProcessor_1de3a096.o: ../../Source/core/ChannelStripProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ChannelStripProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/AudioSourceProcessor_d46aa592.o: ../../Source/core/AudioSourceProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling AudioSourceProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/AudioMixer_72677d64.o: ../../Source/core/AudioMixer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling AudioMixer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ProjectManager_bb0c2f65.o: ../../Source/core/ProjectManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ProjectManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SampleAudioRegion_9d0c3739.o: ../../Source/core/SampleAudioRegion.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SampleAudioRegion.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/AudioRegion_3ad9a943.o: ../../Source/core/AudioRegion.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling AudioRegion.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/AudioTrack_62b571a6.o: ../../Source/core/AudioTrack.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling AudioTrack.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SettingsManager_9e3ee3.o: ../../Source/core/SettingsManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SettingsManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/AudioEngine_7532591.o: ../../Source/core/AudioEngine.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling AudioEngine.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Main_90ebc5c2.o: ../../Source/Main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Main.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_1e890073.o: ../../../Juce/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_devices_25f60471.o: ../../../Juce/juce_audio_devices/juce_audio_devices.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_54774e11.o: ../../../Juce/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_293bb72b.o: ../../../Juce/juce_audio_processors/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_utils_c9347cb1.o: ../../../Juce/juce_audio_utils/juce_audio_utils.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_utils.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_978ecf55.o: ../../../Juce/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_cryptography_200e03af.o: ../../../Juce/juce_cryptography/juce_cryptography.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_cryptography.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_3126551.o: ../../../Juce/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_a7cf8949.o: ../../../Juce/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_868c9c2d.o: ../../../Juce/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_f6dc2529.o: ../../../Juce/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_39278cf1.o: ../../../Juce/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_opengl_6817b175.o: ../../../Juce/juce_opengl/juce_opengl.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_opengl.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_video_7afe3111.o: ../../../Juce/juce_video/juce_video.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_video.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
