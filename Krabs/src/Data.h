#pragma once
#include "Krpch.h"

//http://www.uoxray.uoregon.edu/local/manuals/biosym/discovery/General/Forcefields/AMBER.html#C_all


///LEGEND
/// CT : sp3 with 4 substituent
/// CA : aromatic carbon with 1 substitutent
/// CH : sp2 carbon with 1 hydrogen
/// C2 : sp2 carbon with 2 hydrogens
/// 
/// 
/// O : carbonyl oxygen
/// OS : ether or ester oxygen
/// OH : alcohol oxygen
/// 
/// N2 : sp2 nitrogen in base NH2
/// N : sp2 nitrogen in amide group
/// 
/// H : amide or imino hydrogen
/// H2 : amino hydrogen in NH2
/// HC : explicit hydrogen attached to carbon
/// HO : hydrogen on hydroxyl oxygen
/// HW : hydrogen in water

const std::map<std::string, float> atomicMass = { 

	{"H" , 1.00794},
	{"C" , 12.0107},
	{"O" , 15.9994},
	{"N" , 14.0067},
	{"F" , 18.9984},
	{"P" , 30.9738},
	{"Cl" , 35.4530},
	{"Br" , 79.9040},
	{"I" , 126.904},
	{"He" , 4.00260},
};

//in Angstroms
const std::map<std::string, float> covalentRadius = {
	{"H" , 0.37},
	{"C" , 0.77},
	{"O" , 0.73},
	{"N" , 0.75},
	{"F" , 0.71},
	{"P" , 1.10},
	{"Cl" , 0.99},
	{"Br" , 1.14},
	{"I" , 1.33},
	{"He" , 0.30},
};


//  equilibrium bond length [Angstrom]
// bond spring constant [kcal / (mol * A ^ 2)]
const std::map<std::vector<std::string>, std::array<float, 2>>mapBondVibrationParameter = {

	//aromatics carbon CA
	{ {"CA", "CA"} , {1.409, 469.0}},

	{ {"CA", "CT"} , {1.510f, 317.0f}},
	{ {"CA", "HC"} , {1.080f, 367.0f}},
	{ {"CA", "N2"} , { 1.340f, 481.0f}},

	//alifatic carbon 
	{{"CT", "CT"} , {1.526f, 310.0f}},
	{{"CT", "F"} , {1.380f, 367.0f}},
	{{"CT", "H"} , {1.090f, 340.0f}},
	{{"CT", "H2"} , {1.090f, 340.0f}},
	{{"CT", "CH"} , {1.090f, 340.0f}},
	{{"CT", "HC"} , { 1.090f, 340.0f}},
	{{"CT", "N"} , {1.449f, 337.0f}},
	{{"CT", "N2"} , {1.350f, 337.0f}},
	{{"CT", "OH"} , {1.410f, 320.0f}},
	{{"CT", "OH"} , {1.410f, 320.0f}},
	{{"CT", "OS"} , {1.410f, 320.0f}},
	{{"CT", "S"} , {1.810f, 227.0f}},

	{{"H", "N"} , {1.010f, 434.0f}},
	{{"H", "N2"} , {1.010f, 434.0f}},

	{{"OH", "OH"} , {0.960f, 553.0f}},
	{{"OH", "OS"} , {0.960f, 553.0f}},
	{{"HS", "HS"} , {1.336f, 274.0f}},

	{{"O2", "P"} , {1.480f, 525.0f}},
	{{"OW", "HW"} , {0.9572f, 553.0f}},


};

