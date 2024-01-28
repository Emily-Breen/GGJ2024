#include "Game.h"
#include <iostream>




Game::Game() :
	m_window{ sf::VideoMode{ 1500U, 800U, 32U }, "Caffeine Chaos" },
	m_exitGame{false} //when true game will exit
{

	setupFontAndText(); // load font 
	SetupshopSprites();
	setupShop();
	player.initialiseplayer();
	//customer.initialiseCustomer();
	//player.getBody();
	for (int i = 0; i < MAX_CUSTOMERS; ++i)
	{
		customers[i].initialiseCustomer();
		//coffeeClock.restart();
		customers[i].spawnCustomer(startSpawnPosition);
	
	}
	
}


Game::~Game()
{
}



void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
		
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
			
		}
		

	}
}



void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::A == t_event.key.code)
	{
		sf::Vector2f movement(-5.0f, 0.0f); 
		player.move(movement);
	}
	if (sf::Keyboard::D == t_event.key.code)
	{
		sf::Vector2f movement(5.0f, 0.0f); 
		player.move(movement);
	}
	if (sf::Keyboard::W == t_event.key.code)
	{
		sf::Vector2f movement(0.0f, -5.0f); 
		player.move(movement);
	}
	if (sf::Keyboard::S == t_event.key.code)
	{
		sf::Vector2f movement(0.0f, +5.0f); 
		player.move(movement);

	}
	if (sf::Keyboard::Return == t_event.key.code) {
		if (currentOrderState == TakingOrder) {
			currentOrderState = FulfillingOrder;
			//logic for order to go here 
		}
	}
	m_playerSprite.setPosition(player.getBody().getPosition());
	
}


void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	if (gameMode == GameModes::MAIN_MENU)
{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			gameMode = GameModes::GAME_PLAY;
		}
	}
	else if(gameMode == GameModes::GAME_PLAY){
		spawnCustomers();
	//updatePlayerAnimation
	setupPlayerAnimation();
	
	if (coffeeClock.getElapsedTime() > coffeeTimer&& currentOrderState!=TakingOrder)
	{
		for (int i = 0; i < MAX_CUSTOMERS; ++i)
		{
			customers[i].moveFromCounter(targetPositionb);
			istalking = false;
		}
	}
	else
	{
		for(int i = 0; i < MAX_CUSTOMERS; ++i)
		{
			customers[i].moveTowardCounter(targetPositiona);
			updateCustomerTalking();
			currentOrderState = TakingOrder;
			if (TakingOrder) {
				customers[i].stop();
			}
		}
	}
	switch (currentOrderState) {
	case TakingOrder:
		for (int i = 0; i < MAX_CUSTOMERS; i++) {
			customers[i].stop();
		}
		break;
	case FulfillingOrder:
		
		if (isCoffeecollected() && isSugarCollected() && isMilkCollected() && isDishWaterCollected() && iscupCollected()) {
			
			currentOrderState = OrderComplete;
		}
		break;
	case OrderComplete:
		for (int i = 0; i < MAX_CUSTOMERS; ++i)
		{
			customers[i].moveFromCounter(targetPositionb);
			istalking = false;
			currentOrderState = OrderComplete;
		}
		moneyValue++;
		break;
	case FailedOrder:

		break;
	default:
		// No order or unknown state
		break;
	}
	isCoffeecollected();
	isSugarCollected();
	isMilkCollected();
	isDishWaterCollected();
	iscupCollected();



	}
	

}


void Game::render()
{
	m_window.clear(sf::Color::White);
	//m_window.draw(m_welcomeMessage);
	//m_window.draw(m_logoSprite);
	if (gameMode == GameModes::MAIN_MENU) {
		m_window.draw(m_mainMenuSprite);
		m_window.draw(openSprite);
	}
	else {
		m_window.draw(m_backCounter1);
		m_window.draw(m_backCounter2);
		m_window.draw(m_backCounter3);
		m_window.draw(m_backCounter4);
		m_window.draw(m_backCounter5);
		m_window.draw(backgroundSprite);
		m_window.draw(backCounterSprite);
		m_window.draw(coffeeMachineSprite);
		m_window.draw(servingCounterLeft);
		m_window.draw(servingCountertop);
		m_window.draw(servingCounterRight);
		m_window.draw(counterSprite);
		m_window.draw(cashRegSprite);
		m_window.draw(binSprite);
		m_window.draw(sinkSprite);
		m_window.draw(milkSprite);
		m_window.draw(sugarSprite);
		m_window.draw(cupSprite);
		m_window.draw(m_playerSprite);
		//m_window.draw(m_customerMessage);
		if (istalking = true) {
			//m_window.draw(Dialogbox);

			m_window.draw(m_customerMessage);
		}
		m_window.draw(player.getBody());
		for (int i = 0; i < MAX_CUSTOMERS; ++i)
		{
			sf::Vector2f customerPos = customers[i].getCustomerBody().getPosition();
			//std::cout << "Customer " << i << " position: (" << customerPos.x << ", " << customerPos.y << ")" << std::endl;
			m_window.draw(customers[i].getCustomerBody());
		}
	}
	//m_window.draw(customer.getCustomerBody());
	m_window.display();
}

