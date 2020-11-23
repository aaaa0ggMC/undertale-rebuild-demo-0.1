#ifndef UT_HPP_INCLUDED
#define UT_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;
using namespace sf;

class Animation{
public:
    std::vector<sf::Texture> ani;
    std::string name;
    std::vector<sf::Texture>::iterator it;
    Animation(){
        name = "";
        it = ani.end();
    }
    Animation(std::string name,std::vector<sf::Texture> init){
        this->name = name;
        ani = init;
        it = ani.begin();
    }
    void update(sf::Sprite & s){
        if(ani.size() <= 0)return;
        if(it == ani.end())it = ani.begin();
        else it++;
        s.setTexture(ani[it - ani.begin()],true);
    }
    void back(){
        it = ani.begin();
    }
};

class Animator{
public:
    sf::Sprite man;
    std::vector<Animation> anis;
    std::vector<Animation>::iterator it;
    Animator(std::vector<Animation> t):anis(t){it = anis.begin();}
    Animator(){}
    int play(std::string name){
        for(it = anis.begin();it < anis.end();it++)
            it->back();
        for(it = anis.begin();it < anis.end();it++)
            if(it->name == name)break;
        if(it == anis.end())return -1;
        return 0;
    }
    void update(){
        return it->update(man);
    }
};


#endif // UT_HPP_INCLUDED
