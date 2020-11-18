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

    
    outASlider.setSliderStyle(juce::Slider::LinearHorizontal);
    outASlider.getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::white);
    outASlider.getLookAndFeel().setColour(juce::Slider::trackColourId, juce::Colours::white);
    outASlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 40, 25);
    outASlider.addListener(this);
    addAndMakeVisible(&outASlider);
    
    outAValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "outA", outASlider);

    
    
    outBSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    outBSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 40, 25);
    outBSlider.addListener(this);
    addAndMakeVisible(&outBSlider);
    
    outBValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "outB", outBSlider);

    
    outCSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    outCSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 40, 25);
    outCSlider.addListener(this);
    addAndMakeVisible(&outCSlider);
    
    outCValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "outC", outCSlider);

    
    outDSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    outDSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 40, 25);
    outDSlider.addListener(this);
    addAndMakeVisible(&outDSlider);
    
    outDValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "outD", outDSlider);
    
    

    
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
    g.drawText("Schroeder Reverb", 150, 10, 400, 20, 0);
    
}

void ReverbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    imageComponent.setBounds(20, 25, 700, 230);
    
    outASlider.setBounds(720, 35, 210, 50);
    outBSlider.setBounds(720, 92.5, 210, 50);
    outCSlider.setBounds(720, 150, 210, 50);
    outDSlider.setBounds(720, 207.5, 210, 50);
    
    sizeSlider.setBounds(250, 305, 125, 125);
    decaySlider.setBounds(400, 305, 125, 125);
    mixSlider.setBounds(550, 305, 125, 125);
}

void ReverbAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{


}
