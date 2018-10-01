/*******************************************
Authors: William Boston & Ben Eilts
	  final Project for CS 122
		WSU Fall semester 2015
*******************************************/

#pragma once
#ifndef HEADER_H
#define HEADER_H
 /***********************************************************************
 Merging all Header files together becuase Visual Studio is having issues
 ************************************************************************/

//#include <SFML\Window.hpp>		// SFML 2.5.0
//#include <SFML\Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>	// input and ouptut
#include <random>	
#include <time.h>	// track users time
#include <string.h>	// to show and store score data
#include <fstream>	// file read write

#define	WIDTH 400
#define	HEIGHT 800
#define	LIFE 5

#define BULLET_SPEED 400

#define _CRT_SECURE_NO_WARNINGS


//--------------------------------------------------------------------------------------------------------------------------------------- Space.h
 /*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*\
		 Base Class : Star
 Author: William Boston
 Def: Star is a base class for the List in class Space
 \*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*/
class Star
{
	friend class Space;
public:
	Star() {}
	~Star() {}

	void initStar(int seed, int SpeedMin, int SpeedMax, int sizeMax, int sizeMin, sf::Color color);
	void update(int seed, int speedMax, int speedMin, int sizeMin, int sizeMax);

private:
	int X;
	int Y;
	int Speed;
	sf::CircleShape Dot;

};
void Star::initStar(int seed, int SpeedMin, int SpeedMax, int sizeMax, int sizeMin, sf::Color color)
{
	srand(seed);

	Dot.setRadius(rand() % sizeMax + sizeMin);
	Dot.setFillColor(color);
	Dot.setPointCount(50);
	X = (rand() % WIDTH);
	Y = rand() % HEIGHT;
	Speed = rand() % SpeedMax + SpeedMin;
}
void Star::update(int seed, int speedMin, int speedMax, int sizeMin, int sizeMax)
{
	srand(seed);
	if (Y > HEIGHT)
	{
		Dot.setRadius(rand() % sizeMax + sizeMin);
		Y = -10;
		X = rand() % (WIDTH - 25) + 25;
		Speed = rand() % speedMax + speedMin;
	}
	else
	{
		Y += Speed;
	}

	Dot.setPosition(X, Y);
}

/*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*\
		Wrapper Class : Space
Author: William Boston
Def: class SPACE is the container class for all the graphics that take place in the background
\*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*/
class Space
{
public:
	Space();
	~Space() {}

	void makeSpace();
	void UpdateStars(sf::RenderWindow *window);

private:
	Star close[25];
	Star medium[10];
	Star far[30];
};

Space::Space()
{
	srand(time(0));

	int i = 0;
	for (i = 0; i < 25; i++) // init small list
	{					// ( rand Seed , spMin , spMax , szMax , szMin, color)
		sf::Color dust(sf::Color(255, 255, 255, 90));
		close[i].initStar(rand() % 2000, 10, 14, 3, 1, dust);
	}
	for (i = 0; i < 10; i++)
	{
		sf::Color star(sf::Color(200, 200, 200, 200));
		medium[i].initStar(rand() % 2000, 5, 8, 7, 2, star);
	}
	for (i = 0; i < 30; i++)
	{
		sf::Color planet(50, 50, 50);
		far[i].initStar(rand() % 2000, 2, 7, 3, 1, planet);
	}
}

void Space::makeSpace()
{
	srand(time(0));

	int i = 0;
	for (i = 0; i < 25; i++) // init small list
	{					// ( rand Seed , spMin , spMax , szMax , szMin, color)
		sf::Color dust(sf::Color(255, 255, 255, 90));
		close[i].initStar(rand() % 2000, 10, 14, 3, 1, dust);
	}
	for (i = 0; i < 10; i++)
	{
		sf::Color star(sf::Color(200, 200, 200, 200));
		medium[i].initStar(rand() % 2000, 5, 8, 7, 2, star);
	}
	for (i = 0; i < 30; i++)
	{
		sf::Color planet(50, 50, 50);
		far[i].initStar(rand() % 2000, 2, 7, 7, 1, planet);
	}

}

