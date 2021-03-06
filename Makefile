LIBS=-lGL -lglfw -lGLEW 
HEADERS=  $(HPATH)/allmodels.h  $(HPATH)/constants.h  $(HPATH)/cube.h  $(HPATH)/lodepng.h   $(HPATH)/shaderprogram.h $(HPATH)/obj_parser.h $(HPATH)/bishop.h $(HPATH)/chessboard.h $(HPATH)/scene.h $(HPATH)/pawn.h $(HPATH)/knight.h $(HPATH)/rook.h $(HPATH)/king.h $(HPATH)/queen.h
FILES=  $(SPATH)/lodepng.cpp    $(SPATH)/main_file.cpp  $(SPATH)/bishop.cpp $(SPATH)/shaderprogram.cpp $(SPATH)/obj_parser.cpp $(SPATH)/chessboard.cpp $(SPATH)/scene.cpp $(SPATH)/pawn.cpp $(SPATH)/knight.cpp $(SPATH)/rook.cpp $(SPATH)/king.cpp $(SPATH)/queen.cpp $(SPATH)/ruch.cpp
SPATH=sources
HPATH=headers


main_file: $(FILES) $(HEADERS)
	g++ -o main_file $(FILES)  $(LIBS) -I .
