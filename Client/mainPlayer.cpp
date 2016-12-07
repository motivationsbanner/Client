// sfml includes
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Network/Http.hpp>

#include "mainPlayer.h"


// c++ includes
#include <iostream>
#include <string>

mainPlayer::mainPlayer(int X, int Y,  std::string  pTexturefile)
{
	//Name, X, Y, Items[], Gold, XP, Character Model, Skilltree, Hp
	hp = 100;
	maxhp = 100;
	mana = 100;
	maxmana = 100;
	posX = X;
	posY = Y;
	

	// init movement variables
	move = false;
	frame = 0;

	//Sprite und player texture erstellen
	spriteposition = 0;
	texture = loadTexture("textures/" + pTexturefile + ".bmp");
	sprite.setTexture(texture);
	sprite.setPosition(posX, posY);
	sprite.setTextureRect(sf::IntRect(spriteposition, 0, texture.getSize().x /4, texture.getSize().y / 3));

		//profil erstellen
		profil = loadTexture("textures/" + pTexturefile + "profil.bmp");
		profilsprite.setTexture(profil);
		profilsprite.setScale(1.45f,1.45f);
		profilsprite.setPosition(healthbarsprite.getPosition().x-30, healthbarsprite.getPosition().y);
	
}

mainPlayer::~mainPlayer()
{
	// destructor
}

void mainPlayer::Update(sf::View &view, Map &map) {

		//colliding blocks
		sf::FloatRect boundingBox = sprite.getGlobalBounds();
		boundingBox.top = boundingBox.top+boundingBox.height-15;
		boundingBox.height = 15;

		sf::FloatRect boundingBoxTop = boundingBox;
		boundingBoxTop.top = boundingBoxTop.top - speed;
		sf::FloatRect boundingBoxBottom = boundingBox;
		boundingBoxBottom.top = boundingBoxBottom.top + speed;
		sf::FloatRect boundingBoxLeft = boundingBox;
		boundingBoxLeft.left = boundingBoxLeft.left - speed;
		sf::FloatRect boundingBoxRight = boundingBox;
		boundingBoxRight.left = boundingBoxRight.left + speed;
		// Movement
		move = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && map.Collision(boundingBoxLeft)){
			spriteposition = texture.getSize().x / 4 * 3;
			posX = posX - speed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && map.Collision(boundingBoxRight)) {
			spriteposition = texture.getSize().x / 4 * 2;
			posX = posX + speed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && map.Collision(boundingBoxTop)){
			spriteposition = texture.getSize().x / 4 ;
			posY = posY - speed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && map.Collision(boundingBoxBottom)) {
			spriteposition = 0;
			posY = posY + speed;
		}
		else {
			move = false;
		}
	



	//Hier werden alle Positionen geupdated
	sprite.setPosition(posX, posY);
	view.setCenter(posX, posY);
	healthsprite.setPosition(posX - (health.getSize().x / 2) + (texture.getSize().x / 8), posY + (texture.getSize().y / 3) + 42);
	healthbarsprite.setPosition(posX - (healthbar.getSize().x / 2) + (texture.getSize().x / 8), posY + (texture.getSize().y / 3 + 42));
	manasprite.setPosition(posX - (manatexture.getSize().x / 2) + (texture.getSize().x / 8), posY + (texture.getSize().y / 3) + 56);
	manabarsprite.setPosition(posX - (manabar.getSize().x / 2) + (texture.getSize().x / 8), posY + (texture.getSize().y / 3 + 56));
	profilsprite.setPosition(healthbarsprite.getPosition().x - 30, healthbarsprite.getPosition().y);

	healthspritek.setPosition(posX - (health.getSize().x / 4) + (texture.getSize().x / 8), posY - 20);
	healthbarspritek.setPosition(posX - (healthbar.getSize().x / 4) + (texture.getSize().x / 8), posY - 20);
	manaspritek.setPosition(posX - (manatexture.getSize().x / 4) + (texture.getSize().x / 8), posY - 20 + (manatexture.getSize().y / 2));
	manabarspritek.setPosition(posX - (manatexture.getSize().x / 4) + (texture.getSize().x / 8), posY - 20 + (manatexture.getSize().y / 2));
	txtname.setPosition(posX - (txtname.getLocalBounds().width / 4) + (texture.getSize().x / 8), posY - 35);

	//hier wird die Position an den Server gesendet

	// sprite texture show correct part.
	if (move == true) {
		if (frame % 6 == 0 || frame % 6 == 1) {
			sprite.setTextureRect(sf::IntRect(spriteposition, 0, texture.getSize().x / 4, texture.getSize().y / 3));
		}
		else if (frame % 6 == 2 || frame % 6 == 3) {
			sprite.setTextureRect(sf::IntRect(spriteposition, texture.getSize().y / 3, texture.getSize().x / 4, texture.getSize().y / 3));
		}
		else if (frame % 6 == 4 || frame % 6 == 5) {
			sprite.setTextureRect(sf::IntRect(spriteposition, texture.getSize().y / 3 * 2, texture.getSize().x / 4, texture.getSize().y / 3));
		}
	}
	else {
		if (frame % 6 == 0 || frame % 6 == 1) {
			sprite.setTextureRect(sf::IntRect(spriteposition, 0, texture.getSize().x / 4, texture.getSize().y / 3));
		}
	}

	frame += 1;
	
}

