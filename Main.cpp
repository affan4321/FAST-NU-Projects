#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;



class DateTime {
public:
	string date;
	string time;
	DateTime operator=(const DateTime& dt) {
		this->date = dt.date;
		this->time = dt.time;
		return *this;
	}
};

class Payment {

};


class Appointment {
public:
	string appointmentStatus;
	string appointmentType;
	DateTime dateTime;
	Payment payment;
	Appointment() {}
	friend ostream& operator<<(ostream& Out, const Appointment& apt) {
		Out << "Appointment Date: " << apt.dateTime.date << endl;
		Out << "Appointment Time: " << apt.dateTime.time << endl;
		Out << "Appointment Status: " << apt.appointmentStatus << endl;
		Out << "Appointment Type: " << apt.appointmentType << endl;
		return Out;
	}
	Appointment(const Appointment& copy) {
		this->dateTime = copy.dateTime;
		this->payment = copy.payment;
	}
};

class VideoCunsultation : protected Appointment {

};

class InPerson : protected Appointment {

};

class BankTransfer : protected Payment {

};

class ETransaction : protected Payment {

};

class Jazzcash : protected ETransaction {

};

class Easypaisa : protected ETransaction {

};

class PayPak : protected BankTransfer {

};

class UnionPay : protected BankTransfer {

};


class User {
public:
	string name;
	int age;
	string cnic;
	int phoneNumber;
	virtual int Register() { return 0; }
	virtual int Login() { return 0; }
	
};

class Feedback {
public:
	string feedback;
};

class Doctor : public User {
public:
	int totalDoctors;
	string password;
	string timings;
	string location;
	string hospital;
	double hourlyCharges;
	int sizeDocAppointments;
	string profession;
	bool available;
	Appointment* docAppointments;
	Doctor** docPtr;
	Doctor():totalDoctors(0) {}
	int Login() {
		//.................Asking and Validating CNIC...................................
		string cnic;
		cout << "Please enter your CNIC ($$$$$-$$$$$$$-$): "; cin >> cnic;
		while (cnic[5] != '-' || cnic[13] != '-' || cnic.length() > 15) {
			cout << "Invalid CNIC! Please enter again!" << endl;
			cin >> cnic;
		}


		//..............Searching docPtr for the Doctor with that CNIC.................
		bool found = false;
		Doctor d;
		fstream doctorFile("doctorData.bin", ios::in | ios::out | ios::binary);
		doctorFile.read((char*)& d, sizeof(d));
		int ct = 0, foundLocation;
		while (found == false && ct < d.totalDoctors) {
			if (d.docPtr[ct]->cnic == cnic) {
				cout << "Welcome Dr." << d.docPtr[ct]->name << endl;
				found = true;
				foundLocation = ct;
				doctorFile.close();
				return foundLocation; // returning the current index of doctor in docPtr 
			}
			ct++;
		}
		if (found == false) {
			cout << "No Doctor with that CNIC found! Please Register to get connected." << endl;
			doctorFile.close();
			system("pause");
			return -1;  // returning -1 will take you to doctor registeration portal.
		}
	}
	void viewAppointmentData(int foundDoctorLocation) {
		Doctor temp;
		for (int i = 0; i < temp.docPtr[foundDoctorLocation]->sizeDocAppointments; i++) {
			cout << temp.docPtr[foundDoctorLocation]->docAppointments[i] << endl;
		}

	}
	void setAppointmentStatus(int foundDoctorLocation) {
		//.............Printing all Appointments.................................
		Doctor temp;
		for (int i = 0; i < temp.docPtr[foundDoctorLocation]->sizeDocAppointments; i++) {
			cout << temp.docPtr[foundDoctorLocation]->docAppointments[i] << endl;
		}


		//...........Asking for which appointment to change and changing...................
		cout << "Which appointment do you want to change?" << endl;
		int aptLocation;
		cin >> aptLocation;
		aptLocation -= 1;  //the actual location is 1 less than entered.
		if (!(temp.docPtr[foundDoctorLocation]->docAppointments[aptLocation].appointmentStatus.empty()))  //if appointment status not empty
			cout << "The current appointment status is: " << temp.docPtr[foundDoctorLocation]->docAppointments[aptLocation].appointmentStatus << endl;
		cout << "Enter new status: (approve/pending/reject)" << endl;
		string status;
		cin >> status;
		temp.docPtr[foundDoctorLocation]->docAppointments[aptLocation].appointmentStatus = status;
	}
	void viewAppointmentPatientDetails(int foundDoctorLocation) {

	}
	void changeTimings(int foundDoctorLocation) {
		//.....Looking for specific Doctor's timing through given parameter index...........
		Doctor d;
		if (!(d.docPtr[foundDoctorLocation]->timings.empty()))  // if Doctor's timings is not empty.
			cout << "Your current timings: " << d.docPtr[foundDoctorLocation]->timings << endl;
		cout << "Enter your timings: (HH:MM pm/am - HH:MM pm/am)" << endl;
		string tm;
		cout << "**Make sure to follow the exact given format**" << endl;
		cin >> tm;
		d.docPtr[foundDoctorLocation]->timings = tm;
	}
	void changeLocation(int foundDoctorLocation) {
		//.....Looking for specific Doctor's Location through given parameter index...........
		Doctor d;
		if (!(d.docPtr[foundDoctorLocation]->location.empty()))  // if Doctor's location is not empty.
			cout << "Your current location: " << d.docPtr[foundDoctorLocation]->location << endl;
		cout << "Enter your Location:" << endl;
		string lc;
		cin >> lc;
		d.docPtr[foundDoctorLocation]->location = lc;
	}
	void changeRates(int foundDoctorLocation) {
		//.....Looking for specific Doctor's Rates through given parameter index...........
		Doctor d;
		if (!(d.docPtr[foundDoctorLocation]->hourlyCharges == 0.0))  // if Doctor's hourly charges is not empty.
			cout << "Your current Hourly Rates: " << d.docPtr[foundDoctorLocation]->hourlyCharges << endl;
		cout << "Enter your new Hourly Charges:" << endl;
		double hch;
		cin >> hch;
		d.docPtr[foundDoctorLocation]->hourlyCharges = hch;
	}
};

class Gynecologist : public Doctor {
	string profession = "Gynecologist";
	bool available = true;
public:
	Gynecologist() {}
	int Register() {
		totalDoctors++;  //  Increasing total size of Doctors.


		//...................Copying previous docPtr data into doctemp..................
		Doctor* doctemp = new Doctor[totalDoctors];
		for (int i = 0; i < totalDoctors - 1; i++) {
			doctemp[i].name = docPtr[i]->name;
			doctemp[i].age = docPtr[i]->age;
			doctemp[i].cnic = docPtr[i]->cnic;
			doctemp[i].phoneNumber = docPtr[i]->phoneNumber;
			doctemp[i].hourlyCharges = docPtr[i]->hourlyCharges;
			doctemp[i].available = this->available;
			doctemp[i].profession = this->profession;
			doctemp[i].hospital = docPtr[i]->hospital;
		}


		//............Asking and storing new Doctor's Information in doctemp..........................
		string cnc, tmp, hp; int ag, pnum; double hc; bool av; char tp, nm[20];
		cout << "Please enter your name: "; cin.ignore();
		cin.getline(nm, 20);
		tmp = nm;
		cout << "Please enter your age: ";
		cin >> ag;
		cout << "Please enter your cnic ($$$$$-$$$$$$$-$): ";
		cin >> cnc;
		while (cnc[5] != '-' || cnc[13] != '-' || cnc.length() > 15) {  //validating CNIC
			cout << "Invalid CNIC! Please enter again!" << endl;
			cin >> cnc;
		}

		Doctor d;
		////.................Checking if the CNIC already exist or not............................
		//Doctor d;
		//fstream doctorReadFile("doctorData.bin", ios::in | ios::out | ios::binary);
		//int ct = 0;
		////doctorReadFile.read((char*)& d, sizeof(d));
		//while (ct < totalDoctors) {
		//	if (docPtr[ct++]->cnic == cnic) {
		//		cout << "Error! this CNIC already exists! Please Login instead!" << endl;
		//		return -1;  //returning -1 will take doctor to doctor login portal.
		//	}
		//}
		////doctorReadFile.close();


		ofstream doctorWriteFile("doctorData.bin", ios::binary);
		cout << "Please enter your phone num: ";
		cin >> pnum;
		cout << "Please mention your hourly charges: ";
		cin >> hc;
		cout << "Are you available for the job right now? (Y/N)";
		cin >> tp;
		if (tp == 'Y' || tp == 'y')
			av = true;
		else if (tp == 'N' || tp == 'n')
			av = false;
		cout << "What is your Hospital name? " << endl;
		cin >> hp;


		//.................Getting password and validating it............................
		string pass;
		cout << "Please enter your password: "; cin >> pass;
		bool correctpass = false;
		while (correctpass == false) {
			bool uppercase, lowercase, special, numeric;
			while (!(pass.find("@") != std::string::npos || pass.find("#") != std::string::npos || pass.find("!") != std::string::npos || pass.find("~") != std::string::npos || pass.find("$") != std::string::npos || pass.find("%") != std::string::npos || pass.find("^") != std::string::npos || pass.find("&") != std::string::npos || pass.find("*") != std::string::npos || pass.find("(") != std::string::npos || pass.find(")") != std::string::npos || pass.find("-") != std::string::npos || pass.find("+") != std::string::npos || pass.find("/") != std::string::npos || pass.find(":") != std::string::npos || pass.find(".") != std::string::npos || pass.find(",") != std::string::npos || pass.find("<") != std::string::npos || pass.find(">") != std::string::npos || pass.find("?") != std::string::npos || pass.find("|") != std::string::npos)) {
				special = false;
				cout << "Password Must include atleast one special character. Enter again." << endl;
				cin >> pass;
			}
			special = true;
			while (!(pass.find("A") != std::string::npos || pass.find("B") != std::string::npos || pass.find("C") != std::string::npos || pass.find("D") != std::string::npos || pass.find("E") != std::string::npos || pass.find("F") != std::string::npos || pass.find("G") != std::string::npos || pass.find("H") != std::string::npos || pass.find("I") != std::string::npos || pass.find("J") != std::string::npos || pass.find("K") != std::string::npos || pass.find("L") != std::string::npos || pass.find("M") != std::string::npos || pass.find("N") != std::string::npos || pass.find("O") != std::string::npos || pass.find("P") != std::string::npos || pass.find("Q") != std::string::npos || pass.find("R") != std::string::npos || pass.find("S") != std::string::npos || pass.find("T") != std::string::npos || pass.find("U") != std::string::npos || pass.find("V") != std::string::npos || pass.find("W") != std::string::npos || pass.find("X") != std::string::npos || pass.find("Y") != std::string::npos || pass.find("Z") != std::string::npos)) {
				uppercase = false;
				cout << "Password Must include atleast one uppercase character. Enter again." << endl;
				cin >> pass;
			}
			uppercase = true;
			while (!(pass.find("a") != std::string::npos || pass.find("b") != std::string::npos || pass.find("c") != std::string::npos || pass.find("d") != std::string::npos || pass.find("e") != std::string::npos || pass.find("f") != std::string::npos || pass.find("g") != std::string::npos || pass.find("h") != std::string::npos || pass.find("i") != std::string::npos || pass.find("j") != std::string::npos || pass.find("k") != std::string::npos || pass.find("l") != std::string::npos || pass.find("m") != std::string::npos || pass.find("n") != std::string::npos || pass.find("o") != std::string::npos || pass.find("p") != std::string::npos || pass.find("q") != std::string::npos || pass.find("r") != std::string::npos || pass.find("s") != std::string::npos || pass.find("t") != std::string::npos || pass.find("u") != std::string::npos || pass.find("v") != std::string::npos || pass.find("w") != std::string::npos || pass.find("x") != std::string::npos || pass.find("y") != std::string::npos || pass.find("z") != std::string::npos)) {
				lowercase = false;
				cout << "Password Must include atleast one lowercase character. Enter again." << endl;
				cin >> pass;
			}
			lowercase = true;
			while (!(pass.find("0") != std::string::npos || pass.find("1") != std::string::npos || pass.find("2") != std::string::npos || pass.find("3") != std::string::npos || pass.find("4") != std::string::npos || pass.find("5") != std::string::npos || pass.find("6") != std::string::npos || pass.find("7") != std::string::npos || pass.find("8") != std::string::npos || pass.find("9") != std::string::npos)) {
				numeric = false;
				cout << "Password Must include atleast one number. Enter again." << endl;
				cin >> pass;
			}
			numeric = true;
			if (special == true && uppercase == true && lowercase == true && numeric == true)
				correctpass = true;
		}


		//.........Adding new password and writing new doctor template in doctorData.bin........
		doctemp[totalDoctors - 1].password = pass; //adding new password into docPtr new Doctor

		doctemp[totalDoctors - 1].name = tmp;
		doctemp[totalDoctors - 1].age = ag;
		doctemp[totalDoctors - 1].cnic = cnc;
		doctemp[totalDoctors - 1].phoneNumber = pnum;
		doctemp[totalDoctors - 1].hourlyCharges = hc;
		doctemp[totalDoctors - 1].available = av;
		doctemp[totalDoctors - 1].profession = this->profession;
		doctemp[totalDoctors - 1].hospital = hp;


		//.......Deleting previous docPtr list and creating and copying new data.......
		for (int i = 0; i < totalDoctors - 1; i++)
			delete[]docPtr[i];
		delete[]docPtr;
		docPtr = new Doctor * [totalDoctors];
		for (int i = 0; i < totalDoctors; i++) {
			docPtr[i] = new Doctor;
		}
		docAppointments = new Appointment[sizeDocAppointments];
		for (int i = 0; i < totalDoctors; i++) {
			docPtr[i]->name = doctemp[i].name;
			docPtr[i]->age = doctemp[i].age;
			docPtr[i]->cnic = doctemp[i].cnic;
			docPtr[i]->phoneNumber = doctemp[i].phoneNumber;
			docPtr[i]->hourlyCharges = doctemp[i].hourlyCharges;
			docPtr[i]->available = this->available;
			docPtr[i]->profession = this->profession;
			docPtr[i]->password = doctemp[i].password;
			docPtr[i]->hospital = doctemp[i].hospital;
		}
		cout << "All information noted successfully!" << endl;

		doctorWriteFile.write((char*)& d, sizeof(d));
		doctorWriteFile.close();

		return 0; // returning 0 means successful registration.
	}
};

