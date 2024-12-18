#include "BandpassFilter/BandpassFilter.h"

void BandpassFilter::setCutoffFrequency(float newCutoffFrequency)
{
    this->cutoffFrequency = newCutoffFrequency;
}

void BandpassFilter::setQFactor(float newQFactor)
{
    this->qFactor = newQFactor;
}

void BandpassFilter::setSampleRate(float newSampleRate)
{
    this->sampleRate = newSampleRate;
}

void BandpassFilter::secondOrderAllpassFilter(float newCutoffFrequency, float BW, float newSampleRate)
{
    const auto tan = std::tan(PI * BW / newSampleRate);
    const auto c = (tan - 1.f) / (tan + 1.f);
    const auto d = -std::cos(2.f * PI * newCutoffFrequency / newSampleRate);

    b = {-c, d * (1.f - c), 1.f};
    a = {1.f, d * (1.f - c), -c};
}

void BandpassFilter::processBlock(juce::AudioBuffer<float> &buffer,
                                  juce::MidiBuffer &)
{
    // resize the allpass buffers to the number of channels and
    // zero the new ones
    x1.resize(buffer.getNumChannels(), 0.f);
    x2.resize(buffer.getNumChannels(), 0.f);
    y1.resize(buffer.getNumChannels(), 0.f);
    y2.resize(buffer.getNumChannels(), 0.f);

    // actual processing; each channel separately
    for (auto channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto channelSamples = buffer.getWritePointer(channel);

        float BW = cutoffFrequency / qFactor;

        secondOrderAllpassFilter(cutoffFrequency, BW, sampleRate);

        // for each sample in the channel
        for (auto i = 0; i < buffer.getNumSamples(); ++i)
        {
            float x = channelSamples[i];
            float y = b[0] * x + b[1] * x1[channel] + b[2] * x2[channel] - a[1] * y1[channel] - a[2] * y2[channel];

            y2[channel] = y1[channel];
            y1[channel] = y;
            x2[channel] = x1[channel];
            x1[channel] = x;

            // we scale by 0.5 to stay in the [-1, 1] range
            channelSamples[i] = 0.5f * (x - y);
        }
    }
}