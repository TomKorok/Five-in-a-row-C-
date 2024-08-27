#include <iostream>
struct Lepes
{
	int x;
	int y;
	Lepes() : x(0), y(0){}
	Lepes(int x, int y) : x(x), y(y){}
};

class Palya{
	const int meret=20;
	char p[20][41];

public:
	Palya(char a, char b){
		int sor = 0;
		int oszlop = 0;
		while (sor<meret){
			oszlop = 0;
			while (oszlop<2 * meret + 1){
				p[sor][oszlop] = a;
				p[sor][oszlop + 1] = b;
				oszlop += 2;
			}
			sor++;
		}
	}

	int getmeret(){ return meret; }

	char& operator() (int a, int b){ return p[a][b]; }
	friend std::ostream& operator<<(std::ostream& os, Palya& palya){
		os << "    ";
		for (int x = 0; x<palya.getmeret(); x++){
			if (x<10){
				os << x << "   ";
			}
			else{
				os << x << "  ";
			}
		}
		os << std::endl;
		int y = 0;
		for (int sor = 0; sor<palya.getmeret(); sor++){
			if (y<10){
				os << y << " ";
			}
			else{
				os << y;
			}
			for (int oszlop = 0; oszlop<2 * palya.getmeret() + 1; oszlop++){
				os << palya(sor, oszlop) << " ";
			}
			os << std::endl;
			y++;
		}
		return os;
	}
};

class Jatekos{
protected:
	virtual void lep(Palya& palya, Lepes& koord) = 0;

	bool lepes_valid(Palya& palya, int x, int y);
};

class Ember : public Jatekos{
public:
	void lep(Palya& palya, Lepes& koord);
};

class Bot : public Jatekos{
public:
	void lepes(Lepes& koord, int x, int y);

	bool karakterszamolas(Palya& palya, int x, int y, char keresendo, int xnovelo, int ynovelo, int mennyi, Lepes& koord);

	bool bot_mozgas(Palya& palya, Lepes& koord, char keresendo, int mennyi);

	bool vedekezes3ra_ures_ures(Palya& palya, Lepes& koord);

	void lep(Palya& palya, Lepes& koord);
};
