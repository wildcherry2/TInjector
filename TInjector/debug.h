#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstddef>

namespace debug {
	static std::filesystem::path log_path = "C:\\Users\\tyler\\Documents\\C++ Repos\\cs_theory_project\\TInjector\\log.txt";
	static std::ofstream log_stream;

	static void log(std::string in) {
		log_stream.open(log_path);
		log_stream << in << "\n";
		log_stream.close();
	}
}