#include<iostream>
#include<iomanip>
#include<fstream>
#include <windows.h>
#include<cstring>
#include<conio.h>
#include<stdio.h>
using namespace std;
int emp_no=0;
int switch_count=-1;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
void color(int co)
{
	SetConsoleTextAttribute(console,co);
}
COORD coord;
gotoxy(int x,int y)
{
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(console,coord);
}
void delete_que()
{
	cout<<endl<<endl<<setw(94);
	color(8);cout<<"Are you sure you want to delete this entry ? (";
	color(12);cout<<"Y";color(8);cout<<" / ";color(2);cout<<"N";color(8);
	cout<<") :: ";color(14);
}
void line_end(int i)
{
	for(int j=0;j<i;j++)
		cout<<endl;
}
void invalid_input()
{
	color(12);
	cout<<endl;
	cout<<setw(92)<<"::::::::::::::::::::::::"<<endl;
	cout<<setw(87)<<"Invalid input"<<endl;
	cout<<setw(92)<<"::::::::::::::::::::::::"<<endl;
}
void pause()
{
	line_end(3);
	cout<<setw(65);
	cout<<" ";
	color(207);
	cout<<"                                   ";
	cout<<endl;
	color(3);
	cout<<setw(65);
	cout<<" ";
	color(207);
	cout<<"   ENTER ANY KEY TO CONTINUE ...   ";
	cout<<endl;
	color(3);
	cout<<setw(65);
	cout<<" ";
	color(207);
	cout<<"                                   ";
	getch();
}
class employee
{
	char empname[50], emp_code[10], emp_num[10];
	long emp_sal;
 public:
	static long ts;
	employee()
	{
		strcpy(empname,"no-name");
		strcpy(emp_code,"no-code");
		emp_sal=0;
	}
	void emp_input(employee emp[]);
	void emp_modify(employee emp[]);
	void emp_display();
	void emp_read();
	void totalsal()
	{
		ts=ts+emp_sal;
	}
	void sal_display()
	{
		cout<<endl<<endl<<setw(100)<<"TOTAL MONTHLY SALARIES OF ALL THE EMPLOYEES :: "<<ts;
		cout<<endl<<endl;
	}
	string num()
	{
		return emp_code;
	}
	void tsreset()
	{
		ts=0;
	}
};
long employee::ts=0;
void emp_swi(char i)
{
	switch_count++;
	fstream file1,file2;
	file1.open("employee.txt",ios::in|ios::app);
	employee emp[emp_no+1],temp;
	file2.open("emp_number.txt",ios::app|ios::in);
	file2>>emp_no;
	file2.close();
	if(switch_count==0)
	{
		for(int j=0;j<emp_no;j++)
		{
			file1.read((char *)&emp[j],sizeof(employee));
			emp[j].totalsal();
		}
	}
	fstream file3;
	file3.open("emp_number.txt",ios::out|ios::in);
	switch(i)
	{
		case '1':{
			file1.seekg(0);
			system("cls");
			if(emp_no==0)
			{
				line_end(10);
				color(4);
				cout<<setw(92)<<"::::::::::::::::::::::::"<<endl;
				cout<<setw(87)<<"NO EMPLOYEES"<<endl;
				cout<<setw(92)<<"::::::::::::::::::::::::"<<endl;
				line_end(5);
			}
			else
			{
				for(int i=0;i<emp_no;i++)
				{	
					file1.read((char *)&emp[i],sizeof(employee));
					emp[i].emp_display();
				}	
				emp[emp_no+1].sal_display();
			}
			file1.close();
			pause();
			break;
		}
		case '2':{
			emp[0].emp_input(emp);
			file1.write((char *)&emp[0],sizeof(employee));			
			emp_no=emp_no+1;
			file3<<emp_no;
			switch_count=-1;
			emp[0].ts=0;
			file1.close();
			pause();
			break;
		}
		case '3':{
			file1.close();
			ifstream fi4("employee.txt",ios::in);
			ofstream fi5("temp.txt",ios::out);
			string mod;
			do{
				system("cls");
				cout<<endl;
				color(10);
				line_end(5);
				cout<<setw(110)<<"Enter 'A' to see the list of all stocks."<<endl<<endl;
				cout<<setw(120)<<"Enter the stock's number whose profile is to be modified :: ";
				color(14);
				cin>>ws;
				cin>>mod;
				if(mod=="a"||mod=="A")
				{
					system("cls");
					fstream fi;
					fi.open("employee.txt",ios::in|ios::app);
					fi.seekg(0);
					if(emp_no==0)
					{
						line_end(10);
						color(4);
						cout<<setw(92)<<"::::::::::::::::::::::::"<<endl;
						cout<<setw(87)<<"NO EMPLOYEES"<<endl;
						cout<<setw(92)<<"::::::::::::::::::::::::"<<endl;
						line_end(5);
					}
					else
						for(int i=0;i<emp_no;i++)
						{	
							fi.read((char *)&emp[i],sizeof(emp[i]));
							emp[i].emp_display();
						}
					fi.close();
					pause();
				}
			}while(mod=="a"||mod=="A");
			int cnt=emp_no;
			while(!fi4.eof() && cnt!=0)
			{
				cnt--;
				fi4.read((char*)&temp,sizeof(temp));
				if(temp.num()==mod)
				{
					system("cls");
					color(4);
					line_end(2);
					cout<<setw(100)<<"ENTER '999' TO RETAIN THE ORIGINAL INPUT.";
					temp.emp_display();
					temp.emp_modify(emp);
					fi5.write((char *)&temp,sizeof(temp));
				}
				else
				{
					fi5.write((char*)&temp,sizeof(temp));
				}
			}
			fi4.close();
			fi5.close();
			temp.tsreset();
			switch_count=-1;
			remove("employee.txt");
			rename("temp.txt","employee.txt");
			pause();
			break;
		}
		case '4':{
			file1.close();
			ifstream file4("employee.txt",ios::in);
			ofstream file5("temp.txt",ios::out);
			string del;
			do{
				system("cls");
				color(10);
				cout<<endl;
				cout<<setw(110)<<"Enter 'A' to see the list of all employees."<<endl<<endl;
				cout<<setw(120)<<"Enter the employee's number whose profile is to be deleted :: ";
				color(14);
				cin>>ws;
				cin>>del;
				if(del=="a"||del=="A")
				{
					system("cls");
					fstream fi;
					fi.open("employee.txt",ios::in|ios::app);
					fi.seekg(0);
					line_end(2);
					if(emp_no==0)
					{
						line_end(10);
						color(4);
						cout<<setw(92)<<"::::::::::::::::::::::::"<<endl;
						cout<<setw(87)<<"NO EMPLOYEES"<<endl;
						cout<<setw(92)<<"::::::::::::::::::::::::"<<endl;
						line_end(5);
					}
					else
						for(int i=0;i<emp_no;i++)
						{	
							fi.read((char *)&emp[i],sizeof(employee));
							emp[i].emp_display();
						}
					fi.close();
					pause();
				}
			}while(del=="A"||del=="a");
			int count=emp_no;
			while(!file4.eof() && count!=0)
			{
				count--;
				file4.read((char*)&temp,sizeof(temp));
				if(temp.num()==del)
				{
					cout<<endl<<endl;
					temp.emp_display();
					char ch;
					delete_que();
					ch=getche();
					if(ch=='Y'||ch=='y')
					{
						emp_no=emp_no-1;
						file3<<emp_no;
						system("CLS");
						line_end(10);
						color(4);
						cout<<setw(92)<<"::::::::::::::::::::::::"<<endl;
						cout<<setw(87)<<"ENTRY DELETED"<<endl;
						cout<<setw(92)<<"::::::::::::::::::::::::"<<endl;
						line_end(5);
					}
					else
						file5.write((char*)&temp,sizeof(temp));
				}
				else
				{
					file5.write((char*)&temp,sizeof(temp));
				}
			}
			file4.close();
			file5.close();
			temp.tsreset();
			switch_count=-1;
			remove("employee.txt");
			rename("temp.txt","employee.txt");
			pause();
			break;
		}
	}
	file3.close();	
	cout<<endl;
}
int emp_det()
{
	char i;
	bool check=true;
	system("cls");
	cout<<endl<<endl;
	color(10);
	cout<<setw(110)<<":::::::::::::::::::::::::::::MENU:::::::::::::::::::::::::::::";
	cout<<endl<<endl<<setw(87)<<"1. EMPLOYEE LIST";
	cout<<endl<<endl<<setw(86)<<"2. ADD EMPLOYEE";
	cout<<endl<<endl<<setw(88)<<"3. MODIFY DETAILS";
	color(12);
	cout<<endl<<endl<<setw(89)<<"4. DELETE EMPLOYEE";
	color(10);
	cout<<endl<<endl<<setw(79)<<"5. \tEXIT"<<endl<<endl;
	cout<<setw(94)<<"::::::::::::::::::::::::::::::"<<endl;
	cout<<endl<<setw(90)<<"ENTER YOUR ANSWER :: ";
	color(14);
	i=getche();
	if(i=='1'||i=='2'||i=='3'||i=='4'||i=='5')
		emp_swi(i);
	else
		emp_det();
}
void employee::emp_input(employee emp[])
{
	system("cls");
	cout<<endl<<endl;
	color(10);
	cout<<setw(110)<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::";
	bool check=true;
	fstream file1;
	file1.open("employee.txt",ios::in|ios::app);
	file1.seekg(0);
	for(int i=0;i<emp_no;i++)
		file1.read((char *)&emp[i],sizeof(employee));
	file1.close();
	cout<<endl<<endl<<setw(90);
	cout<<"Enter the name of employee :: ";
	color(14);
	cin>>ws;
	cin.get(empname,50);
	char num[10];
	do
	{
		cout<<endl<<setw(90);
		color(10);
		cout<<"Enter the employee code :: ";
		color(14);
		cin>>ws;
		if(!(cin>>num))
		{
			cin.clear();
			while(cin.get()!='\n');
			check=false;
		}
		else
		{
			check=true;
			for(int i=0;i<emp_no;i++)
			{	
				if(emp[i].num()==num)
				{
					check=false;
					break;
				}
				else
					check=true;
			}
		}
		if(check==false)
			invalid_input();
	}while(check==false);
	strcpy(emp_code,num);
	do{
		cout<<endl<<setw(90);
		color(10);
		cout<<"Enter the salary of employee :: ";
		color(14);
		if(!(cin>>emp_sal))
		{
			cin.clear();
			while(cin.get()!='\n');
			check=false;
		}
		else
		{
			if(emp_sal<=0)
			{
				check=false;
				break;
			}
			else
			check=true;
		}
		if(check==false)
			invalid_input();
	}while(check==false);
	do{
		cout<<endl<<setw(90);
		color(10);
		cout<<"Enter the phone number of employee :: ";
		color(14);
		cin>>ws;
		cin>>emp_num;
		if(strlen(emp_num)!=10)
			check=false;
		else 
			check=true;
		if(check==false)
			invalid_input();
	}while(check==false);

	color(10);
	cout<<endl;
	cout<<setw(110)<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::";
}
void employee::emp_display()
{
	color(10);
	line_end(2);
	cout<<setw(110)<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::";

	cout<<endl<<endl<<setw(90);
	color(10);
	cout<<"The name of employee is :: ";
	color(14);
	cout<<empname;
	
	cout<<endl<<endl<<setw(90);
	color(10);
	cout<<"The employee code is :: ";
	color(14);
	cout<<emp_code;
	
	cout<<endl<<endl<<setw(90);
	color(10);
	cout<<"The salary of employee is :: ";
	color(14);
	cout<<emp_sal;
	
	cout<<endl<<endl<<setw(90);
	color(10);
	cout<<"The phone number of employee :: ";
	color(14);
	cout<<emp_num;

	cout<<endl<<endl;
	color(10);
	cout<<setw(110)<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::";
	
	cout<<endl;
}
void employee::emp_modify(employee emp[])
{
	cout<<endl<<endl;
	char temp[50];
	int temp_int;
	color(10);
	line_end(4);
	cout<<setw(110)<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::";
	bool check=true;
	fstream file1;
	file1.open("employee.txt",ios::in|ios::app);
	file1.seekg(0);
	for(int i=0;i<emp_no;i++)
	{	
		file1.read((char *)&emp[i],sizeof(employee));
	}
	file1.close();
	cout<<endl<<endl<<setw(90);
	cout<<"Enter the name of employee :: ";
	color(14);
	cin>>ws;
	cin.get(temp,50);
	if(strcmp(temp,"999"))
		strcpy(empname,temp);
	int num;
	cout<<endl<<setw(90);
	color(12);
	cout<<"Enter the employee code :: ";
	cout<<emp_code<<"\t(UNCHANGABLE)"<<endl;;
	do{
		cout<<endl<<setw(90);
		color(10);
		cout<<"Enter the salary of employee :: ";
		color(14);
		if(!(cin>>num))
		{
			cin.clear();
			while(cin.get()!='\n');
			check=false;
		}
		else
			if(num<=0)
			{
				check=false;
				break;
			}
			else
			check=true;
		if(check==false)
			invalid_input();
	}while(check==false);
	if(num!=999)
		emp_sal=num;

	do{
		cout<<endl<<setw(90);
		color(10);
		cout<<"Enter the phone number of employee :: ";
		color(14);
		cin>>ws;
		cin>>temp;
		if(strlen(temp)==10)
			check=true;
		else if(strcmp(temp,"999"))
			check=true;
		else
			check=false;
		if(check==false)
			invalid_input();
	}while(check==false);
	if(strcmp(temp,"999"))
		strcpy(emp_num,temp);
	color(10);
	cout<<endl;
	cout<<setw(110)<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::";
}
