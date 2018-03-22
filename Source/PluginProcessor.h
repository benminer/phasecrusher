/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class PhaseCrusherAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    PhaseCrusherAudioProcessor();
    ~PhaseCrusherAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float phaseRate = 0.01f;
    float phaseDepth = 0;
    float isPhaserOn;
    
    float bitCrushAmt;
    bool isBitCrushOn;
    
    float bitCrush (float input, float amt);
    float phase (AudioBuffer<float>& buffer, float input, float depth, float rate);
    
    float Fs = 0.0f;
    
    float Q = 2.0;
    
    void updateAngleDelta();
    
    

private:
    
    float inputSample;
    float outputSample;
    float bufferSample;
    float gainSmooth;
    
    // Signal Sample Values
    // Signal Sample Values
    float x = 0.0f;
    float x1[2] = {0.0f};
    float x2[2] = {0.0f};
    float y = 0.0f;
    float y1[2] = {0.0f};
    float y2[2] = {0.0f};
    
    // Gain Coefficients
    float b0 = 0.0f;
    float b1 = 0.0f;
    float b2 = 0.0f;
    float a0 = 0.0f;
    float a1 = 0.0f;
    float a2 = 0.0f;
    
    float w0 = 0.0f;
    float alpha = 0.0f;
    
    float currentSineSample = 0.0f;
    float currentAngle = 0.0f;
    float angleDelta = 0.0f;
    float offsetFrequency = 1000.0f;
    
    
    
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhaseCrusherAudioProcessor)
};
