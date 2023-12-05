#include <fstream>
#include <cstring>
#define NMAX 175
#define ND 4
using namespace std;
struct Punct { int x, y; };
struct Element { Punct p; Element *urm; };
struct Coada { Element *inc, *sf; };
Punct start, finish;
int dx[] = {-1,0,1,0};
int dy[] = {0,1,0,-1};
int a[NMAX+2][NMAX+2], n, m;
void citesteDateleDeIntrare();
void bordeazaMatricea();
void afiseazaRezultat();
void initializeazaCoada(Coada &);
void adaugaInCoada(Coada &, Punct);
void scoateDinCoada(Coada &, Punct &);
bool suntPuncteEgale(Punct, Punct);
int main()
{
	citesteDateleDeIntrare();
	bordeazaMatricea();
	Coada c;
	initializeazaCoada(c);
	adaugaInCoada(c, start);
	a[start.x][start.y] = 1;
	while (c.inc)
	{ 
		Punct p;
		scoateDinCoada(c, p);
		if (suntPuncteEgale(p, finish)) break;
		for (int d = 0; d < ND; d++)
		{
			Punct v;
			v.x = p.x + dx[d];
			v.y = p.y + dy[d];
			if (a[v.x][v.y] == 0)
			{
				a[v.x][v.y] = a[p.x][p.y] + 1;
				adaugaInCoada(c, v);
			}
		}
	}
	afiseazaRezultat();
	return 0;
}
void afiseazaRezultat()
{
	ofstream g("alee.out");
	g << a[finish.x][finish.y];
	g.close();
}
bool suntPuncteEgale(Punct a, Punct b)
{
	return a.x == b.x && a.y == b.y;
}
void scoateDinCoada(Coada & c, Punct & p)
{
	if (c.inc)
	{
		p = c.inc->p;
		if (c.inc == c.sf)
		{
			delete c.inc;
			c.inc = 0;
			c.sf = 0;
		}
		else
		{
			Element *e = c.inc->urm;
			delete c.inc;
			c.inc = e;
		}
	}
}
void initializeazaCoada(Coada & c)
{
	c.inc = 0;
	c.sf = 0;
}
void adaugaInCoada(Coada & c, Punct p)
{
	Element *e = new Element;
	e->p = p;
	e->urm = 0;
	if (!c.sf)
		c.inc = c.sf = e;
	else
	{
		c.sf->urm = e;
		c.sf = e;
	}
}
void bordeazaMatricea()
{
	for (int j = 0; j < n+2; j++)
		a[0][j] = a[n+1][j] = -1;
	for (int i = 0; i < n+2; i++)
		a[i][0] = a[i][n+1] = -1;
}
void citesteDateleDeIntrare()
{
	ifstream f("alee.in");
	f >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int x, y;
		f >> x >> y;
		a[x][y] = -1;
	}
	f >> start.x >> start.y;
	f >> finish.x >> finish.y;
	f.close();
}
