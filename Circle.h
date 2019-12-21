#pragma once
#include "Figure.h"
#include "math.h"
struct Circle : Figure {
public:

	explicit Circle(const std::array<vertex, 2>& vertices);

	void render(const sdl::renderer& renderer)  override;
	void addBrush(Brush& brush)  override;
	void save(std::ostream& os) const override;

	bool isInside(vertex& v) override;
	
private:
	void DrawCircle(const sdl::renderer&renderer, int32_t centreX, int32_t centreY, int32_t radius);
	int32_t getLength(const vertex& v1, const vertex& v2);
	std::array<vertex, 2> vertices_;
	Brush brush;
	
};



struct CircleBuilder : Builder {
public:
	std::unique_ptr<Figure> add_vertex(const vertex& v);
	explicit CircleBuilder(Brush& brush);
private:
	int32_t n_ = 0;
	std::array<vertex, 2> vertices_;
	Brush brush;
};