class Dermatologist : public Doctor {
	string profession = "Dermatologist";
	bool available = true;
public:
	Dermatologist() {}
	int Register() {
		totalDoctors++;  //  Increasing total size of Doctors.

		//...................Copying previous docPtr data into doctemp..................
		Doctor* doctemp = new Doctor[totalDoctors];
		for (int i = 0; i < totalDoctors - 1; i++) {
			doctemp[i].name = docPtr[i]->name;
			doctemp[i].age = docPtr[i]->age;
			doctemp[i].cnic = docPtr[i]->cnic;
			doctemp[i].phoneNumber = docPtr[i]->phoneNumber;
			doctemp[i].hourlyCharges = docPtr[i]->hourlyCharges;
			doctemp[i].available = this->available;
			doctemp[i].profession = this->profession;
			doctemp[i].hospital = docPtr[i]->hospital;
		}


		//............Asking and storing new Doctor's Information in doctemp..........................
		string cnc, tmp, hp; int ag, pnum; double hc; bool av; char tp, nm[20];
		cout << "Please enter your name: "; cin.ignore();
		cin.getline(nm, 20);
		tmp = nm;
		cout << "Please enter your age: ";
		cin >> ag;
		cout << "Please enter your cnic ($$$$$-$$$$$$$-$): ";
		cin >> cnc;
		while (cnc[5] != '-' || cnc[13] != '-' || cnc.length() > 15) {  //validating CNIC
			cout << "Invalid CNIC! Please enter again!" << endl;
			cin >> cnc;
		}

		Doctor d;
		////.................Checking if the CNIC already exist or not............................
		//Doctor d;
		//fstream doctorReadFile("doctorData.bin", ios::in | ios::out | ios::binary);
		//int ct = 0;
		////doctorReadFile.read((char*)& d, sizeof(d));
		//while (ct < totalDoctors) {
		//	if (docPtr[ct++]->cnic == cnic) {
		//		cout << "Error! this CNIC already exists! Please Login instead!" << endl;
		//		return -1;  //returning -1 will take doctor to doctor login portal.
		//	}
		//}
		////doctorReadFile.close();


		ofstream doctorWriteFile("doctorData.bin", ios::binary);
		cout << "Please enter your phone num: ";
		cin >> pnum;
		cout << "Please mention your hourly charges: ";
		cin >> hc;
		cout << "Are you available for the job right now? (Y/N)";
		cin >> tp;
		if (tp == 'Y' || tp == 'y')
			av = true;
		else if (tp == 'N' || tp == 'n')
			av = false;
		cout << "What is your Hospital name? " << endl;
		cin >> hp;


		//.................Getting password and validating it............................
		string pass;
		cout << "Please enter your password: "; cin >> pass;
		bool correctpass = false;
		while (correctpass == false) {
			bool uppercase, lowercase, special, numeric;
			while (!(pass.find("@") != std::string::npos || pass.find("#") != std::string::npos || pass.find("!") != std::string::npos || pass.find("~") != std::string::npos || pass.find("$") != std::string::npos || pass.find("%") != std::string::npos || pass.find("^") != std::string::npos || pass.find("&") != std::string::npos || pass.find("*") != std::string::npos || pass.find("(") != std::string::npos || pass.find(")") != std::string::npos || pass.find("-") != std::string::npos || pass.find("+") != std::string::npos || pass.find("/") != std::string::npos || pass.find(":") != std::string::npos || pass.find(".") != std::string::npos || pass.find(",") != std::string::npos || pass.find("<") != std::string::npos || pass.find(">") != std::string::npos || pass.find("?") != std::string::npos || pass.find("|") != std::string::npos)) {
				special = false;
				cout << "Password Must include atleast one special character. Enter again." << endl;
				cin >> pass;
			}
			special = true;
			while (!(pass.find("A") != std::string::npos || pass.find("B") != std::string::npos || pass.find("C") != std::string::npos || pass.find("D") != std::string::npos || pass.find("E") != std::string::npos || pass.find("F") != std::string::npos || pass.find("G") != std::string::npos || pass.find("H") != std::string::npos || pass.find("I") != std::string::npos || pass.find("J") != std::string::npos || pass.find("K") != std::string::npos || pass.find("L") != std::string::npos || pass.find("M") != std::string::npos || pass.find("N") != std::string::npos || pass.find("O") != std::string::npos || pass.find("P") != std::string::npos || pass.find("Q") != std::string::npos || pass.find("R") != std::string::npos || pass.find("S") != std::string::npos || pass.find("T") != std::string::npos || pass.find("U") != std::string::npos || pass.find("V") != std::string::npos || pass.find("W") != std::string::npos || pass.find("X") != std::string::npos || pass.find("Y") != std::string::npos || pass.find("Z") != std::string::npos)) {
				uppercase = false;
				cout << "Password Must include atleast one uppercase character. Enter again." << endl;
				cin >> pass;
			}
			uppercase = true;
			while (!(pass.find("a") != std::string::npos || pass.find("b") != std::string::npos || pass.find("c") != std::string::npos || pass.find("d") != std::string::npos || pass.find("e") != std::string::npos || pass.find("f") != std::string::npos || pass.find("g") != std::string::npos || pass.find("h") != std::string::npos || pass.find("i") != std::string::npos || pass.find("j") != std::string::npos || pass.find("k") != std::string::npos || pass.find("l") != std::string::npos || pass.find("m") != std::string::npos || pass.find("n") != std::string::npos || pass.find("o") != std::string::npos || pass.find("p") != std::string::npos || pass.find("q") != std::string::npos || pass.find("r") != std::string::npos || pass.find("s") != std::string::npos || pass.find("t") != std::string::npos || pass.find("u") != std::string::npos || pass.find("v") != std::string::npos || pass.find("w") != std::string::npos || pass.find("x") != std::string::npos || pass.find("y") != std::string::npos || pass.find("z") != std::string::npos)) {
				lowercase = false;
				cout << "Password Must include atleast one lowercase character. Enter again." << endl;
				cin >> pass;
			}
			lowercase = true;
			while (!(pass.find("0") != std::string::npos || pass.find("1") != std::string::npos || pass.find("2") != std::string::npos || pass.find("3") != std::string::npos || pass.find("4") != std::string::npos || pass.find("5") != std::string::npos || pass.find("6") != std::string::npos || pass.find("7") != std::string::npos || pass.find("8") != std::string::npos || pass.find("9") != std::string::npos)) {
				numeric = false;
				cout << "Password Must include atleast one number. Enter again." << endl;
				cin >> pass;
			}
			numeric = true;
			if (special == true && uppercase == true && lowercase == true && numeric == true)
				correctpass = true;
		}


		//.........Adding new password and writing new doctor template in doctorData.bin........
		doctemp[totalDoctors - 1].password = pass; //adding new password into docPtr new Doctor

		doctemp[totalDoctors - 1].name = tmp;
		doctemp[totalDoctors - 1].age = ag;
		doctemp[totalDoctors - 1].cnic = cnc;
		doctemp[totalDoctors - 1].phoneNumber = pnum;
		doctemp[totalDoctors - 1].hourlyCharges = hc;
		doctemp[totalDoctors - 1].available = av;
		doctemp[totalDoctors - 1].profession = this->profession;
		doctemp[totalDoctors - 1].hospital = hp;


		//.......Deleting previous docPtr list and creating and copying new data.......
		for (int i = 0; i < totalDoctors - 1; i++)
			delete[]docPtr[i];
		delete[]docPtr;
		docPtr = new Doctor * [totalDoctors];
		for (int i = 0; i < totalDoctors; i++) {
			docPtr[i] = new Doctor;
		}
		docAppointments = new Appointment[sizeDocAppointments];
		for (int i = 0; i < totalDoctors; i++) {
			docPtr[i]->name = doctemp[i].name;
			docPtr[i]->age = doctemp[i].age;
			docPtr[i]->cnic = doctemp[i].cnic;
			docPtr[i]->phoneNumber = doctemp[i].phoneNumber;
			docPtr[i]->hourlyCharges = doctemp[i].hourlyCharges;
			docPtr[i]->available = this->available;
			docPtr[i]->profession = this->profession;
			docPtr[i]->password = doctemp[i].password;
			docPtr[i]->hospital = doctemp[i].hospital;
		}
		cout << "All information noted successfully!" << endl;

		doctorWriteFile.write((char*)& d, sizeof(d));
		doctorWriteFile.close();

		return 0; // returning 0 means successful registration.
	}
};

