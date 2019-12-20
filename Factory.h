#pragma once
#include "sdl.h"
#include "model/Rectangle.h"
#include "model/Rhombus.h"
#include "model/Trapeze.h"
#include "model/Circle.h"
#include "model/Polyline.h"
#include "model/Polyfigure.h"

struct Factory {
private:
	 std::unique_ptr<Builder> builder;
	 std::unique_ptr<Builder> polyBuilder;

public:
		std::unique_ptr<Figure> buildingFigure(sdl::mouse_button_event mouse_button_event) {
			if (builder && mouse_button_event.button() == sdl::mouse_button_event::left && mouse_button_event.type() == sdl::mouse_button_event::down) {
				std::unique_ptr<Figure> figure =  builder->add_vertex(vertex{ mouse_button_event.x(), mouse_button_event.y() });
				if (figure) {
					this->builder = nullptr;
					return std::move(figure);
				}
			}
			if (polyBuilder && mouse_button_event.button() == sdl::mouse_button_event::left && mouse_button_event.type() == sdl::mouse_button_event::down) {
				std::unique_ptr<Figure> figure = polyBuilder->add_vertex(vertex{ mouse_button_event.x(), mouse_button_event.y() });
				figure = nullptr;
				return nullptr;
			}
			if (polyBuilder && mouse_button_event.button() == sdl::mouse_button_event::right && mouse_button_event.type() == sdl::mouse_button_event::down) {
				std::unique_ptr<Figure> figure = polyBuilder->add_vertex(vertex{ mouse_button_event.x(), mouse_button_event.y() });
				polyBuilder = nullptr;
				return std::move(figure);

			}    
			return nullptr;
		}
		void startBuildFigure() {}
		void startBuildTrapeze(Brush& brush) {
			builder = std::make_unique<RectangleBuilder>(brush);
	

		}
		void startBuildRectangle(Brush& brush) {
			builder = std::make_unique<TrapezeBuilder>(brush);


		}
		void startBuildRhombus(Brush& brush) {
			builder = std::make_unique<RhombusBuilder>(brush);


		}
		void startBuildCircle(Brush& brush) {
			builder = std::make_unique<CircleBuilder>(brush);


		}
		void startPolyBuildLine(Brush& brush) {
			polyBuilder = std::make_unique<PolylineBuilder>(brush);


		}
		void startPolyBuildFigure(Brush& brush) {
			polyBuilder = std::make_unique<PolyfigureBuilder>(brush);


		}
		bool isBuilding() {
			return builder != nullptr || polyBuilder!=nullptr;
		}
		
};