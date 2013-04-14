#include "include/object.h"
#include <math.h>
#include <sstream>

int main()
{
    //mass,radius,x,y
    Object * moon  = new Object(7.34767309e22,.17,720,300.7844);
    Object * earth = new Object(5.97219e24,1.33,720,300.4);
    Object * sun   = new Object(1.9891e30,6.9,720,450);
    Object * mars  = new Object(0.64185e24,3.39,720,243);

    mars ->circle.setFillColor(sf::Color::Red);
    earth->circle.setFillColor(sf::Color::Blue);
    moon ->circle.setFillColor(sf::Color::White);
    sun  ->circle.setFillColor(sf::Color::Yellow);

    // Create the main window
    sf::RenderWindow App(sf::VideoMode(1920, 1030), "SFML window");
    App.setVerticalSyncEnabled(true);

    moon ->calcVelocity(1030+29300.0l,0.0);
    mars ->calcVelocity(26500.0l,0.0);
    earth->calcVelocity(29300,0.0);

    moon ->calcVelocityTheta(1030+29300.0l,0.0);
    earth->calcVelocityTheta(29300,0.0);
    mars ->calcVelocityTheta(26500.0l,0.0);

    earth->addModifier(moon);
    earth->addModifier(sun);
    earth->addModifier(mars);

    moon->addModifier(sun);
    moon->addModifier(earth);
    moon->addModifier(mars);

    mars->addModifier(sun);
    mars->addModifier(earth);
    mars->addModifier(moon);

    sun->addModifier(earth);
    sun->addModifier(moon);
    sun->addModifier(mars);

	// Start the game loop
    while (App.isOpen())
    {
        sf::View view;
        view.reset(sf::FloatRect(0, 0, 300, 300));
        view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
        view.setCenter(earth->circle.getPosition().x+earth->getRadius(),earth->circle.getPosition().y+earth->getRadius());
        view.zoom(.00995);
        //App.setView(view);

        mars ->updateValues();
        moon ->updateValues();
        earth->updateValues();
        //sun  ->updateValues();

        moon ->move();
        earth->move();
        mars ->move();
        //sun  ->move();

        // Create a stringstream to later convert to sf::text
        std::stringstream ss;

        //HOLY SHIT DATAAAAAAA
        ss << "\nSun Coordinates: ("              << sun->circle.getPosition().x<<","<<sun->circle.getPosition().y << "\n";
        /*ss <<"\nVx: "                            << moon->velocity*cos(moon->theta*(PI/180.0));
        ss << "\nVy: "                            << moon->velocity*sin(moon->theta*(PI/180.0));
        ss << "\nVTheta: "                        << moon->theta;
        ss << "\nObj_x: "                         << moon->circle.getPosition().x;
        ss << "\nObj_y: "                         << moon->circle.getPosition().y;
        ss << "\nDistance from earth to moon: "   << moon->calcDist(*earth)/1000;
        ss << "\nDistance from sun to earth: "    << earth->calcDist(*sun);*/

        //Put our data into something sfml can display.
        sf::Text text(ss.str());

        //Text characteristics
        text.setCharacterSize(50);
        text.setStyle(sf::Text::Bold);
        text.setColor(sf::Color::Red);
        text.setPosition(50,5);

        // Process events
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            // Close window : exit
            if (Event.type == sf::Event::Closed)
            {
                App.close();
            }
        }

        // Clear screen
        App.clear();

        //Draw our drawables
        App.draw(text);

        sf::CircleShape moonCirc = moon->circle;
        moonCirc.move(-1*moon->getRadius(), -1*moon->getRadius());

        sf::CircleShape earthCirc = earth->circle;
        earthCirc.move(-1*earth->getRadius(),-1*earth->getRadius());

        sf::CircleShape sunCirc = sun->circle;
        sunCirc.move(-1*sun->getRadius(),-1*sun->getRadius());

        sf::CircleShape marsCirc = mars->circle;
        marsCirc.move(-1*mars->getRadius(),-1*mars->getRadius());
        //earth->circle.rotate(10);
        App.draw(marsCirc);
        App.draw(earthCirc);
        App.draw(moonCirc);
        App.draw(sunCirc);

        // Update the window
        App.display();
    }

    return EXIT_SUCCESS;
}
