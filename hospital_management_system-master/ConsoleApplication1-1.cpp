#include<iostream>
#include<conio.h>
#include<fstream>
#include<Windows.h>
#include<string>

using namespace std;
fstream fp;
int recount = 0;

class password
{
	string code;
public:
	void get_password();
	int verify_password(string);
};
void password::get_password()
{
	cout << " HOSPITAL MANAGEMENT SYSTEM\n";
	cout << "\nSet A Password For Your System :";
START:
	code.clear();
	char ch;
	int count = 0;
	ch = _getch();
	while (ch != 13)
	{
		if (ch == 8)
		{
			cout << "\b \b";
			code.pop_back();
		}
		if (ch != 8)
		{
			cout << "*";
			code.push_back(ch);
		}
		ch = _getch();
		count++;
	}
	if (count > 13)
	{
		cout << "\n\nYour Password Should Have Maximum Of 13 Characters\n";
		cout << "\n Set A Password For Your System:";
		goto START;
	}
	if (count < 5)
	{
		cout << "\n\nYour Password Should Have Minimum Of 5 Characters\n";
		cout << "\n Set A Password For Your System :";
		goto START;
	}
}
int password::verify_password(string pass)
{
	if (pass == code)
		return(1);
}
class doctor
{
	char id[50];
	int code;
	char name[50];
	char age[10];
	char qualification[10];
	char specialization[10];
	char experience[10];
	char state[50];
	char city[50];
public:
	void pack(char[]);
	void unpack(char[]);
	void display();
	void insrec();
	void delrec();
	int search(char[]);
};

struct memindex
{
	char key[15];
	int offset;
};

memindex index[10];

void doctor::pack(char buffer[])
{
	cout << "Enter Doctor's ID:";
	cin >> id;
	strcpy(buffer, id);
	strcat(buffer, "|");
	cout << "Enter Doctor's Name:";
	cin >> name;
	strcat(buffer, name);
	strcat(buffer, "|");
	cout << "Enter Doctor's Age:";
	cin >> age;
	strcat(buffer, age);
	strcat(buffer, "|");
	cout << "Enter Doctor's Qualification:";
	cin >> qualification;
	strcat(buffer, qualification);
	strcat(buffer, "|");
	cout << "Enter Doctor's Specialization:";
	cin >> specialization;
	strcat(buffer, specialization);
	strcat(buffer, "|");
	cout << "Enter Doctor's Experience:";
	cin >> experience;
	strcat(buffer, experience);
	strcat(buffer, "|");
	cout << "Enter Doctor's State:";
	cin >> state;
	strcat(buffer, state);
	strcat(buffer, "|");
	cout << "Enter Doctor's City:";
	cin >> city;
	strcat(buffer, city);
}

void doctor::insrec()
{
	char buffer[100], tem[100];
	int i, j, pos;
	char *id;
	fp.open("doctor.txt", ios::out | ios::ate);
	pack(buffer);
	strcpy(tem, buffer);
	id = strtok(tem, "|");
	pos = search(id);
	if (pos != 0)
	{
		cout << "ID already Exists \n" << endl;
		fp.close();
		return;
	}
	recount++;
	strcpy(index[recount].key,id);
	index[recount].offset = fp.tellg();
	fp << buffer;
	fp << "\n";
	memindex temp;

	for (i = 1; i<recount; i++)
	{
		for (j = 1; j<recount; j++)
		{
			if (strcmp(index[j].key, index[j + 1].key)>0)
			{
				strcpy(temp.key, index[j].key);
				temp.offset = index[j].offset;

				strcpy(index[j].key, index[j + 1].key);
				index[j].offset = index[j + 1].offset;

				strcpy(index[j + 1].key, temp.key);
				index[j + 1].offset = temp.offset;
			}
		}
	}
	fp.close();

}

void doctor::display()
{
	char buffer[50];
	int i, j;
	if (recount == 0)
	{
		cout << "No Records to Display" << endl;
		return;
	}
	cout << "\t---------------" << endl;
	cout << "\t Primary index" << endl;
	cout << "\t---------------" << endl;
	cout << "\t key\t" << "offset" << endl;
	cout << "\t---------------" << endl;
	for (i = 1; i <= recount; i++)
	{
		cout << "\t" << index[i].key << "\t" << index[i].offset << endl;
	}
	cout << "File Contents are" << endl;
	fp.open("doctor.txt", ios::in);
	for (i = 1; i <= recount; i++)
	{
		fp.seekg(index[i].offset, ios::beg);
		fp >> buffer;
		unpack(buffer);
		cout << endl;
	}
	fp.close();


}