void mainPlayer::DrawUI(sf::RenderWindow &window) {
	window.draw(sprite);
	window.draw(manaspritek);
	window.draw(manabarspritek);
	window.draw(healthspritek);
	window.draw(healthbarspritek);
	window.draw(txtname);
	window.draw(healthsprite);
	window.draw(healthbarsprite);
	window.draw(manasprite);
	window.draw(manabarsprite);
	window.draw(profilsprite);
	
}

void mainPlayer::DrawMinimap(sf::RenderWindow &window) {
	window.draw(sprite);
}

void mainPlayer::TakeDamage(int damage) {
	if (hp - damage < 0) {
		//er hat verloren
	}
	else {
		hp = hp-damage;
		healthsprite.setTextureRect(sf::IntRect(0, 0, (health.getSize().x *  hp / maxhp), health.getSize().y));
		healthspritek.setTextureRect(sf::IntRect(0, 0, (health.getSize().x *  hp / maxhp), health.getSize().y));
	}
}

void mainPlayer::SpendMana(int manaspent) {
	if (mana - manaspent < 0) {
		//er hat verloren
	}
	else {
		mana = mana - manaspent;
		manasprite.setTextureRect(sf::IntRect(0, 0, (manatexture.getSize().x *  mana / maxmana), manatexture.getSize().y));
		manaspritek.setTextureRect(sf::IntRect(0, 0, (manatexture.getSize().x *  mana / maxmana), manatexture.getSize().y));
	}
}

void mainPlayer::SetTexture(sf::Texture &newtexture) {
	texture = newtexture;
	sprite.setTexture(texture);
	sprite.setPosition(0, 0);
	sprite.setTextureRect(sf::IntRect(spriteposition, 0, texture.getSize().x / 4, texture.getSize().y / 3));
}

void mainPlayer::SetName(sf::Font &font, std::string Pname) {
	txtname.setFont(font);
	txtname.setCharacterSize(24);
	txtname.setScale(0.5f, 0.5f);
	txtname.setString(Pname);
	txtname.setPosition(posX - (txtname.getLocalBounds().width / 4) + (texture.getSize().x / 8), posY - 15);
}

void mainPlayer::SetManaBar(sf::Texture &pmana, sf::Texture &pmanabar) {
	manatexture = pmana;
	manabar = pmanabar;
	manaspritek.setTexture(manatexture);
	manaspritek.setTextureRect(sf::IntRect(0, 0, (manatexture.getSize().x *  mana / maxmana), manatexture.getSize().y));
	manaspritek.setScale(0.5f, 0.5f);
	manabarspritek.setTexture(manabar);
	manabarspritek.setScale(0.5f, 0.5f);

	manabarsprite.setTexture(manabar);
	manasprite.setTexture(manatexture);
	manasprite.setTextureRect(sf::IntRect(0, 0, (manatexture.getSize().x *  mana / maxmana), manatexture.getSize().y));
}

void mainPlayer::SetHealthBar(sf::Texture &phealth, sf::Texture &phealthbar) {
	health = phealth;
	healthbar = phealthbar;
	healthspritek.setTexture(health);
	healthspritek.setTextureRect(sf::IntRect(0, 0, (health.getSize().x *  hp / maxhp), health.getSize().y));
	healthspritek.setScale(0.5f, 0.5f);
	healthbarspritek.setTexture(healthbar);
	healthbarspritek.setScale(0.5f, 0.5f);

	healthbarsprite.setTexture(healthbar);
	healthsprite.setTexture(health);
	healthsprite.setTextureRect(sf::IntRect(0, 0, (health.getSize().x *  hp / maxhp), health.getSize().y));
}