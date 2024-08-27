#include <iostream>
#include "osztalyok.hpp"
bool nyerte(Palya palya, char ki){
	for (int x = 0; x<palya.getmeret(); x++){
		for (int y = 1; y<2*palya.getmeret(); y += 2){
			if (palya(x, y) == ki){
				if (x<palya.getmeret() && y + 2<2*palya.getmeret() && palya(x, y + 2) == ki){
					int db = 2, x1 = x, y1 = y + 4;
					while (x1<palya.getmeret() && y1<2 * palya.getmeret() && palya(x1, y1) == ki && db<5){
						db++, y1 += 2;
					}
					if (db>4){
						return true;
					}
				}
				if (x + 1<palya.getmeret() && y - 2>0 && palya(x + 1, y - 2) == ki){
					int db = 2, x1 = x + 2, y1 = y - 4;
					while (x1<palya.getmeret() && y1>0 && palya(x1, y1) == ki && db<5){
						db++, x1++, y1 -= 2;
					}
					if (db>4){
						return true;
					}
				}
				if (x + 1<palya.getmeret() && y<2 * palya.getmeret() && palya(x + 1, y) == ki){
					int db = 2, x1 = x + 2, y1 = y;
					while (x1<palya.getmeret() && y1<2 * palya.getmeret() && palya(x1, y1) == ki && db<5){
						db++, x1++;
					}
					if (db>4){
						return true;
					}
				}
				if (x + 1<palya.getmeret() && y + 2<2 * palya.getmeret() && palya(x + 1, y + 2) == ki){
					int db = 2, x1 = x + 2, y1 = y + 4;
					while (x1<palya.getmeret() && y1<2 * palya.getmeret() && palya(x1, y1) == ki && db<5){
						db++, x1++, y1 += 2;
					}
					if (db>4){
						return true;
					}
				}
	}}}
	return false;
}

int main()
{
	Palya palya('|', ' ');
	Ember human;
	Bot bot;
	Lepes koord;
	std::cout << palya;
	while (!nyerte(palya, 'X') && !nyerte(palya, 'O')){
		std::cout << "Ez a jelenlegi allas kerem a kovetkezo lepesed (forma: y x): ";
		human.lep(palya, koord);
		palya(koord.x, koord.y) = 'X';
		if (!nyerte(palya, 'X')){
			bot.lep(palya, koord);
			palya(koord.x, koord.y) = 'O';
		}
		std::cout << palya;
	}
	if (nyerte(palya, 'X'))
	{
		std::cout << "Gratulalunk, nyertel!" << std::endl;
	}
	if (nyerte(palya, 'O'))
	{
		std::cout << "Sajnos vesztettel, probald meg ujra!" << std::endl;
	}
	int x;
	std::cin >> x;
	return 0;
}
