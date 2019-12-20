#pragma once
#include "Figure.h"
#include "Helper.h"



struct Rhombus : Figure {
public:

	Rhombus(const std::array<vertex, 4>& vertices) : vertices_(vertices) {}

	void render(const sdl::renderer& renderer)  override {
		renderer.set_color(brush.red, brush.green, brush.blue);
		for (int32_t i = 0; i < 4; ++i) {
			renderer.draw_line(vertices_[i].x, vertices_[i].y,
				vertices_[(i + 1) % 4].x, vertices_[(i + 1) % 4].y);
		}
		renderer.set_color(0, 0, 0);
	}
	void addBrush(Brush& brush)  override {
		this->brush.blue = brush.blue;
		this->brush.red = brush.red;
		this->brush.green = brush.green;
	}
	void save(std::ostream& os) const override {
		os << "rhombus\n";
		for (int32_t i = 0; i < 4; ++i) {
			os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
		}
		os << brush.red << ' ' << brush.green << ' ' << brush.blue << '\n';

	}
	bool isInside(vertex& v) override {
		return isInside1(vertices_, v);
	}
	~Rhombus() { }

private:
	std::array<vertex, 4> vertices_;
	Brush brush;

};



struct RhombusBuilder : Builder {
public:
	std::unique_ptr<Figure> add_vertex(const vertex& v) {
		vertices_[n_] = v;
		n_ += 1;
		if (n_ != 4) {
			return nullptr;
		}
		std::unique_ptr<Figure>  figure = std::make_unique<Rhombus>(vertices_);
		figure->addBrush(brush);
		return std::move(figure);
	}
	RhombusBuilder(Brush& brush) {
		this->brush.blue = brush.blue;
		this->brush.red = brush.red;
		this->brush.green = brush.green;
	}
private:
	int32_t n_ = 0;
	std::array<vertex, 4> vertices_;
	Brush brush;
};