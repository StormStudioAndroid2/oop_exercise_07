#pragma once

#include <memory>
#include "sdl.h"
#include <array>
#include <vector>
#include <math.h>
#define INF INT16_MAX;
struct vertex {
	int32_t x, y;

};
struct Brush {
	int green;
	int red;
	int blue;
	Brush() {
		red = 0;
		green = 0; 
		blue = 0;
	}
};
struct Figure {
public:
	virtual void render(const sdl::renderer& renderer)  = 0;
	virtual void addBrush(Brush& brush)  = 0;
	virtual bool isInside(vertex& v) = 0;
	virtual void save(std::ostream& os) const = 0;
	virtual ~Figure() = default;
};
struct Builder {
public:

	virtual std::unique_ptr<Figure> add_vertex(const vertex& v) = 0;
	virtual ~Builder() = default;

};
struct Action
{
public:
	virtual void undoAction(std::vector<std::unique_ptr<Figure>>& figures) = 0;
	virtual ~Action() = default;

};
struct CreateAction : Action
{
public:
	void undoAction(std::vector<std::unique_ptr<Figure>>& figures) override;
};
struct DeleteAction : Action
{
public:
	void undoAction(std::vector<std::unique_ptr<Figure>>& figures) override;
	explicit DeleteAction(std::unique_ptr<Figure> figure, size_t index);
private:
	std::unique_ptr<Figure> figure;
	size_t index;
};

bool onSegment(vertex p, vertex q, vertex r);

// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(vertex p, vertex q, vertex r);

bool doIntersect(vertex p1, vertex q1, vertex p2, vertex q2);


bool isInside1(std::vector<vertex>& polygon, vertex p);