#pragma once
#ifndef RATEDPLAYER
#define RATEDPLAYER

#include "TableTennisPlayer.h"

class RatedPlayer : public TableTennisPlayer
{
public:
	explicit RatedPlayer(int n);
	RatedPlayer(unsigned int r = 0, const string & fn = "none", const string & ln = "none", bool ht = false);
	RatedPlayer(unsigned int r, const TableTennisPlayer & tp);

	unsigned int Rating() const { return rating; }
	
	void ResetRating(unsigned int r) { rating = r; }

	~RatedPlayer(void);

	static void Rate(double newRate);

private:
	unsigned int rating;

	static double interestRate;
};

#endif // !RATEDPLAYER


