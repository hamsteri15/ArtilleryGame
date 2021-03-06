#pragma once


#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "player.hpp"



class Game
{

public:


    Game() = default;

    ////////////////////////////////////////////////////////////
    ///
    ///    \Class constructor.
    ///    \param numberOfPlayers: amount of players in the game
    ///    \param window: a reference to the game window
    ///
    ////////////////////////////////////////////////////////////
    Game(int numberOfPlayers, sf::RenderWindow& window)
    : m_window(window)
    , m_players(generatePlayers(numberOfPlayers))
    , m_map(Map(window.getSize()))
    , m_playersAlive(numberOfPlayers)
    {
		m_wind = -10 + static_cast <float> (rand() / (static_cast<float>(RAND_MAX)))*20;
	}
    

    ////////////////////////////////////////////////////////////
    ///
    ///    \Starts a new game. Contains the main loop of the game
    ///     and controls all that happens.
    ///
    ////////////////////////////////////////////////////////////
    int newGame();
    

    ////////////////////////////////////////////////////////////
    ///
    ///    \Checks if players are dead and deletes them when found.
    ///
    ////////////////////////////////////////////////////////////   
    void checkHealths();

    
    ////////////////////////////////////////////////////////////
    ///
    ///    \Based on the tag determines the effect the shot has to
    ///     the game and calls the necessary effects.
    ///    \param tag: a tag indicating the shot effect
    ///
    //////////////////////////////////////////////////////////// 
    void shotEffect(int tag);

    const Player& playerInTurn() const{
        return m_players[m_playerInTurn];
    }       

    Player& playerInTurn(){
        return m_players[m_playerInTurn];
    }       

private:
    
    sf::RenderWindow&           m_window;
    std::vector<Player>         m_players;
    Map                         m_map;
    int                         m_playersAlive;
    float                       m_wind;
    
    size_t                      m_playerInTurn;
    sf::Font                    m_font;
    bool                        m_isShooting;
    sf::Texture                 m_explosionTexture;

    
    ///
    ///@brief Creates the players
    ///
    ///@param numberOfPlayers number of players to create
    ///@return std::vector<Player> all players
    ///
    std::vector<Player> generatePlayers(int numberOfPlayers) const;

    ////////////////////////////////////////////////////////////
    ///
    ///    \Initializes the locations of the players in the game.
    ///
    ////////////////////////////////////////////////////////////
    void initPlayerLocations();    


    ////////////////////////////////////////////////////////////
    ///
    ///    \All drawer functions. 
    ///
    ////////////////////////////////////////////////////////////
    void render();
    void drawMap();
    void drawPlayers();
    void drawMenus();
	void drawWeaponStats();
    void drawHealthbars();
    void drawWind();
	void drawTurnIndicator();
    void drawExplosion(sf::Vector2u loc); 

};

