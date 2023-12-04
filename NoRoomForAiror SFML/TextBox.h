
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#pragma once

#define BACKSPACE 8
#define RETURN 13
#define LEFT_CLICK sf::Mouse::isButtonPressed(sf::Mouse::Left)
#define RIGHT_CLICK sf::Mouse::isButtonPressed(sf::Mouse::Right)

// the textbox functionality is inspired by TermSpar game development textbox/button video.

class TextBox
{
public:
    // constructor
    TextBox(int size, sf::Color color, int maxChars = 20)
    {
        textbox.setCharacterSize(size);
        textbox.setFillColor(color);
        selected = false;
    }

    // sets the font of the textbox
    void setFont(sf::Font& font)
    {
        textbox.setFont(font);
    }

    // sets the position of the textbox in the window
    void setPosition(sf::Vector2f pos)
    {
        textbox.setPosition(pos);
    }

    // sets the maximum number of characters that can be typed
    void setMax(bool cond, int max)
    {
        hasMax = cond;
        maxChars = max;
    }

    // sets the textbox as selected or not
    void setSelected(bool sel)
    {
        selected = sel;
    }

    // gets the text that was typed in by the user
    std::string getText()
    {
        return text.str();
    }

    // function to draw textbox to the window
    void drawTo(sf::RenderWindow& window)
    {
        window.draw(textbox);
    }

    // the functionality for user input
    void typedOn(sf::Event& input)
    {
        if (selected)
        {
            int charTyped = (int)input.text.unicode;  // input to unicode
            if (charTyped < 128)
            {
                if (hasMax)  // if there is a max characters limit
                {
                    if (text.str().length() <= maxChars)  // can type up to the max
                    {
                        inputLogic(charTyped);
                    }
                    else if (text.str().length() > maxChars && charTyped == BACKSPACE)  // deletes the last character when backspace key pressed
                    {
                        backspace();
                    }
                }
                else
                {
                    inputLogic(charTyped);
                }
            }
        }
    }

private:
    sf::Text textbox;  // the stored string in the textbox
    std::ostringstream text;  // the input detection for user input
    bool selected = false;  // if the textbox is selected, false by default
    bool hasMax = false;  // if the textbox has a character ceiling, false by default
    int maxChars;  // the value for the maximum characters in a textbox

    // handles the input for the particular key pressed
    void inputLogic(int charTyped)
    {
        if (charTyped != BACKSPACE && charTyped != RETURN && !LEFT_CLICK && !RIGHT_CLICK)  // no backspace etc. unicode allowed
        {
            text << static_cast<char>(charTyped);
        }
        else if (charTyped == BACKSPACE)  // deletes the last character when backspace key pressed
        {
            if (text.str().length() > 0)
            {
                backspace();
            }
        }
        textbox.setString(text.str());  // updates the stored string
    }

    // normal backspace key functionality
    void backspace()
    {
        std::string currText = text.str();
        std::string newText;
        newText = "";
        for (int i = 0; i < currText.length() - 1; i++)  // stores the same string minus 1 character (deletes one)
        {
            newText += currText[i];
        }
        text.str("");
        text << newText;

        textbox.setString(text.str());  // updates the stored string
    }
};