class Oncologist : public Doctor {
	string profession = "Oncologist";
	bool available = true;
public:
	Oncologist() {}
	int Register() {
		totalDoctors++;  //  Increasing total size of Doctors.

		//...................Copying previous docPtr data into doctemp..................
		Doctor* doctemp = new Doctor[totalDoctors];
		for (int i = 0; i < totalDoctors - 1; i++) {
			doctemp[i].name = docPtr[i]->name;
			doctemp[i].age = docPtr[i]->age;
			doctemp[i].cnic = docPtr[i]->cnic;
			doctemp[i].phoneNumber = docPtr[i]->phoneNumber;
			doctemp[i].hourlyCharges = docPtr[i]->hourlyCharges;
			doctemp[i].available = this->available;
			doctemp[i].profession = this->profession;
			doctemp[i].hospital = docPtr[i]->hospital;
		}


		//............Asking and storing new Doctor's Information in doctemp..........................
		string cnc, tmp, hp; int ag, pnum; double hc; bool av; char tp, nm[20];
		cout << "Please enter your name: "; cin.ignore();
		cin.getline(nm, 20);
		tmp = nm;
		cout << "Please enter your age: ";
		cin >> ag;
		cout << "Please enter your cnic ($$$$$-$$$$$$$-$): ";
		cin >> cnc;
		while (cnc[5] != '-' || cnc[13] != '-' || cnc.length() > 15) {  //validating CNIC
			cout << "Invalid CNIC! Please enter again!" << endl;
			cin >> cnc;
		}

		Doctor d;
		////.................Checking if the CNIC already exist or not............................
		//Doctor d;
		//fstream doctorReadFile("doctorData.bin", ios::in | ios::out | ios::binary);
		//int ct = 0;
		////doctorReadFile.read((char*)& d, sizeof(d));
		//while (ct < totalDoctors) {
		//	if (docPtr[ct++]->cnic == cnic) {
		//		cout << "Error! this CNIC already exists! Please Login instead!" << endl;
		//		return -1;  //returning -1 will take doctor to doctor login portal.
		//	}
		//}
		////doctorReadFile.close();


		ofstream doctorWriteFile("doctorData.bin", ios::binary);
		cout << "Please enter your phone num: ";
		cin >> pnum;
		cout << "Please mention your hourly charges: ";
		cin >> hc;
		cout << "Are you available for the job right now? (Y/N)";
		cin >> tp;
		if (tp == 'Y' || tp == 'y')
			av = true;
		else if (tp == 'N' || tp == 'n')
			av = false;
		cout << "What is your Hospital name? " << endl;
		cin >> hp;


		//.................Getting password and validating it............................
		string pass;
		cout << "Please enter your password: "; cin >> pass;
		bool correctpass = false;
		while (correctpass == false) {
			bool uppercase, lowercase, special, numeric;
			while (!(pass.find("@") != std::string::npos || pass.find("#") != std::string::npos || pass.find("!") != std::string::npos || pass.find("~") != std::string::npos || pass.find("$") != std::string::npos || pass.find("%") != std::string::npos || pass.find("^") != std::string::npos || pass.find("&") != std::string::npos || pass.find("*") != std::string::npos || pass.find("(") != std::string::npos || pass.find(")") != std::string::npos || pass.find("-") != std::string::npos || pass.find("+") != std::string::npos || pass.find("/") != std::string::npos || pass.find(":") != std::string::npos || pass.find(".") != std::string::npos || pass.find(",") != std::string::npos || pass.find("<") != std::string::npos || pass.find(">") != std::string::npos || pass.find("?") != std::string::npos || pass.find("|") != std::string::npos)) {
				special = false;
				cout << "Password Must include atleast one special character. Enter again." << endl;
				cin >> pass;
			}
			special = true;
			while (!(pass.find("A") != std::string::npos || pass.find("B") != std::string::npos || pass.find("C") != std::string::npos || pass.find("D") != std::string::npos || pass.find("E") != std::string::npos || pass.find("F") != std::string::npos || pass.find("G") != std::string::npos || pass.find("H") != std::string::npos || pass.find("I") != std::string::npos || pass.find("J") != std::string::npos || pass.find("K") != std::string::npos || pass.find("L") != std::string::npos || pass.find("M") != std::string::npos || pass.find("N") != std::string::npos || pass.find("O") != std::string::npos || pass.find("P") != std::string::npos || pass.find("Q") != std::string::npos || pass.find("R") != std::string::npos || pass.find("S") != std::string::npos || pass.find("T") != std::string::npos || pass.find("U") != std::string::npos || pass.find("V") != std::string::npos || pass.find("W") != std::string::npos || pass.find("X") != std::string::npos || pass.find("Y") != std::string::npos || pass.find("Z") != std::string::npos)) {
				uppercase = false;
				cout << "Password Must include atleast one uppercase character. Enter again." << endl;
				cin >> pass;
			}
			uppercase = true;
			while (!(pass.find("a") != std::string::npos || pass.find("b") != std::string::npos || pass.find("c") != std::string::npos || pass.find("d") != std::string::npos || pass.find("e") != std::string::npos || pass.find("f") != std::string::npos || pass.find("g") != std::string::npos || pass.find("h") != std::string::npos || pass.find("i") != std::string::npos || pass.find("j") != std::string::npos || pass.find("k") != std::string::npos || pass.find("l") != std::string::npos || pass.find("m") != std::string::npos || pass.find("n") != std::string::npos || pass.find("o") != std::string::npos || pass.find("p") != std::string::npos || pass.find("q") != std::string::npos || pass.find("r") != std::string::npos || pass.find("s") != std::string::npos || pass.find("t") != std::string::npos || pass.find("u") != std::string::npos || pass.find("v") != std::string::npos || pass.find("w") != std::string::npos || pass.find("x") != std::string::npos || pass.find("y") != std::string::npos || pass.find("z") != std::string::npos)) {
				lowercase = false;
				cout << "Password Must include atleast one lowercase character. Enter again." << endl;
				cin >> pass;
			}
			lowercase = true;
			while (!(pass.find("0") != std::string::npos || pass.find("1") != std::string::npos || pass.find("2") != std::string::npos || pass.find("3") != std::string::npos || pass.find("4") != std::string::npos || pass.find("5") != std::string::npos || pass.find("6") != std::string::npos || pass.find("7") != std::string::npos || pass.find("8") != std::string::npos || pass.find("9") != std::string::npos)) {
				numeric = false;
				cout << "Password Must include atleast one number. Enter again." << endl;
				cin >> pass;
			}
			numeric = true;
			if (special == true && uppercase == true && lowercase == true && numeric == true)
				correctpass = true;
		}


		//.........Adding new password and writing new doctor template in doctorData.bin........
		doctemp[totalDoctors - 1].password = pass; //adding new password into docPtr new Doctor

		doctemp[totalDoctors - 1].name = tmp;
		doctemp[totalDoctors - 1].age = ag;
		doctemp[totalDoctors - 1].cnic = cnc;
		doctemp[totalDoctors - 1].phoneNumber = pnum;
		doctemp[totalDoctors - 1].hourlyCharges = hc;
		doctemp[totalDoctors - 1].available = av;
		doctemp[totalDoctors - 1].profession = this->profession;
		doctemp[totalDoctors - 1].hospital = hp;


		//.......Deleting previous docPtr list and creating and copying new data.......
		for (int i = 0; i < totalDoctors - 1; i++)
			delete[]docPtr[i];
		delete[]docPtr;
		docPtr = new Doctor * [totalDoctors];
		docAppointments = new Appointment[sizeDocAppointments];
		for (int i = 0; i < totalDoctors; i++) {
			docPtr[i] = new Doctor;
		}
		for (int i = 0; i < totalDoctors; i++) {
			docPtr[i]->name = doctemp[i].name;
			docPtr[i]->age = doctemp[i].age;
			docPtr[i]->cnic = doctemp[i].cnic;
			docPtr[i]->phoneNumber = doctemp[i].phoneNumber;
			docPtr[i]->hourlyCharges = doctemp[i].hourlyCharges;
			docPtr[i]->available = this->available;
			docPtr[i]->profession = this->profession;
			docPtr[i]->password = doctemp[i].password;
			docPtr[i]->hospital = doctemp[i].hospital;
		}
		cout << "All information noted successfully!" << endl;

		doctorWriteFile.write((char*)& d, sizeof(d));
		doctorWriteFile.close();

		return 0; // returning 0 means successful registration.
	}
};

