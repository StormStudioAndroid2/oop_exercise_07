#include <array>
#include <fstream>
#include <iostream>
#include <vector>
#include "model/Action.h"
#include "sdl.h"
#include "imgui.h"
#include "model/Rectangle.h"
#include "model/Circle.h"
#include "model/Loader.h"
#include "model/Polyfigure.h"
#include <stack>

#include "Factory.h"
void setBrush(Brush& brush) {

	ImGui::InputInt("Green", &brush.green);

	ImGui::InputInt("Blue", &brush.blue);

	ImGui::InputInt("Red", &brush.red);
	if (brush.green > 255) {
		brush.green = 255;
	}
	if (brush.blue > 255) {
		brush.blue = 255;
	}
	if (brush.red > 255) {
		brush.red = 255;
	}
}

int main() {
	Brush brush;
	Factory factory;
	std::stack<std::unique_ptr<Action>> history;

  sdl::renderer renderer("Editor");
  bool quit = false;
  std::unique_ptr<Action> action;
  std::vector<std::unique_ptr<Figure>> figures;
  std::unique_ptr<Builder> active_builder = nullptr;
  const int32_t file_name_length = 128;
  char file_name[file_name_length] = "";
  int32_t remove_id = 0;
  while(!quit){
    renderer.set_color(0,100,0);
	renderer.draw_line(20-1, 20, 20, 20+1);
	renderer.set_color(0, 0, 0);
    renderer.clear();
    sdl::event event;

    while(sdl::event::poll(event)){
      sdl::quit_event quit_event;
      sdl::mouse_button_event mouse_button_event;
      if(event.extract(quit_event)){
        quit = true;
        break;
      } else if(event.extract(mouse_button_event)) {
		  if (factory.isBuilding()) {
			  std::unique_ptr<Figure> figure = factory.buildingFigure(mouse_button_event);
			  if (figure) {
				  figures.emplace_back(std::move(figure));
				  action = std::make_unique<CreateAction>();
				  history.push(std::move(action));
				  active_builder = nullptr;
			  }
		  }
		  else {
			  if (mouse_button_event.button() == sdl::mouse_button_event::right && mouse_button_event.type() == sdl::mouse_button_event::down) {
				  for (int i = 0; i < figures.size(); ++i) {
					  if (figures[i]->isInside(vertex{ mouse_button_event.x(), mouse_button_event.y() })) {
						  figures.erase(figures.begin() + i);
						  break;
					  }
				  }
			  }
		  }
      }
    }

    for(const std::unique_ptr<Figure>& figure: figures){
      figure->render(renderer);
    }

    ImGui::Begin("Menu");
    if(ImGui::Button("New canvas")){
      figures.clear();
    }
    ImGui::InputText("File name", file_name, file_name_length - 1);
    if(ImGui::Button("Save")){
      std::ofstream os(file_name);
      if(os){
        for(const std::unique_ptr<Figure>& figure: figures){
          figure->save(os);
        }
      }
    }
    ImGui::SameLine();
    if(ImGui::Button("Load")){
      std::ifstream is(file_name);
      if(is){
         loader loader;
         figures = loader.load(is);
      }
    }
    if(ImGui::Button("Rectangle")){
		factory.startBuildRectangle(brush);
    }
	ImGui::SameLine();

	if (ImGui::Button("Trapeze")) {
		factory.startBuildTrapeze(brush);
	}
	ImGui::SameLine();

	if (ImGui::Button("Rhombus")) {
		factory.startBuildRhombus(brush);
	}
	ImGui::SameLine();

	if (ImGui::Button("Polyline")) {
		factory.startPolyBuildLine(brush);
	}
	ImGui::SameLine();

	if (ImGui::Button("Polyfigure")) {
		factory.startPolyBuildFigure(brush);
	}
	ImGui::SameLine();

	if (ImGui::Button("Circle")) {
		factory.startBuildCircle(brush);
	}

	if (ImGui::Button("undo")) {
		if (!history.empty()) {
			action = std::move(history.top());
			history.pop();
			action->undoAction(figures);
			action = nullptr;
		}
	}
	setBrush(brush);
	ImGui::InputInt("Remove_Id", &remove_id);

    if(ImGui::Button("Remove")) {
		if (figures.size() > remove_id) {
		std::unique_ptr<Figure> figure = std::move(figures[remove_id]);
		action = std::make_unique<DeleteAction>(std::move(figure),remove_id);
		history.push(std::move(action));
			figures.erase(figures.begin()+remove_id);

			
		}
    }
    // Undo
    ImGui::End();

    renderer.present();
  }


}
