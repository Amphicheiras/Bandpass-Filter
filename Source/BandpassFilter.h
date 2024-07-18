#pragma once
#include <vector>
#include "JuceHeader.h"


class BandpassFilter
{
public:
	void setCutoffFrequency(float cutoffFrequency);
	void setSamplingRate(float samplingRate);

	void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&);

private:
	float cutoffFrequency;
	float samplingRate;
	std::vector<float> dnBuffer;
};

