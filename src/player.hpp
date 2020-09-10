#pragma once

#include <SFML/Graphics.hpp>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "map.hpp"
#include "weapon.hpp"
#include "weapon_textures.hpp"
#include "calc.hpp"

class Weapon;
class Player
{
public:

    Player() = default;

    Player(int number);

            


    void setLocation(sf::Vector2u location); 
    



	void changeWeapon(size_t weaponIndex) {
        m_equippedWeapon = weaponIndex;
    }

	void reduceHealth(int damage);
    


    ////////////////////////////////////////////////////////////
	/// 
	///    \Prepares a shooting operation to be drawn from 
    ///     drawShot().
	///    \param aimed: vector, which indicates the initial shot power
	///    \param players: the players in the game (to check if shot hits one)
    ///    \param map: map of the game (to check if bullet hits ground)
    ///    \param wind: randomized wind coefficient
    ///
	////////////////////////////////////////////////////////////
    int shoot(sf::Vector2i aimed, std::vector<Player>& players, Map map, float wind);



    bool isShooting() {
        return m_isShooting;
    }



    bool isHit(const sf::Vector2u& loc) const;



    ////////////////////////////////////////////////////////////
	/// 
	///    \Draws the complete trajectory of the bullet. Special
    ///     effects are drawn from Game.
	///    \param window: a reference to the game window
    ///
	////////////////////////////////////////////////////////////
    void drawShot(sf::RenderWindow& window);



    ////////////////////////////////////////////////////////////
	/// 
	///    \Draws the player object and moves it to the ground
    ///     if necessary.
	///    \param window: a reference to the game window
    ///    \param map: a reference to the game map
    ///
	////////////////////////////////////////////////////////////
    void draw(sf::RenderWindow& window, const Map& map);

    

    int getHealth() const {
        return m_health;
    }
    
	const sf::Color& getColor() const {
        return m_color;
    }
    
	const sf::Texture& getTexture() const {
        return m_texture;
    }
    
    const sf::Vector2u& getLastLocation() const {
        return m_lastLocation;
    }
        
    const Weapon& getEquippedWeapon() const{
        return m_weapons[m_equippedWeapon];
    }

    Weapon& getEquippedWeapon() {
        return m_weapons[m_equippedWeapon];
    }
    
    const sf::Vector2u& getLocation() const {
        return m_location;
    }

    int getNumber() const {
        return m_playerNumber;
    }
private:
    
    sf::Vector2u            m_location;
    std::vector<Weapon>     m_weapons;
    size_t                  m_equippedWeapon;
    int                     m_health;
    sf::Texture             m_texture;
    sf::Color               m_color;
    bool                    m_isShooting = false;
    int                     m_playerNumber;
    
    sf::Sprite                  m_bullet;
    std::vector<float>          m_bulletAngles;
    std::vector<sf::Vector2u>   m_bulletLocations;
    sf::Vector2u                m_lastLocation;
    int                         m_bulletCourseIndex = 0;
    int                         m_bulletCourseCount = 0;
    int                         m_targetTag;

    ////////////////////////////////////////////////////////////
	/// 
	///    \Prepares the shot trajectory. This is called from
    ///     shoot().
    ///    \param aimed: vector, which indicates the initial shot power
	///    \param players: the players in the game (to check if shot hits one)
    ///    \param map: map of the game (to check if bullet hits ground)
    ///    \param wind: randomized wind coefficient
	///
	////////////////////////////////////////////////////////////
    void setBulletLocs(sf::Vector2i aimed, std::vector<Player>& players, const Map& map, float wind);


    std::vector<Weapon> createWeapons() const;

};

