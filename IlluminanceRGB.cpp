#include "Graphic.h"
#include "Setting.h"

#include <string>
#include <thread>
#include <iostream>
#include <fstream>
#include <filesystem>

void save_rgb(double r, double g, double b) {
	const std::string filename = "./output/output.txt";

	// ファイルの存在を確認
	if (!std::filesystem::exists(filename)) {
		std::ofstream outFile(filename, std::ios::app);
		if (!outFile) {
			std::cerr << "Error: Could not open file " << filename << std::endl;
			return;
		}
		outFile << "r, g, b" << std::endl;
	}
	
	// 保存
	std::ofstream outFile(filename, std::ios::app);
	if (!outFile) {
		std::cerr << "Error: Could not open file " << filename << std::endl;
		return;
	}
	outFile << r << ", " << g << ", " << b << std::endl;
}

void set_color(double r, double g, double b, double duration_sec) {
	gui::Graphic::set_color(r, g, b);
	std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(duration_sec * 1000)));
	save_rgb(r, g, b);
}

void run() {
	std::string file_name;
	std::cin >> file_name;
	auto data = read_csv(file_name);

	// 各色
	for (auto&& e : data) {
		set_color(e.r, e.g, e.b, e.t);
		if (e.interval_t > 0) {
			set_color(0.0, 0.0, 0.0, e.interval_t);
		}
	}

	// 終了処理
	set_color(1.0, 1.0, 1.0, 5);
}

void create_output_dir() {
	const std::string directory = "./output";

	try {
		// ディレクトリを作成
		if (std::filesystem::create_directory(directory)) {
			std::cout << "Directory created: " << directory << std::endl;
		}
		else {
			std::cout << "Directory already exists or could not be created: " << directory << std::endl;
		}
	}
	catch (const std::filesystem::filesystem_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

int main(int argc, char** argv)
{
	std::cout << "initialize" << std::endl;

	create_output_dir();

	gui::GraphicSetting graphic_setting;
	graphic_setting.load_setting();

	gui::Graphic::set_graphic_setting(graphic_setting);
    gui::Graphic::initialize(argc, argv);

	std::cout << "start" << std::endl;
	std::thread th(run);
	gui::Graphic::loop();

	th.join();
}
