LIBS=-lGL -lglfw -lGLEW -lassimp
HEADERS=obj_parser.h
FILES=obj_parser.cpp usage.cpp

main_file: $(FILES) $(HEADERS)
	g++ -o main_file $(FILES)  $(LIBS) -I.