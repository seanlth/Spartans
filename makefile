C=clang++                                                                                
FLAGS= -std=c++11 -o Spartans
all: spartans
spartans: main.cpp 
	$(C) $(FLAGS) main.cpp IO.cpp Map.cpp Player.cpp GraphicsEngine.cpp
