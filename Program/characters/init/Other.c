void CreateOtherCharacters()
{
	ref ch;

	////////////////////////////////////////////////////////////////////////////////////////
	/// персонаж для лодка (заглушка)
	////////////////////////////////////////////////////////////////////////////////////////


	makeref(ch,Characters[BOAT_CHARACTER]);		// boat character

	ch.name 	= "";
	ch.lastname = "";
	ch.id		= "Boat1234";
	ch.nation	= ENGLAND;
	ch.activity_begin = "0";
	ch.activity_end = "24";
	ch.experience = "0";
	ch.Ship.Name = "";
	ch.Ship.Type = GenerateShip(SHIP_BOAT, 1);
	ch.Ship.Stopped = true;

}
