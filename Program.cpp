#include "Program.h"

void Program::undo() {
	if (!history.empty()) {
		std::unique_ptr<Action> action = std::move(history.top());
		history.pop();
		action->undoAction(figures);
		action = nullptr;
	}
 }
void Program::clear() {
	figures.clear();
	factory.clear();
	while (!history.empty()) {
		history.pop();
	}
}
void Program::remove(int remove_id) {
	if (figures.size() > remove_id && remove_id>=0) {
		std::unique_ptr<Figure> figure = std::move(figures[remove_id]);
		std::unique_ptr<Action> action = std::make_unique<DeleteAction>(std::move(figure), remove_id);
		history.push(std::move(action));
		figures.erase(figures.begin() + remove_id);


	}
}
 void Program::render(sdl::renderer& renderer) {
	 for (const std::unique_ptr<Figure>& figure : figures) {
		 figure->render(renderer);
	 }
}
 void Program::mouseClickListener(sdl::mouse_button_event mouse_button_event) {
	 if (factory.isBuilding()) {
		 std::unique_ptr<Figure> figure = factory.buildingFigure(mouse_button_event);
		 if (figure) {
			 figures.emplace_back(std::move(figure));
			 std::unique_ptr<Action> action = std::make_unique<CreateAction>();
			 history.push(std::move(action));
		 }
	 }
	 else {
		 if (mouse_button_event.button() == sdl::mouse_button_event::right && mouse_button_event.type() == sdl::mouse_button_event::down) {
			 for (int i = 0; i < figures.size(); ++i) {
				 if (figures[i]->isInside(vertex{ mouse_button_event.x(), mouse_button_event.y() })) {
					 std::unique_ptr<Action> action = std::make_unique<DeleteAction>(std::move(figures[i]),i);
					 history.push(std::move(action));
					 figures.erase(figures.begin() + i);
					 break;
				 }
			 }
		 }
	 }
 }

 void Program::saveFile(char file_name[128]) {
	 std::ofstream os(file_name);
	 if (os) {
		 for (const std::unique_ptr<Figure>& figure : figures) {
			 figure->save(os);
		 }
	 }
 }
 void Program::loadFile(char file_name[128]) {
	 std::ifstream is(file_name);
	 if (is) {
		 loader loader;
		 figures = loader.load(is);
	 }
 }
 Brush* Program::getBrush() {
	 return &(this->brush);

 }
 void Program::addRectangle() {
	 factory.startBuildRectangle(brush);
	 }
 void Program::addTrapeze() {
	 factory.startBuildTrapeze(brush);
	 }
 void Program::addRhombus() {
	 factory.startBuildRhombus(brush);
	 }
 void Program::addPolyline() {
	 factory.startPolyBuildLine(brush);
	 }
 void Program::addPolyfigure() {
	 factory.startPolyBuildFigure(brush);
	 }
 void Program::addCircle() {
	 factory.startBuildCircle(brush);
	 }

