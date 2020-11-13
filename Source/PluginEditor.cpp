/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ReverbAudioProcessorEditor::ReverbAudioProcessorEditor (ReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    allPassFBSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    allPassFBSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    allPassFBSlider.addListener(this);
    addAndMakeVisible(&allPassFBSlider);
    
    allPassFBValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "apfb", allPassFBSlider);
    
    decaySlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    decaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    decaySlider.addListener(this);
    addAndMakeVisible(&decaySlider);
    
    decayValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "decay", decaySlider);
    
    mixSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    mixSlider.addListener(this);
    addAndMakeVisible(&mixSlider);
    
    mixValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "mix", mixSlider);
    
    
}

ReverbAudioProcessorEditor::~ReverbAudioProcessorEditor()
{
}

//==============================================================================
void ReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    
}

void ReverbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    allPassFBSlider.setBounds(10, getHeight()/2, 110, 110);
    
    decaySlider.setBounds(100, getHeight()/2, 110, 110);
    
    mixSlider.setBounds(210, getHeight()/2, 110, 110);
}

void ReverbAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{


}
