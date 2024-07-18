#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "BandpassFilter.h"

//==============================================================================
/**
*/
class BandpassFilterAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    BandpassFilterAudioProcessorEditor
    (BandpassFilterAudioProcessor&, juce::AudioProcessorValueTreeState& vts);
    ~BandpassFilterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    BandpassFilterAudioProcessor& audioProcessor;

    // Slider, Attachment & Label for filter frequency
    juce::Slider cutoffFrequencySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        cutoffFrequencyAttachment;
    juce::Label cutoffFrequencyLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BandpassFilterAudioProcessorEditor)
};
