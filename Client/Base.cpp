#include "Base.h"

Base::Base()
{
	this->posX = 0;
	this->posY = 0;
}

Base::Base(int hp)
{
	this->hp = hp;
}

Base::Base(int hp, int posX, int posY)
{
	this->hp = hp;
	this->posX = posX;
	this->posY = posY;
}

Base::Base(int hp, int posX, int posY, int map)
{
	this->hp = hp;
	this->posX = posX;
	this->posY = posY;
	this->map = map;

}

Base::~Base(void)
{

}

sf::Texture Base::loadTexture(std::string uri)
{
	sf::Http http("46.101.227.221");
	sf::Http::Request request("files/" + uri);
	auto response = http.sendRequest(request);
	auto data = response.getBody();

	sf::Texture text;
	text.loadFromMemory(data.data(), data.length());

	return text;
}

void Base::setPosition(int x, int y)
{
	this->posX = x;
	this->posY = y;
}