void doctor::delrec()
{
	char usn[15];
	int pos;
	fp.open("doctor.txt", ios::out | ios::ate);
	cout << "\nEnter the USN:";
	cin >> usn;
	pos = search(usn);
	if (pos == 0)
	{
		cout << "\nRecord not found";
		return;
	}
	fp.seekg(index[pos].offset, ios::beg);
	fp << "*";
	fp.close();
	for (int i = pos; i<recount; i++)
	{
		strcpy(index[i].key, index[i + 1].key);
		index[i].offset = index[i + 1].offset;
	}
	cout << "Record Deleted Successfully" << endl;
	recount--;


}

int doctor::search(char id[])
{
	int low = 1, high = recount, mid;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (strcmp(index[mid].key, id) == 0)
			return mid;
		if (strcmp(index[mid].key, id)>0)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return 0;

}

void doctor::unpack(char buffer[])
{
	char *t;
	t = strtok(buffer, "|");
	cout << "Doctor's ID:" << t << endl;
	t = strtok(NULL, "|");
	cout << "Doctor's Name:" << t << endl;
	t = strtok(NULL, "|");
	cout << "Doctor's Age:" << t << endl;
	t = strtok(NULL, "|");
	cout << "Doctor's Qualification:" << t << endl;
	t = strtok(NULL, "|");
	cout << "Doctor's Specialization:" << t << endl;
	t = strtok(NULL, "|");
	cout << "Doctor's Experiance:" << t << endl;
	t = strtok(NULL, "|");
	cout << "Doctor's State:" << t << endl;
	t = strtok(NULL, "|");
	cout << "Doctor's City:" << t << endl;
}

