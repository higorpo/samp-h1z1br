 /*







												 _       _     _    _________     _
												| |     | |   / |  |______  /    / |
												| |     | |  /  |        / /    /  |
												| |     | | / / |       / /    / / |
												| |_____| |/_/| |      / /    /_/| |
												|  _____  |   | |     / /        | |
												| |     | |   | |    / /         | |
												| |     | |   | |   / /          | |
												| |     | | __| |__/ /______   __| |__
												|_|     |_||______/_________| |_______|

															Battle Royale

*/


//------------------------------------------------------------------------------------------------------------------------------------------


/* Definições/Variaveis */
// > enums
	enum Vehicle_Data
	{
		bool:motor,
		bool:luzes,
		combustivel
	}

// > variaveis
	new VehicleInfo[MAX_VEHICLES][Vehicle_Data];

// > forwards
	forward Fuel();
	forward AllVehicles();

//------------------------------------------------------------------------------------------------------------------------------------------
