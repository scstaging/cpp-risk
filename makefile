MainDriver: GameEngine.o GameEngineDriver.o Cards.o CardsDriver.o Player.o PlayerDriver.o MainDriver.o
	g++ GameEngine.o GameEngineDriver.o Cards.o CardsDriver.o Player.o PlayerDriver.o MainDriver.o -o MainDriver

GameEngine.o: GameEngine.cpp
	g++ -c GameEngine.cpp

GameEngineDriver.o: GameEngineDriver.cpp
	g++ -c GameEngineDriver.cpp

Cards.o: Cards.cpp
	g++ -c Cards.cpp

CardsDriver.o: CardsDriver.cpp
	g++ -c CardsDriver.cpp

Player.o: Player.cpp
	g++ -c Player.cpp

PlayerDriver.o: PlayerDriver.cpp
	g++ -c PlayerDriver.cpp

MainDriver.o: MainDriver.cpp
	g++ -c MainDriver.cpp