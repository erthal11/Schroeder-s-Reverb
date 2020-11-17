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
    setSize (800, 300);

    
    sizeSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sizeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    sizeSlider.addListener(this);
    addAndMakeVisible(&sizeSlider);
    
    sizeValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "size", sizeSlider);
    
    sizeLabel.attachToComponent(&sizeSlider, false);
    sizeLabel.setText("Size", juce::dontSendNotification);
    sizeLabel.setJustificationType(juce::Justification::centred);
    
    
    decaySlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    decaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    decaySlider.addListener(this);
    addAndMakeVisible(&decaySlider);
    
    decayValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "decay", decaySlider);
    
    decayLabel.attachToComponent(&decaySlider, false);
    decayLabel.setText("Decay", juce::dontSendNotification);
    decayLabel.setJustificationType(juce::Justification::centred);

    
    outASlider.setSliderStyle(juce::Slider::LinearVertical);
    outASlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    outASlider.addListener(this);
    addAndMakeVisible(&outASlider);
    
    outAValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "outA", outASlider);
    
    outALabel.attachToComponent(&outASlider, false);
    outALabel.setText("Output A", juce::dontSendNotification);
    outALabel.setJustificationType(juce::Justification::centred);

    
    
    outBSlider.setSliderStyle(juce::Slider::LinearVertical);
    outBSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    outBSlider.addListener(this);
    addAndMakeVisible(&outBSlider);
    
    outBValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "outB", outBSlider);
    
    outBLabel.attachToComponent(&outBSlider, false);
    outBLabel.setText("Output B", juce::dontSendNotification);
    outBLabel.setJustificationType(juce::Justification::centred);

    
    outCSlider.setSliderStyle(juce::Slider::LinearVertical);
    outCSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    outCSlider.addListener(this);
    addAndMakeVisible(&outCSlider);
    
    outCValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "outC", outCSlider);
    
    outCLabel.attachToComponent(&outCSlider, false);
    outCLabel.setText("Output C", juce::dontSendNotification);
    outCLabel.setJustificationType(juce::Justification::centred);

    
    outDSlider.setSliderStyle(juce::Slider::LinearVertical);
    outDSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    outDSlider.addListener(this);
    addAndMakeVisible(&outDSlider);
    
    outDValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "outD", outDSlider);
    
    outDLabel.attachToComponent(&outDSlider, false);
    outDLabel.setText("Output D", juce::dontSendNotification);
    outDLabel.setJustificationType(juce::Justification::centred);

    
    mixSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    mixSlider.addListener(this);
    addAndMakeVisible(&mixSlider);
    
    mixValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "mix", mixSlider);
    
    mixLabel.attachToComponent(&mixSlider, false);
    mixLabel.setText("Mix", juce::dontSendNotification);
    mixLabel.setJustificationType(juce::Justification::centred);

    
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
    
    sizeSlider.setBounds(10, getHeight()/2, 110, 110);
    decaySlider.setBounds(110, getHeight()/2, 110, 110);
    outASlider.setBounds(220, getHeight()/2, 110, 110);
    outBSlider.setBounds(330, getHeight()/2, 110, 110);
    outCSlider.setBounds(440, getHeight()/2, 110, 110);
    outDSlider.setBounds(550, getHeight()/2, 110, 110);
    mixSlider.setBounds(660, getHeight()/2, 110, 110);
}

void ReverbAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{


}
