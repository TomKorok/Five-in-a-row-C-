#include "osztalyok.hpp"
//Jatekos fuggvenye

bool Jatekos::lepes_valid(Palya& palya, int x, int y){
	if (x>-1 && x<palya.getmeret() && y>0 && y<2 * palya.getmeret() + 1 && palya(x, y) != 'X' && palya(x, y) != 'O'){
		return true;
	}
	return false;
}

//Ember fuggvenye

void Ember::lep(Palya& palya, Lepes& koord){
	int x, y;
	std::cin >> x >> y;
	y = (2 * y + 1);
	std::cout << std::endl;
	while (!lepes_valid(palya, x, y)){
		std::cout << "ez nem jo, adjon meg masikat!" << std::endl;
		std::cin >> x >> y;
		y = (2 * y + 1);
	}
	koord = { x, y };
}

//Bot fuggvenyei
void Bot::lepes(Lepes& koord, int x, int y){
	koord = { x, y };
	return;
}

bool Bot::karakterszamolas(Palya& palya, int x, int y, char keresendo, int xnovelo, int ynovelo, int mennyi, Lepes& koord){
	int  db = 1;
	x += xnovelo;
	y += ynovelo;
	while (db != mennyi){
		if (x<palya.getmeret() && y<2 * palya.getmeret() + 1 && y>0 && palya(x, y) == keresendo){
			db++;
			x += xnovelo;
			y += ynovelo;
		}
		else{
			break;
		}
	}
	lepes(koord, x, y);
	if (db == mennyi){
		return true;
	}
	return false;
}

bool Bot::bot_mozgas(Palya& palya, Lepes& koord, char keresendo, int mennyi){
	for (int x = 0; x<palya.getmeret(); x++){
		for (int y = 1; y<2 * palya.getmeret() + 1; y += 2){
			if (palya(x, y) == keresendo){
				if (karakterszamolas(palya, x, y, keresendo, 0, 2, mennyi, koord)){
					if (lepes_valid(palya, x, y - 2)){
						lepes(koord, x, y - 2);
						return true;
					}
					if (lepes_valid(palya, koord.x, koord.y)){
						return true;
					}
				}
				if (karakterszamolas(palya, x, y, keresendo, 1, -2, mennyi, koord)){
					if (lepes_valid(palya, x - 1, y + 2)){
						lepes(koord, x - 1, y + 2);
						return true;
					}
					if (lepes_valid(palya, koord.x, koord.y)){
						return true;
					}
				}
				if (karakterszamolas(palya, x, y, keresendo, 1, 0, mennyi, koord)){
					if (lepes_valid(palya, x - 1, y)){
						lepes(koord, x - 1, y);
						return true;
					}
					if (lepes_valid(palya, koord.x, koord.y)){
						return true;
					}
				}
				if (karakterszamolas(palya, x, y, keresendo, 1, 2, mennyi, koord)){
					if (lepes_valid(palya, x - 1, y - 2)){
						lepes(koord, x - 1, y - 2);
						return true;
					}
					if (lepes_valid(palya, koord.x, koord.y)){
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Bot::vedekezes3ra_ures_ures(Palya& palya, Lepes& koord){
	for (int x = 0; x<palya.getmeret(); x++){
		for (int y = 1; y<2 * palya.getmeret() + 1; y += 2){
			if (palya(x, y) == 'X'){
				if (palya(x, y - 2) == ' ' && palya(x, y + 2) == 'X' && palya(x, y + 4) == 'X' && palya(x, y + 6) == ' '){ //keresunk 3mat vizszintesen jobbra ami mindket oldalrol ures
					lepes(koord, x, y - 2);
					return true;
				}
				if (palya(x - 1, y - 2) == ' ' && palya(x + 1, y + 2) == 'X' && palya(x + 2, y + 4) == 'X' && palya(x + 3, y + 6) == ' '){ //keresunk 3mat jobbra le ami mindket oldalrol ures
					lepes(koord, x - 1, y - 2);
					return true;
				}
				if (palya(x - 1, y + 2) == ' ' && palya(x + 1, y - 2) == 'X' && palya(x + 2, y - 4) == 'X' && palya(x + 3, y - 6) == ' '){ //keresunk 3mat balra lefele ami mindket oldalrol ures
					lepes(koord, x - 1, y + 2);
					return true;
				}
				if (palya(x - 1, y) == ' ' && palya(x + 1, y) == 'X' && palya(x + 2, y) == 'X' && palya(x + 3, y) == ' '){       //keresunk 3mat fuggolegesen lefele ami mindket oldalrol ures
					lepes(koord, x - 1, y);
					return true;
				}
			}
		}
	}
	return false;
}


void Bot::lep(Palya& palya, Lepes& koord){
	if (bot_mozgas(palya, koord, 'X', 4)){
		return;
	}
	else if (vedekezes3ra_ures_ures(palya, koord)){
		return;
	}
	int hanyra = 4;
	while (hanyra > 0){
		if (bot_mozgas(palya, koord, 'O', hanyra)){
			return;
		}
		else{
			hanyra--;
		}
	}
	hanyra = 1;
	if (bot_mozgas(palya, koord, 'X', hanyra)){
		return;
	}
}
