#pragma once

#include "BandpassFilter/PluginProcessor.h"
#include "BandpassFilter/BandpassFilter.h"
#include "BandpassFilter/CustomLookAndFeel.h"

class PluginEditor final : public juce::AudioProcessorEditor
{
public:
    explicit PluginEditor(PluginProcessor &, juce::AudioProcessorValueTreeState &vst);
    ~PluginEditor() override;

    void paint(juce::Graphics &) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginProcessor &audioProcessor;

    std::unique_ptr<CustomLookAndFeel> customLookAndFeel;

    // Slider, Attachment & Label for filter frequency
    juce::Slider cutoffFrequencySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        cutoffFrequencyAttachment;
    juce::Label cutoffFrequencyLabel;

    juce::Slider qFactorSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        qFactorAttachment;
    juce::Label qFactorLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};