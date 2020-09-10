#pragma once

#include <SFML/Graphics.hpp>


class Weapon
{
public:

    

    Weapon() = default; 

    ///
    ///@brief Construct a new Weapon object
    ///
    ///@param name name of the weapon
    ///@param radius effect radius of the weapon
    ///@param damage damage exerted
    ///@param weight weight of the bullet
    ///@param ammoCount number of bullets
    ///@param texture_path path to a texture file
    ///
    Weapon(std::string name, int radius, int damage, int weight, int ammoCount, const char* texture_path) 
    : m_name(name)
    , m_effectRadius(radius)
    , m_damage(damage)
    , m_ammoWeight(weight)
    , m_ammoCount(ammoCount)
	, m_maxAmmo(ammoCount)
    , m_texture(createTexture(texture_path))
    {}


    


    ////////////////////////////////////////////////////////////
    ///
    ///    \Default destructor.
    ///     
    ///
    ////////////////////////////////////////////////////////////
    //~Weapon() = default;

	////////////////////////////////////////////////////////////
	///
	///    \Increments ammo counter down by one.
	///
	////////////////////////////////////////////////////////////  
	void reduceAmmoCount();
    
	////////////////////////////////////////////////////////////
	///
	///    \Reloads the weapon.
	///
	////////////////////////////////////////////////////////////  
	void reload();

    ////////////////////////////////////////////////////////////
    ///
    ///    \Loads the weapon texture from file.
    ///
    ////////////////////////////////////////////////////////////        
    sf::Texture createTexture(const char* path) const {
        sf::Texture text;
        text.loadFromFile(path);
        return text;
    }

    ////////////////////////////////////////////////////////////
    ///     
    ///   \Obvious getter functions. Nothing special here.
    ///
    ////////////////////////////////////////////////////////////
	std::string getName() const;
	//
    int getEffectRadius() const;
    //
    int getDamage() const;
    //
    int getAmmoWeight() const;
    //
    int getAmmoCount() const;
    //
    sf::Texture& getTexture();

private:
    std::string m_name;
    int         m_effectRadius;
    int         m_damage;
    int         m_ammoWeight;
    int         m_ammoCount;
	int			m_maxAmmo;

    sf::Texture m_texture;
    
};

