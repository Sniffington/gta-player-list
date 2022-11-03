bool _monkeys_spwn = false; 
bool menu_open = false; 
string lang = "en"; 
string NofPeds, Nofmonkeys, PullNotif, spwnmonkeysCheckB, WelcomeMSG, monkeysSpwnd, SpwnErr; 
uint countOfmonkeys = 0; 
int key = 34; // CTRL + CLICK -> http://www.foreui.com/articles/Key_Code_Table.htm

array<int> peds();

void Translation()
{
    if (lang == "en")
    {   
		NofPeds = "Number of NPCs around you: ";
		Nofmonkeys = "Number of spawned Monkeys: ";
		PullNotif = "TOO MANY SPAWNED!!";
		spwnmonkeysCheckB = "Spawn Monkeys";
        WelcomeMSG = "Hello fellow monkey. Press PG DN button to open & close menu.";
        monkeysSpwnd = "Monkeys spawned: ";
        SpwnErr = "Restart script, the Monkeys have invaded again.";

    }
    else if (lang == "ru")
    {
		NofPeds = "Количество NPC вокруг вас: ";
		Nofmonkeys = "Количество порожденных обезьян: "; 
		PullNotif = "СЛИШКОМ МНОГО ПОЯВИЛОСЬ!!";
		spwnmonkeysCheckB = "Спаун обезьян";
        WelcomeMSG = "Крысиный Король к вашим услугам! Нажмите PG DN чтобы открыть меню.";
        monkeysSpwnd = "Появились обезьяны: "; 
        SpwnErr = "Сценарий перезапуска, обезьяны снова вторглись.";
    }
}

void Render() 
{
	if (KeyPressed(key, false))
	{
		menu_open = !menu_open; 
	}
    
	if (MenuBegin("PLANET OF MONKEYS!", menu_open, 0))
	{
		if (lang == "en") //
        {
            if (SmallButton("Русский")) {lang = "ru";}
        }
        else if (lang == "ru")
        {
            if (SmallButton("English")) {lang = "en";}
        }
		
		Text(NofPeds + PedsCount() + "/250"); 
		Text(Nofmonkeys + countOfmonkeys); 
		if (PedsCount() >= 250) 
		{
			Text(PullNotif);
		}
		else
		{
			Checkbox(spwnmonkeysCheckB, _monkeys_spwn);
		}
		
		if (_monkeys_spwn)
		{
			Text("Spawning...");
		}
		else
		{
			Text("");
		}

		MenuEnd();  
	}
}

void Init() 
{
	printf(WelcomeMSG);
	menu_open = !menu_open;
}

void monkeys_spwn() 
{	
	if (_monkeys_spwn) 
	{	
		Hash hash = GetHashKey("a_c_chimp"); 
		Vector3 coords = GetEntityCoords(PlayerPedId()); 

		if (countOfmonkeys >= 100) 
		{
            uint first_ent = (peds.length() - countOfmonkeys) + 1; 
            int entity = peds[first_ent]; 

            if (entity != 0) 
            {
                DeleteEntity(entity); 
                peds.removeAt(first_ent); 
                countOfmonkeys--; 
            }
            else 
			{ 
				countOfmonkeys--; 
			}
		}
		else
		{
			if (Wait("sleep", 100)) 
			{
				RequestModel(hash); 
				if (HasModelLoaded(hash)) 
				{ 
					auto ped = CreatePed(hash, coords.x, coords.y, coords.z, 90.f, true, false); 
					if (ped != 0) 
					{	
						countOfmonkeys++; 
						peds.insertLast(ped); 
                        TaskWanderInArea(ped, coords.x, coords.y, coords.z, 10.0, 0, 0); 
						printf(monkeysSpwnd + countOfmonkeys);
					} 
					else 
					{
						printf(SpwnErr); 
					}
				}
			}
		}
	}
	else if (peds.length() != 0) 
	{
		for (uint i = 0; i < peds.length(); i++) 
		{ 
			DeleteEntity(peds[i]); 
		}
		peds.removeRange(0, peds.length()); 
		countOfmonkeys = 0; 
	}

}

void Tick() 
{
	monkeys_spwn(); 
	Translation(); 
}