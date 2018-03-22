/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
PhaseCrusherAudioProcessorEditor::PhaseCrusherAudioProcessorEditor (PhaseCrusherAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize(800, 500);
    
    phaseDepthSlider.addListener(this);
    phaseDepthSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    phaseDepthSlider.setBounds(180, 80, 120, 120);
    phaseDepthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 20, 20);
    phaseDepthSlider.setRange(0, 1);
    addAndMakeVisible(phaseDepthSlider);
    
    phaseRateSlider.addListener(this);
    phaseRateSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    phaseRateSlider.setBounds(500, 80, 120, 120);
    phaseRateSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 20, 20);
    phaseRateSlider.setName("Phase Rate");
    phaseRateSlider.setRange(0.01, 10);
    addAndMakeVisible(phaseRateSlider);
    
    bitCrushSlider.addListener(this);
    bitCrushSlider.setSliderStyle(Slider::LinearHorizontal);
    bitCrushSlider.setBounds(250, 300, 300, 100);
    bitCrushSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 20, 20);
    bitCrushSlider.setRange(0, 1);
    addAndMakeVisible(bitCrushSlider);
    
    phaserButton.addListener(this);
    phaserButton.setButtonStyle(HackAudio::Button::SlidingToggle);
    phaserButton.setBounds(40, 85, 60, 60);
//    phaserButton.setState(juce::Button::ButtonState::buttonDown);
    addAndMakeVisible(phaserButton);
    
    bitCrushButton.addListener(this);
    bitCrushButton.setButtonStyle(HackAudio::Button::SlidingToggle);
    bitCrushButton.setBounds(40, 305, 60, 60);
//    bitCrushButton.setState(juce::Button::ButtonState::buttonDown);
    addAndMakeVisible(bitCrushButton);
    
}

PhaseCrusherAudioProcessorEditor::~PhaseCrusherAudioProcessorEditor()
{
    
}


//==============================================================================
void PhaseCrusherAudioProcessorEditor::paint (Graphics& g)
{
    ColourGradient backgroundGradient = ColourGradient(Colour(222, 123, 123), 0, 300, Colour(189, 100, 186), 400, 0, false);
    
    g.setGradientFill(backgroundGradient);
    
    g.setFont (30.0f);
    g.setColour(Colours::white);
    g.drawFittedText("Phase Crusher", 295, 10, 200, 20, Justification::centredTop, 1);
    
    g.setColour(Colours::crimson);
    g.drawRect(0, 50, 800, 200);
    g.fillRect(0, 50, 800, 200);
    
    g.setColour(Colours::aqua);
    g.drawRect(0, 250, 800, 300);
    g.fillRect(0, 250, 800, 300);
    
    g.setColour(Colours::aqua);
    g.setFont(15.0f);
    g.drawFittedText("Phase Depth", 170, 200, 100, 30, Justification::centred, 1);
    g.drawFittedText("Phase Rate", 490, 200, 100, 30, Justification::centred, 1);
    g.drawFittedText("Phaser Toggle", 25, 120, 100, 100, Justification::centred, 1);
    g.setColour(Colours::crimson);
    g.drawFittedText("Bit Crush", 240, 400, 100, 30, Justification::centred, 1);
    g.drawFittedText("Bit Crush Toggle", 25, 340, 100, 100, Justification::centred, 1);

}

void PhaseCrusherAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

//==============================================================================
void PhaseCrusherAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &phaseRateSlider) {
        processor.phaseRate = phaseRateSlider.getValue();
        processor.updateAngleDelta();
    } else if (slider == &phaseDepthSlider) {
        processor.phaseDepth = phaseDepthSlider.getValue();
    } else if (slider == &bitCrushSlider) {
        processor.bitCrushAmt = bitCrushSlider.getValue();
//        float bitRatio = bitCrushSlider.getValue() / 100;
//        std::vector<float> range(250);
//        for (float i = 5; i < 10; i+=.02) {
//            range[i] = i;
//        }
//        float crushIndex = roundf(bitRatio * range.size());
//        processor.bitCrushAmt = range[crushIndex];
//        String message;
//        message << "bit crush amt" + String(processor.bitCrushAmt) << newLine;
//        Logger::getCurrentLogger()->writeToLog (message);
    }

    
}

void PhaseCrusherAudioProcessorEditor::buttonClicked(Button* button)
{
    // Toggle the effects
    if (button == &phaserButton) {
        processor.isPhaserOn = !processor.isPhaserOn;
    } else if (button == &bitCrushButton) {
        processor.isBitCrushOn = !processor.isBitCrushOn;
    }
}
