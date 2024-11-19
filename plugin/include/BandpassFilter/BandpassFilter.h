#pragma once

#include <vector>
#include <juce_audio_processors/juce_audio_processors.h>

class BandpassFilter
{
public:
	void setCutoffFrequency(float cutoffFrequency);
	void setSamplingRate(float samplingRate);
	void secondOrderAllpassFilter();
	void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &);

private:
	float cutoffFrequency;
	float samplingRate;
	std::vector<float> x1;
	std::vector<float> x2;
	std::vector<float> y1;
	std::vector<float> y2;
	std::vector<float> b;
	std::vector<float> a;
	const float Q = 5.f;
	float BW = cutoffFrequency / Q;
	float PI = 3.14159265359f;
};