class Orthopedic : public Doctor {
	string profession = "Orthopedic";
	bool available = true;
public:
	Orthopedic() {}
	int Register() {
		totalDoctors++;  //  Increasing total size of Doctors.

		//...................Copying previous docPtr data into doctemp..................
		Doctor* doctemp = new Doctor[totalDoctors];
		for (int i = 0; i < totalDoctors - 1; i++) {
			doctemp[i].name = docPtr[i]->name;
			doctemp[i].age = docPtr[i]->age;
			doctemp[i].cnic = docPtr[i]->cnic;
			doctemp[i].phoneNumber = docPtr[i]->phoneNumber;
			doctemp[i].hourlyCharges = docPtr[i]->hourlyCharges;
			doctemp[i].available = this->available;
			doctemp[i].profession = this->profession;
			doctemp[i].hospital = docPtr[i]->hospital;
		}


		//............Asking and storing new Doctor's Information in doctemp..........................
		string cnc, tmp, hp; int ag, pnum; double hc; bool av; char tp, nm[20];
		cout << "Please enter your name: "; cin.ignore();
		cin.getline(nm, 20);
		tmp = nm;
		cout << "Please enter your age: ";
		cin >> ag;
		cout << "Please enter your cnic ($$$$$-$$$$$$$-$): ";
		cin >> cnc;
		while (cnc[5] != '-' || cnc[13] != '-' || cnc.length() > 15) {  //validating CNIC
			cout << "Invalid CNIC! Please enter again!" << endl;
			cin >> cnc;
		}

		Doctor d;
		////.................Checking if the CNIC already exist or not............................
		//Doctor d;
		//fstream doctorReadFile("doctorData.bin", ios::in | ios::out | ios::binary);
		//int ct = 0;
		////doctorReadFile.read((char*)& d, sizeof(d));
		//while (ct < totalDoctors) {
		//	if (docPtr[ct++]->cnic == cnic) {
		//		cout << "Error! this CNIC already exists! Please Login instead!" << endl;
		//		return -1;  //returning -1 will take doctor to doctor login portal.
		//	}
		//}
		////doctorReadFile.close();


		ofstream doctorWriteFile("doctorData.bin", ios::binary);
		cout << "Please enter your phone num: ";
		cin >> pnum;
		cout << "Please mention your hourly charges: ";
		cin >> hc;
		cout << "Are you available for the job right now? (Y/N)";
		cin >> tp;
		if (tp == 'Y' || tp == 'y')
			av = true;
		else if (tp == 'N' || tp == 'n')
			av = false;
		cout << "What is your Hospital name? " << endl;
		cin >> hp;


		//.................Getting password and validating it............................
		string pass;
		cout << "Please enter your password: "; cin >> pass;
		bool correctpass = false;
		while (correctpass == false) {
			bool uppercase, lowercase, special, numeric;
			while (!(pass.find("@") != std::string::npos || pass.find("#") != std::string::npos || pass.find("!") != std::string::npos || pass.find("~") != std::string::npos || pass.find("$") != std::string::npos || pass.find("%") != std::string::npos || pass.find("^") != std::string::npos || pass.find("&") != std::string::npos || pass.find("*") != std::string::npos || pass.find("(") != std::string::npos || pass.find(")") != std::string::npos || pass.find("-") != std::string::npos || pass.find("+") != std::string::npos || pass.find("/") != std::string::npos || pass.find(":") != std::string::npos || pass.find(".") != std::string::npos || pass.find(",") != std::string::npos || pass.find("<") != std::string::npos || pass.find(">") != std::string::npos || pass.find("?") != std::string::npos || pass.find("|") != std::string::npos)) {
				special = false;
				cout << "Password Must include atleast one special character. Enter again." << endl;
				cin >> pass;
			}
			special = true;
			while (!(pass.find("A") != std::string::npos || pass.find("B") != std::string::npos || pass.find("C") != std::string::npos || pass.find("D") != std::string::npos || pass.find("E") != std::string::npos || pass.find("F") != std::string::npos || pass.find("G") != std::string::npos || pass.find("H") != std::string::npos || pass.find("I") != std::string::npos || pass.find("J") != std::string::npos || pass.find("K") != std::string::npos || pass.find("L") != std::string::npos || pass.find("M") != std::string::npos || pass.find("N") != std::string::npos || pass.find("O") != std::string::npos || pass.find("P") != std::string::npos || pass.find("Q") != std::string::npos || pass.find("R") != std::string::npos || pass.find("S") != std::string::npos || pass.find("T") != std::string::npos || pass.find("U") != std::string::npos || pass.find("V") != std::string::npos || pass.find("W") != std::string::npos || pass.find("X") != std::string::npos || pass.find("Y") != std::string::npos || pass.find("Z") != std::string::npos)) {
				uppercase = false;
				cout << "Password Must include atleast one uppercase character. Enter again." << endl;
				cin >> pass;
			}
			uppercase = true;
			while (!(pass.find("a") != std::string::npos || pass.find("b") != std::string::npos || pass.find("c") != std::string::npos || pass.find("d") != std::string::npos || pass.find("e") != std::string::npos || pass.find("f") != std::string::npos || pass.find("g") != std::string::npos || pass.find("h") != std::string::npos || pass.find("i") != std::string::npos || pass.find("j") != std::string::npos || pass.find("k") != std::string::npos || pass.find("l") != std::string::npos || pass.find("m") != std::string::npos || pass.find("n") != std::string::npos || pass.find("o") != std::string::npos || pass.find("p") != std::string::npos || pass.find("q") != std::string::npos || pass.find("r") != std::string::npos || pass.find("s") != std::string::npos || pass.find("t") != std::string::npos || pass.find("u") != std::string::npos || pass.find("v") != std::string::npos || pass.find("w") != std::string::npos || pass.find("x") != std::string::npos || pass.find("y") != std::string::npos || pass.find("z") != std::string::npos)) {
				lowercase = false;
				cout << "Password Must include atleast one lowercase character. Enter again." << endl;
				cin >> pass;
			}
			lowercase = true;
			while (!(pass.find("0") != std::string::npos || pass.find("1") != std::string::npos || pass.find("2") != std::string::npos || pass.find("3") != std::string::npos || pass.find("4") != std::string::npos || pass.find("5") != std::string::npos || pass.find("6") != std::string::npos || pass.find("7") != std::string::npos || pass.find("8") != std::string::npos || pass.find("9") != std::string::npos)) {
				numeric = false;
				cout << "Password Must include atleast one number. Enter again." << endl;
				cin >> pass;
			}
			numeric = true;
			if (special == true && uppercase == true && lowercase == true && numeric == true)
				correctpass = true;
		}


		//.........Adding new password and writing new doctor template in doctorData.bin........
		doctemp[totalDoctors - 1].password = pass; //adding new password into docPtr new Doctor

		doctemp[totalDoctors - 1].name = tmp;
		doctemp[totalDoctors - 1].age = ag;
		doctemp[totalDoctors - 1].cnic = cnc;
		doctemp[totalDoctors - 1].phoneNumber = pnum;
		doctemp[totalDoctors - 1].hourlyCharges = hc;
		doctemp[totalDoctors - 1].available = av;
		doctemp[totalDoctors - 1].profession = this->profession;
		doctemp[totalDoctors - 1].hospital = hp;


		//.......Deleting previous docPtr list and creating and copying new data.......
		for (int i = 0; i < totalDoctors - 1; i++)
			delete[]docPtr[i];
		delete[]docPtr;
		docPtr = new Doctor * [totalDoctors];
		for (int i = 0; i < totalDoctors; i++) {
			docPtr[i] = new Doctor;
		}
		docAppointments = new Appointment[sizeDocAppointments];
		for (int i = 0; i < totalDoctors; i++) {
			docPtr[i]->name = doctemp[i].name;
			docPtr[i]->age = doctemp[i].age;
			docPtr[i]->cnic = doctemp[i].cnic;
			docPtr[i]->phoneNumber = doctemp[i].phoneNumber;
			docPtr[i]->hourlyCharges = doctemp[i].hourlyCharges;
			docPtr[i]->available = this->available;
			docPtr[i]->profession = this->profession;
			docPtr[i]->password = doctemp[i].password;
			docPtr[i]->hospital = doctemp[i].hospital;
		}
		cout << "All information noted successfully!" << endl;

		doctorWriteFile.write((char*)& d, sizeof(d));
		doctorWriteFile.close();

		return 0; // returning 0 means successful registration.
	}
};

