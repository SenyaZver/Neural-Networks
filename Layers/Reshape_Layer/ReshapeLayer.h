#pragma once
#include <vector>
#include <iostream>
#include <sstream>




class ReshapeLayer {
private:
	size_t size;


	std::vector<double> reshape(matrix inputLayer) {
		auto result = std::vector<double>(size);

		size_t index = 0;

		for (size_t i = 0; i < inputLayer.size(); i++) {
			for (size_t j = 0; j < inputLayer.size(); j++) {
				result[index] = inputLayer[i][j];
				index++;
			}
		}

		return result;
	}

public:
	ReshapeLayer() {}

	ReshapeLayer(size_t size) {
		this->size = size;
	}

	
	void save(std::ofstream& file) {
		file << "denseInputSize" << std::endl;
		file << this->size << std::endl << std::endl;
	}

	static ReshapeLayer load(std::string filename) {
		std::ifstream file;
		file.open(filename);

		if (file.good() == false) {
			throw "File Loading Failed";
		}
		std::string currentLine;
		size_t size;

		while (getline(file, currentLine)) {
			std::istringstream iss(currentLine);

			std::string temp;
			iss >> temp;


			if (temp == "denseInputSize") {
				size = Utils::readNumber(file);
			}


		}

		return ReshapeLayer(size);
	}



	std::vector<double> propagate(matrix& const input) {
		return this->reshape(input);
	}


	size_t getSize() {
		return size;
	}







};