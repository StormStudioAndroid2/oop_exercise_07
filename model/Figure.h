#pragma once

#include "Builder.h"
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
	void undoAction(std::vector<std::unique_ptr<Figure>>& figures) override {
		figures.erase(figures.end() - 1);
	}
	CreateAction() {}
	~CreateAction() {}
};
struct DeleteAction : Action
{
public:
	void undoAction(std::vector<std::unique_ptr<Figure>>& figures) override {
		figures.insert(figures.begin() + index, std::move(figure));
	}
	DeleteAction(std::unique_ptr<Figure> figure, size_t index) {
		this->figure = (std::move(figure));
		this->index = index;
	}
	~DeleteAction() {}
private:
	std::unique_ptr<Figure> figure;
	size_t index;
};