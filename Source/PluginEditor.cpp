#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BandpassFilterAudioProcessorEditor::BandpassFilterAudioProcessorEditor (BandpassFilterAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(cutoffFrequencySlider);
    cutoffFrequencySlider.setSliderStyle(
        juce::Slider::SliderStyle::LinearVertical);
    cutoffFrequencyAttachment.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment(
            vts, "cutoff_frequency", cutoffFrequencySlider));

    addAndMakeVisible(cutoffFrequencyLabel);
    cutoffFrequencyLabel.setText("Cutoff Frequency", juce::dontSendNotification);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 400);
}

BandpassFilterAudioProcessorEditor::~BandpassFilterAudioProcessorEditor()
{
}

//==============================================================================
void BandpassFilterAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
}

void BandpassFilterAudioProcessorEditor::resized()
{
    cutoffFrequencySlider.setBounds({ 15, 35, 100, 300 });
    cutoffFrequencyLabel.setBounds({ cutoffFrequencySlider.getX() + 30,
        cutoffFrequencySlider.getY() - 30, 200, 50});
}
