#pragma once
#include <vector>
#include <iostream>

// Borrowed from another project of mine :)

int run_tests(std::vector<bool> tests, std::vector<std::string> testNames) {
	bool failed = false;
	for (long unsigned int i = 0; i < tests.size(); i++)
	{
		if (!tests[i]) {
			std::cout << "[FAILED] test: " << testNames[i] << std::endl;
			failed = true;
		}
		else {
			std::cout << "[PASSED] test: " << testNames[i] << std::endl;
		}
	}

	if (failed) {
		return 1;
	}
	return 0;
}
