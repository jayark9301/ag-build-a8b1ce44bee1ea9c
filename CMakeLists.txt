cmake_minimum_required(VERSION 3.15)
project(Velvet VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
include(FetchContent)
FetchContent_Declare(JUCE
  GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
  GIT_TAG        7.0.9
  GIT_SHALLOW    TRUE)
FetchContent_MakeAvailable(JUCE)
juce_add_plugin(Velvet
    COMPANY_NAME "Archergate"
    IS_SYNTH FALSE NEEDS_MIDI_INPUT FALSE NEEDS_MIDI_OUTPUT FALSE IS_MIDI_EFFECT FALSE
    PLUGIN_MANUFACTURER_CODE VELV
    PLUGIN_CODE TEVL
    FORMATS VST3 Standalone
    PRODUCT_NAME "Velvet")
juce_generate_juce_header(Velvet)
target_sources(Velvet PRIVATE Source/PluginProcessor.cpp Source/PluginEditor.cpp)
target_compile_definitions(Velvet PUBLIC JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0 JUCE_VST3_CAN_REPLACE_VST2=0)
target_link_libraries(Velvet PRIVATE juce::juce_audio_utils juce::juce_dsp juce::juce_recommended_config_flags)
