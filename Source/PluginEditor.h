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
    
    void sliderValueChanged (juce::Slider* sliderGain) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ReverbAudioProcessor& audioProcessor;

    juce::Slider sizeSlider;
    juce::Slider decaySlider;
    
    juce::Slider outASlider;
    juce::Slider outBSlider;
    juce::Slider outCSlider;
    juce::Slider outDSlider;
    
    juce::Slider mixSlider;
    
    juce::Label sizeLabel;
    juce::Label decayLabel;
    juce::Label outALabel;
    juce::Label outBLabel;
    juce::Label outCLabel;
    juce::Label outDLabel;
    juce::Label mixLabel;

    
    
public:
    
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> sizeValue;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> decayValue;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> outAValue;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> outBValue;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> outCValue;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> outDValue;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> mixValue;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbAudioProcessorEditor)
};
