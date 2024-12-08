/*
 * Kod interpretera maszyny rejestrowej do projektu z JFTT2023
 *
 * Autor: Maciek Gębala
 * http://ki.pwr.edu.pl/gebala/
 * 2023-11-15
 * (wersja long long)
*/
#include <iostream>
#include <locale>

#include <utility>
#include <vector>
#include <map>

#include <cstdlib> 	// rand()
#include <ctime>

#include "instructions.hh"
#include "colors.hh"

using namespace std;

void run_machine( vector< pair<int,int> > & program )
{
  map<long long,long long> pam;

  long long r[8], tmp;
  long long lr;

  long long load;
  long long store;
  long long add;
  long long sub;
  long long get;
  long long put;
  long long rst;
  long long inc;
  long long dec;
  long long shl;
  long long shr;
  long long jump;
  long long jumppos;
  long long jumpzero;
  long long strk;
  long long jumpr;


  long long t, io;

  cout << cBlue << "Uruchamianie programu." << cReset << endl;
  lr = 0;
  srand( time(NULL) );
  for(int i = 0; i<8; i++ ) r[i] = rand();
  t = 0;
  io = 0;
  load = 0;
  store = 0;
  add = 0;
  sub = 0;
  get = 0;
  put = 0;
  rst = 0;
  inc = 0;
  dec = 0;
  shl = 0;
  shr = 0;
  jump = 0;
  jumppos = 0;
  jumpzero = 0;
  strk = 0;
  jumpr = 0;
  while( program[lr].first!=HALT )	// HALT
  {
    switch( program[lr].first )
    {
      case READ:	cout << "? "; cin >> r[0]; io+=100; lr++; break;
      case WRITE:	cout << "> " << r[0] << endl; io+=100; lr++; break;

      case LOAD:	r[0] = pam[r[program[lr].second]]; t+=50; load+=50; lr++; break;
      case STORE:	pam[r[program[lr].second]] = r[0]; t+=50; store+=50; lr++; break;

      case ADD:		r[0] += r[program[lr].second]; t+=5; add+=5; lr++; break;
      case SUB:		r[0] -= r[0]>=r[program[lr].second]?r[program[lr].second]:r[0]; t+=5; sub+=5; lr++; break;
      case GET:		r[0] = r[program[lr].second]; t+=1; get+=1;lr++; break;
      case PUT:		r[program[lr].second] = r[0]; t+=1; put+=1;lr++; break;
      case RST:		r[program[lr].second] = 0; t+=1; rst+=1;lr++; break;
      case INC:		r[program[lr].second]++; t+=1; inc+=1;lr++; break;
      case DEC:		if(r[program[lr].second]>0) r[program[lr].second]--; t+=1; dec+=1;lr++; break;
      case SHL:		r[program[lr].second]<<=1; t+=1; shl+=1;lr++; break;
      case SHR:		r[program[lr].second]>>=1; t+=1; shr+=1;lr++; break;

      case JUMP: 	lr = program[lr].second; t+=1; jump+=1; break;
      case JPOS:	if( r[0]>0 ) lr = program[lr].second; else lr++; t+=1; jumppos+=1; break;
      case JZERO:	if( r[0]==0 ) lr = program[lr].second; else lr++; t+=1; jumpzero+=1; break;
      
      case STRK:	r[program[lr].second] = lr; t+=1; lr++; strk+=1;  break;
      case JUMPR:	lr = r[program[lr].second]; t+=1; jumpr+=1; break;

      default: break;
    }
    if( lr<0 || lr>=(int)program.size() )
    {
      cerr << cRed << "Błąd: Wywołanie nieistniejącej instrukcji nr " << lr << "." << cReset << endl;
      exit(-1);
    }
  }
  cout.imbue(std::locale(""));
  cout << cBlue << "Skończono program (koszt: " << cRed << (t+io) << cBlue << "; w tym i/o: " << io << ")." << cReset << endl
  << "Tabela:" << endl\
  << "load: " << load << endl\
  << "store: " << store << endl\
  << "add: " << add << endl\
  << "sub: " << sub << endl\
  << "get: " << get << endl\
  << "put: " << put << endl\
  << "rst: " << rst << endl\
  << "inc: " << inc << endl\
  << "dec: " << dec << endl\
  << "shl: " << shl << endl\
  << "shr: " << shr << endl\
  << "jump: " << jump << endl\
  << "jumppos: " << jumppos << endl\
  << "jumpzer: " << jumpzero << endl\
  << "strk: " << strk << endl\
  << "jumpr: " << jumpr << endl;
}

