#include <Gui.hpp>
#include <imgui.h>

using namespace gui;


class App : public Application {
public:
	App() : Application(800,600,"app") {

	}

	void update() override {
		//Main DockSpace 
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

		ImGui::ShowDemoWindow();
	}

	void draw() {

	}
};

int main() {
	App app;
	app.run();

	return 0;
}