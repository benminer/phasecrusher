/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PhaseCrusherAudioProcessor::PhaseCrusherAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

PhaseCrusherAudioProcessor::~PhaseCrusherAudioProcessor()
{

}

//==============================================================================
const String PhaseCrusherAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PhaseCrusherAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #els
    return false;
   #endif
}

bool PhaseCrusherAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PhaseCrusherAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PhaseCrusherAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PhaseCrusherAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PhaseCrusherAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PhaseCrusherAudioProcessor::setCurrentProgram (int index)
{
}

const String PhaseCrusherAudioProcessor::getProgramName (int index)
{
    return {};
}

void PhaseCrusherAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void PhaseCrusherAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    Fs = sampleRate;
    updateAngleDelta();
    isPhaserOn = false;
    isBitCrushOn = false;
}

void PhaseCrusherAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PhaseCrusherAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void PhaseCrusherAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        
        for (int n = 0; n < buffer.getNumSamples(); ++n)
        {
            
            inputSample = buffer.getReadPointer(channel)[n];

            if (isPhaserOn) {
                currentSineSample = sinf(currentAngle);
                currentAngle += angleDelta;
                
                if (currentAngle > ( 2* float_Pi )){
                    currentAngle -= (2 * float_Pi);
                }
                
                currentSineSample = (currentSineSample * phaseDepth * 500) + offsetFrequency;
                
                x = inputSample;
                // Filtering
                w0 = 2 * float_Pi * currentSineSample / Fs;
                
                alpha = sin(w0)/(2*Q);
                
                // APF
                b0 =   1 - alpha;
                b1 =  -2*cos(w0);
                b2 =   1 + alpha;
                a0 =   1 + alpha;
                a1 =  -2*cos(w0);
                a2 =   1 - alpha;
                
                y = (1/a0) * (b0*x + b1*x1[channel] + b2*x2[channel] - a1*y1[channel] - a2*y2[channel]);
                // ff and fb buffers
                x2[channel] = x1[channel];
                x1[channel] = x;
                y2[channel] = y1[channel];
                y1[channel] = y;
                
                outputSample = x + y;
                
            } else {
                outputSample = inputSample;
            }
            
            if (isBitCrushOn) {
                outputSample = bitCrush(outputSample, bitCrushAmt);
            }
            
            buffer.getWritePointer(channel)[n] = outputSample;
        }
    }
}

float PhaseCrusherAudioProcessor::bitCrush (float input, float amt) {

    float propAmt = 8 * (1 - amt) + 2;
    float ampValue = pow (2, propAmt);
    float prepInput = 0.5*input + 0.5;

    float scaleInput = roundf(ampValue * prepInput);

    float prepOut = scaleInput / ampValue;

    return (2*prepOut) - 1;

}

float PhaseCrusherAudioProcessor::phase (AudioBuffer<float>& buffer, float input, float rate, float depth) {
    

    
    return input;
}

void PhaseCrusherAudioProcessor::updateAngleDelta() {
    angleDelta = ((phaseRate / Fs) * 2.0 * float_Pi);
}

//==============================================================================
bool PhaseCrusherAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PhaseCrusherAudioProcessor::createEditor()
{
    return new PhaseCrusherAudioProcessorEditor (*this);
}

//==============================================================================
void PhaseCrusherAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PhaseCrusherAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PhaseCrusherAudioProcessor();
}

;