void Space::UpdateStars(sf::RenderWindow *window)
{
	srand(time(0));
	/***************** UPDATE ***********************/
	int i = 0;
	for (i = 0; i < 25; i++) // init small list
	{
		close[i].update(rand() % 2000, 10, 14, 1, 4);
	}
	for (i = 0; i < 10; i++)
	{
		medium[i].update(rand() % 2000, 5, 12, 2, 7);
	}
	for (i = 0; i < 30; i++)
	{
		far[i].update(rand() % 2000, 1, 7, 2, 7);
	}

	/***************** PRINT ***********************/
	for (i = 0; i < 25; i++) // small star list
	{
		window->draw(close[i].Dot);
	}
	for (i = 0; i < 10; i++) // medium star list
	{
		window->draw(medium[i].Dot);
	}
	for (i = 0; i < 30; i++) // big star list
	{
		window->draw(far[i].Dot);
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------- Projectile.h

using sf::Clock;

/*************************************
Author: Ben Eilts
def: base class NODE
*************************************/
class NodeBullet
{
	friend class ListBullet;
	friend class AsteroidList;

public:
	NodeBullet()
	{

		bullet.setRadius(5);
		bullet.setFillColor(sf::Color::Red);
		clock.restart().asSeconds();
		pNext = nullptr;
		pPrev = nullptr;// added pPrev so its Doubly Linked *
	}
	~NodeBullet()
	{
	}

protected:
	sf::CircleShape bullet;
	sf::Clock clock;
	NodeBullet *pNext;
	NodeBullet *pPrev;// added pPrev so its Doubly Linked *
};

/*************************************
Author: Ben Eilts
def:  Bullet List Class for NODE BULLET
*************************************/
class ListBullet
{
	friend class AsteroidList;
public:
	ListBullet()
	{
		pHead = nullptr;
		pTail = nullptr;
	}
	~ListBullet();
	void shoot_bullet(float X, float Y);
	bool CanShoot();
	bool Update(sf::RenderWindow *window, float ElapsedTime);

	bool stitch(NodeBullet **pCur);
private:
	NodeBullet *pHead;
	NodeBullet *pTail;
	void deleteList();
};

// Destructor
ListBullet::~ListBullet()
{
	deleteList();
}
// Does what is says, it Deletes the list
void ListBullet::deleteList()
{
	NodeBullet *pTemp = NULL;

	while (pHead != NULL)
	{
		pTemp = pHead;
		pHead = pHead->pNext;
		delete (pTemp);
	}
	std::cout << "List deleted" << std::endl;
	pHead = NULL;
}


/*************************************
Author: Ben Eilts
def:  checks linked list, then inserts into correct
  position
*************************************/
void ListBullet::shoot_bullet(float X, float Y)
{
	if (pHead == NULL)
	{
		NodeBullet *pMem = new NodeBullet();
		pMem->bullet.setPosition(X + 28, Y);
		pMem->pNext = NULL;
		pMem->pPrev = NULL; // added pPrev so its Doubly Linked *
		pHead = pTail = pMem;
		std::cout << "First Bullet Fired" << std::endl;
	}
	else if (CanShoot() == true) // checking time
	{
		NodeBullet *pMem = new NodeBullet();
		pMem->bullet.setPosition(X + 28, Y);

		pHead->pPrev = pMem;// added pPrev so its Doubly Linked *
		pMem->pNext = pHead;
		pHead = pMem;
		std::cout << "More Bullets Fired" << std::endl;
	}
}

// checks time sense last bullet was shot
bool ListBullet::CanShoot()
{
	bool result = true;

	if (pHead->clock.getElapsedTime().asSeconds() < .1) // this number is the relaod speed *
	{
		result = false; // can't shoot
	}
	return result;
}

/*************************************
Author: William Boston
def: takes input Node and 'stitches' the list
 together so the Node can be deleted.
*************************************/
bool ListBullet::stitch(NodeBullet ** pCur)
{
	if ((*pCur)->pPrev == nullptr) // head Node?
	{
		if ((*pCur)->pNext == nullptr)
		{
			pHead = nullptr;
			pTail = nullptr;
		}
		else
		{
			pHead = (*pCur)->pNext;
			pHead->pPrev = nullptr;
		}
	}
	else if ((*pCur)->pNext == nullptr)// Tail Node?
	{
		pTail = (*pCur)->pPrev;
		pTail->pNext = nullptr;
	}
	else // Node in the Middle
	{
		(*pCur)->pNext->pPrev = (*pCur)->pPrev;
		(*pCur)->pPrev->pNext = (*pCur)->pNext;
	}

	return true;
}

/***************************************************
Author: Ben Eilts & William Boston
Houses operations to visually update current List
***************************************************/
bool ListBullet::Update(sf::RenderWindow *window, float ElapsedTime)
{

	NodeBullet *pCur = pHead;

	while (pCur != NULL)
	{
		pCur->bullet.move(0, -(ElapsedTime * BULLET_SPEED));
		window->draw(pCur->bullet);

		if (pTail == pHead) // one in list
		{
			if (pHead->bullet.getPosition().y < 0)
			{
				NodeBullet *pTemp = pHead;
				pHead = pTail = NULL;
				std::cout << "bullet deleted" << std::endl;
			}
		}
		else if (pCur->pNext == pTail) // pCur is located second to last
		{
			if (pTail->bullet.getPosition().y < 0) // delete bullet
			{
				NodeBullet *pTemp = pTail;
				pCur->pNext = NULL;
				pTail = pCur;
				delete pTemp;
				std::cout << "bullet deleted" << std::endl;

			}

		}
		pCur = pCur->pNext;
	}

	return true;
}

//--------------------------------------------------------------------------------------------------------------------------------------- Ship.h

/********************************************
def: this class houses the operations and data
  necessary to display the aray of hearts (Lives)
********************************************/
class HeartNode
{
	friend class Ship;
public:
	HeartNode()
	{
		if (!heartPNG.loadFromFile("Health.png"))
		{
			std::cout << "Error Reading 'Health.png'" << std::endl;
		}
		Heart.setTexture(heartPNG);

		heartY = HEIGHT - 26;
	}
	~HeartNode() {}

private:
	sf::Texture heartPNG;
	sf::Sprite Heart;
	int heartX, heartY;
};

// is the class that operates the timer shown in game
class inGameTimer
{
public:
	inGameTimer()
	{
		timeString = "";
		if (!font.loadFromFile("consolab.ttf"))
		{
			std::cout << "error Loading text" << std::endl;
		}

		TimerText.setFont(font);
		TimerText.setFillColor(sf::Color(238, 226, 11));
		TimerText.setString("--:--");
		TimerText.setCharacterSize(23);
		TimerText.setPosition(WIDTH - 90, HEIGHT - 32);
	}
	~inGameTimer() {}

	std::string getString() { return timeString; }

	void updateTimer(int gameClock, sf::RenderWindow * Window)
	{
		int min = 0;
		int sec = 0;

		if (gameClock < 60)
		{
			sec = gameClock;
		}
		else
		{
			min = gameClock / 60;
			sec = gameClock % 60;
		}
		if (min <= 9)
		{
			if (sec <= 9)
			{
				timeString = '0' + std::to_string(min) + ':' + '0' + std::to_string(sec);

			}
			else
			{
				timeString = '0' + std::to_string(min) + ':' + std::to_string(sec);

			}
		}
		else if (sec <= 9)
		{
			timeString = std::to_string(min) + ':' + '0' + std::to_string(sec);

		}
		else
		{
			timeString = std::to_string(min) + ':' + std::to_string(sec);

		}

		TimerText.setString(timeString);
		Window->draw(TimerText);

	}

private:
	std::string timeString;
	sf::Font font;
	sf::Text TimerText; // Selection 1 Play Game
};

class Ship
{
	friend class AsteroidList;
	friend class AsteroidOBJ;
public:
	Ship();
	~Ship() {}

	bool setShipImg(sf::Image image);
	bool update(sf::RenderWindow *Window);

	int getX() { return sSprite.getPosition().x; }
	int getY() { return sSprite.getPosition().y; }
	sf::Sprite &  getSprite() { return sSprite; }

	void setRotate(float degrees);
	void setChange(int NewData) { change = NewData; }


private:
	int X, Y;
	int change;

	int Life;
	HeartNode Lives[LIFE];

	sf::Texture baseTexture;
	sf::Sprite baseSprite;

	sf::Texture ShipImg;
	sf::Sprite sSprite;
};

Ship::Ship()
{
	if (!ShipImg.loadFromFile("Ship.png"))
	{
		std::cout << "Error reading from file" << std::endl;
	}

	if (!baseTexture.loadFromFile("Base.png"))
	{
		std::cout << "Error Reading 'Base.png'" << std::endl;
	}
	Life = LIFE - 1;
	int i = 0;
	for (i = 0; i <= Life; i++)
	{
		Lives[i].heartX = i * 30;
		Lives[i].Heart.setPosition(Lives[i].heartX, Lives[i].heartY);
	}

	baseSprite.setTexture(baseTexture);
	baseSprite.setPosition(0, HEIGHT - 33);


	X = 200;
	Y = HEIGHT - 125;
	change = 0;
	sSprite.setPosition(X, Y);
	sSprite.setTexture(ShipImg);
}

bool Ship::setShipImg(sf::Image image)
{
	return false;
}

void Ship::setRotate(float degrees)
{
	sSprite.rotate(degrees);
}
bool Ship::update(sf::RenderWindow *Window)
{

	int x = sSprite.getPosition().x;
	x += change;

	if (x > WIDTH - 75)
	{
		x = WIDTH - 75;
	}
	else if (x < 0)
	{
		x = 0;
	}
	sSprite.setPosition(x, Y);
	Window->draw(baseSprite);
	int i = 0;
	for (i = 0; i <= Life; i++)
	{
		Window->draw(Lives[i].Heart);
	}
	Window->draw(sSprite);
	return true;
}


//--------------------------------------------------------------------------------------------------------------------------------------- Asteroid.h
/*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*\
Object class : Asteroid
Author: William Boston

Def: class SPACE is the container class for all the graphics that take place in the background

\*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*/
class AsteroidOBJ
{
public:
	AsteroidOBJ()
	{
		x = 0;
		y = -50;
		Size = 0;
		Active = false;

		if (!Img.loadFromFile("LargeAsteroid.png"))
		{
			std::cout << "Error Reading Asteroid IMG" << std::endl;
		}
		else
		{
			Sprte.setTexture(Img);
		}

	}
	~AsteroidOBJ() {}
	bool update(Ship *ship, sf::RenderWindow *Window);
	void reset()
	{
		y = rand() % 200;
		speed = rand() % 5 + 8;
		x = rand() % (WIDTH - 45);
	}

	int getSize() { return Size; }
	void setSize(int newData) { Size = newData; }
	bool getActive() { return Active; }
	void setActive(bool newData) { Active = newData; }

	void setImg(sf::Texture NewImg) { Img = NewImg; }

private:
	int Size;
	int x, y;
	int speed;
	bool Active;
	sf::Texture Img;
	sf::Sprite Sprte;

};

bool AsteroidOBJ::update(Ship *ship, sf::RenderWindow *Window)
{
	y += speed;
	if ((x + 40) >= (ship->sSprite.getPosition().x) // checking horisontal collision
		&& (x + 5 <= (ship->sSprite.getPosition().x + 40)))
	{
		if (y + 40 >= ship->sSprite.getPosition().y  // checking virtical collision
			&& y <= ship->sSprite.getPosition().y + 75)
		{
			reset();
			ship->Life -= 1;
			std::cout << "<< :Lost 1 life! : >>" << std::endl;
			if (ship->Life < 0) // last life
			{
				return false; // end game
			}
		}
	}
	Window->draw(Sprte);
	return true;
}

/*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*\
			Node class : Asteroid
Author: William Boston

Def: class SPACE is the container class for all the graphics that take place in the background

\*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*/

class Asteroid
{
	friend class AsteroidList;
public:
	Asteroid(int seed)
	{
		srand(seed);

		AsteroidImg.loadFromFile("LargeAsteroid.png");
		AsteroidSprite.setTexture(AsteroidImg);
		Y = -20;
		Speed = rand() % 7 + 5;
		X = rand() % (WIDTH - 45);

		pPrev = nullptr;
		pNext = nullptr;

	}
	~Asteroid() {}
	bool updateAsteroid();

private:
	int X, Y, Speed;
	sf::Texture AsteroidImg;
	sf::Sprite AsteroidSprite;
	Asteroid *pPrev;
	Asteroid *pNext;
};

bool Asteroid::updateAsteroid()
{

	Y += Speed;
	AsteroidSprite.setPosition(X, Y);
	if (Y > HEIGHT)
	{
		return false;
	}
	return true;
}


/*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*\
			Node Wrapper : AsteroidList
Author: William Boston & Ben Elits
Def: class SPACE is the container class for all the graphics that take place in the background
\*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*/

class AsteroidList
{
public:
	AsteroidList()
	{
		pHead = nullptr;
		pTail = nullptr;
	}
	~AsteroidList() {}
	void setSeed(int newData) { seed = newData; }

	void insertAtEnd(int seed);
	bool deleteAsteroid(Asteroid **pCur);
	bool updateList(sf::RenderWindow *Window, Ship *ship, ListBullet * bullet); // checks for all collisions

private:
	int seed;
	Asteroid *pHead;
	Asteroid *pTail;
};

/******************************************
def: creates new Asteroid and adds it to the
  End of the linked list
******************************************/
void AsteroidList::insertAtEnd(int seed)
{
	srand(seed);
	if (pHead == nullptr)
	{
		Asteroid *NewData = new Asteroid(rand() % 10000 + 100);
		pHead = NewData;
		pTail = NewData;
	}
	else
	{
		Asteroid *NewData = new Asteroid(rand() % 10000 + 100);
		pTail->pNext = NewData;
		NewData->pPrev = pTail;
		pTail = NewData;

	}
}

/************************************************
def: takes input Node & 'stiches' previous
  and next Nodes together so it can be Deleted
************************************************/
bool AsteroidList::deleteAsteroid(Asteroid **pCur)
{
	if ((*pCur)->pPrev == nullptr) // head Node?
	{
		if ((*pCur)->pNext == nullptr)
		{
			pHead = nullptr;
			pTail = nullptr;
		}
		else
		{
			pHead = (*pCur)->pNext;
			pHead->pPrev = nullptr;
		}
	}
	else if ((*pCur)->pNext == nullptr)// Tail Node?
	{
		pTail = (*pCur)->pPrev;
		pTail->pNext = nullptr;
	}
	else // Node in the Middle
	{
		(*pCur)->pNext->pPrev = (*pCur)->pPrev;
		(*pCur)->pPrev->pNext = (*pCur)->pNext;
	}

	return true;
}

/**************************************************************************************
def: When Update List is called, it iterates through the Asteroid list and moves the asteroid
  then it checks for collisions
**************************************************************************************/
bool AsteroidList::updateList(sf::RenderWindow *Window, Ship *ship, ListBullet * bullet)
{

	Asteroid *pCur = pHead;
	NodeBullet * b_pCur = bullet->pHead;

	while (pCur != nullptr)
	{
		if (!(pCur->updateAsteroid()))
		{
			deleteAsteroid(&pCur); // clear asteroid
			Asteroid *temp = pCur;
			pCur = pCur->pNext;
			delete temp;
			return true;
		}
		// Ship Collision
		else if ((pCur->AsteroidSprite.getPosition().x + 40) >= (ship->sSprite.getPosition().x) // checking horisontal collision
			&& (pCur->AsteroidSprite.getPosition().x + 5 <= (ship->sSprite.getPosition().x + 40)))
		{
			if (pCur->AsteroidSprite.getPosition().y + 40 >= ship->sSprite.getPosition().y  // checking virtical collision
				&& pCur->AsteroidSprite.getPosition().y <= ship->sSprite.getPosition().y + 75)
			{
				deleteAsteroid(&pCur); // clear asteroid
				Asteroid *temp = pCur;
				pCur = pCur->pNext;
				delete temp;

				ship->Life -= 1; // decreasing life
				std::cout << "<< :Lost 1 life! : >>" << std::endl;
				if (ship->Life < 0) // last life
				{
					return false; // end game
				}

			}
		}
		if (pCur == nullptr)
		{
			break;
		}
		else
		{
			Window->draw(pCur->AsteroidSprite);
			pCur = pCur->pNext;
		}
	}

	pCur = pHead;


	// Blaster Collision
	while (pCur != nullptr)
	{
		while (b_pCur != nullptr)
		{
			if (pCur == nullptr)
			{
				break;
			}

			if ((pCur->AsteroidSprite.getPosition().x + 45) >= (b_pCur->bullet.getPosition().x) // checking horisontal collision
				&& (pCur->AsteroidSprite.getPosition().x <= (b_pCur->bullet.getPosition().x + 6)))
			{
				if (pCur->AsteroidSprite.getPosition().y + 42 >= b_pCur->bullet.getPosition().y // checking virticle collision
					&& pCur->AsteroidSprite.getPosition().y <= b_pCur->bullet.getPosition().y + 5)
				{
					deleteAsteroid(&pCur); // clear asteroid
					Asteroid *temp = pCur;
					pCur = pCur->pNext;
					delete temp;

					bullet->stitch(&b_pCur); // clear bullet
					NodeBullet * b_temp = b_pCur;
					b_pCur = b_pCur->pNext;
					delete b_temp;
				}
			}
			if (b_pCur == nullptr) // checks for new updatd null list
			{
				break;
			}
			else
			{
				b_pCur = b_pCur->pNext;
			}

		}
		if (pCur != nullptr)
		{
			Window->draw(pCur->AsteroidSprite);
			pCur = pCur->pNext;
		}
	}


	return true;
}


//--------------------------------------------------------------------------------------------------------------------------------------- Source.h
/*	Function Declarations for Source.cpp	*/


std::string readScore();
void storeTime(std::string gameClock);
bool evaltime(std::string GameTime);

bool updateAList(AsteroidOBJ *List[15], sf::RenderWindow *Window, Ship *ship);
bool initAList2(AsteroidOBJ *List[15], int Size);
bool AutoAsteroid2(sf::RenderWindow *Window, AsteroidOBJ *List[15], Ship *ship, int gameClock);


bool playgame(sf::RenderWindow * Window);
int menue(sf::RenderWindow * Window, std::string HighScore);

#endif // !HEADER_H
