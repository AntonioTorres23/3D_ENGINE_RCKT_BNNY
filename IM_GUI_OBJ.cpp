#include "IM_GUI_OBJ.h"

IM_GUI_OBJ::IM_GUI_OBJ(GLFWwindow* glfw_window_pointer_argument)
{
	//inititalize IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	// have IMGUI grab input output from user
	ImGuiIO& im_gui_input_output = ImGui::GetIO();
	// enable keyboard input by using |= compound assignment operator with related enumeration
	im_gui_input_output.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	// begin tying imgui to our glfw window object; 2nd parameter syncs GLFW callback functions
	ImGui_ImplGlfw_InitForOpenGL(glfw_window_pointer_argument, true); 
	// initialize IMGUI with OpenGL version 3.XX
	ImGui_ImplOpenGL3_Init();
}

IM_GUI_OBJ::~IM_GUI_OBJ()
{
	// Shutdown IMGUI Resources
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}