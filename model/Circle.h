#pragma once
#include "Figure.h"
#include "math.h"
#include "sdl.h"

struct Circle : Figure {
public:

	Circle(const std::array<vertex, 2>& vertices) : vertices_(vertices) {}

	void render(const sdl::renderer& renderer)  override {
		renderer.set_color(brush.red, brush.green, brush.blue);
		;
		DrawCircle(renderer, vertices_[0].x, vertices_[0].y, this->getLength(vertices_[0], vertices_[1]));
		renderer.set_color(0, 0, 0);
	}
	void addBrush(Brush& brush)  override {
		this->brush.blue = brush.blue;
		this->brush.red = brush.red;
		this->brush.green = brush.green;
	}
	void save(std::ostream& os) const override {
		os << "circle\n";
		for (int32_t i = 0; i < 2; ++i) {
			os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
		}
		os << brush.red << ' ' << brush.green << ' ' << brush.blue << '\n';
	}

	bool isInside(vertex& v) override {
		int32_t radius = (vertices_[0].x - vertices_[1].x)*(vertices_[0].x - vertices_[1].x) + (vertices_[0].y - vertices_[1].y)*(vertices_[0].y - vertices_[1].y);
		return ((vertices_[0].x - v.x)*(vertices_[0].x - v.x) + (vertices_[0].y - v.y)*(vertices_[0].y - v.y) < radius);
	}
	~Circle() { }
	
private:
	void DrawCircle(const sdl::renderer&renderer, int32_t centreX, int32_t centreY, int32_t radius)
	{
		const int32_t diameter = (radius * 2);

		int32_t x = (radius - 1);
		int32_t y = 0;
		int32_t tx = 1;
		int32_t ty = 1;
		int32_t error = (tx - diameter);

		while (x >= y)
		{
			//  Each of the following renders an octant of the circle
			renderer.draw_line(centreX + x, centreY - y, centreX + x + 1, centreY - y + 1);
			renderer.draw_line(centreX + x, centreY + y, centreX + x + 1, centreY + y + 1);
			renderer.draw_line(centreX - x, centreY - y, centreX - x + 1, centreY - y + 1);
			renderer.draw_line(centreX - x, centreY + y, centreX - x + 1, centreY + y + 1);
			renderer.draw_line(centreX + y, centreY - x, centreX + y + 1, centreY - x + 1);
			renderer.draw_line(centreX + y, centreY + x, centreX + y + 1, centreY + x + 1);
			renderer.draw_line(centreX - y, centreY - x, centreX - y + 1, centreY - x + 1);
			renderer.draw_line(centreX - y, centreY + x, centreX - y + 1, centreY + x + 1);

			if (error <= 0)
			{
				++y;
				error += ty;
				ty += 2;
			}

			if (error > 0)
			{
				--x;
				tx += 2;
				error += (tx - diameter);
			}
		}
	}
	int32_t getLength(const vertex& v1, const vertex& v2) {
		return (int32_t)sqrt((v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y));
	}
	std::array<vertex, 2> vertices_;
	Brush brush;
	
};



struct CircleBuilder : Builder {
public:
	std::unique_ptr<Figure> add_vertex(const vertex& v) {
		vertices_[n_] = v;
		n_ += 1;
		if (n_ != 2) {
			return nullptr;
		}
		std::unique_ptr<Figure>  figure = std::make_unique<Circle>(vertices_);
		figure->addBrush(brush);
		return std::move(figure);
	}
	CircleBuilder(Brush& brush) {
		this->brush.blue = brush.blue;
		this->brush.red = brush.red;
		this->brush.green = brush.green;
	}
private:
	int32_t n_ = 0;
	std::array<vertex, 2> vertices_;
	Brush brush;
};