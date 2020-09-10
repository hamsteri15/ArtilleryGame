#pragma once


#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <time.h>
#include <memory>
#include <SFML/Graphics.hpp>
#include "calc.hpp"



class Map
{
public:

    ////////////////////////////////////////////////////////////
    ///
    ///    \Class constructor.
    ///    \param sizee: the screen size vector
    ///
    ////////////////////////////////////////////////////////////
    Map(sf::Vector2u size);
    
    
    
    ////////////////////////////////////////////////////////////
    ///
    ///    \Default destructor.
    ///
    ////////////////////////////////////////////////////////////
    ~Map() = default;
    
    

    
    
    
    ////////////////////////////////////////////////////////////
    ///
    ///    \Checks if a location is inside ground.
    ///    \param loc: location to be checked    
    ///     
    ////////////////////////////////////////////////////////////
    bool isLand(const sf::Vector2u& loc) const;



	////////////////////////////////////////////////////////////
	///
	///    \Checks if a location is outside the map.
	///    \param loc: location to be checked    
	///     
	////////////////////////////////////////////////////////////
	bool outOfBounds(const sf::Vector2u& loc) const;
    


    ////////////////////////////////////////////////////////////
    ///
    ///    \Makes a circular hole to the ground. Essentially this
    ///     this colors the map image with the background color.
    ///    \param loc: location of the hole    
    ///    \param r: radius of the hole
    ////////////////////////////////////////////////////////////
    void makeHole(const sf::Vector2u& loc, int r);
    


    //void updatePlayerLocs(std::vector<Player> players);

	
    
    ////////////////////////////////////////////////////////////
    ///
    ///    \Obvious getter functions. Nothing special here.
    ///
    ////////////////////////////////////////////////////////////
    const sf::Vector2u& getSize() const {
        return m_size;
    }
    
    const sf::Texture& getTexture() const {
        return m_texture;
    }

    void draw(sf::RenderWindow& window);
    
    
private:
    
    sf::Vector2u    m_size;
    sf::Texture     m_rockTexture;
    sf::Texture     m_airTexture;
    sf::Image       m_image;    
    sf::Texture     m_texture;


    
    ////////////////////////////////////////////////////////////
    ///
    ///    \Randomly creates the initial land shape. Called
    ///     from constructor.
    ///    \Note that an image of the land must be stored to
    ///     get access to the color-picker functions in SFML.
    ///    
    ////////////////////////////////////////////////////////////
    sf::Image randomizeLand();
    
};


