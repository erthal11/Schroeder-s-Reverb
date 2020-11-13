/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ReverbAudioProcessor::ReverbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
treeState (*this, nullptr, "PARAMETER", createParameterLayout())

#endif
{
}

ReverbAudioProcessor::~ReverbAudioProcessor()
{
}

//==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout ReverbAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    
    auto allPassfbParam = std::make_unique<juce::AudioParameterFloat>("apfb","Apfb", 0.f,1.f,0.7f);
    params.push_back(std::move(allPassfbParam));
    
    auto decayParam = std::make_unique<juce::AudioParameterFloat>("decay","Decay", 0.f,1.f,0.75f);
    params.push_back(std::move(decayParam));
    
    auto mixParam = std::make_unique<juce::AudioParameterFloat>("mix","Mix", 0.f,1.f,1.f);
    params.push_back(std::move(mixParam));
    
    return { params.begin(), params.end() };
}

const juce::String ReverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ReverbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ReverbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ReverbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ReverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ReverbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ReverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ReverbAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ReverbAudioProcessor::getProgramName (int index)
{
    return {};
}

void ReverbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ReverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    lastSampleRate = sampleRate;
    
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    line1.prepare(spec);
    line1.reset();

    line2.prepare(spec);
    line2.reset();
    
    line3.prepare(spec);
    line3.reset();

    line4.prepare(spec);
    line4.reset();
    
    line5.prepare(spec);
    line5.reset();
    
    line6.prepare(spec);
    line6.reset();

    line7.prepare(spec);
    line7.reset();
    

}

void ReverbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ReverbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ReverbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    line1.setDelay(347.f);
    line2.setDelay(113.f);
    line3.setDelay(37.f);
    
    auto apfb =(treeState.getRawParameterValue("apfb"))->load();
    
    auto decay = (treeState.getRawParameterValue("decay"))->load();

    for (int channel = 0; channel<getTotalNumInputChannels(); ++channel)
    {
    auto* channelData = buffer.getWritePointer (channel);
    
        // allpass filters
        for (int sample = 0; sample < buffer.getNumSamples(); ++ sample)
        {
            output1 = line1.popSample(channel);
            line1.pushSample(channel, channelData[sample] + output1 * apfb);
            channelData[sample] = output1 + -1*output1*apfb;
            
            output2 = line2.popSample(channel);
            line2.pushSample(channel, channelData[sample] + output2 * apfb);
            channelData[sample] = output2 + -1*output2*apfb;
            
            output3 = line3.popSample(channel);
            line3.pushSample(channel, channelData[sample] + output3 * apfb);
            channelData[sample] = output3 + -1*output3*apfb;
        }
        
        line4.setDelay(1687);
        line5.setDelay(1601);
        line6.setDelay(2053);
        line7.setDelay(2251);
        
        //combfilters
        auto x1 = channelData;
        auto x2 = channelData;
        auto x3 = channelData;
        auto x4 = channelData;
        for (int sample = 0; sample < buffer.getNumSamples(); ++ sample)
        {
            output4 = line4.popSample(channel);
            line4.pushSample(channel, x1[sample] + output4 * decay);
            x1[sample] = output4;
            
            output5 = line5.popSample(channel);
            line5.pushSample(channel, x2[sample] + output5 * decay);
            x2[sample] = output5;
            
            output6 = line6.popSample(channel);
            line6.pushSample(channel, x3[sample] + output6 * decay);
            x3[sample] = output6;
            
            output7 = line7.popSample(channel);
            line7.pushSample(channel, x4[sample] + output7 * decay);
            x4[sample] = output7;
            
            channelData[sample] = x1[sample] + x2[sample] + x3[sample] + x4[sample];
        }
        
    }

}

//==============================================================================
bool ReverbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ReverbAudioProcessor::createEditor()
{
    return new ReverbAudioProcessorEditor (*this);
}

//==============================================================================
void ReverbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ReverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ReverbAudioProcessor();
}
