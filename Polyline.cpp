#pragma once
#include "Polyline.h"

Polyline::Polyline(const std::vector<vertex>& vertices) : vertices_(vertices) {}

void Polyline::render(const sdl::renderer& renderer) {
	renderer.set_color(brush.red, brush.green, brush.blue);
	for (int32_t i = 0; i < vertices_.size() - 1; ++i) {
		renderer.draw_line(vertices_[i].x, vertices_[i].y,
			vertices_[(i + 1)].x, vertices_[(i + 1)].y);
	}

	renderer.set_color(0, 0, 0);

}
void Polyline::addBrush(Brush& brush) {
	this->brush.blue = brush.blue;
	this->brush.red = brush.red;
	this->brush.green = brush.green;
}

void Polyline::save(std::ostream& os) const {
	os << "polyline" << ' ' << vertices_.size() << std::endl;
	for (int32_t i = 0; i < vertices_.size(); ++i) {
		os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
	}
	os << this->brush.red << ' ' << this->brush.green << ' ' << this->brush.blue << std::endl;
}
bool Polyline::isInside(vertex& v) {
	return	false;


}



std::unique_ptr<Figure> PolylineBuilder::add_vertex(const vertex& v) {
	vertices_.push_back(v);
	std::unique_ptr<Figure>  figure = std::make_unique<Polyline>(vertices_);
	figure->addBrush(brush);
	return std::move(figure);
}
PolylineBuilder::PolylineBuilder(Brush& brush) {
	this->brush.blue = brush.blue;
	this->brush.red = brush.red;
	this->brush.green = brush.green;
}
