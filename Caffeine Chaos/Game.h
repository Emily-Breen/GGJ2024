
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Customer.h"
enum class GameModes {
	MAIN_MENU,
	GAME_PLAY,
	GAME_OVER

};
enum OrderState {
	NoOrder,
	TakingOrder,
	FulfillingOrder,
	FailedOrder,
	OrderComplete
};


class Game
{
public:
	Game();
	~Game();

	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void SetupshopSprites();
	void setupFontAndText();
	void collisionCheckCounter();
	void setupShop();
	void spawnCustomers();
	void resetSpawnTimer();
	void updateCustomerTalking();
	void orderBegins();
	void setupPlayerAnimation();
	//void updatePlayerAnimation();
	
	bool isCoffeecollected();
	bool isSugarCollected();
	bool isMilkCollected();
	bool isDishWaterCollected();
	bool iscupCollected();
	
	GameModes gameMode = GameModes::MAIN_MENU;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Text m_customerMessage;
	
	sf::Texture backCounterTexture;
	sf::Sprite backCounterSprite;
	sf::Texture coffeeMachineTexture;
	sf::Sprite coffeeMachineSprite;
	sf::Texture cashRegTexture;
	sf::Sprite cashRegSprite;
	sf::Texture counterTexture;
	sf::Sprite counterSprite;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Texture binTexture;
	sf::Sprite binSprite;
	sf::Texture sinkTexture;
	sf::Sprite sinkSprite;
	sf::Texture milkTexture;
	sf::Sprite milkSprite;
	sf::Texture cupTexture;
	sf::Sprite cupSprite;
	sf::Texture sugarTexture;
	sf::Sprite sugarSprite;
	sf::Texture m_playerTexture;
	sf::Sprite m_playerSprite;
	sf::Texture m_mainMenuTexture;
	sf::Sprite m_mainMenuSprite;
	sf::Texture openTexture;
	sf::Sprite openSprite;

	//sf::IntRect playerFrames[4];
	OrderState currentOrderState = NoOrder;

	sf::Vector2f targetPositiona{200.0f, 500.0f};
	sf::Vector2f targetPositionb{1600.0f, 500.0f };
	sf::Vector2f spawnPositon{ -10.0f, 225.0f };
	Player player;
	Customer customer;

	static const int MAX_CUSTOMERS = 5;
	Customer customers[MAX_CUSTOMERS];
	
	//back counter rects
	sf::RectangleShape m_backCounter1;
	sf::RectangleShape m_backCounter2;
	sf::RectangleShape m_backCounter3;
	sf::RectangleShape m_backCounter4;
	sf::RectangleShape m_backCounter5;

	sf::RectangleShape Dialogbox;


     //serving counter left
	sf::RectangleShape servingCounterLeft;
	//serving counter top
	sf::RectangleShape servingCountertop;
	//serving counter right
	sf::RectangleShape servingCounterRight;
	int moneyValue;
	
	sf::Clock coffeeClock;
	sf::Time coffeeTimer = sf::seconds(8.0f);
	sf::Clock spawnTimer; 
	sf::Time spawnInterval = sf::seconds(10.0f);
	sf::Vector2f startSpawnPosition = { -10.0f, 225.0f };

	sf::Clock talkingClock;
	float timeValue = 1.0f;


	bool istalking;
	bool isorderFurfilled;
	bool isorderTaken;
	bool blackCoffeeCollected{ false };
	bool milkCollected;
	bool sugarCollected;
	bool dishwaterCollected;
	bool cupCollected;
	int m_playerFrame{ -1 };
	const float PLAYER_FRAME = 1.1; // amount of frames for the movement
	float m_playerFrameCounter = 0.5f; //default frame count
	float m_playerFrameIncrease = 0.05f;

	bool m_exitGame; // contfrol exiting game



};

#endif // !GAME_HPP

