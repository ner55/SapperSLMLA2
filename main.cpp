#include "Sapper.h"
#include <iostream>
#include <SFML/Graphics.hpp>
int main()
{
    Sapper sapper;
    sapper.minesRandom(false, -1, -1);
    sf::RenderWindow window(sf::VideoMode(45 * sapper.fieldWidth + 5, 45 * sapper.fieldHeight + 55), "Sapper A2", sf::Style::Close);
    window.setFramerateLimit(60);
    sf::Font font;
    font.loadFromFile("resources/Comic Sans MS.ttf");
    sf::Text minesText;
    minesText.setFont(font);
    minesText.setString("Mines on field: " + std::to_string(sapper.minesCount));
    minesText.setCharacterSize(35);
    minesText.setFillColor(sf::Color::Red);
    minesText.setStyle(sf::Text::Bold);
    minesText.setPosition(10.f, 5.f);
    bool first = true;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                mine tMine(trunc(sf::Mouse::getPosition(window).x/45)+1, trunc((sf::Mouse::getPosition(window).y)/45));
                bool add = true;
                for (int i = 0; i < sapper.discoveredCells.size(); i++)
                {
                    if (sapper.discoveredCells[i].x == tMine.x && sapper.discoveredCells[i].y == tMine.y) add = false;
                }
                if (add ) {
                    sapper.discoveredCells.push_back(tMine);
                    first = false;
                }
                //std::cout << "x: " << tMine.x << "y: " << tMine.y << "\n";
            }            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) sapper.dCells();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) sapper.minesOutput();
        }

        window.clear(sf::Color(80, 80, 80));
        for (int i = 0; i < sapper.discoveredCells.size(); i++)
        {
            if (sapper.minesAround(sapper.discoveredCells[i].x, sapper.discoveredCells[i].y, false, false) == 10)
            {
                sapper.win = -1;
            }
            if (sapper.discoveredCells.size() == sapper.fieldHeight * sapper.fieldWidth - sapper.minesCount)
            {
                sapper.win = 1;
            }
        }
        for (int i1 = 0; i1 < sapper.fieldWidth; i1++)
        {
            for (int i2 = 0; i2 < sapper.fieldWidth; i2++)
            {
                bool discovered = false;
                for (int i = 0; i < sapper.discoveredCells.size(); i++)
                {
                    if (sapper.discoveredCells[i].x == i1 + 1 && sapper.discoveredCells[i].y == i2 + 1) discovered = true;
                }
                sf::RectangleShape rectangle(sf::Vector2f(40.f, 40.f));
                rectangle.setPosition(5.f + 45 * i1, 5.f + 45 * i2 + 50);
                if (discovered) 
                {
                    rectangle.setFillColor(sf::Color(185, 185, 185));
                } else
                rectangle.setFillColor(sf::Color(230, 230, 230));
                sf::Text mineText;
                mineText.setFont(font);
                window.draw(rectangle);
                if (sapper.minesAround(i1 + 1, i2 + 1, false, false) != 10 && discovered && sapper.minesAround(i1 + 1, i2 + 1, false, false) != 0)
                {
                    mineText.setString(std::to_string(sapper.minesAround(i1 + 1, i2 + 1, false, false)));
                    mineText.setFillColor(sf::Color::Yellow);
                    mineText.setCharacterSize(25);
                    mineText.setPosition(5.f + 45 * i1 + 15, 5.f + 45 * i2 + 5+ 50);
                    mineText.setStyle(sf::Text::Bold);
                    window.draw(mineText);
                }

                
            }
        }
        sf::RectangleShape grectangle(sf::Vector2f(330.f, 130.f));
        grectangle.setPosition(35.f, 260.f);
        grectangle.setFillColor(sf::Color(60, 60, 60));
        window.draw(minesText);
        if (sapper.win == -1) {
            for (int i = 0; i < sapper.minesCount; i++)
            {
                sf::Text mine;
                mine.setFont(font);
                mine.setString("m");
                mine.setCharacterSize(20);
                mine.setPosition(sapper.mines[i].x * 45.f-25, sapper.mines[i].y * 45.f+ 18);
                mine.setFillColor(sf::Color::Red);
                mine.setStyle(sf::Text::Bold);
                window.draw(mine);
            }
            
            window.draw(grectangle);
            sf::Text lt;
            lt.setFont(font);
            lt.setString("You lost!");
            lt.setCharacterSize(50);
            lt.setPosition(65.f, 280.f);
            lt.setFillColor(sf::Color::Red);
            lt.setStyle(sf::Text::Bold);
            window.draw(lt);
        }
        else if (sapper.win == 1)
        {
            for (int i = 0; i < sapper.minesCount; i++)
            {
                sf::Text mine;
                mine.setFont(font);
                mine.setString("m");
                mine.setCharacterSize(20);
                mine.setPosition(sapper.mines[i].x * 45.f - 25, sapper.mines[i].y * 45.f + 18);
                mine.setFillColor(sf::Color::Red);
                mine.setStyle(sf::Text::Bold);
                window.draw(mine);
            }
            window.draw(grectangle);
            sf::Text wt;
            wt.setFont(font);
            wt.setString("You won!");
            wt.setCharacterSize(50);
            wt.setPosition(80.f, 280.f);
            wt.setFillColor(sf::Color::Green);
            wt.setStyle(sf::Text::Bold);
            window.draw(wt);
        }


        window.display();

    }
}