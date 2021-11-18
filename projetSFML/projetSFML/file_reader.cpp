#include "file_reader.h"

std::vector<AttackPattern> GetAllAttacks()
{
	std::vector<AttackPattern> results;

	std::ifstream reader(getRelativePath() + "attacks.json");

	json j;
	reader >> j;
	reader.close();

	for (const auto& attack : j["attacks"].items())
	{
		const auto& value = attack.value();

		MinMax radiusMinMax(value["radiusMin"], value["radiusMax"]);
		ColorsParameters colorsParam;
		std::string jsonColorValue = value["colors"];
		if (jsonColorValue == "primary") colorsParam = ColorsParameters(ColorsParameters::Primary);
		else if (jsonColorValue == "secondary") colorsParam = ColorsParameters(ColorsParameters::Secondary);
		else colorsParam = ColorsParameters(ColorsParameters::Mixed, value["colorsStep"]);


		// Reverse the rotationPerWave and startRotation
			// Add/Substract random value to proj speed
		for (int i = -1; i < 2; i+=2)
		{
			int projNumber = value["projNumber"];

			float startRotation = value["startRotation"];
			startRotation *= i;
			if (rand() % 2 == 0) startRotation += (rand() % int((float(projNumber) / (2 * PI)) * 100)) / 100;

			float rotationPerWave = value["rotationPerWave"];
			rotationPerWave *= i;

			float projSpeed = value["projSpeed"];
			float random = (rand() % 20) / 10;
			if (rand() % 2 == 0) projSpeed += random;
			else projSpeed -= random;

			results.emplace_back(
				AttackPattern(value["waveCount"], startRotation, rotationPerWave, 
				              value["timeBeforeNextWave"], value["projNumber"], projSpeed,
				              radiusMinMax, colorsParam)
			);
		}
	}

	return results;
}

std::string bestScorePath = "bestScore.txt";
int GetBestScore()
{
	int result = -1;

	std::ifstream reader(getRelativePath() + bestScorePath);
	if(reader.is_open())
	{
		std::string line;
		getline(reader, line);

		return std::stoi(line);
	}
	else
	{
		std::cout << "Best score file couldn't be opened";
		return -1;
	} 
}

void SetBestScore(int newValue)
{
	std::ofstream writer(getRelativePath() + bestScorePath);
	if (writer.is_open())
	{
		writer << std::to_string(newValue);
	}
	else std::cout << "Best score file couldn't be opened";
}


