LIBS=-lGL -lglfw -lGLEW -lassimp
<<<<<<< HEAD
HEADERS= $(HPATH)/allmodels.h  $(HPATH)/constants.h  $(HPATH)/cube.h  $(HPATH)/lodepng.h  $(HPATH)/model.h  $(HPATH)/shaderprogram.h
FILES= $(SPATH)/cube.cpp  $(SPATH)/lodepng.cpp  $(SPATH)/main_file.cpp  $(SPATH)/model.cpp  $(SPATH)/shaderprogram.cpp
SPATH=sources
HPATH=headers
=======
HEADERS=parser.h shader.h
FILES=parser.cpp parser_usage_example.cpp

>>>>>>> 524d31e85ec3155ac30b9236d0791a07d4754111
main_file: $(FILES) $(HEADERS)
	g++ -o main_file $(FILES)  $(LIBS) -I.