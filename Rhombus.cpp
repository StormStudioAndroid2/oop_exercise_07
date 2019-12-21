#include "Rhombus.h"



Rhombus::Rhombus(const std::array<vertex, 4>& vertices) : vertices_(vertices) {}

void Rhombus::render(const sdl::renderer& renderer) {
	renderer.set_color(brush.red, brush.green, brush.blue);
	for (int32_t i = 0; i < 4; ++i) {
		renderer.draw_line(vertices_[i].x, vertices_[i].y,
			vertices_[(i + 1) % 4].x, vertices_[(i + 1) % 4].y);
	}
	renderer.set_color(0, 0, 0);
}
void Rhombus::addBrush(Brush& brush) {
	this->brush.blue = brush.blue;
	this->brush.red = brush.red;
	this->brush.green = brush.green;
}
void Rhombus::save(std::ostream& os) const {
	os << "rhombus\n";
	for (int32_t i = 0; i < 4; ++i) {
		os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
	}
	os << brush.red << ' ' << brush.green << ' ' << brush.blue << '\n';

}
bool Rhombus::isInside(vertex& v) {

	std::vector<vertex> vect(this->vertices_.begin(), this->vertices_.end());;

	return	isInside1(vect, v);
}
std::unique_ptr<Figure> RhombusBuilder::add_vertex(const vertex& v) {
	vertices_[n_] = v;
	n_ += 1;
	if (n_ != 4) {
		return nullptr;
	}
	std::unique_ptr<Figure>  figure = std::make_unique<Rhombus>(vertices_);
	figure->addBrush(brush);
	return std::move(figure);
}
RhombusBuilder::RhombusBuilder(Brush& brush) {
	this->brush.blue = brush.blue;
	this->brush.red = brush.red;
	this->brush.green = brush.green;
}