class Patient : public User {
public:
	int totalPatients;
	Patient** patPtr;
	int sizePatAppointments;
	string password;
	double balance;
	Appointment* patAppointments;
	Patient() {}
	int Register() {
		totalPatients++;  //  Increasing total size of Doctors.

		//...................Copying previous docPtr data into doctemp..................
		Patient* pattemp = new Patient[totalPatients];
		for (int i = 0; i < totalPatients - 1; i++) {
			//doctemp[i].name = docPtr[i]->name;
			pattemp[i].age = patPtr[i]->age;
			pattemp[i].cnic = patPtr[i]->cnic;
			pattemp[i].phoneNumber = patPtr[i]->phoneNumber;
			//doctemp[i].hourlyCharges = patPtr[i]->hourlyCharges;
			//doctemp[i].available = this->available;
			//doctemp[i].profession = this->profession;
		}


		//............Asking and storing new Doctor's Information in doctemp..........................
		string cnc, tmp; int ag, pnum; char tp, nm[20];
		cout << "Please enter your name: "; cin.ignore();
		cin.getline(nm, 20);
		tmp = nm;
		cout << "Please enter your age: ";
		cin >> ag;
		cout << "Please enter your cnic ($$$$$-$$$$$$$-$): ";
		cin >> cnc;
		while (cnc[5] != '-' || cnc[13] != '-' || cnc.length() > 15) {  //validating CNIC
			cout << "Invalid CNIC! Please enter again!" << endl;
			cin >> cnc;
		}

		Patient d;
		////.................Checking if the CNIC already exist or not............................
		//Doctor d;
		//fstream doctorReadFile("doctorData.bin", ios::in | ios::out | ios::binary);
		//int ct = 0;
		////doctorReadFile.read((char*)& d, sizeof(d));
		//while (ct < totalDoctors) {
		//	if (docPtr[ct++]->cnic == cnic) {
		//		cout << "Error! this CNIC already exists! Please Login instead!" << endl;
		//		return -1;  //returning -1 will take doctor to doctor login portal.
		//	}
		//}
		////doctorReadFile.close();


		ofstream patientWriteFile("patientData.bin", ios::binary);
		cout << "Please enter your phone num: ";
		cin >> pnum;
		/*cout << "Please mention your hourly charges: ";
		cin >> hc;*/
		/*cout << "Are you available for the job right now? (Y/N)";
		cin >> tp;
		if (tp == 'Y' || tp == 'y')
			av = true;
		else if (tp == 'N' || tp == 'n')
			av = false;*/


			//.................Getting password and validating it............................
		string pass;
		cout << "Please enter your password: "; cin >> pass;
		bool correctpass = false;
		while (correctpass == false) {
			bool uppercase, lowercase, special, numeric;
			while (!(pass.find("@") != std::string::npos || pass.find("#") != std::string::npos || pass.find("!") != std::string::npos || pass.find("~") != std::string::npos || pass.find("$") != std::string::npos || pass.find("%") != std::string::npos || pass.find("^") != std::string::npos || pass.find("&") != std::string::npos || pass.find("*") != std::string::npos || pass.find("(") != std::string::npos || pass.find(")") != std::string::npos || pass.find("-") != std::string::npos || pass.find("+") != std::string::npos || pass.find("/") != std::string::npos || pass.find(":") != std::string::npos || pass.find(".") != std::string::npos || pass.find(",") != std::string::npos || pass.find("<") != std::string::npos || pass.find(">") != std::string::npos || pass.find("?") != std::string::npos || pass.find("|") != std::string::npos)) {
				special = false;
				cout << "Password Must include atleast one special character. Enter again." << endl;
				cin >> pass;
			}
			special = true;
			while (!(pass.find("A") != std::string::npos || pass.find("B") != std::string::npos || pass.find("C") != std::string::npos || pass.find("D") != std::string::npos || pass.find("E") != std::string::npos || pass.find("F") != std::string::npos || pass.find("G") != std::string::npos || pass.find("H") != std::string::npos || pass.find("I") != std::string::npos || pass.find("J") != std::string::npos || pass.find("K") != std::string::npos || pass.find("L") != std::string::npos || pass.find("M") != std::string::npos || pass.find("N") != std::string::npos || pass.find("O") != std::string::npos || pass.find("P") != std::string::npos || pass.find("Q") != std::string::npos || pass.find("R") != std::string::npos || pass.find("S") != std::string::npos || pass.find("T") != std::string::npos || pass.find("U") != std::string::npos || pass.find("V") != std::string::npos || pass.find("W") != std::string::npos || pass.find("X") != std::string::npos || pass.find("Y") != std::string::npos || pass.find("Z") != std::string::npos)) {
				uppercase = false;
				cout << "Password Must include atleast one uppercase character. Enter again." << endl;
				cin >> pass;
			}
			uppercase = true;
			while (!(pass.find("a") != std::string::npos || pass.find("b") != std::string::npos || pass.find("c") != std::string::npos || pass.find("d") != std::string::npos || pass.find("e") != std::string::npos || pass.find("f") != std::string::npos || pass.find("g") != std::string::npos || pass.find("h") != std::string::npos || pass.find("i") != std::string::npos || pass.find("j") != std::string::npos || pass.find("k") != std::string::npos || pass.find("l") != std::string::npos || pass.find("m") != std::string::npos || pass.find("n") != std::string::npos || pass.find("o") != std::string::npos || pass.find("p") != std::string::npos || pass.find("q") != std::string::npos || pass.find("r") != std::string::npos || pass.find("s") != std::string::npos || pass.find("t") != std::string::npos || pass.find("u") != std::string::npos || pass.find("v") != std::string::npos || pass.find("w") != std::string::npos || pass.find("x") != std::string::npos || pass.find("y") != std::string::npos || pass.find("z") != std::string::npos)) {
				lowercase = false;
				cout << "Password Must include atleast one lowercase character. Enter again." << endl;
				cin >> pass;
			}
			lowercase = true;
			while (!(pass.find("0") != std::string::npos || pass.find("1") != std::string::npos || pass.find("2") != std::string::npos || pass.find("3") != std::string::npos || pass.find("4") != std::string::npos || pass.find("5") != std::string::npos || pass.find("6") != std::string::npos || pass.find("7") != std::string::npos || pass.find("8") != std::string::npos || pass.find("9") != std::string::npos)) {
				numeric = false;
				cout << "Password Must include atleast one number. Enter again." << endl;
				cin >> pass;
			}
			numeric = true;
			if (special == true && uppercase == true && lowercase == true && numeric == true)
				correctpass = true;
		}


		//.........Adding new password and writing new doctor template in doctorData.bin........
		pattemp[totalPatients - 1].password = pass; //adding new password into docPtr new Doctor

		pattemp[totalPatients - 1].name = tmp;
		pattemp[totalPatients - 1].age = ag;
		pattemp[totalPatients - 1].cnic = cnc;
		pattemp[totalPatients - 1].phoneNumber = pnum;
		//pattemp[totalPatients - 1].hourlyCharges = hc;
		/*pattemp[totalPatients - 1].available = av;
		pattemp[totalPatients - 1].profession = this->profession;*/


		//.......Deleting previous docPtr list and creating and copying new data.......
		for (int i = 0; i < totalPatients - 1; i++)
			delete[]patPtr[i];
		delete[]patPtr;
		patPtr = new Patient * [totalPatients];
		for (int i = 0; i < totalPatients; i++) {
			patPtr[i] = new Patient;
		}
		patAppointments = new Appointment[sizePatAppointments];
		for (int i = 0; i < totalPatients; i++) {
			patPtr[i]->name = pattemp[i].name;
			patPtr[i]->age = pattemp[i].age;
			patPtr[i]->cnic = pattemp[i].cnic;
			patPtr[i]->phoneNumber = pattemp[i].phoneNumber;
			//patPtr[i]->hourlyCharges = pattemp[i].hourlyCharges;
			//patPtr[i]->available = this->available;
			//patPtr[i]->profession = this->profession;
			patPtr[i]->password = pattemp[i].password;
		}
		cout << "All information noted successfully!" << endl;

		patientWriteFile.write((char*)& d, sizeof(d));
		patientWriteFile.close();

		return 0; // returning 0 means successful registration.
	}
	int Login() {
		//.................Asking and Validating CNIC...................................
		string cnic;
		cout << "Please enter your CNIC ($$$$$-$$$$$$$-$): "; cin >> cnic;
		while (cnic[5] != '-' || cnic[13] != '-' || cnic.length() > 15) {
			cout << "Invalid CNIC! Please enter again!" << endl;
			cin >> cnic;
		}


		//..............Searching docPtr for the Doctor with that CNIC.................
		bool found = false;
		Patient d;
		fstream patientFile("patientData.bin", ios::in | ios::out | ios::binary);
		patientFile.read((char*)& d, sizeof(d));
		int ct = 0, foundLocation;
		while (found == false && ct < d.totalPatients) {
			if (d.patPtr[ct]->cnic == cnic) {
				cout << "Welcome Dr." << d.patPtr[ct]->name << endl;
				found = true;
				foundLocation = ct;
				patientFile.close();
				return foundLocation; // returning the current index of doctor in docPtr 
			}
			ct++;
		}
		if (found == false) {
			cout << "No Patient with that CNIC found! Please Register to get connected." << endl;
			patientFile.close();
			system("pause");
			return -1;  // returning -1 will take you to doctor registeration portal.
		}
	}
	void ResetPassword(int foundPatientIndex) {
		Patient p;
		string pass;
		cout << "Enter new password: "; cin >> pass;
		bool correctpass = false;
		while (correctpass == false) {
			bool uppercase, lowercase, special, numeric;
			while (!(pass.find("@") != std::string::npos || pass.find("#") != std::string::npos || pass.find("!") != std::string::npos || pass.find("~") != std::string::npos || pass.find("$") != std::string::npos || pass.find("%") != std::string::npos || pass.find("^") != std::string::npos || pass.find("&") != std::string::npos || pass.find("*") != std::string::npos || pass.find("(") != std::string::npos || pass.find(")") != std::string::npos || pass.find("-") != std::string::npos || pass.find("+") != std::string::npos || pass.find("/") != std::string::npos || pass.find(":") != std::string::npos || pass.find(".") != std::string::npos || pass.find(",") != std::string::npos || pass.find("<") != std::string::npos || pass.find(">") != std::string::npos || pass.find("?") != std::string::npos || pass.find("|") != std::string::npos)) {
				special = false;
				cout << "Password Must include atleast one special character. Enter again." << endl;
				cin >> pass;
			}
			special = true;
			while (!(pass.find("A") != std::string::npos || pass.find("B") != std::string::npos || pass.find("C") != std::string::npos || pass.find("D") != std::string::npos || pass.find("E") != std::string::npos || pass.find("F") != std::string::npos || pass.find("G") != std::string::npos || pass.find("H") != std::string::npos || pass.find("I") != std::string::npos || pass.find("J") != std::string::npos || pass.find("K") != std::string::npos || pass.find("L") != std::string::npos || pass.find("M") != std::string::npos || pass.find("N") != std::string::npos || pass.find("O") != std::string::npos || pass.find("P") != std::string::npos || pass.find("Q") != std::string::npos || pass.find("R") != std::string::npos || pass.find("S") != std::string::npos || pass.find("T") != std::string::npos || pass.find("U") != std::string::npos || pass.find("V") != std::string::npos || pass.find("W") != std::string::npos || pass.find("X") != std::string::npos || pass.find("Y") != std::string::npos || pass.find("Z") != std::string::npos)) {
				uppercase = false;
				cout << "Password Must include atleast one uppercase character. Enter again." << endl;
				cin >> pass;
			}
			uppercase = true;
			while (!(pass.find("a") != std::string::npos || pass.find("b") != std::string::npos || pass.find("c") != std::string::npos || pass.find("d") != std::string::npos || pass.find("e") != std::string::npos || pass.find("f") != std::string::npos || pass.find("g") != std::string::npos || pass.find("h") != std::string::npos || pass.find("i") != std::string::npos || pass.find("j") != std::string::npos || pass.find("k") != std::string::npos || pass.find("l") != std::string::npos || pass.find("m") != std::string::npos || pass.find("n") != std::string::npos || pass.find("o") != std::string::npos || pass.find("p") != std::string::npos || pass.find("q") != std::string::npos || pass.find("r") != std::string::npos || pass.find("s") != std::string::npos || pass.find("t") != std::string::npos || pass.find("u") != std::string::npos || pass.find("v") != std::string::npos || pass.find("w") != std::string::npos || pass.find("x") != std::string::npos || pass.find("y") != std::string::npos || pass.find("z") != std::string::npos)) {
				lowercase = false;
				cout << "Password Must include atleast one lowercase character. Enter again." << endl;
				cin >> pass;
			}
			lowercase = true;
			while (!(pass.find("0") != std::string::npos || pass.find("1") != std::string::npos || pass.find("2") != std::string::npos || pass.find("3") != std::string::npos || pass.find("4") != std::string::npos || pass.find("5") != std::string::npos || pass.find("6") != std::string::npos || pass.find("7") != std::string::npos || pass.find("8") != std::string::npos || pass.find("9") != std::string::npos)) {
				numeric = false;
				cout << "Password Must include atleast one number. Enter again." << endl;
				cin >> pass;
			}
			numeric = true;
			if (special == true && uppercase == true && lowercase == true && numeric == true)
				correctpass = true;
		}
		p.patPtr[foundPatientIndex]->password = pass;
		cout << "Password Updated!" << endl;
	}
	void searchDoctorBySpeciality() {
		string patdecision;
		cout << "Which doctor you are looking for?" << endl;
		cout << "Are you looking for Gynecologist?" << endl;
		cout << "Are you looking for Dermatologist?" << endl;
		cout << "Are you looking for Oncologist?" << endl;
		cout << "Are you looking for Orthopedic?" << endl;
		cin >> patdecision;
		Doctor d;
		if (patdecision == "Gynecologist" || patdecision == "gynecologist") {
			for (int i = 0; i < d.totalDoctors; i++) {
				if (d.docPtr[i]->profession == "Gynecologist" || d.docPtr[i]->profession == "gynecologist") {
					cout << "Doctor name: " << d.docPtr[i]->name << endl;
				}
			}
		}
		else if (patdecision == "Dermatologist" || patdecision == "dermatologist") {
			for (int i = 0; i < d.totalDoctors; i++) {
				if (d.docPtr[i]->profession == "Dermatologist" || d.docPtr[i]->profession == "dermatologist") {
					cout << "Doctor name: " << d.docPtr[i]->name << endl;
				}
			}
		}
		else if (patdecision == "Oncologist" || patdecision == "oncologist") {
			for (int i = 0; i < d.totalDoctors; i++) {
				if (d.docPtr[i]->profession == "Oncologist" || d.docPtr[i]->profession == "oncologist") {
					cout << "Doctor name: " << d.docPtr[i]->name << endl;
				}
			}
		}
		else if (patdecision == "Orthopedic" || patdecision == "orthopedic") {
			for (int i = 0; i < d.totalDoctors; i++) {
				if (d.docPtr[i]->profession == "Orthopedic" || d.docPtr[i]->profession == "orthopedic") {
					cout << "Doctor name: " << d.docPtr[i]->name << endl;
				}
			}
		}
	}
	void searchDoctorByArea() {
		string patdecision;
		cout << "Enter the Area: " << endl;
		cin >> patdecision;
		Doctor d;
		for (int i = 0; i < d.totalDoctors; i++) {
			if (d.docPtr[i]->location == patdecision) {
				cout << "Doctor name: " << d.docPtr[i]->name << endl;
			}
		}
	}
	void searchDoctorByHospital() {
		string patdecision;
		cout << "Enter the nam of Hospital: " << endl;
		cin >> patdecision;
		Doctor d;
		for (int i = 0; i < d.totalDoctors; i++) {
			if (d.docPtr[i]->hospital == patdecision) {
				cout << "Doctor name: " << d.docPtr[i]->name << endl;
			}
		}
	}
	void checkDoctorAvailability() {
		string patdecision, available;
		cout << "Which Doctor you want to check availability? " << endl;
		cin >> patdecision;
		Doctor d;
		for (int i = 0; i < d.totalDoctors; i++) {
			if (d.docPtr[i]->name == patdecision) {
				if (d.docPtr[i]->available == true)
					available = "available";
				else
					available = "not available";
				cout << "Dr." << d.docPtr[i]->name << "is " << available << endl;
			}
		}
	}
	void checkDoctorCharges() {
		string patdecision;
		cout << "Which field Doctor you want to check charges?" << endl;
		cout << "Gynecologist, Dermatologist, Oncologist, Orthopedic?" << endl;
		cin >> patdecision;
		Doctor d;
		if (patdecision == "Gynecologist" || patdecision == "gynecologist") {
			for (int i = 0; i < d.totalDoctors; i++) {
				if (d.docPtr[i]->profession == "Gynecologist" || d.docPtr[i]->profession == "gynecologist") {
					cout << "Dr." << d.docPtr[i]->name << "'s charges: " << d.docPtr[i]->hourlyCharges << endl;
				}
			}
		}
		else if (patdecision == "Dermatologist" || patdecision == "dermatologist") {
			for (int i = 0; i < d.totalDoctors; i++) {
				if (d.docPtr[i]->profession == "Dermatologist" || d.docPtr[i]->profession == "dermatologist") {
					cout << "Dr." << d.docPtr[i]->name << "'s charges: " << d.docPtr[i]->hourlyCharges << endl;
				}
			}
		}
		else if (patdecision == "Oncologist" || patdecision == "oncologist") {
			for (int i = 0; i < d.totalDoctors; i++) {
				if (d.docPtr[i]->profession == "Oncologist" || d.docPtr[i]->profession == "oncologist") {
					cout << "Dr." << d.docPtr[i]->name << "'s charges: " << d.docPtr[i]->hourlyCharges << endl;
				}
			}
		}
		else if (patdecision == "Orthopedic" || patdecision == "orthopedic") {
			for (int i = 0; i < d.totalDoctors; i++) {
				if (d.docPtr[i]->profession == "Orthopedic" || d.docPtr[i]->profession == "orthopedic") {
					cout << "Dr." << d.docPtr[i]->name << "'s charges: " << d.docPtr[i]->hourlyCharges << endl;
				}
			}
		}
	}
	void bookInPersonAppointment(int foundPatientIndex) {
		string dt, tm;
		double pm;
		patPtr[foundPatientIndex]->patAppointments[foundPatientIndex].appointmentStatus = "pending";
		patPtr[foundPatientIndex]->patAppointments[foundPatientIndex].appointmentType = "InPerson";
		cout << "Enter the date for the appointment: ";
		cin >> dt;
		cout << "Enter the time for the appointment (HH:MM): ";
		cin >> tm;
		patPtr[foundPatientIndex]->patAppointments[foundPatientIndex].dateTime.date = dt;
		patPtr[foundPatientIndex]->patAppointments[foundPatientIndex].dateTime.time = tm;
		patPtr[foundPatientIndex]->patAppointments[foundPatientIndex].payment;// = pm;
		Feedback f;
		cout << "Please provide us the feedback about your experience: " << endl;
		cin >> f.feedback;
	}
	void cancelInPersonAppointment(int foundPatientIndex) {
		patPtr[foundPatientIndex]->patAppointments[foundPatientIndex].appointmentStatus = "cancel";
	}
	void bookVideoAppointment(int foundPatientIndex) {
		string dt, tm;
		double pm;
		patPtr[foundPatientIndex]->patAppointments[foundPatientIndex].appointmentStatus = "pending";
		patPtr[foundPatientIndex]->patAppointments[foundPatientIndex].appointmentType = "Video";
		cout << "Enter the date for the appointment: ";
		cin >> dt;
		cout << "Enter the time for the appointment (HH:MM): ";
		cin >> tm;
		patPtr[foundPatientIndex]->patAppointments[foundPatientIndex].dateTime.date = dt;
		patPtr[foundPatientIndex]->patAppointments[foundPatientIndex].dateTime.time = tm;
		patPtr[foundPatientIndex]->patAppointments[foundPatientIndex].payment;// = pm;
		Feedback f;
		cout << "Please provide us the feedback about your experience: " << endl;
		cin >> f.feedback;
	}
	void cancelVideoAppointment(int foundPatientIndex) {
		patPtr[foundPatientIndex]->patAppointments[foundPatientIndex].appointmentStatus = "cancel";
	}
	void changeAppointmentTime(int foundPatientIndex) {
		string tm;
		cout << "Enter new time (HH:MM): ";
		cin >> tm;
		patPtr[foundPatientIndex]->patAppointments[foundPatientIndex].dateTime.time = tm;
	}
	void changeName(int foundPatientIndex) {
		Patient p;
		char nm[20];
		cout << "Enter new name: ";
		cin.ignore();
		cin.getline(nm, 20);
		string nms = nm;
		p.patPtr[foundPatientIndex]->name = nms;
	}
	void changeCNIC(int foundPatientIndex) {
		Patient p;
		string cnic;
		cout << "Enter new CNIC: ";
		cin >> cnic;
		p.patPtr[foundPatientIndex]->cnic = cnic;
	}
	void changePhoneNumber(int foundPatientIndex) {
		Patient p;
		int pnum;
		cout << "Enter new Phone Number: ";
		cin >> pnum;
		p.patPtr[foundPatientIndex]->phoneNumber = pnum;
	}
	void changeAge(int foundPatientIndex) {
		Patient p;
		int ag;
		cout << "Enter new Age: ";
		cin >> ag;
		p.patPtr[foundPatientIndex]->age = ag;
	}
	void checkAllAppointments(int foundPatientIndex) {
		Patient p;
		cout << "Patient name: " << p.patPtr[foundPatientIndex]->name << endl;
		for (int i = 0; i < sizePatAppointments; i++) {
			cout << "Patient name: " << p.patPtr[foundPatientIndex]->patAppointments[i] << endl;
		}
	}
	void rechargeAccount(int foundPatientIndex) {
		Patient p;
		double amount;
		cout << "How much amount you want to recharge?" << endl;
		cin >> amount;
		p.patPtr[foundPatientIndex]->balance += amount;
		cout << "New balance: " << p.patPtr[foundPatientIndex]->balance << endl;
	}
};

