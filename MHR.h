#ifndef MHR_H
#define MHR_H

#include <iostream>
#include <string>
using namespace std;

class Person {
	protected:
		string name;
		int teleNumber;
	public:
		Person();
		Person(string, int);
		void setName(string);
		void setTN(int);
		string getName();
		int getTN();
};

class Allergies {
	private:
		string allergies;
	public:
		Allergies();
		Allergies(string);
		void setAllergies(string);
		string get();
};

class Prescription {
	private:
		string medicine;
		string quantity;
	public:
		Prescription();
		Prescription(string, string);
		string getMed();
		string getQty();
};

class FollowUp {
	private:
		string date;
		string notes;
	public:
		FollowUp();
		FollowUp(string, string);
		string getFUd();
		string getFUn();
};

class GenDis {
	private:
		string gDisease;
	public:
		GenDis();
		void setGenDis(string);
		string getGenDis();
};

class SurgeryHx {
	
	private:
		string sHx;
	public:
		SurgeryHx();
		void setSHx(string);
		string getSHx();
};

class ProgressNote {
	private:
		char *date;
		string reason4visit;
		string pxFinding;
		string treatmentRendered;
	public:
		ProgressNote();
		ProgressNote(char *d, string r, string p, string t){
			date=d;
			reason4visit=r;
			pxFinding=p;
			treatmentRendered=t;
}
		void setDate(char *);
		string getDate();
		void setReason4Visit(string);
		string getReason4Visit();
		void setPxFinding(string);
		string getPxFinding();
		void setTreatment(string);
		string getTreatment();
};

class ID {
	private:
		string id, gender;
		int age, day, sMonth, year;
	public:
		ID();
		ID(string);
		void setID(string);
		string getID();
		string getGender();
		int getAge();
};

class Patient: public Person {
	private:
		string tN, emname, emctx, idnum;
		
		ID ic;
		Person pat;
		Person ecp;
		Allergies *allergies;
		GenDis *genetic;
		SurgeryHx *surgery;
		ProgressNote *pn;
		FollowUp *fu;
		Prescription *pres;
		
		char bloodType;
		char rhesus;
		double weight;
		double height;
		double bmi;

	public:
		Patient();
		Patient(string, string, int, int, ID, char, char, double, double);
		
		void setPAllergies(Allergies *allergies);
		void setPGenDis(GenDis *);
		void setPSurg(SurgeryHx*);
		void setPID(string);
		void setPBT(char);
		void setPRhe(char);
		void setPAller(string);
		void setPPN(ProgressNote*);
		void setPFU(FollowUp*);
		void setPPres(Prescription *);
		
		string 	getPID();
		int		getPAge();
		string 	getPGender();
		char 	getPBT();
		char 	getPRhe();	
		double	getPWeight();
		double 	getPHeight();
		double 	getPBMI();
		int getPCtx();
		string getPECP();
		int getPECPCtx();
		string getPAller();
		string getPGenDis();
		string getPSur();
		string getPDate();
		string getPComp();
		string getPdf();
		string getPtr();
		string getPFdate();
		string getPFnote();
		string getPPresM();
		string getPPresQ();
};

#endif