void Game::SetupshopSprites()
{
	if (!backCounterTexture.loadFromFile("ASSETS\\IMAGES\\back_counter.png"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	backCounterSprite.setTexture(backCounterTexture);
	backCounterSprite.setPosition(190.0f,625.0f);

	if (!counterTexture.loadFromFile("ASSETS\\IMAGES\\counter.png"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	counterSprite.setTexture(counterTexture);
	counterSprite.setPosition(150.0f, 550.0f);
	if (!backgroundTexture.loadFromFile("ASSETS\\IMAGES\\background.png"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	backgroundSprite.setTexture(backgroundTexture);

	if (!coffeeMachineTexture.loadFromFile("ASSETS\\IMAGES\\machine.png"))
	{
		std::cout << "problem loading arial black font" << std::endl;

	}
	coffeeMachineSprite.setTexture(coffeeMachineTexture);
	coffeeMachineSprite.setPosition(210.0f, 750.0f);
	if (!cashRegTexture.loadFromFile("ASSETS\\IMAGES\\cash_register.png"))
	{
		std::cout << "problem loading arial black font" << std::endl;

	}
	cashRegSprite.setTexture(cashRegTexture);
	cashRegSprite.setPosition(140.0f, 550.0f);
	cashRegSprite.setScale(1.5f, 1.5f);
	cashRegSprite.setRotation(-10);
	if (!binTexture.loadFromFile("ASSETS\\IMAGES\\bin.png"))
	{
		std::cout << "problem loading arial black font" << std::endl;

	}
	binSprite.setTexture(binTexture);
	binSprite.setPosition(1210.0f, 600.0f);
	binSprite.setScale(0.8, 0.8);
	binSprite.setRotation(90);
	if (!milkTexture.loadFromFile("ASSETS\\IMAGES\\milk-jug.png"))
	{
		std::cout << "problem loading arial black font" << std::endl;

	}
	milkSprite.setTexture(milkTexture);
	milkSprite.setPosition(630.0f, 750.0f);
	
	if (!sinkTexture.loadFromFile("ASSETS\\IMAGES\\sink.png"))
	{
		std::cout << "problem loading arial black font" << std::endl;

	}
	sinkSprite.setTexture(sinkTexture);
	sinkSprite.setPosition(840.0f, 750.0f);
	if (!sugarTexture.loadFromFile("ASSETS\\IMAGES\\sugar.png"))
	{
		std::cout << "problem loading arial black font" << std::endl;

	}
	sugarSprite.setTexture(sugarTexture);
	sugarSprite.setPosition(420.0f, 750.0f);
	if (!cupTexture.loadFromFile("ASSETS\\IMAGES\\cups.png"))
	{
		std::cout << "problem loading arial black font" << std::endl;

	}
	cupSprite.setTexture(cupTexture);
	cupSprite.setPosition(1050.0f, 750.0f);
	if (!m_playerTexture.loadFromFile("ASSETS\\IMAGES\\spritesheet.png"))
	{
		std::cout << "problem loading arial black font" << std::endl;

	}
	m_playerSprite.setTexture(m_playerTexture);
	m_playerSprite.setScale(2.0, 2.0);
	m_playerSprite.setPosition(500.0f, 400.0f);
	m_playerSprite.setTextureRect(sf::IntRect(0,0,800,100));

	if (!m_mainMenuTexture.loadFromFile("ASSETS\\IMAGES\\Main Menu.png"))
	{
		std::cout << "problem loading arial black font" << std::endl;

	}
	m_mainMenuSprite.setTexture(m_mainMenuTexture);
	
	if (!openTexture.loadFromFile("ASSETS\\IMAGES\\open.png"))
	{
		std::cout << "problem loading arial black font" << std::endl;

	}
	openSprite.setTexture(openTexture);
	openSprite.setPosition(15.0f, 50.0f);
}


void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	//m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_customerMessage.setFont(m_ArialBlackfont);
	m_customerMessage.setCharacterSize(15U); //set the size of the text onscreen
	m_customerMessage.setPosition(250.0f, 300.0f); //sets the position it appears onscreen
	m_customerMessage.setFillColor(sf::Color::Red); //Colour of text

}


void Game:: collisionCheckCounter()
{

}

void Game::setupShop()
{
	m_backCounter1.setSize(sf::Vector2f(200.0f, 200.0f));
	m_backCounter1.setPosition(210.0f, 750.0f);
	m_backCounter1.setFillColor(sf::Color::Blue);

	m_backCounter2.setSize(sf::Vector2f(200.0f, 200.0f));
	m_backCounter2.setPosition(420.0f, 750.0f);
	m_backCounter2.setFillColor(sf::Color::Blue);

	m_backCounter3.setSize(sf::Vector2f(200.0f, 200.0f));
	m_backCounter3.setPosition(630.0f, 750.0f);
	m_backCounter3.setFillColor(sf::Color::Blue);

	m_backCounter4.setSize(sf::Vector2f(200.0f, 200.0f));
	m_backCounter4.setPosition(840.0f, 750.0f);
	m_backCounter4.setFillColor(sf::Color::Blue);

	m_backCounter5.setSize(sf::Vector2f(200.0f, 200.0f));
	m_backCounter5.setPosition(1050.0f, 750.0f);
	m_backCounter5.setFillColor(sf::Color::Blue);

	servingCounterLeft.setSize(sf::Vector2f(100.0f, 150.0f));
	servingCounterLeft.setPosition(150.0f, 550.0f);
	servingCounterLeft.setFillColor(sf::Color::Red);

	servingCounterRight.setSize(sf::Vector2f(100.0f, 150.0f));
	servingCounterRight.setPosition(1200.0f, 550.0f);
	servingCounterRight.setFillColor(sf::Color::Red);
	
	servingCountertop.setSize(sf::Vector2f(950.0f, 50.0f));
	servingCountertop.setPosition(250.0f, 550.0f);
	servingCountertop.setFillColor(sf::Color::Green);

	Dialogbox.setSize(sf::Vector2f(150.0f, 200.0f));
	Dialogbox.setPosition(250.0f, 300.0f);
	Dialogbox.setFillColor(sf::Color::White);


}


void Game::spawnCustomers()
{
	if (spawnTimer.getElapsedTime() > spawnInterval)
	{
		bool restartClock = true;  // Flag to restart the clock only once

		// Spawn logic.
		for (int i = 0; i < MAX_CUSTOMERS; ++i)
		{
			if (customers[i].isInactive() || customers[i].getCustomerBody().getPosition().x > m_window.getSize().x)
			{
				if (restartClock)
				{
					coffeeClock.restart(); 
					restartClock = false;
				}

				customers[i].spawnCustomer(startSpawnPosition);
				resetSpawnTimer();
				
			}
		}
	}
}

void Game::resetSpawnTimer()
{
	
		spawnTimer.restart(); // Restart

}

void Game::updateCustomerTalking()
{
	
	int randomGen = rand() % 10 + 1; // randomizes the lines in switch statement to appear onscreen
	std::string talking;

	sf::Time talkingCustomer = talkingClock.getElapsedTime();//returns the time from last call to restart
	
	if (timeValue * talkingCustomer.asSeconds() > 6.0&& istalking) //if statement that for every fourth cycle through the update it updates the new line from switch statement
	{

		switch (randomGen) // sswitch to have random messages appear on screen
		{
		case 1:
			talking = "";
			
			m_customerMessage.setString("'Can I have a black coffee?'");
			orderBegins();
			break;
		case 2:
			talking = "";
		
			m_customerMessage.setString("'Can I have a Cappucino'?");
			break;
		case 3:
			talking = "";
			
			m_customerMessage.setString("'Can I have just an empty cup...for reasons'");
			break;
		case 4:
			talking = "";
			
			m_customerMessage.setString("'Dishwater pronto!'");
			break;
		case 5:
			talking = "";
			
			m_customerMessage.setString("'I dont want anything, I'm just here to annoy you'");
			break;
		case 6:
			talking = "";
			
			m_customerMessage.setString("''");
			break;
		case 7:
			talking = "";
			
			m_customerMessage.setString("'Can I have sugar...I need the sweet sweet sugar'");
			break;
		case 8:
			talking = "";
			m_customerMessage.setString("'Nare a chance of some dirty bean juice? '");
			break;
		case 9:
			talking = "";
			 
			m_customerMessage.setString("'Can I have a cappucino...minus the milk'");
			break;
		case 10:
			talking = "";
			
			m_customerMessage.setString("''");
			break;
		}
		talkingClock.restart(); //restarts the clock 
	}
	else
	{
		istalking = false;
	}

}

void Game::orderBegins()
{
	do {

	} while (true);
}

bool Game::isCoffeecollected()
{
	m_playerSprite.setPosition(player.getBody().getPosition());
	if (m_playerSprite.getGlobalBounds().intersects(m_backCounter1.getGlobalBounds())) {
		blackCoffeeCollected = true;
		std::cout << "coffee nommy";
		currentOrderState = FulfillingOrder;
	}
	else {
		blackCoffeeCollected = false;
	}
	return blackCoffeeCollected;
}

bool Game::isSugarCollected()
{
	m_playerSprite.setPosition(player.getBody().getPosition());
	if (m_playerSprite.getGlobalBounds().intersects(m_backCounter2.getGlobalBounds())) {
		sugarCollected = true;
		std::cout << "yes....thats sugar...";
		currentOrderState = FulfillingOrder;
	}
	else {
		sugarCollected = false;
	}

	return sugarCollected;
}

bool Game::isMilkCollected()
{
	m_playerSprite.setPosition(player.getBody().getPosition());
	if (m_playerSprite.getGlobalBounds().intersects(m_backCounter3.getGlobalBounds())) {
		milkCollected = true;
		std::cout << "cow lactate is best lactate";
		currentOrderState = FulfillingOrder;
	}
	else {
		milkCollected = false;
	}

	return milkCollected;
}

bool Game::isDishWaterCollected()
{
	m_playerSprite.setPosition(player.getBody().getPosition());
	if (m_playerSprite.getGlobalBounds().intersects(m_backCounter4.getGlobalBounds())) {
		dishwaterCollected = true;
		std::cout << "christ ";
		currentOrderState = FulfillingOrder;
	}
	else {
		dishwaterCollected = false;
	}

	return dishwaterCollected;
}

bool Game::iscupCollected()
{
	m_playerSprite.setPosition(player.getBody().getPosition());
	if (m_playerSprite.getGlobalBounds().intersects(m_backCounter5.getGlobalBounds())) {
		cupCollected = true;
		std::cout << "Thats a fine cup you have there now ";
		currentOrderState = FulfillingOrder;
	}
	else {
		cupCollected = false;
	}

	return cupCollected;
}
void Game::setupPlayerAnimation()
{
	int frame = 0; // variable for frame
	const int FRAME_WIDTH = 85; //width of the frame
	const int FRAME_HEIGHT = 100;// length of the frame

	m_playerFrameCounter += m_playerFrameIncrease; // sets the increment to the frame counter
	frame = static_cast<int>(m_playerFrameCounter); // sets the frame counter to an int and assigns to frame
	if (frame >= PLAYER_FRAME)
	{// if the frame counter exceeds 11 frames it stops the counter
		frame = 0; // sets variable to 0
		m_playerFrameCounter = 0.0f; // sets counter to 0
	}
	if (frame != m_playerFrame)
	{
		m_playerFrame = frame;
		m_playerSprite.setTextureRect(sf::IntRect{ frame * FRAME_WIDTH,0, FRAME_WIDTH, FRAME_HEIGHT });
	}
}

//void Game::updatePlayerAnimation()
//{
//	// Get the current animation frame based on player movement or direction
//	// For example, if the player is moving left, use playerFrames[3]
//	sf::IntRect currentFrame = playerFrames[3];
//
//	// Update the texture rectangle of the sprite to display the current frame
//	m_playerSprite.setTextureRect(currentFrame);
//}

