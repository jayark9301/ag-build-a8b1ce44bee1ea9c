#pragma once
#include <JuceHeader.h>
class VelvetAudioProcessor : public juce::AudioProcessor {
public:
    VelvetAudioProcessor();
    ~VelvetAudioProcessor() override;
    void prepareToPlay(double, int) override;
    void releaseResources() override;
    bool isBusesLayoutSupported(const BusesLayout&) const override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }
    const juce::String getName() const override { return "Velvet"; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    double getTailLengthSeconds() const override { return 2.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}
    void getStateInformation(juce::MemoryBlock&) override;
    void setStateInformation(const void*, int) override;
    juce::AudioProcessorValueTreeState apvts;
private:
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    double currentSampleRate = 44100.0;
    juce::dsp::Gain<float> gain_T2EC;
    juce::dsp::DelayLine<float,juce::dsp::DelayLineInterpolationTypes::Lagrange3rd> delay_KENU { 96000 };
    juce::dsp::DryWetMixer<float> delayMix_KENU;
    juce::dsp::Compressor<float> comp_WOR8;
    juce::dsp::Gain<float> compMakeup_WOR8;
    juce::dsp::Gain<float> inputGainDsp, outputGainDsp;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VelvetAudioProcessor)
};
