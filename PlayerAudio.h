#pragma once
#include <JuceHeader.h>

class PlayerAudio
{
public:
    PlayerAudio();
    ~PlayerAudio();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();

    void loadFile(const juce::File& file);
    void play();
    void pause();
    void stop();
    void goToStart();
    void goToEnd();
    float previousGain = 1.0f;
    bool isMuted = false;
    void setGain(float gain);
    void mute();
 private:
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
};