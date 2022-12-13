#pragma once

#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "tinyxml.h"

struct Object {
    int GetPropertyInt(std::string name);//номер свойства объекта в нашем списке
    float GetPropertyFloat(std::string name);

    std::string GetPropertyString(std::string name);

    std::string name;//объявили переменную name типа string
    std::string type;//а здесь переменную type типа string
    sf::Rect<float> rect;

    sf::Rect<float> & getRect();

    sf::Sprite & getSprite();

//тип Rect с нецелыми значениями
    std::map<std::string, std::string> properties;//создаём ассоциатиный массив. ключ - строковый тип, значение - строковый
    sf::Sprite sprite;//объявили спрайт
};

int Object::GetPropertyInt(std::string name)//возвращаем номер свойства в нашем списке
{
    return atoi(properties[name].c_str());
}

float Object::GetPropertyFloat(std::string name) {
    return strtod(properties[name].c_str(), NULL);
}

std::string Object::GetPropertyString(std::string name)//получить имя в виде строки.вроде понятно
{
    return properties[name];
}

sf::Rect<float> & Object::getRect() {
    return rect;
}

sf::Sprite & Object::getSprite() {
    return sprite;
}
