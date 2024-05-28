#include "stdafx.h"
#include "Game.h"



bool menu() {


    //main menu details
    int menu_counter = 0;
    sf::Texture Menu;
    sf::Sprite Menus;
    sf::Font font;
    sf::Text play;
    sf::Text exits;
    sf::Event menuEvent;

        //menu details
        play.setFont(font);
        exits.setFont(font);
        play.setFillColor(sf::Color::Red);
        exits.setFillColor(sf::Color::Red);
        play.setString("Play");
        exits.setString("Exit");
        play.setCharacterSize(60);
        exits.setCharacterSize(60);
        play.setPosition(850, 300);
        exits.setPosition(850, 400);

        bool runs = false;

        //Music 
        sf::Music music;
        sf::RenderWindow Window;

        Window.create(sf::VideoMode(1900, 608), "Zombie Slayer");


        if (!Menu.loadFromFile("Images/menu.png"))
        {
            std::cout << "ERROR::GAME::COULD_NOT_SHOW_MAP" << "\n";
        }

        Menus.setTexture(Menu);


        if (!music.openFromFile("Images/song.ogg"))
        {
            std::cout << "ERROR" << std::endl;
        }

        music.play();

        if (!font.loadFromFile("Images/fontinho.ttf")) {
            std::cout << "cant load font" << std::endl;
        }


        while (Window.isOpen() == true)
        {
            Window.draw(Menus);
            Window.draw(play);
            Window.draw(exits);
            Window.display();

            Window.pollEvent(menuEvent); // polling/checking events in menu

            if (menuEvent.type == sf::Event::Closed) //pressing the X on the window closes game
            {
                Window.close();
                return true;
            }

            if (menuEvent.type == sf::Event::KeyPressed && menuEvent.key.code == sf::Keyboard::Down)
            {
                menu_counter = menu_counter + 1;

                if (menu_counter == 0)
                {
                    runs = true;
                    play.setFillColor(sf::Color::White);
                    exits.setFillColor(sf::Color::Red);
                }
                else if (menu_counter == 1)
                {
                    runs = false;
                    exits.setFillColor(sf::Color::White);
                    play.setFillColor(sf::Color::Red);
                }
            }

            if (menuEvent.type == sf::Event::KeyPressed && menuEvent.key.code == sf::Keyboard::Up)
            {
                menu_counter = menu_counter - 1;

                if (menu_counter == 0)
                {
                    runs = true;
                    play.setFillColor(sf::Color::White);
                    exits.setFillColor(sf::Color::Red);
                }
                else if (menu_counter == 1)
                {
                    runs = false;
                    exits.setFillColor(sf::Color::White);
                    play.setFillColor(sf::Color::Red);
                }
            }

            if (menu_counter > 1) {
                menu_counter -= 1;
            }

            if (menuEvent.type == sf::Event::KeyPressed && menuEvent.key.code == sf::Keyboard::Enter && runs == true)
            {
                Window.close();

                Game slayer; //game class basically engine
                srand(static_cast<unsigned>(time(0)));

                while (slayer.getWindow().isOpen())
                {
                    slayer.update();
                    slayer.render();
                }
                Window.create(sf::VideoMode(1900, 608), "Zombie Slayer");
            }
            if (menuEvent.type == sf::Event::KeyPressed && menuEvent.key.code == sf::Keyboard::Enter && runs == false)
            {
                Window.close();
                return true;
            }

        }
 }



int main()
{
    int count= 1;

    while (count != 0){

        if (menu() == true)
        {
            count = 0;
        }
    }

    return 0;
}

