#include "BandpassFilter/PluginEditor.h"
#include "BandpassFilter/PluginProcessor.h"

PluginEditor::PluginEditor(
    PluginProcessor &p, juce::AudioProcessorValueTreeState &vts)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    customLookAndFeel = std::make_unique<CustomLookAndFeel>();

    cutoffFrequencySlider.setLookAndFeel(customLookAndFeel.get());
    cutoffFrequencySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    cutoffFrequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    cutoffFrequencySlider.setTextValueSuffix(" Hz");
    cutoffFrequencyAttachment.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment(
            vts, "cutoffFrequency", cutoffFrequencySlider));
    addAndMakeVisible(cutoffFrequencySlider);

    cutoffFrequencyLabel.setName("cutoffLabel");
    cutoffFrequencyLabel.setColour(juce::Label::textColourId, juce::Colours::wheat);
    cutoffFrequencyLabel.setText("Cutoff Frequency", juce::dontSendNotification);
    cutoffFrequencyLabel.setJustificationType(juce::Justification::centred);
    cutoffFrequencyLabel.attachToComponent(&cutoffFrequencySlider, false);
    addAndMakeVisible(cutoffFrequencyLabel);

    qFactorSlider.setLookAndFeel(customLookAndFeel.get());
    qFactorSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    qFactorSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    qFactorAttachment.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment(
            vts, "qFactor", qFactorSlider));
    addAndMakeVisible(qFactorSlider);

    qFactorLabel.setName("qFactorLabel");
    qFactorLabel.setColour(juce::Label::textColourId, juce::Colours::wheat);
    qFactorLabel.setText("Q", juce::dontSendNotification);
    qFactorLabel.setJustificationType(juce::Justification::centred);
    qFactorLabel.attachToComponent(&qFactorSlider, false);
    addAndMakeVisible(qFactorLabel);

    setSize(300, 200);
}

PluginEditor::~PluginEditor()
{
    cutoffFrequencySlider.setLookAndFeel(nullptr);
    qFactorSlider.setLookAndFeel(nullptr);
}

void PluginEditor::paint(juce::Graphics &g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::blueviolet);
}

void PluginEditor::resized()
{ // Get the window's width and height
    auto windowWidth = getWidth();
    auto windowHeight = getHeight();

    // Define the slider's dimensions
    int sliderWidth = getWidth() / 2;
    int sliderHeight = getHeight() / 2;

    // Calculate the centered position for the slider
    int sliderX = (windowWidth - sliderWidth) / 2;
    int sliderY = (windowHeight - sliderHeight) / 2;

    // Set the slider bounds
    cutoffFrequencySlider.setBounds(sliderX - sliderWidth / 2, sliderY, sliderWidth, sliderHeight);
    qFactorSlider.setBounds(sliderX + sliderWidth / 2, sliderY, sliderWidth, sliderHeight);

    // Define the label's dimensions
    // int labelWidth = 200;
    // int labelHeight = 50;

    // Position the label just above the slider
    // int labelX = sliderX + (sliderWidth - labelWidth) / 2;
    // int labelY = sliderY - labelHeight;
    // cutoffFrequencyLabel.setBounds(labelX, labelY, labelWidth, labelHeight);
}