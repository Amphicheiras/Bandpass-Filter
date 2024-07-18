#include "BandpassFilter.h"

void BandpassFilter::setCutoffFrequency(float cutoffFrequency)
{
	this->cutoffFrequency = cutoffFrequency;
}

void BandpassFilter::setSamplingRate(float samplingRate)
{
	this->samplingRate = samplingRate;
}

void BandpassFilter::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
	constexpr auto PI = 3.14f;
	dnBuffer.resize(buffer.getNumChannels(), 0.f);
	const float highPassCutoffFrequency = cutoffFrequency /*- 500.f*/; // High-pass cutoff frequency in Hz
	const float lowPassCutoffFrequency = cutoffFrequency /*+ 500.f*/;  // Low-pass cutoff frequency in Hz

	// High-pass filter coefficients
	const auto tanHighPass = std::tan(PI * highPassCutoffFrequency / samplingRate);
	const auto a1HighPass = (tanHighPass - 1.f) / (tanHighPass + 1.f);

	// Low-pass filter coefficients
	const auto tanLowPass = std::tan(PI * lowPassCutoffFrequency / samplingRate);
	const auto a1LowPass = (tanLowPass - 1.f) / (tanLowPass + 1.f);

	// Buffer for storing intermediate states
	std::vector<float> dnBufferHighPass(buffer.getNumChannels(), 0.0f);
	std::vector<float> dnBufferLowPass(buffer.getNumChannels(), 0.0f);

	for (auto channel = 0; channel < buffer.getNumChannels(); channel++)
	{
		auto channelSamples = buffer.getWritePointer(channel);
		for (auto i = 0; i < buffer.getNumSamples(); ++i)
		{
			// High-pass filter
			const auto inputSample = channelSamples[i];
			const auto allpassFilteredSampleHighPass = a1HighPass * inputSample + dnBufferHighPass[channel];
			dnBufferHighPass[channel] = inputSample - a1HighPass * allpassFilteredSampleHighPass;
			const auto highPassOutput = 0.5f * (inputSample - allpassFilteredSampleHighPass);

			// Low-pass filter on high-pass output
			const auto allpassFilteredSampleLowPass = a1LowPass * highPassOutput + dnBufferLowPass[channel];
			dnBufferLowPass[channel] = highPassOutput - a1LowPass * allpassFilteredSampleLowPass;
			const auto bandPassOutput = 0.5f * (highPassOutput + allpassFilteredSampleLowPass);

			// Store the result back in the buffer
			channelSamples[i] = bandPassOutput;
		}
	}
}
