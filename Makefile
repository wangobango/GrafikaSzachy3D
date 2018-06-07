LIBS=-lGL -lglfw -lGLEW -lassimp
HEADERS= $(HPATH)/allmodels.h  $(HPATH)/constants.h  $(HPATH)/cube.h  $(HPATH)/lodepng.h  $(HPATH)/model.h  $(HPATH)/shaderprogram.h
FILES= $(SPATH)/cube.cpp  $(SPATH)/lodepng.cpp  $(SPATH)/main_file.cpp  $(SPATH)/model.cpp  $(SPATH)/shaderprogram.cpp
SPATH=sources
HPATH=headers
main_file: $(FILES) $(HEADERS)
	g++ -o main_file $(FILES)  $(LIBS) -I.