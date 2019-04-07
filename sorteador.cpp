#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <random>

#define MAXLINE 256

/**
 * @brief Sorts evaluators assigned to competitors
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

int main(int argc, char *argv[])
{

	if (argc < 5)
	{
		std::cerr << "usage:" << std::endl;
		std::cerr << "./sort "
				  << "<--evaluators | -e> <file> "
				  << "<--competitors | -c> <file> "
				  << "[--ratio | -r <int>]" << std::endl
				  << std::endl;
		std::cerr << "Files must be one name per line, ended on \\n"
				  << std::endl;
		std::cerr << "Ratio must be #evaluators assigned to each competitor (default=1)" << std::endl;
		return 1;
	}

	// Arguments parsing
	int e_index = 0;
	int c_index = 0;
	size_t ratio = 1;

	for (int index = 0; index < argc; index++)
	{
		std::string s = argv[index];
		if (!s.compare("-e") || !s.compare("--evaluators"))
		{
			if (index + 1 >= argc)
			{
				std::cerr << "Expected a file path" << std::endl;
				return 3;
			}
			e_index = index + 1;
		}
		else if (!s.compare("-c") || !s.compare("--competitors"))
		{
			if (index + 1 >= argc)
			{
				std::cerr << "Expected a file path" << std::endl;
				return 3;
			}
			c_index = index + 1;
		}
		else if (!s.compare("-r") || !s.compare("--ratio"))
		{

			if (index + 1 >= argc)
			{
				std::cerr << "Expected a positive integer" << std::endl;
				return 3;
			}
			// Search for a digit in sratio
			std::string sratio = argv[index + 1];
			if ((ratio = std::stoi(sratio)) <= 0 || std::find_if(sratio.begin(), sratio.end(), [](char c) { return isdigit(c); }) > sratio.begin())
			{
				std::cerr << "Expected a valid positive integer" << std::endl;
				return 3;
			}
		}
	}

	if (e_index == 0 || c_index == 0)
	{
		std::cerr << "Expected evaluators or competitors files paths" << std::endl;
		return 4;
	}

	// Files opening
	FILE *evaluators_file = fopen(argv[e_index], "r+");
	FILE *competitors_file = fopen(argv[c_index], "r+");
	if (evaluators_file == NULL || competitors_file == NULL)
	{
		std::cerr << "Could not open " << (evaluators_file ? argv[e_index] : argv[c_index]) << " files" << std::endl;
		return 5;
	}

	// Reading files data
	char *temp_line = (char *)malloc(MAXLINE * sizeof(char));
	struct Evaluator
	{
		std::string name;
		std::vector<std::string> competitors_evaluating;
	};

	std::vector<Evaluator> evaluators_vector;
	std::vector<std::string> competitors_vector;

	while (fgets(temp_line, MAXLINE, evaluators_file) != NULL)
	{
		Evaluator e;
		temp_line[strlen(temp_line) - 1] = 0; // Cuts \n
		e.name = temp_line;
		evaluators_vector.push_back(e);
	}
	while (fgets(temp_line, MAXLINE, competitors_file) != NULL)
	{
		temp_line[strlen(temp_line) - 1] = 0; // Cuts \n
		std::string s = temp_line;
		competitors_vector.push_back(s);
	}

	fclose(evaluators_file);
	fclose(competitors_file);
	delete temp_line;

	// Randomize vectors
	

	std::sort(evaluators_vector.begin(), evaluators_vector.end(), [](const Evaluator &a, const Evaluator &b) {
		std::default_random_engine random_compare_generator;
		std::uniform_int_distribution<int> random_compare_distribution(0, 1);
		return (bool) random_compare_distribution(random_compare_generator);
	});

	std::sort(competitors_vector.begin(), competitors_vector.end(), [](const std::string &a, const std::string &b) {
		std::default_random_engine random_compare_generator;
		std::uniform_int_distribution<int> random_compare_distribution(0, 1);
		return (bool) random_compare_distribution(random_compare_generator);
	});

	// Sorts "ratio" evaluators for each competitor

	for (size_t i = 0; i < competitors_vector.size(); i++)
	{
		std::vector<Evaluator> already_selected;
		for (size_t j = 0; j < ratio; j++)
		{
			std::default_random_engine generator;
			std::uniform_int_distribution<int> distribution(0, evaluators_vector.size() - 1);
			int random_index = distribution(generator);

			evaluators_vector[random_index].competitors_evaluating.push_back(competitors_vector[i]);
			// Copy already selected evaluators and remove from evaluators_vector
			already_selected.push_back(evaluators_vector[random_index]);
			evaluators_vector.erase(evaluators_vector.begin()+random_index);
		}

		for(size_t k = 0; k < already_selected.size(); k++)
		{
			// Restore evaluators_vector
			evaluators_vector.push_back(already_selected[k]);
		}
		already_selected.clear();
	}

	// Print the result on the screen
	for (size_t i = 0; i < evaluators_vector.size(); i++)
	{
		std::cout << evaluators_vector[i].name << ":" << std::endl;
		for (size_t j = 0; j < evaluators_vector[i].competitors_evaluating.size(); j++)
		{
			std::cout << evaluators_vector[i].competitors_evaluating[j] << std::endl;
		}
	}

	return 0;
}
