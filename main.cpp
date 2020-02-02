#include "Mhr.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <windows.h>
#include <time.h>
#include <cstdlib>

using namespace std;

void ClearScreen(){
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  /* Get the number of cells in the current buffer */
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  /* Fill the entire buffer with spaces */
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Fill the entire buffer with the current colors and attributes */
  if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Move the cursor home */
  SetConsoleCursorPosition( hStdOut, homeCoords );
  }
  
void printPatientInfo(fstream& infile){
	char input[1000];
	
	infile.getline(input, 1000);
	cout<<input<<endl;
	while (!infile.eof()){
		infile.getline(input, 1000);
		cout<<input<<endl;
		
	}
}

int menu(){
	int choice;
	cout<<endl;
	cout<<"**********************************************"<<endl;
	cout<<"   Welcome to Patient Medical Record System"<<endl;
	cout<<"**********************************************"<<endl;
	
	cout<<"==================[MENU]======================"<<endl;
	cout<<"1. Search/Display/Add patient identification"<<endl;
	cout<<"2. Insert progress notes"<<endl;
	cout<<"3. View patient's past progress record"<<endl;
	cout<<"4. Exit"<<endl;
	
	cout<<"\nEnter your choice =>";
	cin>>choice;
	
	ClearScreen();
	
	return choice;
	
}

int print(){
	int choice1;
	cout<<endl;
	cout<<"I would like to view patient's... "<<endl;
	cout<<"	1. Previous Progress Notes"<<endl;
	cout<<"	2. Previous Prescriptions"<<endl;
	cout<<"	3. Follow-up List"<<endl;
	cout<<"	4. Health Hx"<<endl;
	cout<<"\nEnter your choice =>";
	cin>>choice1;
	
	return choice1;
}

