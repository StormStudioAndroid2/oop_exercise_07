#include "Factory.h"


	std::unique_ptr<Figure> Factory::buildingFigure(sdl::mouse_button_event mouse_button_event) {
		vertex v1;
		v1.x = mouse_button_event.x();
		v1.y = mouse_button_event.y();
		if (builder && mouse_button_event.button() == sdl::mouse_button_event::left && mouse_button_event.type() == sdl::mouse_button_event::down) {
			std::unique_ptr<Figure> figure = builder->add_vertex(v1);
			if (figure) {
				this->builder = nullptr;
				return std::move(figure);
			}
		}
		if (polyBuilder && mouse_button_event.button() == sdl::mouse_button_event::left && mouse_button_event.type() == sdl::mouse_button_event::down) {
			std::unique_ptr<Figure> figure = polyBuilder->add_vertex(v1);
			figure = nullptr;
			return nullptr;
		}
		if (polyBuilder && mouse_button_event.button() == sdl::mouse_button_event::right && mouse_button_event.type() == sdl::mouse_button_event::down) {
			std::unique_ptr<Figure> figure = polyBuilder->add_vertex(v1);
			polyBuilder = nullptr;
			return std::move(figure);

		}
		return nullptr;
	}
	void Factory::startBuildTrapeze(Brush& brush) {
		builder = std::make_unique<RectangleBuilder>(brush);


	}
	void Factory::startBuildRectangle(Brush& brush) {
		builder = std::make_unique<TrapezeBuilder>(brush);


	}
	void Factory::startBuildRhombus(Brush& brush) {
		builder = std::make_unique<RhombusBuilder>(brush);


	}
	void Factory::startBuildCircle(Brush& brush) {
		builder = std::make_unique<CircleBuilder>(brush);


	}
	void Factory::startPolyBuildLine(Brush& brush) {
		polyBuilder = std::make_unique<PolylineBuilder>(brush);


	}
	void Factory::startPolyBuildFigure(Brush& brush) {
		polyBuilder = std::make_unique<PolyfigureBuilder>(brush);


	}
	bool Factory::isBuilding() {
		return builder != nullptr || polyBuilder != nullptr;
	}
	void Factory::clear() {
		builder = nullptr;
		polyBuilder = nullptr;
	}

