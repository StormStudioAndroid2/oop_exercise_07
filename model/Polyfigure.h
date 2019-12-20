#pragma once
#include "Figure.h"
#include "Helper.h"

struct Polyfigure : Figure {
	Polyfigure(const std::vector<vertex>& vertices) : vertices_(vertices) {}

	void render(const sdl::renderer& renderer)  override {
		renderer.set_color(brush.red, brush.green, brush.blue);
		for (int32_t i = 0; i < vertices_.size() - 1; ++i) {
			renderer.draw_line(vertices_[i].x, vertices_[i].y,
				vertices_[(i + 1)].x, vertices_[(i + 1)].y);
		}
		renderer.draw_line(vertices_[vertices_.size() - 1].x, vertices_[vertices_.size() - 1].y,
			vertices_[0].x, vertices_[0].y);
		renderer.set_color(0, 0, 0);

	}
	void addBrush(Brush& brush)  override {
		this->brush.blue = brush.blue;
		this->brush.red = brush.red;
		this->brush.green = brush.green;
	}

	void save(std::ostream& os) const override {
		os << "polyfigure" << ' ' << vertices_.size() << std::endl;
		for (int32_t i = 0; i < vertices_.size(); ++i) {
			os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
		}
		os << this->brush.red << ' ' << this->brush.green << ' ' << this->brush.blue << std::endl;
	}
	bool isInside(vertex& v) override {
		return	isInside1(vertices_, v);


	}
	~Polyfigure() { }

private:
	std::vector<vertex> vertices_;
	Brush brush;
};
struct PolyfigureBuilder : Builder {
public:
	std::unique_ptr<Figure> add_vertex(const vertex& v) {
		vertices_.push_back(v);
		std::unique_ptr<Figure>  figure = std::make_unique<Polyfigure>(vertices_);
		figure->addBrush(brush);
		return std::move(figure);
	}
	PolyfigureBuilder(Brush& brush) {
		this->brush.blue = brush.blue;
		this->brush.red = brush.red;
		this->brush.green = brush.green;
	}
private:
	int32_t n_ = 0;
	std::vector<vertex> vertices_;
	Brush brush;
};