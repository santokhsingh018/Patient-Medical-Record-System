#include "Mhr.h"

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

//////// PERSON CLASS /////////////
Person::Person(){
	name ="";
	teleNumber =0;
}
Person::Person(string N, int TN){
	name=N;
	teleNumber=TN;
}
void Person::setName(string n){name = n;}
void Person::setTN(int tn){teleNumber = tn;}
string Person::getName(){return name;}
int Person::getTN(){return teleNumber;}

///////// ALLERGIES CLASS ////////
Allergies::Allergies(){allergies="";}
Allergies::Allergies(string allerg){allergies = allerg;}
void Allergies::setAllergies(string allerg){allergies=allerg;}
string Allergies::get(){return allergies;}

///////// PRESCRIPTION CLASS ///////
Prescription::Prescription(){
	medicine="";
	quantity="";
}
Prescription::Prescription(string m, string q){
	medicine=m;
	quantity=q;
}
string Prescription::getMed(){return medicine;}
string Prescription::getQty(){return quantity;}

///////// FOLLOWUP CLASS //////////
FollowUp::FollowUp(){
	notes ="";
}
FollowUp::FollowUp(string d, string nt){
	date=d;
	notes=nt;
}
string FollowUp::getFUd(){return date;}
string FollowUp::getFUn(){return notes;}

//////// SURGERYHX CLASS ///////////
SurgeryHx::SurgeryHx(){sHx="";}
void SurgeryHx::setSHx(string shx){sHx=shx;}
string SurgeryHx::getSHx(){return sHx;}

////// HEALTH HX CLASS /////////
GenDis::GenDis(){gDisease="";}
void GenDis::setGenDis(string gd){gDisease=gd;}
string GenDis::getGenDis(){return gDisease;}

//////// PROGRESSNOTES CLASS ///////
ProgressNote::ProgressNote(){
	reason4visit="";
	pxFinding="";
	treatmentRendered="";
}

void ProgressNote::setDate(char* d){date=d;}
string ProgressNote::getDate(){return date;}
void ProgressNote::setReason4Visit(string r4v){reason4visit=r4v;}
string ProgressNote::getReason4Visit(){return reason4visit;}
void ProgressNote::setPxFinding(string pf){pxFinding=pf;}
string ProgressNote::getPxFinding(){return pxFinding;}
void ProgressNote::setTreatment(string tr){treatmentRendered=tr;}
string ProgressNote::getTreatment(){return treatmentRendered;}

/////// ID CLASS //////////
ID::ID(){
	id = gender = "";
	age = day = sMonth = year = 0;;
}
ID::ID(string ic){id=ic;}
void ID::setID(string ic){id=ic;}
string ID::getID(){return id;}
string ID::getGender(){
	string sLastDigit = id.substr(id.length()-1,1);	//Extract last character from ID

	int lastDigit=atoi(sLastDigit.c_str());		// Convert the last digit to a number
	
	// Determine the gender such that, an odd value is male and even is female
	if (lastDigit%2==0) gender = "Female";
	else gender = "Male";
	
	return gender;
}

int ID::getAge(){	
	// Calculate the age
	int age = 2018 - year;
	return age;
}

//////// PATIENT CLASS ////////
Patient::Patient(){};
Patient::Patient(string name, string emname, int emctx, int tN, ID idnum, char bloodType, char rhesus, double weight, double height): pat(name, tN), ecp(emname, emctx), ic(idnum){
	this->bloodType=bloodType;
	this->rhesus=rhesus;
	this->weight=weight;
	this->height=height;
	bmi = weight/(height*height);
}
void Patient::setPID(string i){ic.setID(i);}
void Patient::setPBT(char bt){bloodType=bt;}
void Patient::setPRhe(char rhe){rhesus=rhe;}
void Patient::setPAllergies(Allergies *a){allergies=a;}
void Patient::setPGenDis(GenDis *g){genetic=g;}
void Patient::setPSurg(SurgeryHx *su){surgery=su;}
void Patient::setPPN(ProgressNote *pn){this->pn=pn;}
void Patient::setPFU(FollowUp *fol){fu=fol;}
void Patient::setPPres(Prescription *pr){pres=pr;}

string Patient::getPID(){return ic.getID();}
int Patient::getPAge(){return ic.getAge();}
string Patient::getPGender(){return ic.getGender();}
char Patient::getPBT(){return bloodType;}
char Patient::getPRhe(){return rhesus;}
double Patient::getPWeight(){return weight;}
double Patient::getPHeight(){return height;}
double Patient::getPBMI(){return bmi;}
int Patient::getPCtx(){ return teleNumber;}
string Patient::getPECP(){ecp.getName();}
int Patient::getPECPCtx(){ecp.getTN();}
string Patient::getPAller(){allergies->get();}
string Patient::getPGenDis(){return genetic->getGenDis();}
string Patient::getPSur(){return surgery->getSHx();}
string Patient::getPDate(){return pn->getDate();}
string Patient::getPComp(){return pn->getReason4Visit();}
string Patient::getPdf(){return pn->getPxFinding();}
string Patient::getPtr(){return pn->getTreatment();}
string Patient::getPFdate(){return fu->getFUd();}
string Patient::getPFnote(){return fu->getFUn();}
string Patient::getPPresM(){return pres->getMed();}
string Patient::getPPresQ(){return pres->getQty();}
