#include "game.hpp"


int Game::newGame()
{
	m_window.setFramerateLimit(40);
    size_t turn = 0;
    m_playerInTurn = turn;
    initPlayerLocations();
    
    
    m_font.loadFromFile("../fonts/DejaVuSans-Bold.ttf");
    m_explosionTexture.loadFromFile("../images/explosion0.png");

    m_isShooting = false;
    srand(time(NULL));

    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            // Close window
            if (event.type == sf::Event::Closed){
                m_window.close();
                return 0;
            }
            
            // End game
            if (m_playersAlive < 2)
            {   
                m_window.close();
                return m_players[0].getNumber();
            }

            // Change weapon
			if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::Num0 < event.key.code && event.key.code <= sf::Keyboard::Num3) {
					playerInTurn().changeWeapon((int)event.key.code - 26 - 1);
				}
				if (event.key.code == sf::Keyboard::R) {
					playerInTurn().getEquippedWeapon().reload();

					m_playerInTurn = ++turn % m_players.size(); //m_players[++turn % m_players.size()];

					if ((turn % m_players.size()) == 0) { // Full turn
						Calculate::wind(m_wind);
					}
				}

			}
            

            // Shoot
            if (event.type == sf::Event::MouseButtonPressed 
                && event.mouseButton.button == sf::Mouse::Left 
                && playerInTurn().getEquippedWeapon().getAmmoCount() > 0 
                && !m_isShooting){
                
                m_isShooting = true;
            
                sf::Vector2i aimed = sf::Vector2i(event.mouseButton.x,event.mouseButton.y);
                       
                shotEffect(playerInTurn().shoot(aimed, m_players, m_map, m_wind));

                m_playerInTurn = ++turn % m_players.size(); //m_players[ ++turn % m_players.size() ];

                if ((turn % m_players.size()) == 0) { // Full turn
                    Calculate::wind(m_wind);
                }
                
            }
            
        }
        m_isShooting = false;
        render();
    }
    return 0;
}

std::vector<Player> Game::generatePlayers(int numberOfPlayers) const 
{
    std::vector<Player> players;
    for (int i=0; i < numberOfPlayers; i++){
        players.push_back(Player(i + 1));
    }
    return players;
}

void Game::initPlayerLocations()
{
    int locV = 180; // Variation of players location
    sf::Vector2u loc;
    
    srand(time(NULL));
    auto numberOfPlayers = m_players.size();
    
    for(auto i = 0u; i < numberOfPlayers; i++) {
        loc.y = 100;
        loc.x = rand() % (locV/2) + i * (m_window.getSize().x - (locV/2)) / (numberOfPlayers - 1);
        
        // We don't want the player to be too close to the side so he can't shoot
        if(loc.x < 20)
            loc.x = 20;
        if(loc.x > m_window.getSize().x - 20)
            loc.x = m_window.getSize().x - 20;
        
        while(!m_map.isLand(loc)) {
            if(loc.y >= 592) { break; }
            loc.y += 1;
        }
        m_players[i].setLocation(loc);
    }
}



void Game::render()
{
    m_window.clear();

    drawMap();
    drawPlayers();
    drawMenus();

    m_window.display();
}


void Game::drawMap()
{
    m_map.draw(m_window);
}


void Game::drawPlayers()
{

    for(auto& player : m_players) {
            player.draw(m_window,m_map);
    }

}

void Game::drawMenus()
{
    drawWind();
    drawHealthbars();
    drawWeaponStats();
	drawTurnIndicator();
}

void Game::drawWind()
{
    sf::Text text;
    text.setFont(m_font);
    
    char str[20];
    snprintf(str, 20, "Wind: %.2f m/s", m_wind);
    text.setString(str);
    text.setCharacterSize(14);
    text.setColor(sf::Color::Blue);
    text.setPosition((m_window.getSize().x / 2) - 14*6, 50);
    m_window.draw(text);
}

