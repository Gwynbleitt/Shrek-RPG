all:  include/glad/glad.c src/*.cpp
	g++ include/glad/glad.c src/*.cpp  -o out -I /usr/include/X11  -I include/ -I headers/ -lglfw  -lX11 -lGL -lGLU -lassimp -fsanitize=address