int main(){
		
	char input;

	int menuchoice;
	ID ic;
	bool a;
	Patient p;
	
	while(1)
	{
		
A:	menuchoice = menu();	

	
	if(menuchoice<4)
	{
	
B:		switch(menuchoice){
			case 1: {
				string _name, _ecp, _aller, _idnum, _phy, _id, _cd, _gn, _pp, _shx;
				int _telNo, _ecn;
				char _mS, _bT, _rhe;
				double _weight;
				double _height;
				string cic;
				
				string fileName;
				fstream npfile;
				
				cout<<"Please enter patient's IC Number: "<<endl;
				cin.ignore();
				getline(cin, fileName);	
				
				ic.setID(fileName);												
				
				npfile.open((fileName+".txt").c_str(), ios::in);
				
				if(!npfile){
					cout<<"No record for patient "<<fileName<<".txt"<<" found.";
					cout<<"\nDo you wish to insert a new record?\nEnter y or n:";
					cin>>input;
					cin.ignore();
					ClearScreen();
					
					if((input=='y') || (input=='Y')){
						string j=fileName+".txt";						
						npfile.open(j.c_str(), ios::out);
						
						cout<<"========= New Patient Identification ======="<<endl<<endl;
						
						if(!npfile)
							cout<<"Error creating file. Please contact Administrator.";
						else{
							
						// Class declaration			
							cout<<"Please enter the following patient's information... "<<endl;
							
							cout<<"Name: ";
							getline(cin, _name);
			
							cout<<"Telephone number (e.g 0123456789): ";
							cin.ignore();
							cin >> _telNo;
							cin.ignore();
							
							cout<<"Emergency contact person: ";
							getline(cin, _ecp);

							cout<<"Emergency contact number(e.g 0123456789): ";
							cin.ignore();
							cin >> _ecn;
			
							cout<<"Blood type: ";
							cin.ignore();
							cin.get(_bT);
			
							cout<<"Rhesus: ";
							cin.ignore();
							cin.get(_rhe);
										
							cout<<"Weight(KG): ";
							cin.ignore();
							cin>>_weight;
											
							cout<<"Height(meter): ";
							cin>>_height;
							cin.ignore();
			
							cout<<"Allergies & adverse medication: ";	
							getline(cin, _aller);
							Allergies *al = new Allergies(_aller);
							p.setPAllergies(al);      
							
							Patient	p(_name, _ecp, _ecn, _telNo, ic, _bT, _rhe, _weight, _height);			//// Overload Constructor
							
							npfile<<"======== Patient Information ========"<< endl;
							npfile<<"Name: "<<_name<<endl;		////////
							npfile<<"IC Number: "<<fileName<<endl;
							npfile<<"Gender:"<<ic.getGender()<<endl;
							npfile<<"Age: "<<ic.getAge()<<endl;
							npfile<<"Telephone Number: "<<_telNo<<endl;
							npfile<<"Emergency contact person: "<<_ecp;
							npfile<<"\tEmergency contact number: "<<_ecn<<endl;
							npfile<<"Blood type: "<<_bT;
							npfile<<"\tRhesus: "<<_rhe<<endl;
							npfile<<"Weight(KG): "<<_weight;
							npfile<<"\tHeight(meter): "<<_height;
							npfile<<"\tBMI: "<<p.getPBMI()<<endl;
							npfile<<"Allergies & adverse medication: "<< _aller <<endl;
							
							ClearScreen();
							
							cout<<"<<<<< Health History >>>>>"<<endl;
							cout<<"Specify the following information. Enter '-' if not related."<<endl;
							
							fstream hfile;
							string hname = fileName +"_healthHx.txt";
							hfile.open(hname.c_str(), ios::out|ios::app);
			
							cout<<"\n1. Genetic/chronic disease ? If genetic disease, specify dad or mom. "<<endl;
							getline(cin, _gn);
							GenDis *gen = new GenDis();
							gen->setGenDis(_gn);
							p.setPGenDis(gen);
							
							cout<<"\n2. Surgery history ?"<<endl;			
							getline(cin, _shx);
							SurgeryHx *sur = new SurgeryHx();
							sur->setSHx(_shx);
							p.setPSurg(sur);
							
							hfile<<"<<<<< HEALTH HISTORY >>>>>"<<endl;
							hfile<<"\nGENETIC DISEASE:"<<endl<<"\t"<<_gn;
							hfile<<"\nSURGERY Hx:"<<endl<<"\t"<<_shx;
							
							ClearScreen();
							
							cout<<"\nInformation saved."<<endl<<endl;
							cout<<"Do you want to proceed with physical examination?\nPress y-yes or n-no => ";
							cin>>input;
							cout<<endl;
							
							if((input=='y') || (input=='Y')){
								string pnic;
								fstream pnfile;
					
								pnic = fileName+"_progressn.txt";
								pnfile.open(pnic.c_str(), ios::app);				
								
								string _pc;
								cout<<"======= PROGRESS NOTES ======="<<endl;
								char date[9];
								_strdate(date);	
								cout<<("Date: %s\n", date)<<endl;
								
								cout<<"Patient's symptoms: "<<endl;
								cin.ignore();
								getline(cin, _pc);
														
								string _df;
								cout<<"\nDiagnostic findings? "<<endl;
								getline(cin, _df);
								
								string _tr;
								cout<<"\nTreatment Rendered: "<<endl;
								getline(cin, _tr);
								
								ProgressNote *progn = new ProgressNote(date, _pc, _df, _tr);
								p.setPPN(progn);
								pnfile<<"======= PROGRESS NOTES ======="<<endl;
								_strdate(date);	
								pnfile<<"Creatd on: "<<date<<endl;	
								pnfile<<"PATIENT'S SYMPTOMPS: "<<_pc<<endl;
								pnfile<<"\nDIAGNOSTIC FINDINGS: "<<_df<<endl;
								pnfile<<"\nTREATMENT RENDERED: "<<_tr<<endl;
							}
								
							char fd;
							cout<<"\nAttempt to note a follow-up?\nPress y-yes or n-no: ";
							cin>>fd;
				
							if((fd=='y') || (fd=='Y')){
								string _date, _notes;
								fstream fpfile;
								string fp;
								
								fp=fileName+"_followup.txt";
								fpfile.open(fp.c_str(), ios::app);
								
								cout<<"\n======= Follow Up ========"<<endl;
								cout<<"Next visit on =>";
								cin.ignore();
								getline(cin, _date);
									
								cout<<"\nFollow up notes =>"<<endl;
								getline(cin, _notes);
								
								FollowUp *fol = new FollowUp(_date, _notes);
								p.setPFU(fol);
				
								fpfile<<p.getPFdate();
							}
				
							char pd;
							cout<<"\nApply prescription for the patient?\nPress y to continue or n to proceed: ";
							cin>>pd;
							cin.ignore();
				
							if((pd=='y') || (pd=='Y')){
								string prefile;
								fstream pfile;
								prefile=fileName+"_prescription.txt";
								pfile.open(prefile.c_str(), ios::app);
								
								char date[9];
								_strdate(date);
								
								pfile<<("Date: %s\n", date)<<endl;
						
								cout<<"\n====== PRESCRIPTION ======"<<endl;
								
								do{			
									string _medn, _qty;
													
									cout<<"Medicine name: ";
									cin.ignore();
									getline(cin, _medn);
									
									cout<<"Quantity: ";
									getline(cin, _qty);
									
									Prescription *presptr = new Prescription(_medn, _qty);
									p.setPPres(presptr);
						
									pfile<<p.getPPresM()<<"\t"<<p.getPPresQ()<<endl;
									
									pfile<<_medn<<"\t"<<_qty<<endl;
									cout<<"\nAdd medicine? Press y-yes or n-no: ";
									cin>>pd;
									cout<<"\n";		
			
								}while((pd=='y') || (pd=='Y'));
							}
			
							ClearScreen();
						}
					}
				}
				else
				{
					printPatientInfo(npfile);
	
					cout<<"All data shown."<<endl;
					system("pause");
					ClearScreen();
				}
			break;
			}
		
			case 2:{
				fstream pnfile;
				string pnic=ic.getID();
				
				if(pnic=="\0"){
					
					cout<<"Enter patient's IC Number: "<<endl;
					cin.ignore();
					getline(cin, pnic);
					
					ic.setID(pnic);
				}
				
				string pnname;
				pnname=pnic+"_progressn.txt";
				pnfile.open(pnname.c_str(), ios::app);	
				
				string _pc;
				cout<<"\n======= PROGRESS NOTES ======="<<endl;
				char date[9];
				_strdate(date);	
				cout<<"Date: "<<("Date: %s\n", date)<<endl;
								
				cout<<"Patient's symptoms: "<<endl;
				cin.ignore();
				getline(cin, _pc);
														
				string _df;
				cout<<"\nDiagnostic findings? "<<endl;
				getline(cin, _df);
							
				string _tr;
				cout<<"\nTreatment Rendered: "<<endl;
				getline(cin, _tr);
								
				ProgressNote *progn = new ProgressNote(date, _pc, _df, _tr);
				p.setPPN(progn);
				pnfile<<"\n======= PROGRESS NOTES ======="<<endl;
				_strdate(date);	
				pnfile<<"Created on:"<<p.getPDate()<<endl;	
				pnfile<<"PATIENT'S SYMPTOMPS: "<<_pc<<endl;
				pnfile<<"\nDIAGNOSTIC FINDINGS: "<<_df<<endl;
				pnfile<<"\nTREATMENT RENDERED: "<<_tr<<endl;
							
				
				char fd;
				cout<<"\nAttempt to note a follow-up?\nPress y-yes or n-no: ";
				cin>>fd;
				
				ClearScreen;
				
				if((fd=='y') || (fd=='Y')){
					string _date, _notes;
								fstream fpfile;
								string pnname;
								pnname=pnic+"_followup.txt";
								fpfile.open(pnname.c_str(), ios::app);
								
								cout<<"\n======= Follow Up ========"<<endl;
								cout<<"Next visit on =>";
								cin.ignore();
								getline(cin, _date);
									
								cout<<"\nFollow up notes =>"<<endl;
								getline(cin, _notes);
								
								FollowUp *fp = new FollowUp(_date, _notes);
								p.setPFU(fp);
				
								fpfile<<p.getPFdate();
					
				}
				
				char pd;
				cout<<"\nApply prescription for the patient?\nPress y-yes or n-no: ";
				cin>>pd;
				cin.ignore();
				
				if((pd=='y') || (pd=='Y')){
					ClearScreen();
					
					fstream pfile;
					pnname = pnic +"_prescription.txt";
					pfile.open(pnname.c_str(), ios::app);
					
					char date[9];
					_strdate(date);
					
					cout<<"\n======= PRESCRIPTION ========"<<endl;
					
					pfile<<"\n"<<("Date: %s\n", date)<<endl;
					
					do{			
						string _medn, _qty;
										
						cout<<"Medicine name: ";
						getline(cin, _medn);
						
						cout<<"Quantity: ";
						getline(cin, _qty);
						
						Prescription *presptr = new Prescription(_medn, _qty);
						p.setPPres(presptr);
						
						pfile<<_medn<<"\t"<<_qty<<endl;
						
						cout<<"\nAdd medicine? Press y-yes or n-no =>";
						cin>>pd;
						cout<<"\n";		
			
					}while((pd=='y') || (pd=='Y'));
				}
				break;
			}
				
		case 3:{
			string mon = ic.getID();
			
			if (mon =="\0")
				cout<<"Your attempted Patient Identification is not found ! Please search it first from Menu no.1"<<endl;
		
			else {
				int viewd;
				viewd = print();
				if (viewd==1){
						fstream profile;
						string icno = ic.getID();
						string proname = icno+"_progressn.txt";
						try{
							
						profile.open(proname.c_str(), ios::in);
						
						if (!profile)
						   a=1;
						else
							a=0;
						
						throw a;
					}
					catch(bool a){
						if(a==true){
							cout<<"No record found!"<<endl;
							
						}
						else if(a==false){
						char input[1000];
	
						profile.getline(input, 1000);
						cout<<input<<endl;
						while (!profile.eof()){
							profile.getline(input, 1000);
							cout<<input<<endl;
							}
						system("pause");
						ClearScreen();
						}
						}
					}
						
					else if (viewd==2){
						fstream prefile;
						cout<<"====== PREVIOUS PRESCRIPTION ======"<<endl;
						string prename = ic.getID()+"_prescription.txt";
						try{
							
						prefile.open(prename.c_str(), ios::in);
						
						if (!prefile)
						   a=1;
						else
							a=0;
						
						throw a;
					}
					catch(bool a){
						if(a==true){
							cout<<"No record found!"<<endl;
							
						}
						else if(a==false){
							char input[1000];
	
						prefile.getline(input, 1000);
						cout<<input<<endl;
						while (!prefile.eof()){
							prefile.getline(input, 1000);
							cout<<input<<endl;
						}
						system("pause");
						ClearScreen();
						}
						}
						}
			
					else if (viewd==3){
						fstream fofile;
						string foname = ic.getID()+"_followup.txt";
					try{
							
						fofile.open(foname.c_str(), ios::in);
						
						if (!fofile)
						   a=1;
						else
							a=0;
						
						throw a;
					}
					catch(bool a){
						if(a==true){
							cout<<"No record found!"<<endl;
							
						}
						else if(a==false){
							char input[1000];
						cout<<"===== PATIENT'S FOLLOW UP ====="<<endl;
						fofile.getline(input, 1000);
						cout<<input<<endl;
						while (!fofile.eof()){
							fofile.getline(input, 1000);
							cout<<input<<endl;
						}
						system("pause");
						ClearScreen();
						}
						}
					}
		
	
					else if (viewd==4){
						fstream hxfile;
						string hxname = ic.getID()+"_healthHx.txt";
						try{
							
						hxfile.open(hxname.c_str(), ios::in);
						
						if (!hxfile)
						   a=1;
						else
							a=0;
						
						throw a;
					}
					catch(bool a){
						if(a==true){
							cout<<"No record found!"<<endl;
						}
						else if(a==false){
							char input[1000];
							cout<<"====== PATIENT'S HEALTH HX ======"<<endl;
							hxfile.getline(input, 1000);
							cout<<input<<endl;
							while (!hxfile.eof()){
							hxfile.getline(input, 1000);
							cout<<input<<endl;
						}
						system("pause");
						ClearScreen();
						}
					}
					}
				}
				break;
			}
		case 4: {
			exit(1);
			}
	}
	}
	else
	{
			cout<<"Invalid choice. Please re-enter."<<endl;
			goto A;
		}
}
}
