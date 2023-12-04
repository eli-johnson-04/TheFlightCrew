
#include "TextBox.h"
#include <cmath>

// the textbox functionality is inspired by TermSpar video https://www.youtube.com/watch?v=T31MoLJws4U&ab_channel=TermSpar
int main()
{
    // makes window of the application with size 1200x600
    sf::RenderWindow window;
    window.create(sf::VideoMode(1200, 600), "No Room For Air-or", sf::Style::Titlebar | sf::Style::Close);
    window.setKeyRepeatEnabled(true);
    sf::Color lightBlue(135, 206, 235);

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
    midBorder.setPosition(490.f, 0.f);
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
    fromBox.setOutlineColor(sf::Color::Black);
    fromBox.setOutlineThickness(2.f);

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
    toBox.setOutlineColor(sf::Color::Black);
    toBox.setOutlineThickness(2.f);

    // error message for missing input placeholder
    sf::Text missingInputText("", comicNeueBold, 20);
    missingInputText.setPosition(sf::Vector2f(20.f,380.f));
    missingInputText.setFillColor(sf::Color::Red);

    // TODO: 1/4 testing data set
    std::vector<std::vector<std::string>> airlineTable(6, std::vector<std::string>(9, "-"));
    airlineTable[0] = {"Airline", "Overall", "Entertainment", "Food", "Comfort", "Service", "Value", "Ground\nService", "WiFi"};

    const float cellWidth = 76.0f;
    const float cellHeight = 30.0f;
    const float posAdjustX = 510.f;
    const float posAdjustY = 100.f;

    std::vector<sf::Text> values;

    // TODO: 2/4 converts the data values into text objects and puts in a vector

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
                    if (LEFT_CLICK)
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
                                /*
                                 * Processor* prog = new Processor();
                                 * prog->start();
                                 * std::pair<double, double> timePair = setRouteVec(fromLoc.getText(), toLoc.getText());
                                 * if (timePair.first == -1)
                                 * {
                                 *      auto routeVec =
                                 * }
                                 *
                                 * // make the time result text lines
                                 *
                                 * auto routeVec = prog->getRouteVec();
                                 * for (int i = 0; i < (routeVec.size() < 5 ? routeVec.size() : 5; i++)
                                 * for (int j = 0; j < airlineTable[0].size(); j++)
                                 * {
                                 *      if (j == 0)
                                 *      {
                                 *          airlineTable[i+1] = routeVec[i].getName();
                                 *      }
                                 *      else
                                 *      {
                                 *          airlineTable[i+1][j] = "" + routeVec[i].getScores()[j];
                                 *      }
                                 * }
                                 */
                                /*
                                airlineTable =
                                              {
                                    {"Overall", "Airline", "Entertainment", "Food", "Comfort", "Service", "Value", "Ground\nService", "WiFi"},
                                    {"9.9", "Airline A", "10", "10", "10", "10", "10", "10", "10"},
                                    {"9.9", "Airline B", "10", "10", "10", "10", "10", "10", "10"},
                                    {"9.9", "Airline C", "10", "10", "10", "10", "10", "10", "10"},
                                    {"9.9", "Airline D", "10", "10", "10", "10", "10", "10", "10"},
                                    {"9.9", "Airline E", "10", "10", "10", "10", "10", "10", "10"} };
                                    */
                                for (int i = 0; i < airlineTable.size(); ++i)
                                {
                                    for (int j = 0; j < airlineTable[i].size(); ++j)
                                    {
                                        sf::Text info(airlineTable[i][j], comicNeueReg, 11);
                                        info.setPosition(2+posAdjustX+(cellWidth * (float)j), posAdjustY+(cellHeight * (float)i));
                                        info.setFillColor(sf::Color::Black);
                                        values.push_back(info);
                                    }
                                }
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
            // reset screen to sky blue
            window.clear(lightBlue);

            // renders the left-hand side text + screen split
            window.draw(title);
            window.draw(fromText);
            window.draw(toText);
            window.draw(midBorder);

            // renders all go button related visuals
            window.draw(goOutline);
            window.draw(goButton);
            window.draw(goText);
            window.draw(missingInputText);

            // renders the from-location box
            window.draw(fromBox);
            fromLoc.drawTo(window);

            // renders the to-location box
            window.draw(toBox);
            toLoc.drawTo(window);

            // renders the table template
            //window.draw(tableVert1);

            // TODO: 3/4 renders the table template
            for (int i = 0; i < airlineTable.size(); ++i)
            {
                for (int j = 0; j < airlineTable[i].size(); ++j)
                {
                    sf::RectangleShape cell(sf::Vector2f(cellWidth, cellHeight));
                    cell.setPosition(posAdjustX+(cellWidth * (float)j), posAdjustY+(cellHeight * (float)i));
                    cell.setOutlineThickness(2.0f);
                    cell.setOutlineColor(sf::Color::Black);
                    window.draw(cell);
                }
            }

            // TODO: 4/4 puts text on the cells
            for (const auto& text : values)
            {
                window.draw(text);
            }

            // shows the new window frame
            window.display();
        }
    }
}
