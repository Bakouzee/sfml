//#define BUILD
#include "attacks_pattern_json_reader.h"

std::vector<AttackPattern> GetAllAttacks()
{
	std::vector<AttackPattern> results;

	std::ifstream reader(
#ifdef BUILD
		getAppPath()
#endif
#ifndef BUILD
		getWorkingDir()
#endif
		+ "attacks.json"
	);

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

		results.emplace_back(
			AttackPattern(value["waveCount"], value["startRotation"], value["rotationPerWave"], 
			              value["timeBeforeNextWave"], value["projNumber"], value["projSpeed"],
			              radiusMinMax, colorsParam)
		);
	}

	return results;
}
