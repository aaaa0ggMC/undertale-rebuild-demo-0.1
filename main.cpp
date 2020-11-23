#include <SFML/Graphics.hpp>
#include <windows.h>
#include <stdio.h>
#include "ut.hpp"

void init(sf::RenderWindow & win);
void start(sf::RenderWindow & win);

void dataLoad();

sf::Font sansation,pixel;

sf::Music bgm;

int main()
{

    dataLoad();

    // Create the main window
    sf::RenderWindow win(sf::VideoMode(800, 600),
                          "Undertale Demo BY aaaa0ggMc"
                          ,sf::Style::Titlebar | sf::Style::Close);


    init(win);
    start(win);

    while (win.isOpen()){
        sf::Event e;
        while(win.pollEvent(e)){
            if(e.type == sf::Event::Closed)win.close();
        }
        win.clear();
        win.display();
    }

    return EXIT_SUCCESS;
}

void init(sf::RenderWindow & win){
    int frame = 0;
    bool open = true;
    sf::Time delay = sf::microseconds(0),mdelay = sf::seconds(6);
    sf::Clock cloc;
    sf::Texture img;
    if(!img.loadFromFile("data\\images\\start\\0.png"))exit(EXIT_FAILURE);
    std::vector<std::string> words =
    {
        "Long long ago,two races ruled Earth:\nHUMANS and MONSTERS",
        "One day,war broke out between the two \nraces.",
        "After a long battle,the humans were\n victorious.",
        "They sealed the monsters underground \nwith a magic spell.",
        "In the year 201X,a human child climbs\n Mt.Ebott.",
        "But those that climb the mountain never\n return."
    };
    const int maxFrame = words.size()+3;

    cloc.restart();
    sf::Text text = sf::Text(words[0],pixel,24);
    sf::Text mt = sf::Text("Mt.Ebott",pixel,24);
    sf::Text skip(">>skip",pixel,8);
    sf::Sprite png(img);
    sf::Cursor hand,arrow;
    if(!hand.loadFromSystem(sf::Cursor::Hand))exit(EXIT_FAILURE);
    if(!arrow.loadFromSystem(sf::Cursor::Arrow))exit(EXIT_FAILURE);
    png.setPosition(175,50);
    mt.setPosition(325,550);
    mt.setFillColor(sf::Color::Yellow);
    mt.setOutlineColor(sf::Color::Yellow);
    skip.setPosition(750,580);
    skip.setFillColor(sf::Color::White);
    skip.setOutlineColor(sf::Color::White);
    text.setPosition(10,10);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::White);
    text.rotate(0);
    bgm.play();
    bgm.setVolume(50);
    while (open){
        sf::Event e;
        sf::Vector2i pos = sf::Mouse::getPosition(win);
        while(win.pollEvent(e)){
            if(e.type == sf::Event::Closed){
                win.clear(sf::Color::White);
                win.display();
                for(int i = 0;i < 10;i++){
                    win.setPosition({win.getPosition().x - 10,win.getPosition().y +10});
                    Sleep(5);
                    win.setPosition({win.getPosition().x + 10,win.getPosition().y -10});
                    Sleep(5);
                }
            }
        }
        delay += cloc.restart();
        if(delay >= mdelay){
            frame ++;
            delay = sf::milliseconds(0);
            if(frame > maxFrame-1){open = false;continue;}
            if(frame <= 5)text.setString(words[frame]);
            else mdelay = sf::seconds(8);
            char pic;//仅仅在picture量小于九时有效
            sprintf(&pic,"%d",frame);
            std::string str = "data\\images\\start\\";
            str += &pic;
            str += ".png";
            if(!img.loadFromFile(str))exit(EXIT_FAILURE);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
           || sf::Keyboard::isKeyPressed(sf::Keyboard::B))open = false;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(skip.getGlobalBounds().contains(pos.x,pos.y))open = false;
        }
        if(skip.getGlobalBounds().contains(pos.x,pos.y))
            win.setMouseCursor(hand);
        else win.setMouseCursor(arrow);
        win.clear();
        win.draw(png);
        win.draw(text);
        win.draw(skip);
        if(frame == 4){
            win.draw(mt);
        }
        win.display();
    }
    bgm.stop();
    win.clear();
    win.display();
}

void start(sf::RenderWindow & win){
    sf::Texture imgs[4];
    if(!imgs[0].loadFromFile("data\\images\\man\\lw.png"))exit(EXIT_FAILURE);
    if(!imgs[1].loadFromFile("data\\images\\man\\ls.png"))exit(EXIT_FAILURE);
    if(!imgs[2].loadFromFile("data\\images\\man\\rw.png"))exit(EXIT_FAILURE);
    if(!imgs[3].loadFromFile("data\\images\\man\\rs.png"))exit(EXIT_FAILURE);
    Animator animator({Animation("l",{imgs[0],imgs[1]})
                      ,Animation("r",{imgs[2],imgs[3]})});
    animator.man.setPosition(100,100);
    sf::Time delay = sf::microseconds(0),mdelay = sf::milliseconds(100);
    sf::Clock cloc;
    const float sp = 10;
    animator.play("l");
    animator.update();
    cloc.restart();
    while (true){
        sf::Event e;
        //sf::Vector2i pos = sf::Mouse::getPosition(win);
        while(win.pollEvent(e)){
            if(e.type == sf::Event::Closed){
                win.clear(sf::Color::White);
                win.display();
                for(int i = 0;i < 10;i++){
                    win.setPosition({win.getPosition().x - 10,win.getPosition().y +10});
                    Sleep(5);
                    win.setPosition({win.getPosition().x + 10,win.getPosition().y -10});
                    Sleep(5);
                }
            }
        }
        delay += cloc.restart();
        if(delay >= mdelay){
            delay = sf::milliseconds(0);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                animator.play("l");
                animator.update();
                animator.man.move(-sp,0);
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                animator.play("r");
                animator.update();
                animator.man.move(sp,0);
            }
        }
        win.clear();
        win.draw(animator.man);
        win.display();
    }
}

void dataLoad(){
    if(!sansation.loadFromFile("data\\fonts\\sansation.ttf"))exit(EXIT_FAILURE);
    if(!pixel.loadFromFile("data\\fonts\\pixel.ttf"))exit(EXIT_FAILURE);
    if(!bgm.openFromFile("data\\audio\\story.ogg"))exit(EXIT_FAILURE);
}
