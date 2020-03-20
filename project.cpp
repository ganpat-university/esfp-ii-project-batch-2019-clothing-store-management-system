#include"emp.h"
#include"start.h"
#include"stock.h"
#include"sales.h"
using namespace std;
bool END=true;
char menu()
{
	color(6);
	system("cls");
	cout<<endl<<endl;
	cout<<setw(110)<<":::::::::::::::::::::::::::::MENU:::::::::::::::::::::::::::::";
	color(10);
	cout<<endl<<endl<<setw(90)<<"1. EMPLOYEE DETAILS";
	color(13);
	cout<<endl<<endl<<setw(87)<<"2. STOCK DETAILS";
	color(3);
	cout<<endl<<endl<<setw(91)<<"3. PURCHASE REGESTER";
	color(8);
	cout<<endl<<endl<<setw(88)<<"4. SALES REGESTER";
	color(12);
	cout<<endl<<endl<<setw(81)<<"5.    QUIT"<<endl;
	color(6);
	cout<<endl<<setw(94)<<"::::::::::::::::::::::::::::::"<<endl;
	cout<<endl<<setw(90)<<"ENTER YOUR ANSWER :: ";
	color(14);
	char i=getche();
	cout<<endl;
	return i;
}
bool Quit()
{
	char check;system("cls");line_end(18);color(8);
	cout<<setw(95)<<"Are you sure you want quit ?( ";color(12);cout<<"Y";
	color(8);cout<<" / ";color(2);cout<<"N";color(8);cout<<" ):: ";
	color(14);check=getche();
	if(check=='y'||check=='Y')
	{
		return false;
	}
	else
		return true;
}
int main()
{
	start_page();
	fontsize(20,20);
	do{
		char i=menu();
		switch(i)
		{
			case '1':				//Employee Details
				emp_det();
				break;
			case '2':				//Stock Details
				see_stock();
				break;
			case '3':				//Purchase Register				
				stock_det();
				break;
			case '4':				//Sales Register 
				sales_det();
				break;			
			case '5':				//QUIT
				END=Quit();
				line_end(20);
				break;
		}			
	}while(END==true);
}	
