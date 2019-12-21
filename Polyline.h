#pragma once
#include "Figure.h"

struct Polyline : Figure {
	explicit Polyline(const std::vector<vertex>& vertices);

	void render(const sdl::renderer& renderer)  override;
	void addBrush(Brush& brush)  override;

	void save(std::ostream& os) const override;
	bool isInside(vertex& v) override;

private:
	std::vector<vertex> vertices_;
	Brush brush;
};
struct PolylineBuilder : Builder {
public:
	std::unique_ptr<Figure> add_vertex(const vertex& v);
	explicit PolylineBuilder(Brush& brush);
private:
	int32_t n_ = 0;
	std::vector<vertex> vertices_;
	Brush brush;
};