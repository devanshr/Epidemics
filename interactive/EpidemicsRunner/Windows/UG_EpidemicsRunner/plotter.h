#pragma once
#include <algorithm>


namespace ug{
	namespace epi {



		template<class E, class T>
		class Plotter {
			using F = typename T::value_type;

		public:
			void plot(E obj, const T& times, const T& data, System::String^ name, int dim, int col) {
				//obj->chart1->Invalidate();
				for (int i = 0; i < times.size(); i++) {

					System::Windows::Forms::DataVisualization::Charting::DataPoint^ dataPoint1 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(times[i],
						data[i*dim+col]));

					obj->chart1->Series[name]->Points->Add(dataPoint1);
				}
			}

		};


		template<class E,class T>
		class PlotterOld {
		private:
			using F = typename T::value_type;

			int grid_x = 0;
			int grid_y = 0;
			int window_length;
			int window_height;

		public:
			PlotterOld(int _grid_x, int _grid_y, int _window_length, int _window_height):grid_x(_grid_x),grid_y(_grid_y),window_height(_window_height),window_length(_window_length) {

			}
			void plot(E& obj,const T& times, const T& data, int dim, int col) {
				////auto min = std::min_element(times.begin(), times.end());
			//	auto max = std::max_element(times.begin(), times.end());
				size_t n = times.size();
				F min_t = times[0];
				F max_t = times[n - 1];

				//F min_d= *std::min_element(times.begin(), times.end());
				//F max_d= *std::max_element(data.begin(), data.end());
				F min_d = 0;
				F max_d = 800000;


				auto world_to_grid = [&](float wt, float wy, float* res) {
					float st = (wt - min_t) / (max_t - min_t);
					float sd= (wy - min_d) / (max_t - min_d);
					int gt = grid_x + st * window_length;
					int gy = -(grid_y + sd * window_height)+window_height-1;
					res[0] = gt;
					res[1] = gy;
				};
			
			

			//	array<String^>^ managedArray = gcnew array<String^>(10);
			//	array<System::Drawing::PointF^>^ points = gcnew array<System::Drawing::PointF^>(2);
			//	points[0].X = 0;
				float res[4];
				for (int i = 0; i < n-1; i+=2) {
					world_to_grid(times[i], data[(i * dim) + col], res);
					world_to_grid(times[i+1], data[((i+1) * dim) + col], res);
					System::Drawing::PointF point1(0, window_height-1);
					System::Drawing::PointF point2(10, window_height-1);
				//	System::Drawing::PointF point1(0, window_height);
				//	System::Drawing::PointF point2(50, 50);
					//443, 261
					obj->DrawLine(System::Drawing::Pens::Black, point1, point2);
				}
				//obj->DrawLines(System::Drawing::Pens::Black,  points);
				// Draw line to screen.
			//	obj->DrawLine(System::Drawing::Pens::Black, point1, point2);
			

			}
		};
	}
}