class Admin : public User {
	string username;
	string password;
public:
	Admin() :username("affan4321"), password("Affan4321@$") {}
	int Login() {
		string usernm, pass;
		cout << "Enter the username: " << endl;
		cin >> usernm;
		cout << "Enter the password: " << endl;
		cin >> pass;
		if (this->username == usernm && this->password == pass) {
			cout << "Welcome " << username << "!" << endl;
		}
		else {
			while (this->username != usernm && this->password != pass) {
				cout << "Wrong Credentials! Enter again." << endl;
				cout << "Enter username: ";
				cin >> usernm;
				cout << "Enter Password: ";
				cin >> pass;
			}
			cout << "Welcome " << username << "!" << endl;
		}
		return 0;
	}
	void viewDoctorData() {
		Doctor temp;
		int ct = 0;
		while (temp.docPtr[ct] != NULL && ct < temp.totalDoctors) {
			cout << "The doctor name is: " << temp.docPtr[ct]->name << endl;
			cout << "Doctor's age: " << temp.docPtr[ct]->age << endl;
			cout << "Doctor's CNIC: " << temp.docPtr[ct]->cnic << endl;
			cout << "Doctor's Profession: " << temp.docPtr[ct]->profession << endl;
			cout << "Doctor's available: " << temp.docPtr[ct]->available << endl;
			cout << "Doctor's timings: " << temp.docPtr[ct]->timings << endl;
			ct++;
		}
	}
	void editDoctorData() {
		Doctor temp;
		int ct = 0;
		while (temp.docPtr[ct] != NULL && ct < temp.totalDoctors) {
			cout << "The doctor name is: " << temp.docPtr[ct]->name << endl;
			cout << "Doctor's age: " << temp.docPtr[ct]->age << endl;
			cout << "Doctor's CNIC: " << temp.docPtr[ct]->cnic << endl;
			cout << "Doctor's Profession: " << temp.docPtr[ct]->profession << endl;
			cout << "Doctor's available: " << temp.docPtr[ct]->available << endl;
			ct++;
			cout << "Do you want to edit it? (Y/N)" << endl;
			char admindecision;
			cin >> admindecision;
			if (admindecision == 'Y' || admindecision == 'y') {
				bool end = false;
				while (end == false) {
					cout << "which element to edit? (N/A/C/a)" << endl;
					cout << "Make sure that you enter the exact case ie~ upper or lower." << endl;
					cin >> admindecision;
					if (admindecision == 'N') {
						cout << "Enter Doctor's new name: ";
						cin >> temp.docPtr[ct]->name;
					}
					else if (admindecision == 'A') {
						cout << "Enter Doctor's new age: ";
						cin >> temp.docPtr[ct]->age;
					}
					else if (admindecision == 'C') {
						cout << "Enter Doctor's new CNIC: ";
						cin >> temp.docPtr[ct]->cnic;
					}
					else if (admindecision == 'a') {
						cout << "Enter Doctor's availability ststus: ";
						cin >> temp.docPtr[ct]->available;
					}
					cout << "Do you further want to edit anything? (Y/N): ";
					cin >> admindecision;
					if (admindecision == 'N' || admindecision == 'n')
						end = true;
				}
			}
			else if (admindecision == 'N' || admindecision == 'n') {
				cout << "Alright, have a good day!" << endl;
			}
		}
	}
	void checkDoctorAvailability() {
		Doctor temp;
		for (int i = 0; i < temp.totalDoctors; i++) {
			cout << "The doctor is: " << temp.docPtr[i]->available << endl;
		}
	}
	void viewPatientData() {
		Patient temp;
		int ct = 0;
		while (temp.patPtr[ct] != NULL && ct < temp.totalPatients) {
			cout << "The Patient's name is: " << temp.patPtr[ct]->name << endl;
			cout << "Patient's age: " << temp.patPtr[ct]->age << endl;
			cout << "Patient's CNIC: " << temp.patPtr[ct]->cnic << endl;
			ct++;
		}
	}
	void viewDoctorAppointments() {
		Doctor temp;
		int ct = 0;
		while (temp.docAppointments != NULL && ct < temp.sizeDocAppointments)
			cout << temp.docAppointments[ct++] << endl;
	}
	void editDoctorAppointments() {
		char decision;
		cout << "Do you want to Cancel or Book an Appointment? (B/C)" << endl;
		cin >> decision;
		Doctor temp;
		if (decision == 'B' || decision == 'b') {
			int newsize = temp.sizeDocAppointments + 1;
			Appointment* apptemp = new Appointment[newsize];
			for (int i = 0; i < newsize - 1; i++) {
				apptemp[i] = temp.docAppointments[i];
			}
			string dt, tm;
			cout << "At what date do you want to set appointment? (MM-DD-YYYY)" << endl;
			cin >> dt;
			cout << "At what time do you want to set appointment? (HH-MM)" << endl;
			cin >> tm;
			apptemp[newsize - 1].dateTime.date = dt;
			apptemp[newsize - 1].dateTime.time = tm;
			apptemp[newsize - 1].payment;// = payment;
			delete[] temp.docAppointments;
			temp.docAppointments = new Appointment[newsize];
			for (int a = 0; a < newsize; a++) {
				temp.docAppointments[a] = apptemp[a];
			}
		}
		else if (decision == 'C' || decision == 'c') {
			string dt2;
			cout << "At what date did you book an appointment? (MM-DD-YYYY)" << endl;
			cin >> dt2;
			int ct = 0;
			while (temp.docAppointments != NULL && ct < temp.sizeDocAppointments) {
				if (temp.docAppointments[ct++].dateTime.date == dt2) {
					temp.sizeDocAppointments--;
					for (int b = ct; b < temp.sizeDocAppointments; b++) {
						temp.docAppointments[b] = temp.docAppointments[b + 1];
					}
				}
			}
		}
		else {
			while (decision != 'b' && decision != 'B' && decision != 'c' && decision != 'C') {
				cout << "Wrong choice! Enter again!" << endl;
				cin >> decision;
			}
		}
	}
	void printAdmin() {
		cout << "The admin username: " << this->username << endl;
		cout << "The Password: " << this->password << endl;
	}
};


