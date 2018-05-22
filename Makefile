LIBS=-lGL -lglfw -lGLEW -lassimp
HEADERS=parser.h 
FILES=parser.cpp parser_usage_example.cpp

main_file: $(FILES) $(HEADERS)
	g++ -o main_file $(FILES)  $(LIBS) -I.