#include "player.hpp"

Player::Player(int number)
{
    m_location = sf::Vector2u(0,0);
    m_weapons = createWeapons();
    m_equippedWeapon = 0;
    m_health = 100;
    m_texture.loadFromFile("../images/pixel-tank.png");
    m_color = sf::Color(std::rand() % 255, std::rand() % 255, std::rand() % 255);

    m_bullet.setColor(m_color);
    m_playerNumber = number;
}

void Player::setLocation(sf::Vector2u location)
{
    m_location = location;  
}



std::vector<Weapon> Player::createWeapons() const
{
    std::vector<Weapon> weapons;
    weapons.push_back(Weapon("Cannon",20,15,20,100, t_cannon));
	weapons.push_back(Weapon("Railgun", 5, 15, 3, 2, t_railgun));
	weapons.push_back(Weapon("Teleport", 1, 0, 20, 1, t_teleport));
    

    return weapons;
}






int Player::shoot(sf::Vector2i aimed, std::vector<Player>& players, Map map, float wind)
{

    
    m_bulletCourseCount = 0;
    m_isShooting = true;
    getEquippedWeapon().reduceAmmoCount();

    auto weaponTexture = getEquippedWeapon().getTexture();
    m_bullet.setOrigin(weaponTexture.getSize().x / 2.f, weaponTexture.getSize().y / 2.f);
    m_bullet.setScale(0.03f,0.03f);

    m_bulletCourseIndex = 0;

    // clear the vectors
    m_bulletAngles.clear();
    m_bulletLocations.clear();

    
    setBulletLocs(aimed, players, map, wind);    

    
    return m_targetTag;
    
}


void Player::setBulletLocs(sf::Vector2i aimed, std::vector<Player>& players, const Map& map, float wind)
{

    
    // initialize the location of the bullet to start slightly above the player
    m_bulletLocations.push_back(m_location + sf::Vector2u(-4u, -10u));

    
    // initialize bullet speed
    auto shootingForce = (aimed - sf::Vector2i(m_bulletLocations[0]))*400;
	m_bulletAngles.push_back(Calculate::angle(sf::Vector2f(shootingForce)));
	int mass = getEquippedWeapon().getAmmoWeight();
	float energy = std::min(pow(pow(shootingForce.x, 2) + pow(shootingForce.y, 2), 0.5), (double)200*400);
    sf::Vector2f bulletSpeed = Calculate::initialSpeed(mass, energy, m_bulletAngles.back());


    // calculate all the angles and locations of the bullet course
    while (1){

        //check if bullet hits a player
        for (unsigned int i = 0; i < players.size(); i++) {       
            if (players[i].isHit(m_bulletLocations[m_bulletCourseIndex])){
                m_targetTag = i;
                break;
            }
         }    

        //check if bullet hits land
        if (map.isLand(m_bulletLocations[m_bulletCourseIndex])){
            m_targetTag = -1;
            break;
        }

        //check if bullet out of bounds
        if (map.outOfBounds(m_bulletLocations[m_bulletCourseIndex])){
            m_targetTag = -2;
            break;
        }
        //...bullet still flies
        m_bulletCourseIndex++;
        bulletSpeed = Calculate::newSpeed(bulletSpeed, wind, mass);
        m_bulletAngles.push_back(Calculate::angle(bulletSpeed));
        m_bulletLocations.push_back(Calculate::nextLocation(bulletSpeed, m_bulletLocations[m_bulletCourseIndex - 1]));
        
    }
    
    
    
    //tama sama homma pitaisi kai tehda kun osuu suoraan pelaajaan
    if (m_targetTag >= -1){
    auto bulletLocation = m_bulletLocations[m_bulletCourseIndex];
    auto oldLocation = m_bulletLocations[m_bulletCourseIndex - 1];
    while (pow((int)bulletLocation.x - (int)oldLocation.x,2) + pow((int)bulletLocation.y - (int)oldLocation.y, 2) > 2) {
        auto temp = sf::Vector2u((bulletLocation.x + oldLocation.x) / 2, (bulletLocation.y + oldLocation.y) / 2);
        if (map.isLand(temp))
                bulletLocation = temp;
        else 
                oldLocation = temp;
        }
        m_bulletLocations[m_bulletCourseIndex] = bulletLocation;

    }
    
    m_bulletCourseCount = m_bulletCourseIndex;
    m_bulletCourseIndex = 0;
    m_lastLocation = m_bulletLocations[m_bulletCourseCount];
    

}






void Player::drawShot(sf::RenderWindow& window)
{
    
    
    //create an image of the current screen to speed things up a little
    auto img = window.capture();
    //create a drawable object of the image
    auto tempVec = sf::Vector2f((int)window.getSize().x, (int)window.getSize().y);
    sf::Texture text;  
    text.loadFromImage(img);
    sf::RectangleShape rect(tempVec);
    rect.setTexture(&text);

    auto bulletTexture = getEquippedWeapon().getTexture();
    m_bullet.setTexture(bulletTexture);

    //this is the trajectory loop
    while (m_bulletCourseIndex < m_bulletCourseCount){
		if (m_bulletCourseIndex % 2 == 0) {

			window.clear();
			window.draw(rect);

			m_bullet.setRotation(90.f - m_bulletAngles[m_bulletCourseIndex]);
			m_bullet.setPosition(sf::Vector2f(m_bulletLocations[m_bulletCourseIndex]));

			window.draw(m_bullet);
			window.display();
		}
        m_bulletCourseIndex++;
    }
    m_isShooting = false; 
    
    


}

void Player::draw(sf::RenderWindow& window, const Map& map)
{
    

    sf::Sprite tank;
    sf::Vector2u loc = m_location;

    tank.setTexture(m_texture);
    tank.setColor(m_color);
    tank.setOrigin(15,10);
    while(!(map.isLand(loc))){
        if (loc.y >= 592)
            break;
        loc.y += 1;
    }
    tank.setPosition((float)loc.x, (float)loc.y);
    m_location = loc;
	if (loc.x < map.getSize().x / 2) tank.scale(-1.f, 1.f);
    window.draw(tank);
    
}


bool Player::isHit(const sf::Vector2u& loc) const
{

    sf::Vector2i rectLoc(m_location.x,m_location.y); 
    //a bit larger rectangle than the texture size could be used here...
    sf::Vector2i rectSize(m_texture.getSize().x, m_texture.getSize().y);
    sf::IntRect rect(rectLoc,rectSize);
    if (rect.contains(loc.x,loc.y)){
        return true;
    }
    return false;
    
}




void Player::reduceHealth(int damage) 
{

    if (m_health - damage > 0)
        m_health -= damage;
    else
        m_health = 0;

}

