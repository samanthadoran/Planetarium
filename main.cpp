#include "include/object.h"
#include <math.h>
#include <sstream>
#include <iostream>
int main()
{
    //Name, mass, radius, x, y
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

    //Consider switching this to initializeVelocity(long double velocity, long double theta)
    moon ->calcVelocity(1030+29300.0l,0.0);
    mars ->calcVelocity(26500.0l,0.0);
    earth->calcVelocity(29300,0.0);

    moon ->calcVelocityTheta(1030+29300.0l,0.0);
    earth->calcVelocityTheta(29300,0.0);
    mars ->calcVelocityTheta(26500.0l,0.0);

    //Give earth pointers to the objects that can modify it.
    earth->addModifier(moon);
    earth->addModifier(sun);
    earth->addModifier(mars);

    //Give the moon pointers to the objects that can modify it.
    moon->addModifier(sun);
    moon->addModifier(earth);
    moon->addModifier(mars);

    //Give mars pointers to the objects that can modify it.
    mars->addModifier(sun);
    mars->addModifier(earth);
    mars->addModifier(moon);

    //Give the sun pointers to the objects that can modify it.
    sun->addModifier(earth);
    sun->addModifier(moon);
    sun->addModifier(mars);

    std::vector<Object*> bodies;

    //Make loops easier
    bodies.push_back(sun);
    bodies.push_back(earth);
    bodies.push_back(moon);
    bodies.push_back(mars);

	//Used to navigate the object list
	unsigned int index = 0;
	//Magnifying glass
	bool focus = true;

	// Start the game loop
    while (App.isOpen())
    {
        sf::View view;

        //If we are focusing, zoom in on our target!
        if(focus)
        {
            view.reset(sf::FloatRect(0, 0, 300, 300));
            view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
            view.setCenter(bodies[index]->circle.getPosition().x+bodies[index]->getRadius(),bodies[index]->circle.getPosition().y+bodies[index]->getRadius());
            view.zoom(.00995);
            App.setView(view);
        }
        else
        {
            App.setView(App.getDefaultView());
        }

        //Update everything relative to its modifiers before we move things, thus movement is simultaneous
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
        ss << "\nPress v to switch between solar system focus the object you have selected";
        ss << "\nSun Coordinates: ("              << sun->getX() <<"," << sun->getY() << ")\n";
        ss << "\nObject selected: "               << bodies[index]->getName();
        ss << "'s current mass: "                 << bodies[index]->getMass();

        //Put our data into something sfml can display.
        sf::Text text(ss.str());

        //Text characteristics
        text.setCharacterSize(30);
        text.setStyle(sf::Text::Bold);
        text.setColor(sf::Color::Green);
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
                    //Move up our vector
                    case sf::Keyboard::Left:
                    {
                        //Loop around if we hit the top of the vector
                        if(index+1==bodies.size())
                        {
                            index=0;
                        }
                        else
                        {
                            ++index;
                        }

                        break;
                    }

                    //Move down our vector
                    case sf::Keyboard::Right:
                    {
                        //Loop around if we hit the bottom of the vector
                        if(index==0)
                        {
                            index=bodies.size()-1;
                        }
                        else
                        {
                            --index;
                        }

                        break;
                    }

                    //Modify the mass of the object at position index, consider making this dynamic relative to current mass
                    case sf::Keyboard::Up:
                    {
                        if(Event.key.code == sf::Keyboard::Up)
                        {
                            bodies[index]->setMass(bodies[index]->getMass()+1.0e30);
                        }

                        break;
                    }

                    //Modify the mass of the object at position index, consider making this dynamic relative to current mass
                    case sf::Keyboard::Down:
                    {
                        if(Event.key.code == sf::Keyboard::Down)
                        {
                            bodies[index]->setMass(bodies[index]->getMass()-1.0e30);
                        }

                        break;
                    }

                    //Switch between showing the solar system and a finer view of the object selected
                    case sf::Keyboard::V:
                    {
                        focus=!focus;
                        if(focus)
                        {
                            for(Object *x : bodies)
                            {
                                x->setRadius(x->getRadius()/10.0);
                            }
                        }
                        else
                        {
                            for(Object *x : bodies)
                            {
                                x->setRadius((x->getRadius()*10.0));
                            }
                        }

                        break;
                    }

                    //Quit
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
            }
        }

        // Clear screen
        App.clear();

        //Draw our drawables
        App.draw(text);

        for(Object *x: bodies)
        {
            App.draw(x->circle);
        }

        // Update the window
        App.display();
    }

    return EXIT_SUCCESS;
}