//radius van der waals [Angstrom]
//actraction magnitude [kcal/mol]
const std::map<std::string, std::array<float, 2>> mapVanDerWaalsPar ={

	{"CA", {1.9080f, 0.0860f}},
	{"CT", {1.9080, 0.1094}},
	{"F", {1.7500, 0.0610}},
	{"H", {0.6000, 0.0157}},
	{"H1", {1.3870, 0.0157}},
	{"H2", {1.2870, 0.0157}},
	{"HC", {1.4870, 0.0157}},
	{"HO", {0.0001, 0.0000}},
	{"HW", {0.0001, 0.0000}},
	{"HS", {0.6000, 0.0157}},
	{"N", {1.8240, 0.1700}},
	{"O", {1.6612, 0.2100}},
	{"O2", {1.6612, 0.2100}},
	{"OH", {1.7210, 0.2104}},
	{"OS", {1.6837, 0.1700}},
	{"OW", {1.7683, 0.1520}},
	{"P", {2.1000, 0.2000}},
	{"S", {2.0000, 0.2500}},
	{"N", {1.8240, 0.1700}},
	{"N2", {1.8240, 0.1700}},
	{"He", {1.5800, 0.0112}},


};

const std::map<std::vector<std::string>, std::array<float, 2>> mapAngleBendPar{
	{{"CA", "CA", "CA"},  {63.0, 120.00}},	{{"CA", "CA", "CT"},  {70.0, 120.00}},	
	{{"CA", "CT", "CT"},  {63.0, 114.00}},	{{"CA", "CT", "HC"},  {50.0, 109.50}},	
	{{"CA", "N2", "CT"},  {50.0, 123.20}},	{{"CA", "N2", "H"},   {35.0, 120.00}},

	{{"CT", "CT", "CT"},  {40.0, 109.50}},	{{"CT", "CT", "H1"},  {50.0, 109.50}},
	{{"CT", "CT", "H2"},  {50.0, 109.50}},	{{"CT", "CT", "HC"},  {50.0, 109.50}},
	{{"CT", "CT", "N"},   {80.0, 109.70}},	{{"CT", "CT", "N2"},  {80.0, 111.20}},
	{{"CT", "CT", "OH"},  {80.0, 109.50}},	{{"CT", "CT", "OS"},  {80.0, 109.50}},
	{{"CT", "CT", "S"},   {50.0, 114.70}},	{{"CT", "N", "CT"},   {50.0, 118.00}},
	{{"CT", "N", "H"},    {30.0, 118.04}},	{{"CT", "N2", "H"},   {35.0, 118.00}},
	{{"CT", "OS", "CT"},  {60.0, 109.50}},	{{"CT", "OS", "P"},   {100.0, 120.50}},
	{{"CT", "S", "CT"},   {62.0,  98.90}},	{{"CT", "S", "S"},    {62.0,  103.70}},

	{{"F", "CT", "F"},    {77.0, 109.10}},
	{{"F", "CT", "H1"},   {35.0, 109.50}},
	{{"H1", "N", "H1"},   {35.0, 120.00}},
	{{"H1", "N2", "H1"},  {35.0, 120.00}},
	{{"H1", "CT", "H1"},  {35.0, 109.50}},
	{{"H1", "CT", "N"},   {50.0, 109.50}},
	{{"H1", "CT", "N2"},  {50.0, 109.50}},
	{{"H1", "CT", "OH"},  {50.0, 109.50}},
	{{"H1", "CT", "OS"},  {50.0, 109.50}},
	{{"H1", "CT", "S"},   {50.0, 109.50}},
	{{"H1", "CT", "SH"},  {50.0, 109.50}},
	{{"H1", "CT", "H2"},  {35.0, 109.50}},
	{{"H1", "CT", "OS"},  {50.0, 109.50}},


	{{"HC", "CT", "HC"},  {35.0, 109.50}},

	{{"HW", "OW", "HW"},  {100.0, 104.52}},
	{{"N2", "CA", "N2"},  {70.0, 120.00}},
};


