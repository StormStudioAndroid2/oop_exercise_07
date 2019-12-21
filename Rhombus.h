#pragma once
#include "Figure.h"



struct Rhombus : Figure {
public:

	explicit Rhombus(const std::array<vertex, 4>& vertices);

	void render(const sdl::renderer& renderer);
	void addBrush(Brush& brush)  override;
	void save(std::ostream& os) const override;
	bool isInside(vertex& v);



private:
	std::array<vertex, 4> vertices_;
	Brush brush;

};



struct RhombusBuilder : Builder {
public:
	std::unique_ptr<Figure> add_vertex(const vertex& v);
	explicit RhombusBuilder(Brush& brush);
private:
	int32_t n_ = 0;
	std::array<vertex, 4> vertices_;
	Brush brush;
};