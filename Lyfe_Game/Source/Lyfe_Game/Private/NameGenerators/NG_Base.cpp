// Fill out your copyright notice in the Description page of Project Settings.

#include "NG_Base.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//++++++++++++++++++++++++ functions +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//++++++++++++++++++++++  private  +++++++++++++++++++++++++//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

std::string NG_Base::LANGUAGE_TYPE_NORMAL(std::uint8_t index)
{
	switch (index % 49)
	{
	case 0:		return "a"; break;
	case 1:		return "e"; break;
	case 2:		return "i"; break;
	case 3:		return "o"; break;
	case 4:		return "u"; break;
	case 5:		return "n"; break;
	case 6:		return "wa"; break;
	case 7:		return "ra"; break;
	case 8:		return "ya"; break;
	case 9:		return "ma"; break;
	case 10:	return "ha"; break;
	case 11:	return "na"; break;
	case 12:	return "ta"; break;
	case 13:	return "sa"; break;
	case 14:	return "ka"; break;
	case 15:	return "ri"; break;
	case 16:	return "mi"; break;
	case 17:	return "hi"; break;
	case 18:	return "ni"; break;
	case 19:	return "chi"; break;
	case 20:	return "shi"; break;
	case 21:	return "ki"; break;
	case 22:	return "ru"; break;
	case 23:	return "yu"; break;
	case 24:	return "mu"; break;
	case 25:	return "fu"; break;
	case 26:	return "nu"; break;
	case 27:	return "tsu"; break;
	case 28:	return "zu"; break;
	case 29:	return "su"; break;
	case 30:	return "ku"; break;
	case 31:	return "re"; break;
	case 32:	return "me"; break;
	case 33:	return "he"; break;
	case 34:	return "ne"; break;
	case 35:	return "te"; break;
	case 36:	return "se"; break;
	case 37:	return "ke"; break;
	case 38:	return "wo"; break;
	case 39:	return "ro"; break;
	case 40:	return "yo"; break;
	case 41:	return "mo"; break;
	case 42:	return "ho"; break;
	case 43:	return "no"; break;
	case 44:	return "to"; break;
	case 45:	return "so"; break;
	case 46:	return "ko"; break;
	case 47:	return "zo"; break;
	case 48:	return "sch"; break;
	}
}

/*
 * Picks a syllable to add to the name;
 * Based on the type of 'language' you use
 */
std::string NG_Base::PickSyllable(std::uint8_t type)
{
	int index = rand() % 1000;
	switch (type)
	{
	case 0:
		return LANGUAGE_TYPE_NORMAL(index);
		break;
	}
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//++++++++++++++++++++++  public  ++++++++++++++++++++++++++//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

/*
 * Generates a name based on syllable count and the type of 'language' it should use
 *
 * type:
 *	0 -> normal
 */
std::string NG_Base::GenerateName(std::uint16_t sylbCount, std::uint8_t type)
{
	std::string name = "";

	for (std::int16_t i = 0; i < sylbCount; i++)
	{
		name += PickSyllable(type);
	}

	return name;
}

std::string NG_Base::GenerateName(std::uint16_t sylbCount)
{
	std::uint8_t type = rand() % LANGUAGE_TYPES_COUNT;

	return GenerateName(sylbCount, type);
}

NG_Base::NG_Base()
{
}

NG_Base::~NG_Base()
{
}
