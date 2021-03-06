#include "weapon.hpp"




std::string Weapon::getName() const
{
	return m_name;
}

int Weapon::getEffectRadius() const
{
    return m_effectRadius;
}

int Weapon::getDamage() const
{
    return m_damage;
}

int Weapon::getAmmoWeight() const
{
    return m_ammoWeight;
}

int Weapon::getAmmoCount() const
{
    return m_ammoCount;
}

sf::Texture& Weapon::getTexture()
{
    return m_texture;
}

void Weapon::reduceAmmoCount()
{
	if(m_ammoCount > 0) 
		m_ammoCount--;
}

void Weapon::reload()
{
	m_ammoCount = m_maxAmmo;
}
