PlayerStrategiesDriver: GameEngine.o Cards.o Player.o Orders.o Map.o PlayerStrategies.o testPlayerStrategies.o PlayerStrategiesDriver.o
	g++ GameEngine.o Cards.o Player.o Orders.o Map.o PlayerStrategies.o testPlayerStrategies.o PlayerStrategiesDriver.o -o PlayerStrategiesDriver

GameEngine.o: GameEngine.cpp
	g++ -std=c++14 -c GameEngine.cpp

Cards.o: Cards.cpp
	g++ -std=c++14 -c Cards.cpp

Player.o: Player.cpp
	g++ -std=c++14 -c Player.cpp

Orders.o: Orders.cpp
	g++ -std=c++14 -c Orders.cpp

Map.o: Map.cpp
	g++ -std=c++14 -c Map.cpp

CommandProcessing.o: CommandProcessing.cpp
	g++ -std=c++14 -c CommandProcessing.cpp

PlayerStrategies.o: PlayerStrategies.cpp
	g++ -std=c++14 -c PlayerStrategies.cpp

testPlayerStrategies.o: testPlayerStrategies.cpp
	g++ -std=c++14 -c testPlayerStrategies.cpp

PlayerStrategiesDriver.o: PlayerStrategiesDriver.cpp
	g++ -std=c++14 -c PlayerStrategiesDriver.cpp