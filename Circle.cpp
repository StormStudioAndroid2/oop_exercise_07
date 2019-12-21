#include "Circle.h"
#include "math.h"

	Circle::Circle(const std::array<vertex, 2>& vertices) : vertices_(vertices) {}

	void Circle::render(const sdl::renderer& renderer)   {
		renderer.set_color(brush.red, brush.green, brush.blue);
		;
		DrawCircle(renderer, vertices_[0].x, vertices_[0].y, this->getLength(vertices_[0], vertices_[1]));
		renderer.set_color(0, 0, 0);
	}
	void Circle::addBrush(Brush& brush)   {
		this->brush.blue = brush.blue;
		this->brush.red = brush.red;
		this->brush.green = brush.green;
	}
	void Circle::save(std::ostream& os) const  {
		os << "circle\n";
		for (int32_t i = 0; i < 2; ++i) {
			os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
		}
		os << brush.red << ' ' << brush.green << ' ' << brush.blue << '\n';
	}

	bool Circle::isInside(vertex& v)  {
		int32_t radius = (vertices_[0].x - vertices_[1].x)*(vertices_[0].x - vertices_[1].x) + (vertices_[0].y - vertices_[1].y)*(vertices_[0].y - vertices_[1].y);
		return ((vertices_[0].x - v.x)*(vertices_[0].x - v.x) + (vertices_[0].y - v.y)*(vertices_[0].y - v.y) < radius);
	}

	void Circle::DrawCircle(const sdl::renderer&renderer, int32_t centreX, int32_t centreY, int32_t radius)
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
			renderer.draw_point(centreX + x, centreY - y);
			renderer.draw_point(centreX + x, centreY + y);
			renderer.draw_point(centreX - x, centreY - y);
			renderer.draw_point(centreX - x, centreY + y);
			renderer.draw_point(centreX + y, centreY - x);
			renderer.draw_point(centreX + y, centreY + x);
			renderer.draw_point(centreX - y, centreY - x);
			renderer.draw_point(centreX - y, centreY + x);

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
	int32_t Circle::getLength(const vertex& v1, const vertex& v2) {
		return (int32_t)sqrt((v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y));
	}
	




	std::unique_ptr<Figure> CircleBuilder::add_vertex(const vertex& v) {
		vertices_[n_] = v;
		n_ += 1;
		if (n_ != 2) {
			return nullptr;
		}
		std::unique_ptr<Figure>  figure = std::make_unique<Circle>(vertices_);
		figure->addBrush(brush);
		return std::move(figure);
	}
	CircleBuilder::CircleBuilder(Brush& brush) {
		this->brush.blue = brush.blue;
		this->brush.red = brush.red;
		this->brush.green = brush.green;
	}
