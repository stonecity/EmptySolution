#include "stdafx.h"
#include "RatedPlayer.h"

double RatedPlayer::interestRate = 0;

RatedPlayer::RatedPlayer(int n)
{
}

RatedPlayer::RatedPlayer(unsigned int r, 
						 const string & fn, 
					     const string & ln, 
						 bool ht) : TableTennisPlayer(fn, ln, ht)
{
	rating = r;
}

RatedPlayer::RatedPlayer(unsigned int r, const TableTennisPlayer & tp) 
	: TableTennisPlayer(tp), rating(r)
{

}

RatedPlayer::~RatedPlayer(void)
{
}

void RatedPlayer::Rate(double newRate) 
{
	interestRate = newRate;
}
