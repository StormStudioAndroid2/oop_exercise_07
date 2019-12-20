#pragma once
#include "Rectangle.h"
struct Fabric {

	Figure createRectangle() {
		Builder builder;


		void startBuildFigure() {}
		void startBuildRectangle() {

			builder = std::make_unique<RectangleBuilder>();
		}
	}
};