#include "stdafx.h"
#include "TableTennisPlayer.h"
#include <iostream>


TableTennisPlayer::TableTennisPlayer(const string& fn,
		const string& ln, bool ht) : firstName(fn), lastName(ln), hasTable(ht)
{
}

TableTennisPlayer::~TableTennisPlayer(void)
{
}

void TableTennisPlayer::Name() const
{
	std::cout << lastName << "," << firstName;
}
