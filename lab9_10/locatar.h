#pragma once
#include<string>
#include<iostream>
using std::string;

class LocatarException {
	std::string msg;
public:
	LocatarException(const string& m) :msg{ m } {};
	string getMsg()const { return msg; }
};

class Locatar
{
private:
	int apartament;
	string proprietar;

	int suprafata;
	string tip;
public:
	/*
	functia returneaza apartamentul locatarului respectiv
	input:
	output:int apartament;
	*/
	int getApartament() const noexcept;
	/*
	functia returneaza apartamentul locatarului respectiv
	input:
	output:
	*/
	string getProprietar() const;
	/*
	functia returneaza proprietarul locatarului respectiv
	input:
	output:string proprietar;
	*/
	string getTip() const;
	/*
	functia returneaza tipul locatarului respectiv
	input:
	output:string tip;
	*/
	int getSuprafata()const noexcept;
	/*
	functia returneaza suprafata locatarului respectiv
	input:
	output:double suprafata;
	*/
	//constuctorul domeniului
	Locatar() = default;
	Locatar(int apartament, string proprietar, int suprafata, string tip) :apartament{ apartament }, proprietar{ proprietar }, suprafata{ suprafata }, tip{ tip }{}

};
