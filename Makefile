CC = g++ -g -std=c++11 $(GTK)

# libs
OGL = -lGL -lGLU -lGLEW -lglut
CEF = -Lcef/linux/lib -lcef -lcef_dll_wrapper -Wl,-R. -Wl,-Rcef/linux/lib
CEFGUI = -Lbin -lcefgui -Wl,-Rbin

# required for me to properly build on Arch Linux
GTK = $$(pkg-config gtk+-2.0 --cflags) $$(pkg-config gtk+-2.0 --libs)

simple_example:
	$(CC) -o examples/simple_example examples/simple_example.cpp $(CEFGUI) $(OGL) $(CEF)

cefgui:
	$(CC) -shared -fPIC -o bin/libcefgui.so src/*.cpp $(OGL) $(CEF)
	cp -a cef/linux/lib/. bin/

all:
	make cefgui
	make simple_example
	examples/simple_example
