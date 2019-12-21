#pragma once
#include "Figure.h"
#include "Factory.h"
#include <vector>
#include <fstream>
#include <iostream>
#include "Loader.h"
#include <stack>
struct Program {
private:
	std::stack<std::unique_ptr<Action>> history;
	Brush brush;
	std::vector<std::unique_ptr<Figure>> figures;
    Factory factory;
public:

	 void undo();
	 void clear();
	 void render(sdl::renderer& renderer);
	 void addRectangle();
	 void addTrapeze();
	 void addRhombus();
	 void addPolyline();
	 void addPolyfigure();
	 void addCircle();
	 void mouseClickListener(sdl::mouse_button_event mouse_button_event);
	 void remove(int remove_id);
	 void saveFile(char file_name[128] );
	 void loadFile(char file_name[128]);
	 Brush* getBrush();
};