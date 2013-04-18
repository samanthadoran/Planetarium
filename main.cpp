#include "include/object.h"
#include <sstream>
int main()
{
    /*Group the planets and their respective moons, using columns for clarity.
                                   Name,     mass,           radius,     x,   y*/
    Object * sun     = new Object("Sun",     1.9891e30l,     6.955e-1l,  720, 450);

    Object * mercury = new Object("Mercury", 3.3022e23l,     2.44e-3l,   720, 392.09);

    Object * venus   = new Object("Venus",   4.867e24l,      6.052e-3l,  720, 342.523);

    Object * earth   = new Object("Earth",   5.97219e24l,    6.371e-3l,  720, 300.4);
    Object * moon    = new Object("Moon",    7.34767309e22l, 1.7374e-3l, 720, 300.7844l);

    Object * mars    = new Object("Mars",    6.4185e23l,     3.39e-3l,   720, 243);
    Object * deimos  = new Object("Deimos",  1.48e15l,       6.2e-6l,    720, 242.97654l);
    Object * phobos  = new Object("Phobos",  1.072e16l,      1.11e-5l,   720, 242.990765l);

    //Make loops easier
    std::vector<Object*> bodies;

    bodies.push_back(sun);

    bodies.push_back(venus);

    bodies.push_back(mercury);

    bodies.push_back(earth);
    bodies.push_back(moon);

    bodies.push_back(mars);
    bodies.push_back(deimos);
    bodies.push_back(phobos);

    //Every object modifies each other, however, it does not modify itself
    for(Object *x: bodies)
    {
        for(Object *y: bodies)
        {
            if(!(*y == *x))
            {
                y->addModifier(x);
            }
        }
    }

    sun    ->circle.setFillColor(sf::Color::Yellow);

    mercury->circle.setFillColor(sf::Color::Cyan);

    venus  ->circle.setFillColor(sf::Color::White);

    earth  ->circle.setFillColor(sf::Color::Blue);
    moon   ->circle.setFillColor(sf::Color::White);

    mars   ->circle.setFillColor(sf::Color::Red);
    deimos ->circle.setFillColor(sf::Color::White);
    phobos ->circle.setFillColor(sf::Color::White);

    // Create the main window
    sf::RenderWindow App(sf::VideoMode(1920, 1030), "SFML window");
    App.setVerticalSyncEnabled(true);

    //calcMomentum takes two arguments: the x and y component of velocity.
    sun    ->calcMomentum(0.0,           0.0);

    venus  ->calcMomentum(35020,         0.0);

    mercury->calcMomentum(47870,         0.0);

    earth  ->calcMomentum(29300,         0.0);
    moon   ->calcMomentum(1030+29300.0l, 0.0);

    mars   ->calcMomentum(26500.0l,      0.0);
    deimos ->calcMomentum(1350+26500.0l, 0.0);
    phobos ->calcMomentum(2138+26500.0l, 0.0);

	//Used to navigate the object list
	unsigned int index = 0;

	//Magnifying glass
	bool focus = true;

	// Start the game loop
    while (App.isOpen())
    {
        //Update everything relative to its modifiers before we move things, thus movement is simultaneous
        for(Object *x: bodies)
        {
            x->updateValues();
        }

        for(Object *x: bodies)
        {
            x->move();
        }

        //If we are focusing, zoom in on our target!
        if(focus)
        {
            sf::View view;
            view.setCenter(bodies[index]->circle.getPosition());
            //view.zoom(.0008999); //Reg zoom
            view.zoom(.0000999); //Phobos/Deimos zoom
            App.setView(view);
        }
        else
        {
            App.setView(App.getDefaultView());
        }

        // Create a stringstream to later convert to sf::text
        std::stringstream ss;

        //HOLY SHIT DATAAAAAAA
        ss << "Press the left and right arrow keys to select different objects, press up and down to change their mass.";
        ss << "\nPress v to switch between solar system focus the object you have selected";
        ss << "\nSun Coordinates: ("              << sun->getX() <<"," << sun->getY() << ")\n";
        ss << "\nObject selected: "               << bodies[index]->getName();
        ss << "'s current mass: "                 << bodies[index]->getMass();
        ss << "\nDistance from "                  << bodies[index]->getName() << " to the Sun: "<< bodies[index]->calcDist(*sun);

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
                break;
            }

            if(Event.type == sf::Event::KeyPressed)
            {
                switch(Event.key.code)
                {
                    //Move up our vector
                    case sf::Keyboard::Right:
                    {
                        //Loop around if we hit the top of the vector
                        if(index+1 == bodies.size())
                        {
                            index = 0;
                        }
                        else
                        {
                            ++index;
                        }

                        break;
                    }

                    //Move down our vector
                    case sf::Keyboard::Left:
                    {
                        //Loop around if we hit the bottom of the vector
                        if(index == 0)
                        {
                            index = bodies.size()-1;
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
                        bodies[index]->setMass(bodies[index]->getMass()+1.0e30);

                        break;
                    }

                    //Modify the mass of the object at position index, consider making this dynamic relative to current mass
                    case sf::Keyboard::Down:
                    {
                        bodies[index]->setMass(bodies[index]->getMass()-1.0e30);

                        break;
                    }

                    //Switch between showing the solar system and a finer view of the object selected
                    case sf::Keyboard::V:
                    {
                        focus =! focus;
                        if(focus)
                        {
                            for(Object *x : bodies)
                            {
                                x->setRadius(x->getRadius()/100.0);
                            }
                        }
                        else
                        {
                            for(Object *x : bodies)
                            {
                                x->setRadius((x->getRadius()*100.0));
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
