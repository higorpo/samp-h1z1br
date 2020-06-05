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


/* Includes necessárias para o bom funcionamento do script */
#include <YSI\y_hooks>


//------------------------------------------------------------------------------------------------------------------------------------------

hook OnGameModeInit()
{
	EnableTirePopping(true); // Define que os players poderão furar o pneu dos veiculos.
	ManualVehicleEngineAndLights(); // Define que a engine dos veiculos será manual.
	SetTimer("AllVehicles", 1000, true);
	return 1;
}

public AllVehicles()
{
	foreach(new i : Vehicle)
	{
		new Float:health;
		GetVehicleHealth(i, health);
		if(health <= 240)
		{
			SetVehicleHealth(i, 240);
		}
	}
	return 1;
}