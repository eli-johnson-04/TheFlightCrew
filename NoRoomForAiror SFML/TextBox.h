
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#pragma once

#define BACKSPACE 8
#define RETURN 13
#define LEFT_CLICK sf::Mouse::isButtonPressed(sf::Mouse::Left)
#define RIGHT_CLICK sf::Mouse::isButtonPressed(sf::Mouse::Right)

class TextBox
{
public:
    TextBox() {}
    TextBox(int size, sf::Color color)
    {
        textbox.setCharacterSize(size);
        textbox.setFillColor(color);
        selected = false;
        /*
        if (selected)
        {
            textbox.setString("|");
        }
        else
        {
            textbox.setString("");
        }
        */
    }

    void setFont(sf::Font& font)
    {
        textbox.setFont(font);
    }

    void setPosition(sf::Vector2f pos)
    {
        textbox.setPosition(pos);
    }

    void setLimit(bool cond)
    {
        hasLimit = cond;
    }

    void setLimit(bool cond, int lim)
    {
        hasLimit = cond;
        maxChars = lim;
    }

    void setSelected(bool sel)
    {
        selected = sel;
        if (!selected)
        {

        }
        /*if (!sel)
        {
            std::string t = text.str();
            std::string newT = "";
            for (int i = 0; i < t.length() - 1; i++)
            {
                newT += t[i];
            }
            textbox.setString(newT);
        }*/
    }

    std::string getText()
    {
        return text.str();
    }

    void drawTo(sf::RenderWindow& window)
    {
        window.draw(textbox);
    }

    void typedOn(sf::Event& input)
    {
        if (selected)
        {
            int charTyped = (int)input.text.unicode;
            if (charTyped < 128)
            {
                if (hasLimit)
                {
                    if (text.str().length() <= maxChars)
                    {
                        inputLogic(charTyped);
                    }
                    else if (text.str().length() > maxChars && charTyped == BACKSPACE)
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
    sf::Text textbox;
    std::ostringstream text;
    bool selected = false;
    bool hasLimit = false;
    int maxChars;

    void inputLogic(int charTyped)
    {
        if (charTyped != BACKSPACE && charTyped != RETURN && !LEFT_CLICK && !RIGHT_CLICK)
        {
            text << static_cast<char>(charTyped);
        }
        else if (charTyped == BACKSPACE)
        {
            if (text.str().length() > 0)
            {
                backspace();
            }
        }
        textbox.setString(text.str());  // add "|" here
    }

    void backspace()
    {
        std::string currText = text.str();
        std::string newText = "";
        for (int i = 0; i < currText.length() - 1; i++)
        {
            newText += currText[i];
        }
        text.str("");
        text << newText;

        textbox.setString(text.str());
    }
};
