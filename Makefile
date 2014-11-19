CC = g++ -g -std=c++11

OGL_LINUX = -lGL -lGLEW -lglfw
CEF = -Lcef/linux/lib -lcef -lcef_dll_wrapper -Wl,-R. -Wl,-Rcef/linux/lib
CEFGUI = -Lbin -lcefgui -Wl,-Rbin

GTK = $$(pkg-config gtk+-2.0 --cflags) $$(pkg-config gtk+-2.0 --libs)

simple_example_linux:
	$(CC) $(GTK) -o examples/simple_example examples/simple_example.cpp $(CEFGUI) $(CEF) $(OGL_LINUX)

cefgui_linux:
	$(CC) $(GTK) -shared -fPIC -o bin/libcefgui.so src/*.cpp $(CEF) $(OGL_LINUX)
	cp -a cef/linux/lib/. bin/

linux:
	make cefgui_linux
	make simple_example_linux
	examples/simple_example
