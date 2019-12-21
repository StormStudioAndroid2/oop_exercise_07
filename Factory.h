#pragma once
#include "sdl.h"
#include "Rectangle.h"
#include "Rhombus.h"
#include "Trapeze.h"
#include "Circle.h"
#include "Polyline.h"
#include "Polyfigure.h"

struct Factory {
private:
	 std::unique_ptr<Builder> builder;
	 std::unique_ptr<Builder> polyBuilder;

public:
	std::unique_ptr<Figure> buildingFigure(sdl::mouse_button_event mouse_button_event);
		void startBuildFigure() {}
		void startBuildTrapeze(Brush& brush);
		void startBuildRectangle(Brush& brush);
		void startBuildRhombus(Brush& brush);
		void startBuildCircle(Brush& brush);
		void startPolyBuildLine(Brush& brush);
		void startPolyBuildFigure(Brush& brush);
		bool isBuilding();
		void clear();

};