class olaDoc {
	User* user;
public:
	olaDoc() :user(new User) { firstScreenDisplay(); }
	void firstScreenDisplay() {
		system("CLS");
		cout << "				................................................" << endl;
		cout << "				.              Welcome to OlaDoc               ." << endl;
		cout << "				.         By Muhammad Affan (21i-0474)         ." << endl;
		cout << "				................................................" << endl;
		cout << "				.      Press 'A' if you are an Admin           ." << endl;
		cout << "				.      Press 'B' if you are a Doctor           ." << endl;
		cout << "				.      Press 'C' if you are a Patient          ." << endl;
		cout << "				................................................" << endl;
		cout << endl << endl;
		char choice;
		cin >> choice;
		if (choice == 'a' || choice == 'A') {
			adminInitialPortal(); // Admin Initial Portal
		}
		else if (choice == 'b' || choice == 'B') {
			doctorInitialPortal();  // Doctor Initial Portal
		}
		else if (choice == 'c' || choice == 'C') {
			patientInitialPortal();  // Patient Initial Portal
		}
	}
	void adminInitialPortal() {
		system("CLS");
		cout << "				................................................" << endl;
		cout << "				.           Welcome to Admin Portal            ." << endl;
		cout << "				.                  in OlaDoc                   ." << endl;
		cout << "				.         By Muhammad Affan (21i-0474)         ." << endl;
		cout << "				................................................" << endl;
		cout << "				.      Press 'A' to Login                      ." << endl;
		cout << "				.      Press 'B' to look for Admin Info        ." << endl;
		cout << "				................................................" << endl;
		cout << endl << endl;
		char choice;
		cin >> choice;
		if (choice == 'a' || choice == 'A') {
			adminLoginPortal();  // Admin Login
		}
		else if (choice == 'b' || choice == 'B') {
			adminInfo();  // Admin general Information
			system("pause");
			firstScreenDisplay();
		}
	}
	void adminInfo() {
		Admin a;
		a.printAdmin();
	}
	void doctorInitialPortal() {
		system("CLS");
		cout << "				................................................" << endl;
		cout << "				.           Welcome to Doctor Portal           ." << endl;
		cout << "				.                 in OlaDoc                    ." << endl;
		cout << "				.         By Muhammad Affan (21i-0474)         ." << endl;
		cout << "				................................................" << endl;
		cout << "				.      Press 'A' to Register                   ." << endl;
		cout << "				.      Press 'B' to Login                      ." << endl;
		cout << "				................................................" << endl;
		cout << endl << endl;
		char choice;
		cin >> choice;
		if (choice == 'a' || choice == 'A') {
			doctorRegisterationPortal(); // Doctor Registration Portal
		}
		else if (choice == 'b' || choice == 'B') {
			doctorLoginPortal();        // Doctor Login Portal
		}
	}
	void patientInitialPortal() {
		system("CLS");
		cout << "				................................................" << endl;
		cout << "				.          Welcome to Patient Portal           ." << endl;
		cout << "				.                 in OlaDoc                    ." << endl;
		cout << "				.         By Muhammad Affan (21i-0474)         ." << endl;
		cout << "				................................................" << endl;
		cout << "				.      Press 'A' to Register                   ." << endl;
		cout << "				.      Press 'B' to Login                      ." << endl;
		cout << "				................................................" << endl;
		cout << endl << endl;
		char choice;
		cin >> choice;
		if (choice == 'a' || choice == 'A') {
			patientRegisterationPortal();    // Patient Registration Portal
		}
		else if (choice == 'b' || choice == 'B') {
			patientLoginPortal();           // Patient Login Portal
		}
	}
	void doctorRegisterationPortal() {
		system("CLS");
		cout << "				................................................" << endl;
		cout << "				.    Welcome to Doctor Registration Portal     ." << endl;
		cout << "				.                  in OlaDoc                   ." << endl;
		cout << "				.         By Muhammad Affan (21i-0474)         ." << endl;
		cout << "				................................................" << endl;
		cout << "				.  **Please go through simple steps in order   ." << endl;
		cout << "				.            to Register, Thanks!**            ." << endl;
		cout << "				................................................" << endl;
		cout << endl << endl;
		
		//.........Asking Doctor about profession to create instance of that class............................
		cout << "Please tell us about your profession: " << endl;
		string p;
		cout << "Are you a Gynecologist?\nAre you a Dermatologist?\nAre you an Oncologist?\nAre you an Orthopedic?\n";
		cin >> p;
		int foundLocation;
		if (p == "Gynecologist" || p == "gynecologist") {
			Gynecologist gt;
			foundLocation = gt.Register();
			if (foundLocation == -1)     // -1 means registration failed, the doctor already registered
					doctorLoginPortal();    // Calling Doctor Login Portal.
			else {
				cout << "Doctor Registration successful!" << endl;
				system("pause");
				doctorPortal(foundLocation);
			}
		}
		else if (p == "Dermatologist" || p == "dermatologist") {
			Dermatologist dmt;
			foundLocation = dmt.Register();
			if (foundLocation == -1)   // -1 means registration failed, the doctor already registered
				doctorLoginPortal();    // Calling Doctor Login Portal.
			else {
				cout << "Doctor Registration successful!" << endl;
				system("pause");
				doctorPortal(foundLocation);
			}
		}
		else if (p == "Oncologist" || p == "oncologist") {
			Oncologist onc;
			foundLocation = onc.Register();
			if (foundLocation == -1)   // -1 means registration failed, the doctor already registered
				doctorLoginPortal();    // Calling Doctor Login Portal.
			else {
				cout << "Doctor Registration susccessful!" << endl;
				system("pause");
				doctorPortal(foundLocation);
			}
		}
		else if (p == "Orthopedic" || p == "orthopedic") {
			Orthopedic ort;
			foundLocation = ort.Register();
			if (foundLocation == -1)   // -1 means registration failed, the doctor already registered
				doctorLoginPortal();    // Calling Doctor Login Portal.
			else {
				cout << "Doctor Registration susccessful!" << endl;
				system("pause");
				doctorPortal(foundLocation);
			}
		}
	}
	void patientRegisterationPortal() {
		system("CLS");
		cout << "				................................................" << endl;
		cout << "				.    Welcome to Patient Registration Portal    ." << endl;
		cout << "				.                  in OlaDoc                   ." << endl;
		cout << "				.         By Muhammad Affan (21i-0474)         ." << endl;
		cout << "				................................................" << endl;
		cout << "				.  **Please go through simple steps in order   ." << endl;
		cout << "				.            to Register, Thanks!**            ." << endl;
		cout << "				................................................" << endl;
		cout << endl << endl;
		Patient p;
		int foundLocation = p.Register();
		if (foundLocation == -1)   // -1 means registration failed, the patient already registered
			patientLoginPortal();    // Calling Patient Login Portal.
		else {
			cout << "Patient Registration susccessful!" << endl;
			system("pause");
			patientPortal(foundLocation);
		}
	}
	void adminLoginPortal() {

		system("CLS");
		cout << "				................................................" << endl;
		cout << "				.        Welcome to Admin Login Portal         ." << endl;
		cout << "				.                  in OlaDoc                   ." << endl;
		cout << "				.         By Muhammad Affan (21i-0474)         ." << endl;
		cout << "				................................................" << endl;
		cout << "				.  **You will need to Verify your credentials  ." << endl;
		cout << "				.             before you may begin**           ." << endl;
		cout << "				................................................" << endl;
		cout << endl << endl;

		//.........Creating Admin temp and calling Login method through it..........
		Admin tmp;
		int foundLocation = tmp.Login();
		system("pause");
		adminPortal();  // calling Admin Portal
	}
	void patientLoginPortal() {
		system("CLS");
		cout << "				................................................" << endl;
		cout << "				.        Welcome to Patient Login Portal       ." << endl;
		cout << "				.                  in OlaDoc                   ." << endl;
		cout << "				.         By Muhammad Affan (21i-0474)         ." << endl;
		cout << "				................................................" << endl;
		cout << "				.  **You will need to Verify your credentials  ." << endl;
		cout << "				.             before you may begin**           ." << endl;
		cout << "				................................................" << endl;
		cout << endl << endl;

		//.........Creating Patient temp and storing found index of Patient from patPtr......
		Patient tmp;
		int foundLocation = tmp.Login();
		if (foundLocation == -1) {       // -1 means Login failed, No Patient with that cnic found.
			patientRegisterationPortal();  // calling Patient Registration Portal.
		}
		else {
			system("pause");
			patientPortal(foundLocation);  // calling Patient Portal and providing index of that found patient as parameter.
		}
	}
	void doctorLoginPortal() {
		system("CLS");
		cout << "				................................................" << endl;
		cout << "				.        Welcome to Doctor Login Portal        ." << endl;
		cout << "				.                  in OlaDoc                   ." << endl;
		cout << "				.         By Muhammad Affan (21i-0474)         ." << endl;
		cout << "				................................................" << endl;
		cout << "				.  **You will need to Verify your credentials  ." << endl;
		cout << "				.             before you may begin**           ." << endl;
		cout << "				................................................" << endl;
		cout << endl << endl;
		
		
		//.........Creating Doctor temp and storing found index of Doctor from docPtr......
		Doctor tmp;
		int foundLocation = tmp.Login();
		if (foundLocation == -1) {       // -1 means Login failed, No doctor with that cnic found.
			doctorRegisterationPortal();  // calling Doctor Registration Portal.
		}
		else {
			system("pause");
			doctorPortal(foundLocation);  // calling Doctor Portal and providing index of that found doctor as parameter.
		}
	}
	void doctorPortal(int foundDoctorLocation) {
		system("CLS");
		cout << "				..................................................." << endl;
		cout << "				.          Welcome to Doctor Portal               ." << endl;
		cout << "				.                  in OlaDoc                      ." << endl;
		cout << "				.         By Muhammad Affan (21i-0474)            ." << endl;
		cout << "				..................................................." << endl;
		cout << "				.    Press 'A' to view Appointment Data           ." << endl;
		cout << "				.    Press 'B' to set Appointment Status          ." << endl;
		cout << "				.    Press 'C' to view Appointment Patient Details." << endl;
		cout << "				.    Press 'D' to change Timings                  ." << endl;
		cout << "				.    Press 'E' to change Location                 ." << endl;
		cout << "				.    Press 'F' to change Rates                    ." << endl;
		cout << "				..................................................." << endl;
		cout << endl << endl;
		char choice;
		cin >> choice;


		//................Using Doctor d to call Doctor's methods.......................
		Doctor d;
		if (choice == 'a' || choice == 'A') {
			d.viewAppointmentData(foundDoctorLocation);    // Calling View Appointment Data in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'b' || choice == 'B') {
			d.setAppointmentStatus(foundDoctorLocation);           // Calling Set Appointment Status in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'c' || choice == 'C') {
			d.viewAppointmentPatientDetails(foundDoctorLocation);   // Calling View Appointment Patient Details in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'd' || choice == 'D') {
			d.changeTimings(foundDoctorLocation);             // Calling Change Timings in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'e' || choice == 'E') {
			d.changeLocation(foundDoctorLocation);              // Calling Change Location in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'f' || choice == 'F') {
			d.changeRates(foundDoctorLocation);              // Calling Change Rates in Doctor class
			system("pause");
			firstScreenDisplay();
		}
	}
	void adminPortal() {
		system("CLS");
		cout << "				..................................................." << endl;
		cout << "				.          Welcome to Admin Portal                ." << endl;
		cout << "				.                  in OlaDoc                      ." << endl;
		cout << "				.         By Muhammad Affan (21i-0474)            ." << endl;
		cout << "				..................................................." << endl;
		cout << "				.    Press 'A' to view Doctor Data                ." << endl;
		cout << "				.    Press 'B' edit Doctor Data                   ." << endl;
		cout << "				.    Press 'C' check Doctor Availability          ." << endl;
		cout << "				.    Press 'D' view Patient Data                  ." << endl;
		cout << "				.    Press 'E' view Doctor Appointments           ." << endl;
		cout << "				.    Press 'F' edit Doctor Appointments           ." << endl;
		cout << "				..................................................." << endl;
		cout << endl << endl;
		char choice;
		cin >> choice;

		Admin a;
		if (choice == 'a' || choice == 'A') {
			a.viewDoctorData();    // Calling View Appointment Data in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'b' || choice == 'B') {
			a.editDoctorData();           // Calling Set Appointment Status in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'c' || choice == 'C') {
			a.checkDoctorAvailability();   // Calling View Appointment Patient Details in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'd' || choice == 'D') {
			a.viewPatientData();             // Calling Change Timings in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'e' || choice == 'E') {
			a.viewDoctorAppointments();              // Calling Change Location in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'f' || choice == 'F') {
			a.editDoctorAppointments();              // Calling Change Rates in Doctor class
			system("pause");
			firstScreenDisplay();
		}
	}
	void patientPortal(int foundPatientLocation) {
		system("CLS");
		cout << "				......................................................" << endl;
		cout << "				.          Welcome to Patient Portal                 ." << endl;
		cout << "				.                  in OlaDoc                         ." << endl;
		cout << "				.         By Muhammad Affan (21i-0474)               ." << endl;
		cout << "				......................................................" << endl;
		cout << "				.    Press 'A' to reset password                     ." << endl;
		cout << "				.    Press 'B' to search Doctor By Speciality        ." << endl;
		cout << "				.    Press 'C' to search Doctor By Area              ." << endl;
		cout << "				.    Press 'D' to search Doctor By Hospital          ." << endl;
		cout << "				.    Press 'E' to check Doctor Availability          ." << endl;
		cout << "				.    Press 'F' to check Doctor Charges               ." << endl;
		cout << "				.    Press 'G' to book In-Person Appointment         ." << endl;
		cout << "				.    Press 'H' to cancel In-Person Appointment       ." << endl;
		cout << "				.    Press 'I' to book Video Appointment             ." << endl;
		cout << "				.    Press 'J' to cancel Video Appointment           ." << endl;
		cout << "				.    Press 'K' to change Appointment Time            ." << endl;
		cout << "				.    Press 'L' to change Name                        ." << endl;
		cout << "				.    Press 'M' to change CNIC                        ." << endl;
		cout << "				.    Press 'N' to change Phone Number                ." << endl;
		cout << "				.    Press 'O' to change Age                         ." << endl;
		cout << "				.    Press 'P' to check All Appointments             ." << endl;
		cout << "				.    Press 'Q' to recharge Account                   ." << endl;
		cout << "				......................................................" << endl;
		cout << endl << endl;
		char choice;
		cin >> choice;


		//................Using Doctor d to call Doctor's methods.......................
		Patient p;
		if (choice == 'a' || choice == 'A') {
			p.ResetPassword(foundPatientLocation);    // Calling View Appointment Data in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'b' || choice == 'B') {
			p.searchDoctorBySpeciality();           // Calling Set Appointment Status in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'c' || choice == 'C') {
			p.searchDoctorByArea();   // Calling View Appointment Patient Details in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'd' || choice == 'D') {
			p.searchDoctorByHospital();             // Calling Change Timings in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'e' || choice == 'E') {
			p.checkDoctorAvailability();              // Calling Change Location in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'f' || choice == 'F') {
			p.checkDoctorCharges();              // Calling Change Rates in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'g' || choice == 'G') {
			p.bookInPersonAppointment(foundPatientLocation);           // Calling Set Appointment Status in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'h' || choice == 'H') {
			p.cancelInPersonAppointment(foundPatientLocation);   // Calling View Appointment Patient Details in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'i' || choice == 'I') {
			p.bookVideoAppointment(foundPatientLocation);             // Calling Change Timings in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'j' || choice == 'J') {
			p.cancelVideoAppointment(foundPatientLocation);              // Calling Change Location in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'k' || choice == 'K') {
			p.changeAppointmentTime(foundPatientLocation);              // Calling Change Rates in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'l' || choice == 'L') {
			p.changeName(foundPatientLocation);           // Calling Set Appointment Status in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'm' || choice == 'M') {
			p.changeCNIC(foundPatientLocation);   // Calling View Appointment Patient Details in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'n' || choice == 'N') {
			p.changePhoneNumber(foundPatientLocation);             // Calling Change Timings in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'o' || choice == 'O') {
			p.changeAge(foundPatientLocation);              // Calling Change Location in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'p' || choice == 'P') {
			p.checkAllAppointments(foundPatientLocation);              // Calling Change Rates in Doctor class
			system("pause");
			firstScreenDisplay();
		}
		else if (choice == 'q' || choice == 'Q') {
			p.rechargeAccount(foundPatientLocation);              // Calling Change Rates in Doctor class
			system("pause");
			firstScreenDisplay();
		}
	}
};


int main() {
	olaDoc mainTerminal;

	return 0;
}