/*
#   * (float) vn/2 [kcal/mol], rotation barrier height
#   * (float) gamma [degrees], barrier minimum offset angle
#   * (int) n [unitless], frequency of barrier
#   * (int) paths [unitless], number of unique torsion paths
_TORSION_23_PARAMETERS = {
	('C' , 'CA') : (14.50, 180.0, 2, 4), ('C' , 'CB') : (12.00, 180.0, 2, 4),
	('C' , 'CM') : (8.70, 180.0, 2, 4), ('C' , 'CT') : (0.00,   0.0, 2, 4),
	('C' , 'N') : (10.00, 180.0, 2, 4), ('C' , 'N*') : (5.80, 180.0, 2, 4),
	('C' , 'NA') : (5.40, 180.0, 2, 4), ('C' , 'NC') : (8.00, 180.0, 2, 2),
	('C' , 'OH') : (1.80, 180.0, 2, 2), ('C*', 'CB') : (6.70, 180.0, 2, 4),
	('C*', 'CT') : (0.00,   0.0, 2, 6), ('C*', 'CW') : (26.10, 180.0, 2, 4),
	('CA', 'CA') : (14.50, 180.0, 2, 4), ('CA', 'CB') : (14.00, 180.0, 2, 4),
	('CA', 'CM') : (10.20, 180.0, 2, 4), ('CA', 'CN') : (14.50, 180.0, 2, 4),
	('CA', 'CT') : (0.00,   0.0, 2, 6), ('CA', 'N2') : (9.60, 180.0, 2, 4),
	('CA', 'NA') : (6.00, 180.0, 2, 2), ('CA', 'NC') : (9.60, 180.0, 2, 2),
	('CB', 'CB') : (21.80, 180.0, 2, 4), ('CB', 'CN') : (12.00, 180.0, 2, 4),
	('CB', 'N*') : (6.60, 180.0, 2, 4), ('CB', 'NB') : (5.10, 180.0, 2, 2),
	('CB', 'NC') : (8.30, 180.0, 2, 2), ('CC', 'CT') : (0.00,   0.0, 2, 6),
	('CC', 'CV') : (20.60, 180.0, 2, 4), ('CC', 'CW') : (21.50, 180.0, 2, 4),
	('CC', 'NA') : (5.60, 180.0, 2, 4), ('CC', 'NB') : (4.80, 180.0, 2, 2),
	('CK', 'N*') : (6.80, 180.0, 2, 4), ('CK', 'NB') : (20.00, 180.0, 2, 2),
	('CM', 'CM') : (26.60, 180.0, 2, 4), ('CM', 'CT') : (0.00,   0.0, 3, 6),
	('CM', 'N*') : (7.40, 180.0, 2, 4), ('CN', 'NA') : (6.10, 180.0, 2, 4),
	('CQ', 'NC') : (13.60, 180.0, 2, 2), ('CR', 'NA') : (9.30, 180.0, 2, 4),
	('CR', 'NB') : (10.00, 180.0, 2, 2), ('CT', 'CT') : (1.40,   0.0, 3, 9),
	('CT', 'N') : (0.00,   0.0, 2, 6), ('CT', 'N*') : (0.00,   0.0, 2, 6),
	('CT', 'N2') : (0.00,   0.0, 3, 6), ('CT', 'N3') : (1.40,   0.0, 3, 9),
	('CT', 'OH') : (0.50,   0.0, 3, 3), ('CT', 'OS') : (1.15,   0.0, 3, 3),
	('CT', 'S') : (1.00,   0.0, 3, 3), ('CT', 'SH') : (0.75,   0.0, 3, 3),
	('CV', 'NB') : (4.80, 180.0, 2, 2), ('CW', 'NA') : (6.00, 180.0, 2, 4),
	('OH', 'P') : (0.75,   0.0, 3, 3), ('OS', 'P') : (4.80, 180.0, 2, 2) }

	# AMBER94 molecular mechanics torsion parameters for atom type quartets
	# where all 4 atom types are known(see above for parameter descriptions).
	_TORSION_1234_PARAMETERS = {
		('C' , 'N' , 'CT', 'C') : [(0.00,   0.0, -4, 1), (0.00, 180.0, -3, 1),
								   (0.20, 180.0, -2, 1), (0.00, 180.0,  1, 1)] ,
		('CT', 'CT', 'C' , 'N') : [(0.10,   0.0, -4, 1), (0.00,   0.0, -3, 1),
								   (0.07,   0.0, -2, 1), (0.00, 180.0,  1, 1)] ,
		('CT', 'CT', 'N' , 'C') : [(0.50, 180.0, -4, 1), (0.15, 180.0, -3, 1),
								   (0.00, 180.0, -2, 1), (0.53,   0.0,  1, 1)] ,
		('CT', 'CT', 'OS', 'CT') : [(0.383,   0.0, -3, 1), (0.10, 180.0,  2, 1)] ,
		('CT', 'S' , 'S' , 'CT') : [(0.60,   0.0,  3, 1), (3.50,   0.0, -2, 1)] ,
		('H' , 'N' , 'C' , 'O') : [(2.50, 180.0, -2, 1), (2.00,   0.0,  1, 1)] ,
		('N' , 'CT', 'C' , 'N') : [(0.40, 180.0, -4, 1), (0.00,   0.0, -3, 1),
								   (1.35, 180.0, -2, 1), (0.75, 180.0,  1, 1)] ,
		('OH', 'CT', 'CT', 'OH') : [(0.144,   0.0, -3, 1), (1.00,   0.0,  2, 1)] ,
		('OH', 'P' , 'OS', 'CT') : [(0.25,   0.0, -3, 1), (1.20,   0.0,  2, 1)] ,
		('OS', 'CT', 'CT', 'OH') : [(0.144,   0.0, -3, 1), (1.00,   0.0,  2, 1)] ,
		('OS', 'CT', 'CT', 'OS') : [(0.144,   0.0, -3, 1), (1.00,   0.0,  3, 1)] ,
		('OS', 'CT', 'N*', 'CK') : [(0.50, 180.0, -2, 1), (2.50,   0.0,  1, 1)] ,
		('OS', 'CT', 'N*', 'CM') : [(0.50, 180.0, -2, 1)] ,
		('OS', 'P' , 'OS', 'CT') : [(0.25,   0.0, -3, 1), (1.20,   0.0, 2.0, 1)] ,
		('S' , 'CT', 'N*', 'CM') : [(2.50,   0.0,  1, 1)] }

		# AMBER94 molecular mechanics outofplane parameters for atom type
	# quartets where only final 2 atom types are known :
#   * (float) vn/2 [kcal/mol], rotation barrier height
_OUTOFPLANE_34_PARAMETERS = {
	('C' , 'O') : 10.5, ('CA', 'H4') : 1.1, ('CA', 'H5') : 1.1,
	('CA', 'HA') : 1.1, ('CK', 'H5') : 1.1, ('CM', 'H4') : 1.1,
	('CM', 'HA') : 1.1, ('CQ', 'H5') : 1.1, ('CR', 'H5') : 1.1,
	('CV', 'H4') : 1.1, ('CW', 'H4') : 1.1, ('N' , 'H') : 1.0,
	('N2', 'H') : 1.0, ('NA', 'H') : 1.0 }

	# AMBER94 molecular mechanics outofplane parameters for atom type
	# quartets where only final 3 atom types are known(see above for
		# parameter descriptions).
	_OUTOFPLANE_234_PARAMETERS = {
		('CT', 'N' , 'CT') : 1.0, ('N2', 'CA', 'N2') : 10.5,
		('O2', 'C' , 'O2') : 10.5 }

		# AMBER94 molecular mechanics outofplane parameters for atom type
	# quartets where al 4 atom types are known(see above for parameter
		# descriptions).
	_OUTOFPLANE_1234_PARAMETERS = {
		('CA', 'CA', 'C' , 'OH') : 1.1, ('CA', 'CA', 'CA', 'CT') : 1.1,
		('CB', 'NC', 'CA', 'N2') : 1.1, ('CK', 'CB', 'N*', 'CT') : 1.0,
		('CM', 'C' , 'CM', 'CT') : 1.1, ('CM', 'C' , 'N*', 'CT') : 1.0,
		('CT', 'CM', 'CM', 'C') : 1.1, ('CW', 'CB', 'C*', 'CT') : 1.1,
		('NC', 'CM', 'CA', 'N2') : 1.1, ('NA', 'CV', 'CC', 'CT') : 1.1,
		('NA', 'CW', 'CC', 'CT') : 1.1, ('NA', 'NC', 'CA', 'N2') : 1.1,
		('NB', 'CW', 'CC', 'CT') : 1.1 }

		*/