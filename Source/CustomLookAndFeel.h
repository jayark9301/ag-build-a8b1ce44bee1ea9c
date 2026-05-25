#pragma once
#include <JuceHeader.h>
class VelvetLookAndFeel : public juce::LookAndFeel_V4 {
public:
    VelvetLookAndFeel() {
        setColour(juce::Slider::thumbColourId,juce::Colour(0xff4d8bff));
        setColour(juce::Slider::rotarySliderFillColourId,juce::Colour(0xff4d8bff));
        setColour(juce::Slider::rotarySliderOutlineColourId,juce::Colour(0x40ffffff));
        setColour(juce::Label::textColourId,juce::Colour(0xffe8eaf0));
        setColour(juce::ResizableWindow::backgroundColourId,juce::Colour(0xff0d1117));
        setColour(juce::Slider::textBoxTextColourId,juce::Colour(0xffe8eaf0));
        setColour(juce::Slider::textBoxBackgroundColourId,juce::Colours::transparentBlack);
        setColour(juce::Slider::textBoxOutlineColourId,juce::Colours::transparentBlack);
        setColour(juce::Slider::textBoxHighlightColourId,juce::Colour(0x40ffffff));
    }
    void drawRotarySlider(juce::Graphics& g,int x,int y,int w,int h,float pos,float sa,float ea,juce::Slider& sl) override {
        float r=juce::jmin(w*.5f,h*.5f)-4.f,cx=x+w*.5f,cy=y+h*.5f,angle=sa+pos*(ea-sa);
        g.setColour(juce::Colour(0xff1a1a1a)); g.fillEllipse(cx-r,cy-r,r*2.f,r*2.f);
        juce::Path bg,fill;
        bg.addArc(cx-r,cy-r,r*2,r*2,sa,ea,true); g.setColour(sl.findColour(juce::Slider::rotarySliderOutlineColourId)); g.strokePath(bg,juce::PathStrokeType(3.5f,juce::PathStrokeType::curved,juce::PathStrokeType::rounded));
        fill.addArc(cx-r,cy-r,r*2,r*2,sa,angle,true); g.setColour(sl.findColour(juce::Slider::rotarySliderFillColourId)); g.strokePath(fill,juce::PathStrokeType(3.5f,juce::PathStrokeType::curved,juce::PathStrokeType::rounded));
        float tx=cx+(r-6)*std::cos(angle-juce::MathConstants<float>::halfPi),ty=cy+(r-6)*std::sin(angle-juce::MathConstants<float>::halfPi);
        g.setColour(sl.findColour(juce::Slider::thumbColourId)); g.fillEllipse(tx-2.5f,ty-2.5f,5.f,5.f);
    }
    void drawLabel(juce::Graphics& g,juce::Label& lbl) override {
        if(lbl.isBeingEdited()) return;
        g.setColour(lbl.findColour(juce::Label::textColourId));
        g.setFont(lbl.getFont());
        g.drawFittedText(lbl.getText(),lbl.getLocalBounds().reduced(1),juce::Justification::centred,1);
    }
};
