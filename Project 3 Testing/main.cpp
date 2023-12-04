
#include "TextBox.h"
#include "Processor.h"
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
    title.setPosition(sf::Vector2f(25.f,50.f));
    title.setFillColor(sf::Color::Black);
    sf::Text theFlightCrew("Brought to you by TheFlightCrew", comicNeueBold, 15);
    theFlightCrew.setPosition(sf::Vector2f(27.5,100.f));
    theFlightCrew.setFillColor(sf::Color(139, 0, 0));
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
    fromLoc.setMax(true, 20);

    // makes the backdrop and outline of the "from location" box
    sf::RectangleShape fromBox;
    fromBox.setSize(sf::Vector2f(365.f, 30.f));
    fromBox.setPosition(70.f, 200.f);
    fromBox.setFillColor(sf::Color::White);
    fromBox.setOutlineColor(sf::Color::Black);
    fromBox.setOutlineThickness(2.f);

    // creation of the "to location" box
    TextBox toLoc = TextBox(20, sf::Color::Black);
    toLoc.setFont(comicNeueReg);
    toLoc.setPosition(sf::Vector2f(75.f,302.5));
    toLoc.setMax(true, 20);

    // makes the backdrop and outline for "to location" box
    sf::RectangleShape toBox;
    toBox.setSize(sf::Vector2f(365.f, 30.f));
    toBox.setPosition(70.f, 300.f);
    toBox.setFillColor(sf::Color::White);
    toBox.setOutlineColor(sf::Color::Black);
    toBox.setOutlineThickness(2.f);

    // error message for missing input placeholder
    sf::Text missingInputText("", comicNeueBold, 20);
    missingInputText.setPosition(sf::Vector2f(20.f,380.f));
    missingInputText.setFillColor(sf::Color::Red);

    // time of data structures creation
    sf::Text hashTime("", comicNeueBold, 20);
    hashTime.setPosition(sf::Vector2f(510.f, 290.f));
    hashTime.setFillColor(sf::Color::Black);
    sf::Text splayTime("", comicNeueBold, 20);
    splayTime.setPosition(sf::Vector2f(510.f, 315.f));
    splayTime.setFillColor(sf::Color::Black);

    // the title for the right-hand side of the window
    sf::Text rightHandTitle("Who is the best airline for your route?", comicNeueBold, 40);
    rightHandTitle.setPosition(sf::Vector2f(515.f, 25.f));
    rightHandTitle.setFillColor(sf::Color::Black);

    // the instructions for the program
    sf::Text instructionsTitle("Instructions:", comicNeueBold, 25);
    instructionsTitle.setPosition(sf::Vector2f(920.f, 330.f));
    instructionsTitle.setFillColor(sf::Color(139, 0, 0));
    sf::Text instructionsDesc("Type a city into the \"from\" box"
                               "\n  and \"to\" box and press GO!"
                               "\n Give the engine time to load."
                               "\n\n Try -> from: Paris to: Tokyo!", comicNeueBold, 25);
    instructionsDesc.setPosition(sf::Vector2f(820.f, 360.f));
    instructionsDesc.setFillColor(sf::Color(105, 105, 105));

    // error message for invalid route placeholder
    sf::Text invalidRouteError("", comicNeueBold, 30);
    invalidRouteError.setPosition(sf::Vector2f(520.f,350.f));
    invalidRouteError.setFillColor(sf::Color::Red);

    // creates the default airline table with the categories in the first row
    std::vector<std::vector<std::string>> airlineTable(6, std::vector<std::string>(9, "-"));
    airlineTable[0] = {"Airline", "Overall", "Entertainment", "Food", "Comfort", "Service", "Value", "Ground\nService", "WiFi"};
    sf::Text info("", comicNeueReg, 10);

    // table information
    const float cellWidth = 76.0f;
    const float cellHeight = 30.0f;
    const float posAdjustX = 510.f;
    const float posAdjustY = 100.f;

    // creates the default values vector - important to reset the table
    std::vector<sf::Text> values(54, sf::Text("", comicNeueReg, 11));

    // while the program is running
    while (window.isOpen())
    {
        // detects mouse clicks etc.
        sf::Event event{};
        while (window.pollEvent(event))
        {
            // gets mouse position and distance to go button every frame
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            auto distance = (float)std::sqrt(std::pow((float)mousePosition.x - goCenter.x, 2) + std::pow((float)mousePosition.y - goCenter.y, 2));
            switch(event.type)
            {
                // if the program is closed, close the window
                case sf::Event::Closed:
                {
                    window.close();
                }
                // if a mouse button is pressed
                case sf::Event::MouseButtonPressed:
                {
                    // if left mouse click
                    if (LEFT_CLICK)
                    {
                        // check if the "from" box is clicked
                        if (mousePosition.x > 70 && mousePosition.x < 435 && mousePosition.y > 200 && mousePosition.y < 230)
                        {
                            fromLoc.setSelected(true);
                            fromBox.setOutlineColor(sf::Color::Green);
                            toLoc.setSelected(false);
                            toBox.setOutlineColor(sf::Color::Black);
                        }
                        // check if the "to" box is clicked
                        else if (mousePosition.x > 70 && mousePosition.x < 435 && mousePosition.y > 300 && mousePosition.y < 330)
                        {
                            toLoc.setSelected(true);
                            toBox.setOutlineColor(sf::Color::Green);
                            fromLoc.setSelected(false);
                            fromBox.setOutlineColor(sf::Color::Black);
                        }
                        // if the boxes are not clicked, deselect and un-highlight
                        else
                        {
                            fromLoc.setSelected(false);
                            fromBox.setOutlineColor(sf::Color::Black);
                            toLoc.setSelected(false);
                            toBox.setOutlineColor(sf::Color::Black);
                        }
                        // if the GO button is pressed
                        if (distance <= goButton.getRadius())
                        {
                            // throw error message if the boxes have nothing in them
                            if (fromLoc.getText().empty() || toLoc.getText().empty())
                            {
                                missingInputText.setString("Must have input\nin both boxes!");
                            }
                            // otherwise run the table making process
                            else
                            {
                                missingInputText.setString("");  // cancels the error message if present
                                auto* prog = new Processor();  // starts up the backend data manipulation
                                prog->start();  // runs the process
                                std::pair<double, double> timePair = prog->setRouteVec(fromLoc.getText(), toLoc.getText());  // returns the times based on the data structure
                                if (timePair.first == -1)  // if the route was invalid
                                {
                                  hashTime.setString("");  // cancels hash time and splay time texts if present vvv
                                  splayTime.setString("");
                                  invalidRouteError.setString("No Data For Route!\n  Maybe a typo?");  // displays the error message
                                  break;  // exits process
                                }
                                hashTime.setString("Hash Map time: " + to_string(timePair.first) + " seconds");  // displays the hash map and splay tree times vvv
                                splayTime.setString("Splay Tree time: " + to_string(timePair.second) + " seconds");
                                invalidRouteError.setString("");  // cancels invalid route error
                                std::string fitName;  // declares the placeholder name variable
                                bool once = false;  // will be flipped if a space is detected in the airline name (only one space)
                                auto routeVec = prog->getRouteVec();  // vector of Airline objects
                                int num;  // outside loop scope counter - important for consecutive uses of the engine (table clearing)
                                for (num = 0; num < (routeVec.size() < 5 ? routeVec.size() : 5); num++)  // only fills up table data for top 5 airlines (at most)
                                {
                                    for (int j = 0; j < airlineTable[0].size(); j++)
                                    {
                                        if (j == 0)
                                        {
                                            for (auto character : routeVec[num]->getName())  // gets airline name if in first column
                                            {
                                                if (character == ' ' && !once)  // if a space in the name, put the rest on a new line (for fitting in the table)
                                                {
                                                    character = '\n';
                                                    fitName += character;
                                                    once = true;  // other spaces will just be spaces in the name
                                                }
                                                else
                                                {
                                                    fitName += character;
                                                }
                                            }
                                            airlineTable[num + 1][j] = fitName;
                                            fitName = "";
                                            once = false;
                                        }
                                        else  // if not the airline name, get the score associated to the particular column
                                        {
                                            airlineTable[num + 1][j] = to_string(routeVec[num]->getScores()[j-1]);
                                        }
                                    }
                                }
                                if (num < 5)  // if there are more empty rows in the table, fill in with "-"
                                {
                                    for (int i = num+1; i < 6; i++)
                                    {
                                        for (int j = 0; j < airlineTable[0].size(); j++)
                                        {
                                            airlineTable[i][j] = "-";
                                        }
                                    }
                                }
                                for (int i = 0; i < airlineTable.size(); ++i)  // creates the table and lays the text over the corresponding cells
                                {
                                    for (int j = 0; j < airlineTable[i].size(); ++j)
                                    {
                                        info.setString(airlineTable[i][j]);
                                        info.setPosition(1+posAdjustX+(cellWidth * (float)j), posAdjustY+(cellHeight * (float)i));  // +1 for proper fit in cell
                                        info.setFillColor(sf::Color::Black);
                                        values[i*airlineTable[i].size()+j] = info;
                                    }
                                }
                            }
                        }
                    }
                }
                case sf::Event::TextEntered:  // will activate the textbox to receive input (only if selected)
                {
                    fromLoc.typedOn(event);
                    toLoc.typedOn(event);
                }
            }
            // reset screen to sky blue
            window.clear(lightBlue);

            // renders the left-hand side text + right-hand side text + screen split
            window.draw(title);
            window.draw(theFlightCrew);
            window.draw(fromText);
            window.draw(toText);
            window.draw(rightHandTitle);
            window.draw(instructionsTitle);
            window.draw(instructionsDesc);
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

            // puts the text in the table cells
            for (const auto& text : values)
            {
                window.draw(text);
            }

            // renders times of data structures and invalid route message
            window.draw(hashTime);
            window.draw(splayTime);
            window.draw(invalidRouteError);

            // shows the new window frame
            window.display();
        }
    }
}
