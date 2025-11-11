#include "MainComponent.h"

MainComponent::MainComponent()
{
    addAndMakeVisible(playerGUI);

    playerGUI.onButtonClicked = [this](const juce::String& action)
        {
            if (action == "load")
            {
                fileChooser = std::make_unique<juce::FileChooser>(
                    "Select an audio file...", juce::File{}, "*.wav;*.mp3");
                fileChooser->launchAsync(
                    juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
                    [this](const juce::FileChooser& fc)
                    {
                        auto file = fc.getResult();
                        if (file.existsAsFile()) playerAudio.loadFile(file);
                    });
            }
            else if (action == "play") playerAudio.play();
            else if (action == "pause") playerAudio.pause();
            else if (action == "stop") playerAudio.stop();
            else if (action == "start") playerAudio.goToStart();
            else if (action == "end")  playerAudio.goToEnd();
        };

    playerGUI.onVolumeChanged = [this](float value)
        {
            playerAudio.setGain(value);
        };

    setSize(500, 250);
    setAudioChannels(0, 2);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    playerAudio.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    playerAudio.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    playerAudio.releaseResources();
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
}

void MainComponent::resized()
{
    playerGUI.setBounds(getLocalBounds());
}