void Game::drawHealthbars()
{
    for (auto& player : m_players){
        sf::RectangleShape healthbar, remainingHealth;
        const auto& loc = player.getLocation();
        healthbar.setSize(sf::Vector2f(30, 5));
        healthbar.setPosition(sf::Vector2f((float)loc.x - 14, (float)(loc.y - 25)));
        healthbar.setFillColor(sf::Color::Red);

        remainingHealth.setSize(sf::Vector2f((float)(3 * int(player.getHealth() / 10)), (float)5));
        remainingHealth.setPosition(sf::Vector2f((float)loc.x - 14, (float)(loc.y - 25)));
        remainingHealth.setFillColor(sf::Color::Green);

        m_window.draw(healthbar);
        m_window.draw(remainingHealth);
    }
}

void Game::drawWeaponStats()
{
    auto numberOfPlayers = (int)m_players.size();
    sf::Text text;
    text.setFont(m_font);
    text.setCharacterSize(14);
    std::stringstream oss;

    for (int i = 0; i < numberOfPlayers; i ++){

        oss << "Player " << (i+1) << std::endl;
        oss << "Weapon: " << m_players[i].getEquippedWeapon().getName() << std::endl;
        oss << "Ammo: " << m_players[i].getEquippedWeapon().getAmmoCount();
        text.setString(oss.str());
        
        if (m_players[i].getEquippedWeapon().getAmmoCount() > 0)
            text.setColor(sf::Color::Blue);
        else
            text.setColor(sf::Color::Red);
        
        text.setPosition(6 + (m_window.getSize().x - 150)*i/(numberOfPlayers-1), 0);
        m_window.draw(text);
        oss.str("");
    }
}

void Game::drawTurnIndicator() 
{
	sf::CircleShape indicator(10, 3);
	auto playerPosition = playerInTurn().getLocation();
	indicator.setPosition(sf::Vector2f(playerPosition) + sf::Vector2f(-10, 15));
	indicator.setFillColor(sf::Color::Blue);
	m_window.draw(indicator);
}

void Game::drawExplosion(sf::Vector2u loc) 
{
	
    sf::Sprite explosion;
    explosion.setTexture(m_explosionTexture);
    explosion.setOrigin(m_explosionTexture.getSize().x / 2.f, m_explosionTexture.getSize().y / 2.f);
    explosion.setPosition((int)loc.x,(int)loc.y);    
    explosion.scale(0.35,0.35);
    for (int i = 0; i < 10; i++){
	    m_window.draw(explosion);
        m_window.display();
    }
    m_window.clear();
}


void Game::checkHealths()
{

    for (auto it = m_players.begin(); it < m_players.end(); it++) {
        if ((*it).getHealth() == 0){
            it = m_players.erase(it);
            m_playersAlive--;
         }
    }
    
}

void Game::shotEffect(int tag)
{
    

    playerInTurn().drawShot(m_window);

    //ground hits
    if (tag == -1){
      
        if (playerInTurn().getEquippedWeapon().getName() == "Teleport")
            playerInTurn().setLocation(playerInTurn().getLastLocation());   

        //groundhit but player on effect radius
        else{     
            m_map.makeHole(playerInTurn().getLastLocation(), playerInTurn().getEquippedWeapon().getEffectRadius());
            for (auto& player : m_players){
                if ( Calculate::belongsToCircle(player.getLocation(), playerInTurn().getLastLocation(), playerInTurn().getEquippedWeapon().getEffectRadius()*1.5))
                    player.reduceHealth(playerInTurn().getEquippedWeapon().getDamage());                                
            }     
        
        }
    }
    //direct player hits
    if (tag>=0){
        m_players[tag].reduceHealth(playerInTurn().getEquippedWeapon().getDamage());
        m_map.makeHole(playerInTurn().getLastLocation(), playerInTurn().getEquippedWeapon().getEffectRadius());
    }

    

    if (tag > -2 && playerInTurn().getEquippedWeapon().getName() == "Cannon"){ 
    drawExplosion(playerInTurn().getLastLocation());
    }
    checkHealths();
    
    

}
