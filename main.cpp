#include <array>

#include <vector>
#include "sdl.h"
#include "imgui.h"
#include "Loader.h"
#include <stack>
#include "Program.h"
void setBrush(Program& program) {

	ImGui::InputInt("Blue", &(program.getBrush()->blue));

	ImGui::InputInt("Green", &(program.getBrush()->green));

	ImGui::InputInt("Red", &(program.getBrush()->red));
	if (program.getBrush()->red > 255) {
		program.getBrush()->red = 255;
	}
	if (program.getBrush()->blue > 255) {
		program.getBrush()->blue = 255;
	}
	if (program.getBrush()->green > 255) {
		program.getBrush()->green = 255;
	}
	if (program.getBrush()->red < 0) {
		program.getBrush()->red = 0;
	}
	if (program.getBrush()->blue < 0) {
		program.getBrush()->blue = 0;
	}
	if (program.getBrush()->green < 0) {
		program.getBrush()->green = 0;
	}
}

int main() {
	Brush brush;
	Program program;
  sdl::renderer renderer("Editor");
  bool quit = false;
  std::unique_ptr<Action> action;
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
		  program.mouseClickListener(mouse_button_event);
      }
    }

	program.render(renderer);

    ImGui::Begin("Menu");
    if(ImGui::Button("New canvas")){
		program.clear();
	
	}
    ImGui::InputText("File name", file_name, file_name_length - 1);
    if(ImGui::Button("Save")) {
		program.saveFile(file_name);
    }
    ImGui::SameLine();
    if(ImGui::Button("Load")){
		program.loadFile(file_name);
    }
    if(ImGui::Button("Rectangle")){
		program.addRectangle();
    }
	ImGui::SameLine();

	if (ImGui::Button("Trapeze")) {
		program.addTrapeze();
	}
	ImGui::SameLine();

	if (ImGui::Button("Rhombus")) {
		program.addRhombus();
	}
	ImGui::SameLine();

	if (ImGui::Button("Polyline")) {
		program.addPolyline();
	}
	ImGui::SameLine();

	if (ImGui::Button("Polyfigure")) {
		program.addPolyfigure();
	}
	ImGui::SameLine();

	if (ImGui::Button("Circle")) {
		program.addCircle();
	}

	if (ImGui::Button("undo")) {
		program.undo();
	}
	setBrush(program);
	ImGui::InputInt("Remove_Id", &remove_id);

    if(ImGui::Button("Remove")) {
		program.remove(remove_id);
    }
    // Undo
    ImGui::End();

    renderer.present();
  }
  return 0;

}
