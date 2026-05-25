#pragma once
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"
class VelvetAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
    VelvetAudioProcessorEditor(VelvetAudioProcessor&);
    ~VelvetAudioProcessorEditor() override;
    void paint(juce::Graphics&) override;
    void resized() override;
private:
    VelvetAudioProcessor& processorRef;
    VelvetLookAndFeel lnf;
    juce::Slider knob_INPUT_GAIN;
    juce::Label lbl_INPUT_GAIN;
    juce::AudioProcessorValueTreeState::SliderAttachment att_INPUT_GAIN;
    juce::Slider knob_GAIN_GAIN_DB_T2EC;
    juce::Label lbl_GAIN_GAIN_DB_T2EC;
    juce::AudioProcessorValueTreeState::SliderAttachment att_GAIN_GAIN_DB_T2EC;
    juce::Slider knob_DELAY_DELAY_MS_KENU;
    juce::Label lbl_DELAY_DELAY_MS_KENU;
    juce::AudioProcessorValueTreeState::SliderAttachment att_DELAY_DELAY_MS_KENU;
    juce::Slider knob_DELAY_FEEDBACK_KENU;
    juce::Label lbl_DELAY_FEEDBACK_KENU;
    juce::AudioProcessorValueTreeState::SliderAttachment att_DELAY_FEEDBACK_KENU;
    juce::Slider knob_DELAY_MIX_KENU;
    juce::Label lbl_DELAY_MIX_KENU;
    juce::AudioProcessorValueTreeState::SliderAttachment att_DELAY_MIX_KENU;
    juce::Slider knob_COMPRESSOR_THRESHOLD_WOR8;
    juce::Label lbl_COMPRESSOR_THRESHOLD_WOR8;
    juce::AudioProcessorValueTreeState::SliderAttachment att_COMPRESSOR_THRESHOLD_WOR8;
    juce::Slider knob_COMPRESSOR_RATIO_WOR8;
    juce::Label lbl_COMPRESSOR_RATIO_WOR8;
    juce::AudioProcessorValueTreeState::SliderAttachment att_COMPRESSOR_RATIO_WOR8;
    juce::Slider knob_COMPRESSOR_ATTACK_WOR8;
    juce::Label lbl_COMPRESSOR_ATTACK_WOR8;
    juce::AudioProcessorValueTreeState::SliderAttachment att_COMPRESSOR_ATTACK_WOR8;
    juce::Slider knob_COMPRESSOR_RELEASE_WOR8;
    juce::Label lbl_COMPRESSOR_RELEASE_WOR8;
    juce::AudioProcessorValueTreeState::SliderAttachment att_COMPRESSOR_RELEASE_WOR8;
    juce::Slider knob_COMPRESSOR_MAKEUP_WOR8;
    juce::Label lbl_COMPRESSOR_MAKEUP_WOR8;
    juce::AudioProcessorValueTreeState::SliderAttachment att_COMPRESSOR_MAKEUP_WOR8;
    juce::Slider knob_OUTPUT_GAIN;
    juce::Label lbl_OUTPUT_GAIN;
    juce::AudioProcessorValueTreeState::SliderAttachment att_OUTPUT_GAIN;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VelvetAudioProcessorEditor)
};
