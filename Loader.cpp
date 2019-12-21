#include "Loader.h"

std::vector<std::unique_ptr<Figure>> loader::load(std::ifstream& is) {
	std::string figure_name;
	std::vector<std::unique_ptr<Figure>> figures;
	while (is >> figure_name) {
		vertex v;

		if (figure_name == std::string("rhombus")) {
			std::array<vertex, 4> vertices;
			for (int32_t i = 0; i < 4; ++i) {
				is >> v.x >> v.y;
				vertices[i] = v;
			}
			Brush load_clr{};
			is >> load_clr.red >> load_clr.green >> load_clr.blue;
			figures.emplace_back(std::make_unique<Rhombus>(vertices));
			(*figures[figures.size() - 1]).addBrush(load_clr);
		}
		else if (figure_name == std::string("rectangle")) {
			std::array<vertex, 4> vertices;
			for (int32_t i = 0; i < 4; ++i) {
				is >> v.x >> v.y;
				vertices[i] = v;
			}
			Brush load_clr{};
			is >> load_clr.red >> load_clr.green >> load_clr.blue;
			figures.emplace_back(std::make_unique<Rectangle>(vertices));
			(*figures[figures.size() - 1]).addBrush(load_clr);
		}
		else if (figure_name == std::string("trapeze")) {
			std::array<vertex, 4> vertices;
			for (int32_t i = 0; i < 4; ++i) {
				is >> v.x >> v.y;
				vertices[i] = v;
			}
			Brush load_clr{};
			is >> load_clr.red >> load_clr.green >> load_clr.blue;
			figures.emplace_back(std::make_unique<Trapeze>(vertices));
			(*figures[figures.size() - 1]).addBrush(load_clr);
		}
		else if (figure_name == std::string("circle")) {
			std::array<vertex, 2> vertices;
			for (int i = 0; i < 2; ++i) {
				is >> v.x >> v.y;
				vertices[i] = v;
			}
			Brush load_clr{};
			is >> load_clr.red >> load_clr.green >> load_clr.blue;
			figures.emplace_back(std::make_unique<Circle>(vertices));
			(*figures[figures.size() - 1]).addBrush(load_clr);
		}
		else if (figure_name == std::string("polyline")) {
			std::vector<vertex> vertices;
			int count_v;
			is >> count_v;
			for (int i = 0; i < count_v; ++i) {
				is >> v.x >> v.y;
				vertices.push_back(v);
			}
			Brush load_clr{};
			is >> load_clr.red >> load_clr.green >> load_clr.blue;
			figures.emplace_back(std::make_unique<Polyline>(vertices));
			(*figures[figures.size() - 1]).addBrush(load_clr);
		}
		else if (figure_name == std::string("polyfigure")) {
			std::vector<vertex> vertices;
			int count_v;
			is >> count_v;
			for (int i = 0; i < count_v; ++i) {
				is >> v.x >> v.y;
				vertices.push_back(v);
			}
			Brush load_clr{};
			is >> load_clr.red >> load_clr.green >> load_clr.blue;
			figures.emplace_back(std::make_unique<Polyfigure>(vertices));
			(*figures[figures.size() - 1]).addBrush(load_clr);
		}
	}
	return figures;
}