// sfml includes
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Network/Http.hpp>

#include "Player.h"

// c++ includes
#include <iostream>
#include <string>


Player::Player()
{
	//Name, X, Y, Items[], Gold, XP, Character Model, Skilltree, Hp
	hp = 100;
	maxhp = 100;
	mana = 100;
	maxmana = 100;
	posX = 0;
	posY = 0;


	// init movement variables
	move = false;
	frame = 0;

	//Sprite und player texture erstellen
	spriteposition = 0;
}

Player::~Player()
{
	// destructor
}

void Player::Update(sf::View &view) {


	//hier w�rde die Position vom server gesetzt

	move = true;
	
	
	 if (sprite.getPosition().x < posX && sprite.getPosition().y == posY) {
		spriteposition = texture.getSize().x / 4 * 2;
		move = true;
	}
	else if (sprite.getPosition().x > posX && sprite.getPosition().y == posY) {
		spriteposition = texture.getSize().x / 4 * 3;
		move = true;
	}
	else if (sprite.getPosition().x == posX && sprite.getPosition().y < posY) {
		spriteposition = 0;
		move = true;
	}
	else if (sprite.getPosition().x == posX && sprite.getPosition().y > posY) {
		spriteposition = texture.getSize().x / 4;
		move = true;
	}
	else {
		move = false;
	}

	//Hier werden alle Positionen geupdated
	sprite.setPosition(posX, posY);
	txtname.setPosition(posX - (txtname.getLocalBounds().width / 4) + (texture.getSize().x / 8), posY - 35);
	healthsprite.setPosition(posX - (health.getSize().x / 4) + (texture.getSize().x / 8), posY - 20);
	healthbarsprite.setPosition(posX - (healthbar.getSize().x / 4) + (texture.getSize().x / 8), posY - 20);
	manasprite.setPosition(posX - (manatexture.getSize().x / 4) + (texture.getSize().x / 8), posY - 20 + (manatexture.getSize().y / 2));
	manabarsprite.setPosition(posX - (manatexture.getSize().x / 4) + (texture.getSize().x / 8), posY - 20 + (manatexture.getSize().y / 2));

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

	std::cout << frame << std::endl;
	
}

void Player::DrawUI(sf::RenderWindow &window) {
	window.draw(sprite);
	window.draw(txtname);
	window.draw(manasprite);
	window.draw(manabarsprite);
	window.draw(healthsprite);
	window.draw(healthbarsprite);
}

void Player::DrawMinimap(sf::RenderWindow &window) {
	window.draw(sprite);
}

void Player::TakeDamage(int damage) {
	if (hp - damage < 0) {
		//er hat verloren
	}
	else {
		hp = hp-damage;
		healthsprite.setTextureRect(sf::IntRect(0, 0, (health.getSize().x *  hp / maxhp), health.getSize().y));
	}
}

void Player::SpendMana(int manaspent) {
	if (mana - manaspent < 0) {
		//er hat verloren
	}
	else {
		mana = mana - manaspent;
		manasprite.setTextureRect(sf::IntRect(0, 0, (manatexture.getSize().x *  mana / maxmana), manatexture.getSize().y));
	}
}

void Player::SetTexture(sf::Texture &newtexture) {
	texture = newtexture;
	sprite.setTexture(texture);
	sprite.setPosition(posX, posY);
	sprite.setTextureRect(sf::IntRect(spriteposition, 0, texture.getSize().x / 4, texture.getSize().y / 3));
}

void Player::SetName(sf::Font &font, std::string Pname) {
	txtname.setFont(font);
	txtname.setCharacterSize(24);
	txtname.setScale(0.5f, 0.5f);
	txtname.setString(Pname);
	txtname.setPosition(posX - (txtname.getLocalBounds().width / 4) + (texture.getSize().x / 8), posY - 15);
}

void Player::SetManaBar(sf::Texture &pmana, sf::Texture &pmanabar) {
	manatexture = pmana;
	manabar = pmanabar;
	manasprite.setTexture(manatexture);
	manasprite.setTextureRect(sf::IntRect(0, 0, (manatexture.getSize().x *  mana / maxmana), manatexture.getSize().y));
	manasprite.setScale(0.5f, 0.5f);
	manabarsprite.setTexture(manabar);
	manabarsprite.setScale(0.5f, 0.5f);
}

void Player::SetHealthBar(sf::Texture &phealth, sf::Texture &phealthbar) {
	health = phealth;
	healthbar = phealthbar;
	healthsprite.setTexture(health);
	healthsprite.setTextureRect(sf::IntRect(0, 0, (health.getSize().x *  hp / maxhp), health.getSize().y));
	healthsprite.setScale(0.5f, 0.5f);
	healthbarsprite.setTexture(healthbar);
	healthbarsprite.setScale(0.5f, 0.5f);
}