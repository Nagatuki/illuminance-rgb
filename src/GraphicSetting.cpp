#include "GraphicSetting.h"

#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <iostream>

namespace gui {
	GraphicSetting::GraphicSetting()
		: width_mm(10)
		, width_pixel(10) {
	}

	int GraphicSetting::get_width_mm() const {
		return this->width_mm;
	}

	int GraphicSetting::get_width_pixel() const {
		return this->width_pixel;
	}

	void GraphicSetting::load_setting() {
		// create file path
		std::filesystem::path file_path = "display.csv";
		std::string file_path_str = file_path.string();

		std::cout << "Graphic setting: " << file_path_str << std::endl;

		// open the file
		FILE* fp;
		errno_t error;
		error = fopen_s(&fp, file_path_str.c_str(), "r");
		if (error != 0) {
			throw std::runtime_error("file open error!!");
		}

		// buffer
		char str[1500];

		// read the setting
		fgets(str, sizeof(str), fp); // ignore header
		fgets(str, sizeof(str), fp);
		auto _ = sscanf_s(str, "%d,%d", &this->width_mm, &this->width_pixel);
	}
}

