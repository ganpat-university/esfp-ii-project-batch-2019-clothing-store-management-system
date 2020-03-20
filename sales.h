int sale_no=0;	
class sale_reg
{
 char buyer_name[50],code[30];
 int quantity,cost;
 int date,month,year;
 public:
 	void sales_display();
 	bool sales_insert();
};
void sale_reg :: sales_display()
{
	color(8);
	line_end(2);
	cout<<setw(110)<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::";
	
	cout<<endl<<endl<<setw(92);
	color(8);
	cout<<"The name of the Buyer :: ";
	color(14);
	cout<<buyer_name;
	
	cout<<endl<<endl<<setw(92);
	color(8);
	cout<<"The code of the product :: ";
	color(14);
	cout<<code;
		
	cout<<endl<<endl<<setw(92);
	color(8);
	cout<<"The quantity of the product :: ";
	color(14);
	cout<<quantity<<" mtr.";

	cout<<endl<<endl<<setw(92);
	color(8);
	cout<<"The cost of the product :: ";
	color(14);
	cout<<cost<<" Rs";

	cout<<endl<<endl<<setw(92);
	color(8);
	cout<<"The date of sale :: ";
	color(14);
	cout<<date<<"/"<<month<<"/"<<year;

	cout<<endl;
	color(8);
	cout<<endl<<setw(110)<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::";
	
	cout<<endl;
}
bool sale_reg :: sales_insert()
{
	system("cls");
	bool yes=false,check=true;
	ofstream fi11("temp.txt",ios::out);
	ifstream fi10("stock.txt",ios::in);
	fstream file2;
	file2.open("stock_number.txt",ios::in|ios::app);
	file2>>stk_no;
	file2.close();
	color(8);
	cout<<setw(110)<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::";
	cout<<endl<<endl<<setw(90);
	cout<<"Enter the name of buyer :: ";
	color(14);
	cin>>ws;
	cin.get(buyer_name,50);
	stock stk[stk_no+1];
	int i=0;
	color(8);
	cout<<endl<<setw(90);
	cout<<"Enter the pdt_code :: ";
	color(14); 		
	cin>>ws;
	cin.get(code,30);
	fi10.seekg(0);
	int count=stk_no;
	while(!fi10.eof() && count!=0)
	{
		count--;	
		fi10.read((char *)&stk[i],sizeof(stk[i]));
		if(code==stk[i].return_code())
		{
			stk[i].display();
			do{	
				color(8);
				cout<<endl<<endl<<setw(90);
		 		cout<<"Enter the quantity :: ";
		 		color(14);
		 		if(!(cin>>quantity))
		 		{
		 			cin.clear();
					while(cin.get()!='\n');
					check=false;
				}
				else
				{
					if(quantity<=0||quantity>stk[i].return_in())
						check=false;
					else
					{
						check=true;
						stk[i].tsreset();
			 			stk[i].reducein(quantity);
			 		}
			 	}
			 	if(check==false)
					invalid_input();
			}while(check==false);
	 		cost=quantity*stk[i].return_cost();
	 		int tdays;
			bool leap,che;
            do{
	            do{
		            color(8);
		 			cout<<endl<<endl<<setw(90);
		            cout<<"The date of sale (dd/mm/yyyy):: ";
		            color(14);
		            char ch;
	            	check=true;
		            if(!(cin>>date))
		            {
		            	cin.clear();
		            	while(cin.get()!='\n');
		            	check=false;
		            	break;
		            }
		            cin>>ch;
		            if(!(cin>>month))
		            {
		            	cin.clear();
		            	while(cin.get()!='\n');
		            	check=false;
		            	break;
		            }
		            cin>>ch;
		            if(!(cin>>year))
		            {
		            	cin.clear();
		            	while(cin.get()!='\n');
		            	check=false;
		            	break;
		            }
		            if(check==false)
		            	invalid_input();
	        	}while(check==false);

				if((year%4!=0 || year%100==0) && year%400!=0)
					leap=false;
				else
					leap=true;

				if(month<=7)
				{
					if(month==2)
					{
						if(leap==false)
							tdays=28;
						else
							tdays=29;
					}
					else if(month%2!=0)
						tdays=31;
					else if(month%2==0)
						tdays=30;
				}
				else
				{		
					if(month%2!=0)
						tdays=30;
					else
						tdays=31;
				}
				if((date<=tdays)&&month<13&&month>0&&year<=2020&&year>2000)
					che=true;
				else
				{
					invalid_input();
					che=false;
				}
			}while(che==false);
			
	 		fi11.write((char *)&stk[i],sizeof(stk[i]));
	 		yes=true;
	 		switch_count1=-1;
		}
		else
		{
			fi11.write((char *)&stk[i],sizeof(stk[i]));
		}
		i++;
	}
	int j=0;
	system("cls");
	sales_display();
	fi10.close();
	fi11.close();
	remove("stock.txt");
	rename("temp.txt","stock.txt");
	return yes;
}
void sales_swi(char i)
{
	fstream file2,file3;
	file2.open("sale_number.txt",ios::in|ios::app);
	file2>>sale_no;
	file2.close();
	sale_reg sale[2];
	fstream fi1;
	fi1.open("sales_register.txt",ios::in|ios::app);
	switch(i)
	{
		case '1':{
			if(sale_no==0)
			{
				system("cls");
				line_end(10);
				color(4);
				cout<<setw(92)<<"::::::::::::::::::::::::"<<endl;
				cout<<setw(86)<<"NO RECORDS"<<endl;
				cout<<setw(92)<<"::::::::::::::::::::::::"<<endl;
				line_end(5);
			}
			else
			{
				system("CLS");
				for(int j=0;j<sale_no;j++)
				{
					fi1.read((char *)&sale[0],sizeof(sale[0]));
					sale[0].sales_display();
				}
			}
			pause();
			break;
		}
		case '2':{
			bool check;
			check=sale[1].sales_insert();
			if(check==true)
			{
				fi1.write((char *)&sale[1],sizeof(sale[1]));
				file3.open("sale_number.txt",ios::out|ios::in);
				sale_no=sale_no+1;
				file3<<sale_no;
				file3.close();
				pause();
			}
			break;
		}
	}
	fi1.close();
}
void sales_det()
{
	char i;
	bool check=true;
		system("cls");
		cout<<endl<<endl;
		color(8);
		cout<<setw(110)<<":::::::::::::::::::::::::::::MENU:::::::::::::::::::::::::::::";
		cout<<endl<<endl<<setw(89)<<"1. SALES REGESTER";
		cout<<endl<<endl<<setw(86)<<"2. ADD INVOICE";
		cout<<endl<<endl<<setw(80)<<"3. \tEXIT"<<endl<<endl;
		cout<<setw(94)<<"::::::::::::::::::::::::::::::"<<endl;
		cout<<endl<<setw(90)<<"ENTER YOUR ANSWER :: ";
		color(14);
		i=getche();
		if(i=='1'||i=='2'||i=='3')
			sales_swi(i);
		else
			sales_det();
}