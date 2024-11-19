#include "BandpassFilter/PluginEditor.h"
#include "BandpassFilter/PluginProcessor.h"

PluginEditor::PluginEditor(
    PluginProcessor &p, juce::AudioProcessorValueTreeState &vts)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    addAndMakeVisible(cutoffFrequencySlider);
    cutoffFrequencySlider.setSliderStyle(
        juce::Slider::SliderStyle::LinearVertical);
    cutoffFrequencyAttachment.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment(
            vts, "cutoff_frequency", cutoffFrequencySlider));

    addAndMakeVisible(cutoffFrequencyLabel);
    cutoffFrequencyLabel.setText("Cutoff Frequency", juce::dontSendNotification);

    setSize(200, 400);
}

PluginEditor::~PluginEditor() {}

void PluginEditor::paint(juce::Graphics &g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(juce::FontOptions(15.0f));
}

void PluginEditor::resized()
{
    cutoffFrequencySlider.setBounds({15, 35, 100, 300});
    cutoffFrequencyLabel.setBounds({cutoffFrequencySlider.getX() + 30,
                                    cutoffFrequencySlider.getY() - 30, 200, 50});
}