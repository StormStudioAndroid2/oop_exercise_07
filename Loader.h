#ifndef D_LOADER_H
#define D_LOADER_H
#pragma once
#include<vector>
#include<memory>
#include "Circle.h"
#include "Figure.h"
#include "Rhombus.h"
#include "Rectangle.h"
#include "Trapeze.h"
#include "Polyline.h"
#include "Polyfigure.h"
#include <iostream>
#include <fstream>
struct loader {
	std::vector<std::unique_ptr<Figure>> load(std::ifstream& is);
	~loader() = default; 
};

#endif //D_LOADER_H