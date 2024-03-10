#include <chrono>
#include <vector>

#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"
#include "imgui_plot.h"

#include "MemoryTestImGui.h"

dae::MemoryTestImGui::MemoryTestImGui()
: m_Averages{}
, m_AveragesGameObjects3D{}
, m_AveragesGameObjects3DAlt{}
{
	m_Exercise1SamplesSize = new int(10);
	m_Exercise2SamplesSize = new int(10);
}

dae::MemoryTestImGui::~MemoryTestImGui()
{
	delete m_Exercise1SamplesSize;
	delete[] m_IntArray;

	delete m_Exercise2SamplesSize;
	delete[] m_GameObject3DArray;

	delete[] m_GameObject3DAltArray;
}

void dae::MemoryTestImGui::DrawImGuiWindow()
{
	const float steps[m_MaxBufferSize] = { 1,2,4,8,16,32,64,128,256,512,1024 };

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	///
	ImGui::Begin("Exercise 1");
	ImGui::InputInt("# samples", m_Exercise1SamplesSize);
	if (ImGui::Button("Trash the cache"))
		Exercise1();
	if(m_ButtonHasBeenPressed)
	{
		ImGui::PlotConfig conf;
		conf.values.xs = steps; // this line is optional
		conf.values.ys = m_Averages;
		conf.values.count = m_MaxBufferSize+1;
		conf.scale.min = 0;
		conf.scale.max = m_Averages[0];
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(200, 100);
		conf.line_thickness = 2.f;

		ImGui::Plot("plot", conf);
	}
	ImGui::End();


	ImGui::Begin("Exercise 2");
	ImGui::InputInt("# samples", m_Exercise2SamplesSize);
	if (ImGui::Button("Trash the cache with GameObject3D"))
		Exercise2NoFix();
	if (m_Button2HasBeenPressed)
	{
		ImGui::PlotConfig conf;
		conf.values.xs = steps; // this line is optional
		conf.values.ys = m_AveragesGameObjects3D;
		conf.values.count = m_MaxBufferSize + 1;
		conf.scale.min = 0;
		conf.scale.max = m_AveragesGameObjects3D[0];
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(200, 100);
		conf.line_thickness = 2.f;

		ImGui::Plot("plot", conf);
	}
	if (ImGui::Button("Trash the cache with GameObject3DAlt"))
		Exercise2WithFix();
	if (m_Button3HasBeenPressed)
	{
		ImGui::PlotConfig conf;
		conf.values.xs = steps; // this line is optional
		conf.values.ys = m_AveragesGameObjects3DAlt;
		conf.values.count = m_MaxBufferSize + 1;
		conf.scale.min = 0;
		conf.scale.max = m_AveragesGameObjects3DAlt[0];
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(200, 100);
		conf.line_thickness = 2.f;

		ImGui::Plot("plot", conf);
	}

	if (m_Button2HasBeenPressed && m_Button3HasBeenPressed)
	{
		ImGui::Text("Combined :");
		float highestValue = m_AveragesGameObjects3D[0];
		if (highestValue < m_AveragesGameObjects3DAlt[0]) highestValue = m_AveragesGameObjects3DAlt[0];
		static const float* combined[] = { m_AveragesGameObjects3D, m_AveragesGameObjects3DAlt };
		static ImU32 colors[3] = { ImColor(0, 255, 0), ImColor(255, 0, 0) };
		ImGui::PlotConfig conf;
		conf.values.xs = steps; // this line is optional
		conf.values.ys_list = combined;
		conf.values.ys_count = 2;
		conf.values.colors = colors;
		conf.values.count = m_MaxBufferSize + 1;
		conf.scale.min = 0;
		conf.scale.max = highestValue;
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(200, 100);
		conf.line_thickness = 2.f;

		ImGui::Plot("plot", conf);
	}
	ImGui::End();
	///
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void dae::MemoryTestImGui::Exercise1()
{
	m_ButtonHasBeenPressed = false;
	const int sampleSize{ *m_Exercise1SamplesSize};

	std::vector<long long> results;
	int index{ 0 };
	for (int stepSize = 1; stepSize < 1024; stepSize *= 2)
	{
		for (int testRound = 0; testRound < sampleSize; ++testRound)
		{
			auto start = std::chrono::high_resolution_clock::now();

			for (int i = 0; i < size; i += stepSize)
			{
				m_IntArray[i] *= 2;
			}

			auto end = std::chrono::high_resolution_clock::now();
			const auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			results.push_back(elapsedTime);
		}

		std::ranges::sort(results);
		results.erase(results.begin());
		results.pop_back();

		long long sum = 0;
		for (const auto num : results) {
			sum += num;
		}

		m_Averages[index] = static_cast<float>(sum) / static_cast<float>(sampleSize - 2);
		++index;

		results.clear();
	}
	m_ButtonHasBeenPressed = true;
}

void dae::MemoryTestImGui::Exercise2NoFix()
{
	m_Button2HasBeenPressed = false;
	const int sampleSize{ *m_Exercise2SamplesSize };

	std::vector<long long> results;
	int index{ 0 };

	for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		for (int testRound = 0; testRound < sampleSize; ++testRound)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < size2; i += stepSize)
			{
				m_GameObject3DArray[i].ID *= 2;
			}

			auto end = std::chrono::high_resolution_clock::now();
			const auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			results.push_back(elapsedTime);
		}

		std::ranges::sort(results);
		results.erase(results.begin());
		results.pop_back();

		long long sum = 0;
		for (const auto num : results) {
			sum += num;
		}
		m_AveragesGameObjects3D[index] = static_cast<float>(sum) / static_cast<float>(sampleSize - 2);
		++index;
		results.clear();
	}
	m_Button2HasBeenPressed = true;
}

void dae::MemoryTestImGui::Exercise2WithFix()
{
	m_Button3HasBeenPressed = false;
	const int sampleSize{ *m_Exercise2SamplesSize };

	std::vector<long long> results;
	int index{ 0 };

	for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		for (int testRound = 0; testRound < sampleSize; ++testRound)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < size2; i += stepSize)
			{
				m_GameObject3DAltArray[i].ID *= 2;
			}

			auto end = std::chrono::high_resolution_clock::now();
			const auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			results.push_back(elapsedTime);
		}

		std::ranges::sort(results);
		results.erase(results.begin());
		results.pop_back();

		long long sum = 0;
		for (const auto num : results) {
			sum += num;
		}
		m_AveragesGameObjects3DAlt[index] = static_cast<float>(sum) / static_cast<float>(sampleSize - 2);
		++index;
		results.clear();
	}
	m_Button3HasBeenPressed = true;
}
