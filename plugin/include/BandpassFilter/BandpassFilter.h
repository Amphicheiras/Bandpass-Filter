#pragma once

#include <vector>
#include <juce_audio_processors/juce_audio_processors.h>

class BandpassFilter
{
public:
	void setCutoffFrequency(float cutoffFrequency);
	void setQFactor(float qFactor);
	void setSampleRate(float newSampleRate);
	void secondOrderAllpassFilter(float cutoffFrequency, float BW, float sampleRate);
	void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &);

private:
	float cutoffFrequency;
	float sampleRate;
	float qFactor;
	std::vector<float> x1;
	std::vector<float> x2;
	std::vector<float> y1;
	std::vector<float> y2;
	std::vector<float> b;
	std::vector<float> a;
	float PI = 3.14159265359f;
};
