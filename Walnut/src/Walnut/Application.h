#pragma once

#include "Layer.h"

#include <string>
#include <vector>
#include <memory>
#include <iostream>   // HamSlices, 10/06/2025
#include <filesystem> // HamSlices, 10/06/2025
#include <functional>

#include "imgui.h"
#include "vulkan/vulkan.h"

void check_vk_result(VkResult err);

struct GLFWwindow;

// Mod block, HamSlices, 10/6/2025
extern ImFont* consoleFont;
extern ImFont* regularFont;
extern ImFont* robotoFont;

enum class WalnutCursor
{
	Arrow = 0,
	TextInput,
	ResizeAll,
	ResizeNS,
	ResizeEW,
	ResizeNESW,
	ResizeNWSE,
	Hand
};
// end mod block

namespace Walnut {

	struct ApplicationSpecification
	{
		std::string Name = "Walnut App";
		uint32_t Width = 1600;
		uint32_t Height = 900;
		bool CustomTitlebar = false; //HamSlices, 10/6/2025
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& applicationSpecification = ApplicationSpecification());
		~Application();

		static Application& Get();

		void Run();
		void SetMenubarCallback(const std::function<void()>& menubarCallback) { m_MenubarCallback = menubarCallback; }

		template<typename T>
		void PushLayer()
		{
			static_assert(std::is_base_of<Layer, T>::value, "Pushed type is not subclass of Layer!");
			m_LayerStack.emplace_back(std::make_shared<T>())->OnAttach();
		}

		void PushLayer(const std::shared_ptr<Layer>& layer) { m_LayerStack.emplace_back(layer); layer->OnAttach(); }

		void Close();

		float GetTime();
		GLFWwindow* GetWindowHandle() const { return m_WindowHandle; }

        // mod block, HamSlices, 10/06/2025
		void Minimize();
		void Maximize();
		void Restore();
		bool IsMaximized() const;

		void GetWindowPosition(int* x, int* y) const;
		void SetWindowPosition(int x, int y);

		void SetWindowSize(int width, int height);
		void GetWindowSize(int* width, int* height) const;

		void SetCursor(WalnutCursor cursor);
		void SetResizing(bool resizing);

		void SetWindowIcon(int width, int height, const unsigned char* pixels);

		void SetFileDropCallback(const std::function<void(const std::vector<std::filesystem::path>&)>& callback);
		// end mod block

		static VkInstance GetInstance();
		static VkPhysicalDevice GetPhysicalDevice();
		static VkDevice GetDevice();

		static VkCommandBuffer GetCommandBuffer(bool begin);
		static void FlushCommandBuffer(VkCommandBuffer commandBuffer);

		static void SubmitResourceFree(std::function<void()>&& func);
	private:
		void Init();
		void Shutdown();
	private:
		ApplicationSpecification m_Specification;
		GLFWwindow* m_WindowHandle = nullptr;
		bool m_Running = false;

		float m_TimeStep = 0.0f;
		float m_FrameTime = 0.0f;
		float m_LastFrameTime = 0.0f;

		std::vector<std::shared_ptr<Layer>> m_LayerStack;
		std::function<void()> m_MenubarCallback;
	};

	// Implemented by CLIENT
	Application* CreateApplication(int argc, char** argv);
}