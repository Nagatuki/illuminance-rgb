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

void run(std::string file_path, bool flag) {
	auto data = read_csv(file_path);

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
	if (std::filesystem::create_directory(directory)) {
		std::cout << "Directory created: " << directory << std::endl;
	}
}

int main(int argc, char** argv)
{
	// 実行時引数の解析
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <file_path> [flag (0 or 1)]" << std::endl;
		return 1; // エラーコード
	}

	// 第1引数: ファイルパス
	std::string file_path = argv[1];

	// 第2引数: フラグ (0または1)
	bool flag = false;
	if (argc == 3) {
		std::string flag_arg = argv[2];

		if (flag_arg == "0") {
			flag = false;
		}
		else if (flag_arg == "1") {
			flag = true;
		}
		else {
			std::cerr << "Error: Flag must be '0' or '1'." << std::endl;
			return 1;
		}
	}

	std::cout << "initialize" << std::endl;

	create_output_dir();

	gui::GraphicSetting graphic_setting;
	graphic_setting.load_setting();

	gui::Graphic::set_graphic_setting(graphic_setting);
    gui::Graphic::initialize(argc, argv);

	std::cout << "start" << std::endl;
	std::thread th(run, file_path, flag);
	gui::Graphic::loop();

	th.join();
}
