#include "PlayerGUI.h"

PlayerGUI::PlayerGUI()
{
    for (auto* btn : { &loadButton, &playButton, &pauseButton, &startButton, &endButton, &stopButton ,&muteButton })
    {
        btn->addListener(this);
        addAndMakeVisible(btn);
    }

    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);
}

PlayerGUI::~PlayerGUI() {}

void PlayerGUI::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
}

void PlayerGUI::resized()
{
    int y = 30;
    loadButton.setBounds(20, y, 80, 40);
    playButton.setBounds(110, y, 60, 40);
    pauseButton.setBounds(180, y, 60, 40);
    startButton.setBounds(250, y, 60, 40);
    endButton.setBounds(320, y, 60, 40);
    stopButton.setBounds(390, y, 70, 40);
    muteButton.setBounds(470, y, 70, 40);
    volumeSlider.setBounds(20, 100, getWidth() - 40, 30);
}

void PlayerGUI::buttonClicked(juce::Button* button)
{
    if (onButtonClicked)
    {
        if (button == &loadButton) onButtonClicked("load");
        else if (button == &playButton) onButtonClicked("play");
        else if (button == &pauseButton) onButtonClicked("pause");
        else if (button == &startButton) onButtonClicked("start");
        else if (button == &endButton) onButtonClicked("end");
        else if (button == &stopButton) onButtonClicked("stop");
        else if (button == &muteButton) onButtonClicked("mute");
    }
}

void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (onVolumeChanged && slider == &volumeSlider)
        onVolumeChanged((float)slider->getValue());
}