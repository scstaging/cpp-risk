MainDriver: GameEngine.o GameEngineDriver.o Cards.o CardsDriver.o Player.o PlayerDriver.o Orders.o OrdersDriver.o Map.o MapDriver.o MainDriver.o
	g++ GameEngine.o GameEngineDriver.o Cards.o CardsDriver.o Player.o PlayerDriver.o Orders.o OrdersDriver.o Map.o MapDriver.o MainDriver.o -o MainDriver

GameEngine.o: GameEngine.cpp
	g++ -std=c++14 -c GameEngine.cpp

GameEngineDriver.o: GameEngineDriver.cpp
	g++ -std=c++14 -c GameEngineDriver.cpp

Cards.o: Cards.cpp
	g++ -std=c++14 -c Cards.cpp

CardsDriver.o: CardsDriver.cpp
	g++ -std=c++14 -c CardsDriver.cpp

Player.o: Player.cpp
	g++ -std=c++14 -c Player.cpp

PlayerDriver.o: PlayerDriver.cpp
	g++ -std=c++14 -c PlayerDriver.cpp

Orders.o: Orders.cpp
	g++ -std=c++14 -c Orders.cpp

OrdersDriver.o: OrdersDriver.cpp
	g++ -std=c++14 -c OrdersDriver.cpp

Map.o: Map.cpp
	g++ -std=c++14 -c Map.cpp

MapDriver.o: MapDriver.cpp
	g++ -std=c++14 -c MapDriver.cpp

MainDriver.o: MainDriver.cpp
	g++ -std=c++14 -c MainDriver.cpp

CommandProcessing.o: CommandProcessing.cpp
	g++ -std=c++14 -c CommandProcessing.cpp