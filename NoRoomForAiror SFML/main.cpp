
#include "TextBox.h"
#include <cmath>

int main()
{
    // makes window of the application with size 1200x600
    sf::RenderWindow window;
    window.create(sf::VideoMode(1200, 600), "No Room For Air-or", sf::Style::Titlebar | sf::Style::Close);
    window.setKeyRepeatEnabled(true);

    // loads the comic neue fonts for use
    sf::Font comicNeueReg;
    comicNeueReg.loadFromFile("images/Comic_Neue/ComicNeue-Regular.ttf");
    sf::Font comicNeueBold;
    comicNeueBold.loadFromFile("images/Comic_Neue/ComicNeue-Bold.ttf");

    // creation of the title and other left-hand side text
    sf::Text title("No Room For Air-or", comicNeueBold, 50);
    title.setPosition(sf::Vector2f(40.f,50.f));
    title.setFillColor(sf::Color::Black);
    sf::Text fromText("From:", comicNeueBold, 30);
    fromText.setPosition(sf::Vector2f(70.f,160.f));
    fromText.setFillColor(sf::Color::Black);
    sf::Text toText("To:", comicNeueBold, 30);
    toText.setPosition(sf::Vector2f(70.f,260.f));
    toText.setFillColor(sf::Color::Black);

    // creation of the GO BUTTON!
    sf::CircleShape goButton(100.f, 100);
    goButton.setPosition(sf::Vector2f(155.f,360.f));
    goButton.setFillColor(sf::Color::Green);
    sf::CircleShape goOutline(105.f, 100);
    goOutline.setPosition(sf::Vector2f(150.5,355.5));
    goOutline.setFillColor(sf::Color::Black);
    sf::Text goText("GO!! >>", comicNeueBold, 60);
    goText.setPosition(sf::Vector2f(160.f,420.f));
    goText.setFillColor(sf::Color::Black);

    // go button center calculations
    sf::Vector2f goCenter = goButton.getPosition();
    goCenter.x = goCenter.x + goButton.getRadius();
    goCenter.y = goCenter.y + goButton.getRadius();

    // makes the application splitting border
    sf::RectangleShape midBorder;
    midBorder.setSize(sf::Vector2f(15.f, 600.f));
    midBorder.setPosition(550.f, 0.f);
    midBorder.setFillColor(sf::Color::Black);

    // creation of the "from location" box
    TextBox fromLoc = TextBox(20, sf::Color::Black);
    fromLoc.setFont(comicNeueReg);
    fromLoc.setPosition(sf::Vector2f(75.f,202.5));
    fromLoc.setLimit(true, 20);

    // makes the backdrop and outline of the "from location" box
    sf::RectangleShape fromBox;
    fromBox.setSize(sf::Vector2f(365.f, 30.f));
    fromBox.setPosition(70.f, 200.f);
    fromBox.setFillColor(sf::Color::Red);
    sf::RectangleShape fromOutline;
    fromOutline.setSize(sf::Vector2f(369.f, 34.f));
    fromOutline.setPosition(68.f, 198.f);
    fromOutline.setFillColor(sf::Color::Black);
    /*
    sf::RectangleShape fromLeft;
    fromLeft.setSize(sf::Vector2f(2.f, 32.f));
    fromLeft.setPosition(70.f, 200.f);
    fromLeft.setFillColor(sf::Color::Black);
    sf::RectangleShape fromTop;
    fromTop.setSize(sf::Vector2f(365.f, 2.f));
    fromTop.setPosition(70.f, 200.f);
    fromTop.setFillColor(sf::Color::Black);
    sf::RectangleShape fromRight;
    fromRight.setSize(sf::Vector2f(2.f, 30.f));
    fromRight.setPosition(435.f, 200.f);
    fromRight.setFillColor(sf::Color::Black);
    sf::RectangleShape fromBottom;
    fromBottom.setSize(sf::Vector2f(365.f, 2.f));
    fromBottom.setPosition(72.f, 230.f);
    fromBottom.setFillColor(sf::Color::Black);
*/
    // creation of the "to location" box
    TextBox toLoc = TextBox(20, sf::Color::Black);
    toLoc.setFont(comicNeueReg);
    toLoc.setPosition(sf::Vector2f(75.f,302.5));
    toLoc.setLimit(true, 20);

    // makes the backdrop and outline for "to location" box
    sf::RectangleShape toBox;
    toBox.setSize(sf::Vector2f(365.f, 30.f));
    toBox.setPosition(70.f, 300.f);
    toBox.setFillColor(sf::Color::Yellow);
    sf::RectangleShape toOutline;
    toOutline.setSize(sf::Vector2f(369.f, 34.f));
    toOutline.setPosition(68.f, 298.f);
    toOutline.setFillColor(sf::Color::Black);
    /*
    sf::RectangleShape toLeft;
    toLeft.setSize(sf::Vector2f(2.f, 32.f));
    toLeft.setPosition(70.f, 300.f);
    toLeft.setFillColor(sf::Color::Black);
    sf::RectangleShape toTop;
    toTop.setSize(sf::Vector2f(365.f, 2.f));
    toTop.setPosition(70.f, 300.f);
    toTop.setFillColor(sf::Color::Black);
    sf::RectangleShape toRight;
    toRight.setSize(sf::Vector2f(2.f, 30.f));
    toRight.setPosition(435.f, 300.f);
    toRight.setFillColor(sf::Color::Black);
    sf::RectangleShape toBottom;
    toBottom.setSize(sf::Vector2f(365.f, 2.f));
    toBottom.setPosition(72.f, 330.f);
    toBottom.setFillColor(sf::Color::Black);
     */

    // error message for missing input placeholder
    sf::Text missingInputText("", comicNeueBold, 20);
    missingInputText.setPosition(sf::Vector2f(20.f,380.f));
    missingInputText.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            auto distance = (float)std::sqrt(std::pow((float)mousePosition.x - goCenter.x, 2) + std::pow((float)mousePosition.y - goCenter.y, 2));
            switch(event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                }
                case sf::Event::MouseButtonPressed:
                {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        std::cout << mousePosition.x << " " << mousePosition.y << std::endl;
                        if (mousePosition.x > 70 && mousePosition.x < 435 && mousePosition.y > 200 && mousePosition.y < 230)
                        {
                            fromLoc.setSelected(true);
                            toLoc.setSelected(false);
                        }
                        else if (mousePosition.x > 70 && mousePosition.x < 435 && mousePosition.y > 300 && mousePosition.y < 330)
                        {
                            toLoc.setSelected(true);
                            fromLoc.setSelected(false);
                        }
                        else
                        {
                            fromLoc.setSelected(false);
                            toLoc.setSelected(false);
                        }

                        if (distance <= goButton.getRadius())
                        {
                            if (fromLoc.getText().empty() || toLoc.getText().empty())
                            {
                                missingInputText.setString("Must have input\nin both boxes!");
                            }
                            else
                            {
                                missingInputText.setString("");
                                std::cout << "DO THE THING FROM THE OTHER CODE!!" << std::endl; //TODO: change to proper function
                            }
                        }
                    }
                }
                case sf::Event::TextEntered:
                {
                    fromLoc.typedOn(event);
                    toLoc.typedOn(event);
                }
            }
            window.clear(sf::Color::White);

            window.draw(title);
            window.draw(fromText);
            window.draw(toText);
            window.draw(midBorder);

            window.draw(goOutline);
            window.draw(goButton);
            window.draw(goText);
            window.draw(missingInputText);

            window.draw(fromOutline);
            window.draw(fromBox);
            /*
            window.draw(fromLeft);
            window.draw(fromTop);
            window.draw(fromRight);
            window.draw(fromBottom);
*/
            window.draw(toOutline);
            window.draw(toBox);
            /*
            window.draw(toLeft);
            window.draw(toTop);
            window.draw(toRight);
            window.draw(toBottom);
*/
            fromLoc.drawTo(window);
            toLoc.drawTo(window);
            window.display();
        }
    }
}
