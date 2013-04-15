#include "include/object.h"
#include <math.h>
#include <sstream>

int main()
{
    //mass,radius,x,y
    Object * moon  = new Object("Moon",7.34767309e22,.017,720,300.7844);
    Object * earth = new Object("Earth",5.97219e24,.133,720,300.4);
    Object * sun   = new Object("Sun",1.9891e30,.69,720,450);
    Object * mars  = new Object("Mars",0.64185e24,.339,720,243);

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
    std::vector<Object*> bodies;

    bodies.push_back(sun);
    bodies.push_back(earth);
    bodies.push_back(moon);
    bodies.push_back(mars);

	int index = 0;
	// Start the game loop
    while (App.isOpen())
    {
        sf::View view;
        view.reset(sf::FloatRect(0, 0, 300, 300));
        view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
        //view.setCenter(earth->circle.getPosition().x+earth->getRadius(),earth->circle.getPosition().y+earth->getRadius());
        view.setCenter(bodies[index]->circle.getPosition().x+bodies[index]->getRadius(),bodies[index]->circle.getPosition().y+bodies[index]->getRadius());
        view.zoom(.00995);
        App.setView(view);

        mars ->updateValues();
        moon ->updateValues();
        earth->updateValues();

        moon ->move();
        earth->move();
        mars ->move();

        // Create a stringstream to later convert to sf::text
        std::stringstream ss;

        //HOLY SHIT DATAAAAAAA
        ss << "Press the left and right arrow keys to select different objects, press up and down to change their mass.";
        ss << "\nSun Coordinates: ("              << sun->circle.getPosition().x<<","<<sun->circle.getPosition().y << ")\n";
        ss << "\nObject selected: "               << bodies[index]->getName();
        ss << "'s current mass: "                 << bodies[index]->getMass();

        //Put our data into something sfml can display.
        sf::Text text(ss.str());

        //Text characteristics
        text.setCharacterSize(30);
        text.setStyle(sf::Text::Bold);
        text.setColor(sf::Color::Red);
        text.setPosition(50,5);

        // Process events
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            // Close window : exit
            if(Event.type == sf::Event::Closed)
            {
                App.close();
            }

            if(Event.type == sf::Event::KeyPressed)
            {
                switch(Event.key.code)
                {
                    case sf::Keyboard::Left:
                    {
                        if(index+1==bodies.size())
                        {
                            index=0;
                        }
                        else
                        {
                            index++;
                        }

                        break;
                    }

                    case sf::Keyboard::Right:
                    {
                        if(index-1<0)
                        {
                            index=bodies.size()-1;
                        }
                        else
                        {
                            index--;
                        }

                        break;
                    }

                    case sf::Keyboard::Up:
                    {
                        if(Event.key.code == sf::Keyboard::Up)
                        {
                            bodies[index]->setMass(bodies[index]->getMass()+1.0e30);
                        }

                        break;
                    }

                    case sf::Keyboard::Down:
                    {
                        if(Event.key.code == sf::Keyboard::Down)
                        {
                            bodies[index]->setMass(bodies[index]->getMass()-1.0e30);
                        }

                        break;
                    }

                    case sf::Keyboard::Escape:
                    {
                        App.close();
                        break;
                    }

                    default:
                    {
                        break;
                    }
                }
                /*if(Event.key.code == sf::Keyboard::Escape)
                {
                    App.close();
                }
                if(Event.key.code == sf::Keyboard::Left)
                {
                    if(index+1==bodies.size())
                    {
                        index=0;
                    }
                    else
                    {
                        index++;
                    }
                }

                if(Event.key.code == sf::Keyboard::Right)
                {
                    if(index-1<0)
                    {
                        index=bodies.size()-1;
                    }
                    else
                    {
                        index--;
                    }
                }
                if(Event.key.code == sf::Keyboard::Up)
                {
                    bodies[index]->setMass(bodies[index]->getMass()+1.0e22);
                }

                if(Event.key.code == sf::Keyboard::Down)
                {
                    bodies[index]->setMass(bodies[index]->getMass()-1.0e22);
                }*/
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

        App.draw(marsCirc);
        App.draw(earthCirc);
        App.draw(moonCirc);
        App.draw(sunCirc);

        // Update the window
        App.display();
    }

    return EXIT_SUCCESS;
}
