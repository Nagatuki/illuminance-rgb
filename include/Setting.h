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

// CSV�t�@�C����ǂݎ��֐�
std::vector<DataRow> read_csv(const std::string& filename) {
    std::vector<DataRow> data;
    std::ifstream in_file(filename);

    if (!in_file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return data;
    }

    std::string line;
    bool isHeader = true;  // �w�b�_�[�s���X�L�b�v���邽�߂̃t���O

    while (std::getline(in_file, line)) {
        if (isHeader) {
            // �ŏ��̍s�i�w�b�_�[�j�̓X�L�b�v
            isHeader = false;
            continue;
        }

        std::istringstream ss(line);  // ������X�g���[���ɍs��ǂݍ���
        std::string value;
        DataRow row;

        // r, g, b, t �̏��Œl���p�[�X
        if (std::getline(ss, value, ',')) row.r = std::stod(value);
        if (std::getline(ss, value, ',')) row.g = std::stod(value);
        if (std::getline(ss, value, ',')) row.b = std::stod(value);
        if (std::getline(ss, value, ',')) row.t = std::stod(value);
        if (std::getline(ss, value, ',')) row.interval_t = std::stod(value);

        data.push_back(row);  // �f�[�^���x�N�^�[�ɒǉ�
    }

    return data;
}