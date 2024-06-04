#pragma once
#if defined(_WIN32) || defined(_DEBUG)
constexpr int size{ 999999 };
constexpr int size2{ 999999 };

#else
constexpr int size{ 99999 };
constexpr int size2{ 99999 };
#endif


namespace dae
{
	struct TransformTest
	{
		float matrix[16] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1 };
	};

	class GameObject3D
	{
	public:
		TransformTest transform{};
		int ID{};
	};

	class GameObject3DAlt
	{
	public:
		TransformTest* transform = new TransformTest();
		int ID{};

		~GameObject3DAlt()
		{
			delete transform;
		}
	};


	class MemoryTestImGui
	{
	public:
		MemoryTestImGui();
		~MemoryTestImGui();

		MemoryTestImGui(const MemoryTestImGui& other) = delete;
		MemoryTestImGui(MemoryTestImGui&& other) = delete;
		MemoryTestImGui& operator=(const MemoryTestImGui& other) = delete;
		MemoryTestImGui& operator=(MemoryTestImGui&& other) = delete;


		void DrawImGuiWindow();

	private:
		static constexpr int m_MaxBufferSize{ 11 };

		//exercise 1 values
		
		int* m_Exercise1SamplesSize;
		bool m_ButtonHasBeenPressed{ false };
		float m_Averages[m_MaxBufferSize];
		int* m_IntArray = new int[size];


		int* m_Exercise2SamplesSize;

		bool m_Button2HasBeenPressed{false};
		GameObject3D* m_GameObject3DArray = new GameObject3D[size2];
		float m_AveragesGameObjects3D[m_MaxBufferSize];

		bool m_Button3HasBeenPressed{ false };
		GameObject3DAlt* m_GameObject3DAltArray = new GameObject3DAlt[size2];
		float m_AveragesGameObjects3DAlt[m_MaxBufferSize];

		void Exercise1();

		void Exercise2NoFix();

		void Exercise2WithFix();
	};
}





//void dae::MemoryTestImGui::Exercise1()
//{
//	m_ButtonHasBeenPressed = false;
//	const int sampleSize{ *m_Exercise1SamplesSize };
//
//	std::vector<long long> results;
//	int index{ 0 };
//	for (int stepSize = 1; stepSize < 1024; stepSize *= 2)
//	{
//		for (int testRound = 0; testRound < sampleSize; ++testRound)
//		{
//			auto start = std::chrono::high_resolution_clock::now();
//
//			for (int i = 0; i < size; i += stepSize)
//			{
//				m_IntArray[i] *= 2;
//			}
//
//			auto end = std::chrono::high_resolution_clock::now();
//			const auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
//
//			results.push_back(elapsedTime);
//		}
//
//		std::ranges::sort(results);
//		results.erase(results.begin());
//		results.pop_back();
//
//		long long sum = 0;
//		for (const auto num : results) {
//			sum += num;
//		}
//
//		m_Averages[index] = static_cast<float>(sum / (sampleSize - 2));
//		++index;
//
//		results.clear();
//	}
//	m_ButtonHasBeenPressed = true;
//}








