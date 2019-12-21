#pragma once
#include "Figure.h"



struct Rectangle : Figure {
public:

	explicit Rectangle(const std::array<vertex, 4>& vertices);

	void render(const sdl::renderer& renderer);
	void addBrush(Brush& brush)  override;
	void save(std::ostream& os) const override;
	bool isInside(vertex& v);



private:
	std::array<vertex, 4> vertices_;
	Brush brush;

};



struct RectangleBuilder : Builder {
public:
	std::unique_ptr<Figure> add_vertex(const vertex& v);
	explicit RectangleBuilder(Brush& brush);
private:
	int32_t n_ = 0;
	std::array<vertex, 4> vertices_;
	Brush brush;
};