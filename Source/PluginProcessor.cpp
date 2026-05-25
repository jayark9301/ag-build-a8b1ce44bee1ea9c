#include "PluginProcessor.h"
#include "PluginEditor.h"
VelvetAudioProcessor::VelvetAudioProcessor()
    : AudioProcessor(BusesProperties().withInput("Input",juce::AudioChannelSet::stereo()).withOutput("Output",juce::AudioChannelSet::stereo())),
      apvts(*this,nullptr,"Parameters",createParameterLayout()) {}
VelvetAudioProcessor::~VelvetAudioProcessor() {}
juce::AudioProcessorValueTreeState::ParameterLayout VelvetAudioProcessor::createParameterLayout() {
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add(std::make_unique<juce::AudioParameterFloat>("INPUT_GAIN","Input Gain",juce::NormalisableRange<float>(-24.0f,24.0f,0.01f),0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("OUTPUT_GAIN","Output Gain",juce::NormalisableRange<float>(-24.0f,24.0f,0.01f),0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("GAIN_GAIN_DB_T2EC","Gain Gain",juce::NormalisableRange<float>(-24.0f,24.0f,0.01f),0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("DELAY_DELAY_MS_KENU","Delay Time",juce::NormalisableRange<float>(1.0f,2000.0f,0.01f),250.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("DELAY_FEEDBACK_KENU","Delay Feedback",juce::NormalisableRange<float>(0.0f,95.0f,0.01f),40.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("DELAY_MIX_KENU","Delay Mix",juce::NormalisableRange<float>(0.0f,100.0f,0.01f),30.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("COMPRESSOR_THRESHOLD_WOR8","Compressor Threshold",juce::NormalisableRange<float>(-60.0f,0.0f,0.01f),-18.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("COMPRESSOR_RATIO_WOR8","Compressor Ratio",juce::NormalisableRange<float>(1.0f,20.0f,0.1f),4.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("COMPRESSOR_ATTACK_WOR8","Compressor Attack",juce::NormalisableRange<float>(0.1f,200.0f,0.01f),10.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("COMPRESSOR_RELEASE_WOR8","Compressor Release",juce::NormalisableRange<float>(10.0f,2000.0f,0.01f),150.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("COMPRESSOR_MAKEUP_WOR8","Compressor Makeup",juce::NormalisableRange<float>(0.0f,24.0f,0.01f),0.0f));
    return layout;
}
void VelvetAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    currentSampleRate = sampleRate;
    juce::dsp::ProcessSpec spec;
    spec.sampleRate=(uint32_t)sampleRate; spec.maximumBlockSize=(uint32_t)samplesPerBlock; spec.numChannels=(uint32_t)getTotalNumOutputChannels();
    inputGainDsp.prepare(spec); inputGainDsp.setGainDecibels(0.0f);
    outputGainDsp.prepare(spec); outputGainDsp.setGainDecibels(0.0f);
    gain_T2EC.prepare(spec); gain_T2EC.setGainDecibels(0.0f);
    delay_KENU.prepare(spec); delay_KENU.setMaximumDelayInSamples((int)(spec.sampleRate*2.0)); delayMix_KENU.prepare(spec); delayMix_KENU.setWetMixProportion(0.3f);
    comp_WOR8.prepare(spec); comp_WOR8.setThreshold(-18.0f); comp_WOR8.setRatio(4.0f); comp_WOR8.setAttack(10.0f); comp_WOR8.setRelease(150.0f); compMakeup_WOR8.prepare(spec); compMakeup_WOR8.setGainDecibels(0.0f);
}
void VelvetAudioProcessor::releaseResources() {}
bool VelvetAudioProcessor::isBusesLayoutSupported(const BusesLayout& l) const {
    return l.getMainOutputChannelSet()==juce::AudioChannelSet::stereo()&&l.getMainInputChannelSet()==juce::AudioChannelSet::stereo();
}
void VelvetAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) {
    juce::ScopedNoDenormals noDenormals;
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    inputGainDsp.setGainDecibels(*apvts.getRawParameterValue("INPUT_GAIN")); inputGainDsp.process(context);
    gain_T2EC.setGainDecibels(*apvts.getRawParameterValue("GAIN_GAIN_DB_T2EC")); gain_T2EC.process(context);
    { delay_KENU.setDelay((float)(*apvts.getRawParameterValue("DELAY_DELAY_MS_KENU")*currentSampleRate/1000.0)); delayMix_KENU.setWetMixProportion(*apvts.getRawParameterValue("DELAY_MIX_KENU")/100.0f); delayMix_KENU.pushDrySamples(block); delay_KENU.process(context); delayMix_KENU.mixWetSamples(block); }
    comp_WOR8.setThreshold(*apvts.getRawParameterValue("COMPRESSOR_THRESHOLD_WOR8")); comp_WOR8.setRatio(*apvts.getRawParameterValue("COMPRESSOR_RATIO_WOR8")); comp_WOR8.setAttack(*apvts.getRawParameterValue("COMPRESSOR_ATTACK_WOR8")); comp_WOR8.setRelease(*apvts.getRawParameterValue("COMPRESSOR_RELEASE_WOR8")); compMakeup_WOR8.setGainDecibels(*apvts.getRawParameterValue("COMPRESSOR_MAKEUP_WOR8")); comp_WOR8.process(context); compMakeup_WOR8.process(context);
    outputGainDsp.setGainDecibels(*apvts.getRawParameterValue("OUTPUT_GAIN")); outputGainDsp.process(context);
}
void VelvetAudioProcessor::getStateInformation(juce::MemoryBlock& d) {
    auto s=apvts.copyState(); std::unique_ptr<juce::XmlElement> xml(s.createXml()); copyXmlToBinary(*xml,d);
}
void VelvetAudioProcessor::setStateInformation(const void* d,int sz) {
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(d,sz));
    if(xml&&xml->hasTagName(apvts.state.getType())) apvts.replaceState(juce::ValueTree::fromXml(*xml));
}
juce::AudioProcessorEditor* VelvetAudioProcessor::createEditor() { return new VelvetAudioProcessorEditor(*this); }
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new VelvetAudioProcessor(); }
