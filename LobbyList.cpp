int selected_player = -1; //Here we store the id of the selected player

bool teleport = false; //Variable for the teleport function to the player

void Render() //This is the main thread for drawing on the screen
{
	//Create a menu
	if (MenuBegin("Lobby List / Teleport to player", true, 0))
	{
		//Loop through all the players in the session
		for (int i = 0; i < 32; i++)
		{
			//Get a player by id
			PlayerClass player = PlayerAt(i);
			
			//Simple check for player validation
			if (player.name.length() < 3)
				continue;
			
			//Select a player from the list
			if (Button(player.name, 110, 25))
			{
				selected_player = i;
			}
		}
		
		//If the player was selected
		if (selected_player != -1)
		{
			SetCursorPosX(140);
			SetCursorPosY(30);
			Text(PlayerAt(selected_player).name);

			SetCursorPosX(140);
			SetCursorPosY(70);
			if (Button("Teleport to player", 105, 25))
			{
				teleport = true;
			}
		}
		
		
		MenuEnd(); //Be sure to close the menu if it opened earlier
	}
}

void Tick() //This is the main thread of the scripts
{
	//If the player is not selected yet -> end the function
	if (selected_player == -1)
		return;
	
	if (teleport)
	{
		teleport = false; //To make the teleport work only once
		
		Vector3 pos = GetEntityCoords(PlayerAt(selected_player).handle);
		SetEntityCoordsNoOffset(PlayerPedId(), pos.x, pos.y, pos.z, false, false, false);
	}
}