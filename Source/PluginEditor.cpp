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
    setSize (950, 450);
    
    auto schroederImage = juce::ImageCache::getFromMemory (BinaryData::image_png, BinaryData::image_pngSize);
        
        if (! schroederImage.isNull())
            imageComponent.setImage (schroederImage, juce::RectanglePlacement::stretchToFit);
        else
            jassert (! schroederImage.isNull());
    
    addAndMakeVisible(imageComponent);

    
    sizeSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sizeSlider.getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::white);
    sizeSlider.getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::whitesmoke);
    sizeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    sizeSlider.addListener(this);
    addAndMakeVisible(&sizeSlider);
    
    sizeValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "size", sizeSlider);
    
    sizeLabel.attachToComponent(&sizeSlider, false);
    sizeLabel.setText("+ Size", juce::dontSendNotification);
    sizeLabel.setJustificationType(juce::Justification::centred);
    
    
    decaySlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    decaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    decaySlider.addListener(this);
    addAndMakeVisible(&decaySlider);
    
    decayValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "decay", decaySlider);
    
    decayLabel.attachToComponent(&decaySlider, false);
    decayLabel.setText("+ Decay", juce::dontSendNotification);
    decayLabel.setJustificationType(juce::Justification::centred);

    
    outASlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    outASlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    outASlider.addListener(this);
    addAndMakeVisible(&outASlider);
    
    outAValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "outA", outASlider);
    
    outALabel.attachToComponent(&outASlider, false);
    outALabel.setText("Output A", juce::dontSendNotification);
    outALabel.setJustificationType(juce::Justification::centred);

    
    
    outBSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    outBSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    outBSlider.addListener(this);
    addAndMakeVisible(&outBSlider);
    
    outBValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "outB", outBSlider);
    
    outBLabel.attachToComponent(&outBSlider, false);
    outBLabel.setText("Output B", juce::dontSendNotification);
    outBLabel.setJustificationType(juce::Justification::centred);

    
    outCSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    outCSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    outCSlider.addListener(this);
    addAndMakeVisible(&outCSlider);
    
    outCValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "outC", outCSlider);
    
    outCLabel.attachToComponent(&outCSlider, false);
    outCLabel.setText("Output C", juce::dontSendNotification);
    outCLabel.setJustificationType(juce::Justification::centred);

    
    outDSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
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
   // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colours::black);

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawText("Schroeder Reverb", 400, 10, 400, 20, 0);
    
}

void ReverbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    imageComponent.setBounds(125, 25, 700, 230);
    
    sizeSlider.setBounds(20, 305, 125, 125);
    decaySlider.setBounds(150, 305, 125, 125);
    outASlider.setBounds(280, 305, 125, 125);
    outBSlider.setBounds(410, 305, 125, 125);
    outCSlider.setBounds(540, 305, 125, 125);
    outDSlider.setBounds(670, 305, 125, 125);
    mixSlider.setBounds(800, 305, 125, 125);
}

void ReverbAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{


}
