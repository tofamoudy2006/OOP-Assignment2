#pragma once
#include <JuceHeader.h>

class PlayerGUI : public juce::Component,
    public juce::Button::Listener,
    public juce::Slider::Listener
{
public:
    PlayerGUI();
    ~PlayerGUI() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;

    std::function<void(const juce::String&)> onButtonClicked;
    std::function<void(float)> onVolumeChanged;

private:
    juce::TextButton loadButton{ "Load" };
    juce::TextButton playButton{ juce::String::fromUTF8("\xE2\x96\xB6") };
    juce::TextButton pauseButton{ "||" };
    juce::TextButton startButton{ "|" + juce::String::fromUTF8("\xE2\x97\x80") };
    juce::TextButton endButton{ juce::String::fromUTF8("\xE2\x96\xB6") + "|" };
    juce::TextButton stopButton{ juce::String::fromUTF8("\xE2\xAC\x9B") };
    juce::TextButton muteButton{ juce::String::fromUTF8("\xF0\x9F\x94\x88") + "X"};
    juce::Slider volumeSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)
};