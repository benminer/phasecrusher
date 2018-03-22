/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class PhaseCrusherAudioProcessorEditor  : public AudioProcessorEditor,
                                          public Slider::Listener, public Button::Listener


{
public:
    PhaseCrusherAudioProcessorEditor (PhaseCrusherAudioProcessor&);
    ~PhaseCrusherAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(Slider *slider) override;
    void buttonClicked(Button *button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PhaseCrusherAudioProcessor& processor;
    
    // Sliders
    HackAudio::Slider phaseDepthSlider;
    HackAudio::Slider phaseRateSlider;
    HackAudio::Slider bitCrushSlider;
    
    // On Off Switches
    HackAudio::Button phaserButton;
    HackAudio::Button bitCrushButton;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhaseCrusherAudioProcessorEditor)
};
