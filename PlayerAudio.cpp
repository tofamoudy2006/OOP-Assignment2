#include "PlayerAudio.h"

PlayerAudio::PlayerAudio()
{
    formatManager.registerBasicFormats();
}

PlayerAudio::~PlayerAudio() {}

void PlayerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (transportSource.getLengthInSeconds() - transportSource.getCurrentPosition() <= 1.0001) {
        transportSource.setPosition(0.0);
        transportSource.start();
    }
    else
    transportSource.getNextAudioBlock(bufferToFill);
}

void PlayerAudio::releaseResources()
{
    transportSource.releaseResources();
}

void PlayerAudio::loadFile(const juce::File& file)
{
    if (auto* reader = formatManager.createReaderFor(file))
    {
        readerSource.reset(new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(readerSource.get(), 0, nullptr, reader->sampleRate);
    }
}

void PlayerAudio::play() { transportSource.start();}
void PlayerAudio::pause() { transportSource.stop(); }
void PlayerAudio::stop() { transportSource.stop(); transportSource.setPosition(0.0); }
void PlayerAudio::goToStart() { transportSource.setPosition(0.0); }

void PlayerAudio::goToEnd()
{
    transportSource.setPosition(transportSource.getLengthInSeconds());
}

void PlayerAudio::setGain(float gain)
{
    transportSource.setGain(gain);
}
void PlayerAudio::mute() {
    if (! isMuted) {
        previousGain = transportSource.getGain();
        transportSource.setGain(0.0f);
        isMuted = true;
    }
    else {
        transportSource.setGain(previousGain);
        isMuted = false;
    }
}
