//
//  Event.cpp
//  Build-Age
//
//  Created by Patrik Štrba on 2.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#include "Client/Control/Events.h"

#include "Client/World/World.h"

void Events::startListening(Player *p) {
    c = Control::instance();
    WSFML *w = WSFML::instance();
    
    sf::Event event;
    sf::Vector2i m, wpc;
    
    while(w->getWindow()->isOpen()) {
        while (WSFML::instance()->getWindow()->pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    WSFML::instance()->getWindow()->close();
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code) {
                        case sf::Keyboard::Left:
                        case sf::Keyboard::A:
                            c->k_left = true;
                            break;
                        case sf::Keyboard::Right:
                        case sf::Keyboard::D:
                            c->k_right = true;
                            break;
                        case sf::Keyboard::Up:
                        case sf::Keyboard::W:
                            c->k_up = true;
                            break;
                        case sf::Keyboard::Down:
                        case sf::Keyboard::S:
                            c->k_down = true;
                            break;
                        case sf::Keyboard::Space:
                            c->k_jump = true;
                            break;
                        case sf::Keyboard::Q:
                            WSFML::instance()->close();
                            break;
                            
                            
                        case sf::Keyboard::O:
                            c->y += 0.5;
                            break;
                        case sf::Keyboard::L:
                            c->y -= 0.5;
                            break;
                            
                        default:
                            break;
                    }
                    break;
                    
                case sf::Event::KeyReleased:
                    switch(event.key.code) {
                        case sf::Keyboard::Left:
                        case sf::Keyboard::A:
                            c->k_left = false;
                            break;
                        case sf::Keyboard::Right:
                        case sf::Keyboard::D:
                            c->k_right = false;
                            break;
                        case sf::Keyboard::Up:
                        case sf::Keyboard::W:
                            c->k_up = false;
                            break;
                        case sf::Keyboard::Down:
                        case sf::Keyboard::S:
                            c->k_down = false;
                            break;
                        default:
                            break;
                    }
                    break;
                    
                case sf::Event::MouseMoved:
                    m = sf::Mouse::getPosition(*WSFML::instance()->getWindow());
                    wpc.x = WSFML::getWidth()/2;
                    wpc.y = WSFML::getHeight()/2;
                    
                    
                    //printf("%d %d # %d %d\n",m.x,m.y, sf::Mouse::getPosition().x,sf::Mouse::getPosition().y);
                    if(m.x != wpc.x || m.y != wpc.y) {
                        //printf("CHANGE\n");
                        p->setView(m.x, m.y);

                        sf::Mouse::setPosition(sf::Vector2i(wpc.x, wpc.y), *WSFML::instance()->getWindow());
                    }
                    break;
                    
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Left)
                        c->m_left = true;
                    if(event.mouseButton.button == sf::Mouse::Right)
                        c->m_right = true;
                    break;
                    
                case sf::Event::MouseButtonReleased:
                    if(event.mouseButton.button == sf::Mouse::Left)
                        c->m_left = false;
                    if(event.mouseButton.button == sf::Mouse::Right)
                        c->m_right = false;
                    break;
                default:
                    break;
            }
        }
        //sf::sleep(sf::milliseconds(1));
    }
}