void main()
{

	int counter = 0, y = 0, pos;
	password p;
	doctor d;
	char id[10], buffer[100];
	p.get_password();
	void add_patient_data();
	void assign_patient();
	void modify_patient_data();

	void delete_patient_data();
	void delete_contents1();
	void display1();
	void report();
	void bill ();
	
	//int y = display_patient_data();
	system("CLS");
START1:
	system("CLS");
	cout << "********************************************************************************\n";
	cout << "\n\t\t HOSPITAL MANAGEMENT SYSTEM\n\n";
	cout << "********************************************************************************\n";
	cout << "\n\t\t\t\t1.Main Menu\n";
	cout << "\n\t\t\t\t2.Shut Down\n\n";
	cout << "********************************************************************************\n";
	int op, ch, count = 0, x;
	char c;
	string pass;
	cout << "\nPlease Enter Your Choice :";
	cin >> op;
	cout << "\n\n";
	system("PAUSE");
START3:
	switch (op)
	{
	case 1:
		system("CLS");
		cout << "********************************************************************************\n";
		cout << "\t\t\t\tMain Menu\n\n";
		cout << "********************************************************************************\n";
		cout << "\n\n\t\t1.Enter Into Doctor's Database\n";
		cout << "\n\t\t2.Enter into Patient's Database\n";
		cout << "\n\t\t3.Generate Patient's Report\n";
		cout << "\n\t\t4.Generate Patient's Bills\n";
		cout << "\n\t\t5.Exit\n\n";
		cout << "********************************************************************************";
		cout << "\n\n\tPlease Choose Your Choice :";
		cin >> ch;
		switch (ch)
		{
		case 1:
			system("CLS");
		START2:
			count++;
			cout << "\nPlease Enter Your Password To Enter Into This Database :";
			pass.clear();
			c = _getch();
			while (c != 13)
			{
				if (c == 8)
				{
					cout << "\b \b";
					pass.pop_back();
				}
				if (c != 8)
				{
					cout << "*";
					pass.push_back(c);
				}
				c = _getch();
			}
			x = p.verify_password(pass);
			if (x == 1)
			{
				cout << "\n\nAccess Granted ";
				cout << "\n\n";
				system("PAUSE");
				system("CLS");
				while (1)
				{
					system("CLS");
					cout << "********************************************************************************\n";
					cout << "\n\t\t\tWelcome to Doctor's Database\n";
					cout << "\n********************************************************************************\n";
					cout << "\n\t\t1.Add New Doctor's Information\n";
					cout << "\n\t\t2.Display The Doctor's Information\n";
					cout << "\n\t\t3.Display The Details Of All The Doctors\n";
					cout << "\n\t\t4.Delete The Doctor's Information\n";
					cout << "\n\t\t5.Number Of Doctors In The Hospital\n";
					cout << "\n\t\t6.Exit\n";
					cout << "\n********************************************************************************\n";
					int opt;
					cout << "Please Choose Your Choice :";
					cin >> opt;
					int y;
					switch (opt)
					{
					case 1:
						system("CLS");
						d.insrec();
						system("PAUSE");
						break;
					case 2:

						system("CLS");
						cout << "\nEnter the Doctor's ID:";
						cin >> id;
						pos = d.search(id);
						if (pos == 0)
						{
							cout << "Record not found\n";
							break;
						}
						fp.open("doctor.txt", ios::in);
						fp.seekg(index[pos].offset, ios::beg);
						fp >> buffer;
						d.unpack(buffer);
						fp.close();
						system("PAUSE");
						break;
					case 3:
						system("CLS");
						d.display();
						system("PAUSE");
						break;
					case 4:

						system("CLS");
						d.delrec();
						system("PAUSE");
						break;
					}
				}
			}
			else
			{
				if (count >= 3)
				{
					system("CLS");
					cout << "\n\nAccess Denied!!!You Have Entered Wrong Password Too Many Times\n";
					cout << "\nThis System Will Shut Down.Please Come Back Again\n";
					cout << "\nThank You\n";
					cout << "\n";
					system("PAUSE");
					exit(0);
				}
				cout << "\n\nWrong Password.Access Denied!!!\n";
				goto START2;
			}
		case 2:
			system("CLS");
		START4:
			count++;
			cout << "\nPlease Enter Your Password To Enter Into This Database :";
			pass.clear();
			c = _getch();
			while (c != 13)
			{
				if (c == 8)
				{
					cout << "\b \b";
					pass.pop_back();
				}
				if (c != 8)
				{
					cout << "*";
					pass.push_back(c);
				}
				c = _getch();
			}
			x = p.verify_password(pass);
			if (x == 1)
			{
				cout << "\n\nAccess Granted ";
				cout << "\n\n";
				system("PAUSE");
				system("CLS");
				while (1)
				{
					system("CLS");
					cout << "********************************************************************************\n";
					cout << "\n\t\t\tWelcome To Patient's Database\n\n";
					cout << "********************************************************************************\n";
					cout << "\n\t\t1.Add Patient's Information\n";
					cout << "\n\t\t2.Assign A Patient To A Doctor\n";
					cout << "\n\t\t3.Edit Patient's Information\n";
					cout << "\n\t\t4.Display Patient's Information\n";
					cout << "\n\t\t5.Delete Patient's Information\n";
					cout << "\n\t\t6.No.Of Patients In The Hospital\n";
					cout << "\n\t\t7.Delete All The Contents In The Database\n";
					cout << "\n\t\t8.Display The Details Of All The Patients In The Hospital\n";
					cout << "\n\t\t9.Exit\n\n";
					cout << "********************************************************************************\n";
					int opt;
					cout << "\nPlease Choose Your Choice :";
					cin >> opt;
					int y;
					switch (opt)
					{
					case 1:
						system("CLS");
						add_patient_data();
						break;
					case 2:
						system("CLS");
						assign_patient();
						break;
					case 3:
						system("CLS");
						modify_patient_data();
						break;
					case 4:
						system("CLS");
						y = display_patient_data();
						if (y != 1)
						{
							cout << "\nNo Record To Display!!!\n";
							cout << "\n";
							system("PAUSE");
						}
						break;
					case 5:
						system("CLS");
						delete_patient_data();
						cout << "\n";
						system("PAUSE");
						break;
					case 6:
						system("CLS");
						cout << "\nNo.Of Patient's In The Hospital are :" << number();
						cout << "\n\n";
						system("PAUSE");
						break;
					case 7:
						system("CLS");
						delete_contents1();
						cout << "\nAll The Contents Of The Database Are Deleted";
						cout << "\n\n";
						system("PAUSE");
						break;
					case 8:
						system("CLS");
						display1();
						cout << "\n\n";
						system("PAUSE");
						break;
					case 9:
						system("CLS");
						goto START3;
						_getch();
					}
				}
			}
			else
			{
				if (count >= 3)
				{
					system("CLS");
					cout << "\n\nAccess Denied!!!You Have Entered Wrong Password Too Many Times\n";
					cout << "\nThis System Will Shut Down.Please Come Back Again\n";
					cout << "\nThank You\n";
					cout << "\n";
					system("PAUSE");
					exit(0);
				}
				cout << "\n\nWrong Password.Access Denied!!!\n";
				goto START4;
			}
		case 3:
			system("CLS");
			cout << "\n\n";
			report();
			cout << "\n\n";
			system("PAUSE");
			goto START3;
			break;
		case 4:
			system("CLS");
			bill();
			cout << "\n\n";
			system("PAUSE");
			system("CLS");
			goto START3;
			break;

		case 5:
			cout << "\n";
			cout << "\n";
			goto START1;
		default:
			cout << "\nWrong Choice ";
		}
		break;
	case 2:
		cout << "\n\n";
		exit(0);
		break;
	default:
		cout << "\nWrong Choice ";
	}
	_getch();
		}
	
