#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

struct DataRow {
    double r;
    double g;
    double b;
    double t;
    double interval_t;
};

// CSVファイルを読み取る関数
std::vector<DataRow> read_csv(const std::string& filename) {
    std::vector<DataRow> data;
    std::ifstream in_file(filename);

    if (!in_file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return data;
    }

    std::string line;
    bool isHeader = true;  // ヘッダー行をスキップするためのフラグ

    while (std::getline(in_file, line)) {
        if (isHeader) {
            // 最初の行（ヘッダー）はスキップ
            isHeader = false;
            continue;
        }

        std::istringstream ss(line);  // 文字列ストリームに行を読み込む
        std::string value;
        DataRow row;

        // r, g, b, t の順で値をパース
        if (std::getline(ss, value, ',')) row.r = std::stod(value);
        if (std::getline(ss, value, ',')) row.g = std::stod(value);
        if (std::getline(ss, value, ',')) row.b = std::stod(value);
        if (std::getline(ss, value, ',')) row.t = std::stod(value);
        if (std::getline(ss, value, ',')) row.interval_t = std::stod(value);

        data.push_back(row);  // データをベクターに追加
    }

    return data;
}