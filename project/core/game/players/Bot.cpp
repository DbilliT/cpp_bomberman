//
// Bot.cpp for Bot in /home/david_k/cpp_rendu/cpp_bomberman/project/core/game/players
// 
// Made by paul david
// Login   <david_k@epitech.net>
// 
// Started on  Sun May 24 15:32:16 2015 paul david
// Last update Sun Jun 14 15:08:22 2015 paul david
//

#include "Bot.hpp"

Bot::Bot(std::pair<unsigned int, unsigned int> const &pos, unsigned int color) : character(pos, color)
{}

Bot::Bot(std::pair<unsigned int, unsigned int> const &pos, unsigned int color, unsigned int speed, unsigned int power, unsigned int bomb) : character(pos, color, speed, power, bomb)
{
}

Bot::~Bot()
{}
