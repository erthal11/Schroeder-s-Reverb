/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ReverbAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                    public juce::Slider::Listener
{
public:
    ReverbAudioProcessorEditor (ReverbAudioProcessor&);
    ~ReverbAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ReverbAudioProcessor& audioProcessor;

    juce::Slider sizeSlider;
    juce::Slider mixSlider;
    
//    juce::Slider outA;
//    juce::Slider outB;
//    juce::Slider outC;
//    juce::Slider outD;
    
    void sliderValueChanged (juce::Slider* sliderGain) override;
    
public:
    
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> sizeValue;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> mixValue;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbAudioProcessorEditor)
};
