using namespace std;
int switch_count1=-1;
int stk_no=0;
class stock{
	char pdt_name[50],pdt_code[30],vendor_name[50];
	int pdt_cost,pdt_in,total_cost,pdt_tax,date,month,year;
	float grand_total;
 public:
	static long tstk;
	stock(){
		strcpy(vendor_name,"No-Vendor");
		strcpy(pdt_name,"No-Name");
		strcpy(pdt_code,"No-Code");
		total_cost=0;
		pdt_tax=0;
		grand_total=0;
		pdt_cost=0;
		pdt_in=0;
	}
	void stk_modify(stock stk[]);
	void totalstk(){
		tstk=tstk+(pdt_in*pdt_cost);
	}
	void stock_value(){
		cout<<endl<<endl<<setw(90)<<"CLOSING STOCK VALUE :: ";
		color(14);
		cout<<tstk;
		cout<<endl<<endl;
	}
	void stk_input(stock stk[]);
	void stk_display();
	void display();
	void tsreset(){
		tstk=0;
	}
	string return_code(){
		return pdt_code;
	}
	void reducein(int i){
		pdt_in=pdt_in-i;
	}
	int return_in(){
		return pdt_in;
	}
	int return_cost(){
		return pdt_cost;
	}
};
long stock::tstk=0;
void stk_swi(char i){
	switch_count1++;
	fstream file1,file2,copy;
	file1.open("purchase_register.txt",ios::in|ios::app);
	file2.open("stock_number.txt",ios::in|ios::app);
	file2>>stk_no;
	file2.close();
	copy.open("stock.txt",ios::app);
	stock stk[stk_no+1],temp;
	if(switch_count1==0){
		for(int j=0;j<stk_no;j++){	
			file1.read((char *)&stk[j],sizeof(stock));
			stk[j].totalstk();
		}
	}
	fstream file3;
	file3.open("stock_number.txt",ios::out|ios::in);
	switch(i){
		case '1':{
			file1.seekg(0);
			system("cls");
			if(stk_no==0){
				line_end(10);
				color(4);
				cout<<setw(92)<<"::::::::::::::::::::::::"<<endl;
				cout<<setw(86)<<"NO PRODUCTS"<<endl;
				cout<<setw(92)<<"::::::::::::::::::::::::"<<endl;
				line_end(5);
			}
			else{
				for(int i=0;i<stk_no;i++){	
					file1.read((char *)&stk[i],sizeof(stock));
					stk[i].stk_display();
				}	
			}
			file1.close();
			pause();
			break;
		}
		case '2':{
			stk[0].stk_input(stk);
			system("cls");
			stk[0].stk_display();
			file1.write((char *)&stk[0],sizeof(stock));
			copy.write((char *)&stk[0],sizeof(stock));
			stk_no=stk_no+1;
			file3<<stk_no;
			switch_count1=-1;
			stk[0].tstk=0;
			file1.close();
			pause();
			break;
		}
		case '3':{
			file1.close();
			copy.close();
			ifstream fi4("purchase_register.txt",ios::in);
			ofstream fi5("temp.txt",ios::out);
			ofstream fi6("temp2.txt",ios::out);
			string mod;
			do{
				color(3);
				system("cls");
				line_end(6);
				cout<<setw(100)<<"Enter 'A' to see the list of all stocks."<<endl<<endl;
				cout<<setw(110)<<"Enter the stock's number whose profile is to be modified :: ";
				color(14);
				cin>>ws;
				cin>>mod;
				if(mod=="a"||mod=="A"){
					system("cls");
					fstream fi;
					fi.open("purchase_register.txt",ios::in|ios::app);
					fi.seekg(0);
					if(stk_no==0){
						line_end(10);
						color(4);
						cout<<setw(92)<<"::::::::::::::::::::::::"<<endl;
						cout<<setw(86)<<"NO PRODUCTS"<<endl;
						cout<<setw(92)<<"::::::::::::::::::::::::"<<endl;
						line_end(5);
					}
					else
						for(int i=0;i<stk_no;i++){	
							fi.read((char *)&stk[i],sizeof(stock));
							stk[i].stk_display();
						}
					fi.close();
					pause();
				}
			}while(mod=="a"||mod=="A");
			int cnt=stk_no;
			while(!fi4.eof() && cnt!=0){
				cnt--;
				fi4.read((char*)&temp,sizeof(temp));
				if(temp.return_code()==mod){
					color(4);
					system("cls");
					line_end(2);
					cout<<setw(100)<<"ENTER '999' TO RETAIN THE ORIGINAL INPUT.";
					temp.stk_display();
					temp.stk_modify(stk);
					system("cls");
					temp.stk_display();					
					fi5.write((char *)&temp,sizeof(temp));
					fi6.write((char *)&temp,sizeof(temp));
				}
				else{
					fi5.write((char*)&temp,sizeof(temp));
					fi6.write((char *)&temp,sizeof(temp));
				}
			}
			fi4.close();
			fi5.close();
			fi6.close();
			temp.tsreset();
			switch_count1=-1;
			remove("purchase_register.txt");
			rename("temp.txt","purchase_register.txt");
			remove("stock.txt");
			rename("temp2.txt","stock.txt");
			pause();
			break;
		}
		case '4':{
			file1.close();
			copy.close();
			ifstream file4("purchase_register.txt",ios::in);
			ofstream file5("temp.txt",ios::out);
			ofstream file6("temp2.txt",ios::out);
			string dele;
			do{
				color(3);
				system("cls");
				line_end(6);
				cout<<setw(100)<<"Enter 'A' to see the list of all stocks."<<endl<<endl;
				cout<<setw(110)<<"Enter the stock's number whose profile is to be deleted :: ";
				color(14);
				cin>>ws;
				cin>>dele;
				if(dele=="a"||dele=="A"){
					system("cls");
					fstream fi;
					fi.open("purchase_register.txt",ios::in|ios::app);
					fi.seekg(0);
					if(stk_no==0){
						line_end(10);
						color(4);
						cout<<setw(92)<<"::::::::::::::::::::::::"<<endl;
						cout<<setw(86)<<"NO PRODUCTS"<<endl;
						cout<<setw(92)<<"::::::::::::::::::::::::"<<endl;
						line_end(5);
					}
					else
						for(int i=0;i<stk_no;i++){	
							fi.read((char *)&stk[i],sizeof(stock));
							stk[i].stk_display();
						}
					fi.close();
					pause();
				}
			}while(dele=="a"||dele=="A");
			int count=stk_no;
			while(!file4.eof() && count!=0){
				count--;
				file4.read((char*)&temp,sizeof(temp));
				if(temp.return_code()==dele){
					system("cls");
					line_end(5);
					temp.stk_display();
					char ch;
					line_end(3);
					delete_que();
					ch=getche();
					if(ch=='y'||ch=='Y'){
						stk_no=stk_no-1;
						file3<<stk_no;
						color(4);
						system("CLS");
						line_end(10);
						cout<<setw(92)<<"::::::::::::::::::::::::"<<endl;
						cout<<setw(87)<<"ENTRY DELETED"<<endl;
						cout<<setw(92)<<"::::::::::::::::::::::::"<<endl;
						line_end(5);
					}
					else{
						file5.write((char*)&temp,sizeof(temp));
						file6.write((char*)&temp,sizeof(temp));
					}
				}
				else{
					file5.write((char*)&temp,sizeof(temp));
					file6.write((char*)&temp,sizeof(temp));
				}
			}
			file4.close();
			file5.close();
			file6.close();
			temp.tsreset();
			switch_count1=-1;
			remove("purchase_register.txt");
			rename("temp.txt","purchase_register.txt");
			remove("stock.txt");
			rename("temp2.txt","stock.txt");
			pause();
			break;
		}
	}
	file3.close();
}
void stock_det(){
	char i;
	bool check=true;
	color(3);
	system("cls");
	cout<<endl<<endl;
	cout<<setw(110)<<":::::::::::::::::::::::::::::MENU:::::::::::::::::::::::::::::";
	cout<<endl<<endl<<setw(88)<<"1. PURCHASE LIST";
	cout<<endl<<endl<<setw(87)<<"2. ADD PURCHASE";
	cout<<endl<<endl<<setw(89)<<"3. MODIFY DETAILS";
	color(12);
	cout<<endl<<endl<<setw(90)<<"4. DELETE PURCHASE";
	color(3);
	cout<<endl<<endl<<setw(80)<<"5. \tEXIT"<<endl<<endl;
	cout<<setw(94)<<"::::::::::::::::::::::::::::::"<<endl;
	cout<<endl<<setw(90)<<"ENTER YOUR ANSWER :: ";
	color(14);
	i=getche();
	if(i=='1'||i=='2'||i=='3'||i=='4'||i=='5')
		stk_swi(i);
	else
		stock_det();
}
void stock::stk_input(stock stk[]){
	color(3);
	system("cls");
	cout<<endl<<endl;
	cout<<setw(110)<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::";
	bool check=true;
	fstream file1;
	file1.open("purchase_register.txt",ios::in|ios::app);
	file1.seekg(0);
	for(int i=0;i<stk_no;i++)
		file1.read((char *)&stk[i],sizeof(stock));
	file1.close();
	cout<<endl<<endl<<setw(90);
	cout<<"Enter the name of the vendor :: ";			//vendor name
	color(14);
	cin>>ws;
	cin.get(vendor_name,50);
	cout<<endl<<setw(90);
	color(3);
	cout<<"Enter the name of the product :: ";			//product name
	color(14);
	cin>>ws;
	cin.get(pdt_name,50);
	ifstream file4("purchase_register.txt",ios::in);
	char code[30];
	do{													//product code
		cout<<endl<<setw(90);
		color(3);
		cout<<"Enter the code :: ";
		color(14);
		if(!(cin>>code)){
			cin.clear();
			while(cin.get()!='\n');
				check=false;
		}
		else{
			check=true;
			for(int i=0;i<stk_no;i++){	
				if(stk[i].return_code()==code){
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
	strcpy(pdt_code,code);
	file4.close();

	int tdays;
	bool leap,che;
    do{													//purchase date
        do{
            color(3);
 			cout<<endl<<setw(90);
            cout<<"The date of sale (dd/mm/yyyy):: ";
            color(14);
            char ch;
        	check=true;
            if(!(cin>>date)){
            	cin.clear();
            	while(cin.get()!='\n');
            	check=false;
            	break;
            }
            cin>>ch;
            if(!(cin>>month)){
            	cin.clear();
            	while(cin.get()!='\n');
            	check=false;
            	break;
            }
            cin>>ch;
            if(!(cin>>year)){
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

		if(month<=7){
			if(month==2){
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
		else{		
			if(month%2!=0)
				tdays=30;
			else
				tdays=31;
		}
		if((date<=tdays)&&month<13&&month>0&&year<=2020&&year>2000&&date>0)
			che=true;
		else{
			invalid_input();
			che=false;
		}
	}while(che==false);

	do{														//product price
		cout<<endl<<setw(90);
		color(3);
		cout<<"Enter the price (in Rs/mtr) :: ";				
		color(14);
		if(!(cin>>pdt_cost)){
			cin.clear();
			while(cin.get()!='\n');
			check=false;
		}
		else{
			if(pdt_cost<=0)
				check=false;
			else
				check=true;
		}
		if(check==false)
			invalid_input();
	}while(check==false);

	do{														//product quantity
		cout<<endl<<setw(90);
		color(3);
		cout<<"Enter the quantity of (in mt) :: ";
		color(14);
		if(!(cin>>pdt_in)){
			cin.clear();
			while(cin.get()!='\n');
			check=false;
			cout<<endl;
		}
		else{
			if(pdt_in<=0)
				check=false;
			else
				check=true;
		}
		if(check==false)
			invalid_input();
	}while(check==false);
	cout<<endl<<setw(90);
	color(3);
	cout<<"Total cost of product  :: ";						//total cost
	color(14);
	total_cost=(pdt_cost*pdt_in);
	cout<<total_cost<<" Rs.";
	do{														//product tax
		cout<<endl<<endl<<setw(90);
		color(3);
		cout<<"Enter the GST (in %):: ";
		color(14);
		if(!(cin>>pdt_tax)){
			cin.clear();
			while(cin.get()!='\n');
			check=false;
		}
		else{
			if(pdt_tax<0||pdt_tax>20)
				check=false;
			else
				check=true;
		}
		if(check==false)
			invalid_input();										
	}while(check==false);

	float tax=(pdt_tax*total_cost)/100;
	grand_total=total_cost+(tax);
}
void stock::stk_display(){
	color(3);
	line_end(2);
	cout<<setw(110)<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::";
	
	cout<<endl<<endl<<setw(92);
	color(3);
	cout<<"The name of the vendor :: ";
	color(14);
	cout<<vendor_name;

	cout<<endl<<endl<<setw(92);
	color(3);
	cout<<"The name of the product :: ";
	color(14);
	cout<<pdt_name;
	
	cout<<endl<<endl<<setw(92);
	color(3);
	cout<<"The code of the product :: ";
	color(14);
	cout<<pdt_code;

	cout<<endl<<endl<<setw(92);
	color(3);
	cout<<"The date of purchase :: ";
	color(14);
	cout<<date<<"/"<<month<<"/"<<year;

	cout<<endl<<endl<<setw(92);
	color(3);
	cout<<"The cost of the product :: ";
	color(14);
	cout<<pdt_cost<<" Rs/mt";
	
	cout<<endl<<endl<<setw(92);
	color(3);
	cout<<"The quantity of the product :: ";
	color(14);
	cout<<pdt_in<<" mtr.";
	
	cout<<endl<<endl<<setw(92);
	color(3);
	cout<<"The tax on the product :: ";
	color(14);
	cout<<pdt_tax<<" %";

	cout<<endl<<endl<<setw(92);
	color(3);
	cout<<"The price of the product :: ";
	color(14);
	total_cost=(pdt_cost*pdt_in);
	float tax=(pdt_tax*total_cost)/100;
	grand_total=total_cost+(tax);
	cout<<grand_total<<" Rs.";

	cout<<endl<<endl;
	color(3);
	cout<<setw(110)<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::";
	
	cout<<endl;
}
void stock::stk_modify(stock stk[]){
	char temp[50];
	int temp_int;
	color(3);
	line_end(4);
	cout<<setw(110)<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::";
	bool check=true;
	fstream file1;
	file1.open("purchase_register.txt",ios::in|ios::app);
	file1.seekg(0);
	for(int i=0;i<stk_no;i++)
		file1.read((char *)&stk[i],sizeof(stock));
	file1.close();
	cout<<endl<<endl<<setw(90);
	cout<<"Enter the name of the vendor :: ";
	color(14);
	cin>>ws;
	cin.get(temp,50);
	if(strcmp(temp,"999"))
		strcpy(vendor_name,temp);
	cout<<endl<<setw(90);
	color(3);
	cout<<"Enter the name of the product:: ";		//product name
	color(14);
	cin>>ws;
	cin.get(temp,50);
	if(strcmp(temp,"999"))
		strcpy(pdt_name,temp);
	cout<<endl<<setw(90);
	color(12);
	cout<<"Enter the code of the product:: ";				//product code
	cout<<pdt_code <<"\t(UNCHANGABLE)"<<endl;
	int temp_date,temp_month,temp_year;
	int tdays;
	bool leap,che=true;
    do{													//purchase date
    	int td,tm,ty;
        do{
            color(3);
 			cout<<endl<<setw(90);
            cout<<"The date of sale (dd/mm/yyyy):: ";
            color(14);
            char ch;
        	check=true;
            if(!(cin>>temp_date)){
            	cin.clear();
            	while(cin.get()!='\n');
            	check=false;
            	break;
            }
            cin>>ch;
            if(!(cin>>temp_month)){
            	cin.clear();
            	while(cin.get()!='\n');
            	check=false;
            	break;
            }
            cin>>ch;
            if(!(cin>>temp_year)){
            	cin.clear();
            	while(cin.get()!='\n');
            	check=false;
            	break;
            }
            if(check==false)
            	invalid_input();
    	}while(check==false);

		if(temp_date!=999){
			td=date;
			date=temp_date;
		}
		if(temp_month!=999){
			tm=month;
			month=temp_month;
		}
		if(temp_year!=999){
			ty=year;
			year=temp_year;
		}
		
		if((year%4!=0 || year%100==0) && year%400!=0)
			leap=false;
		else
			leap=true;
		if(month<=7){
			if(month==2){
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
		else{		
			if(month%2!=0)
				tdays=30;
			else
				tdays=31;
		}
		if((date<=tdays)&&month<13&&month>0&&year<=2020&&year>2000&&date>0)
			che=true;
		else{
			invalid_input();
			che=false;
			month=tm;
			date=td;
			year=ty;
		}
	}while(che==false);	
	do{
		cout<<endl<<setw(90);
		color(3);
		cout<<"Enter the price (in Rs/mtr) :: ";				//product cost
		color(14);
		if(!(cin>>temp_int)){
			cin.clear();
			while(cin.get()!='\n');
			check=false;
		}
		else{
			if(temp_int<=0)
				check=false;
			else
				check=true;
		}
		if(check==false)
			invalid_input();
	}while(check==false);
	if(temp_int!=999)
		pdt_cost=temp_int;
	do{
		cout<<endl<<setw(90);
		color(3);
		cout<<"Enter the quantity of (in mt) :: ";				//product in
		color(14);
		if(!(cin>>temp_int)){
			cin.clear();
			while(cin.get()!='\n');
			check=false;
		}
		else{
			if(temp_int<0)
				check=false;
			else
				check=true;
		}
		if(check==false)
			invalid_input();
	}while(check==false);
	if(temp_int!=999)
		pdt_in=temp_int;
	do{														//product tax
		cout<<endl<<setw(90);
		color(3);
		cout<<"Enter the GST (in %):: ";
		color(14);
		if(!(cin>>temp_int)){
			cin.clear();
			while(cin.get()!='\n');
			check=false;
		}
		else{
			if(temp_int==999)
				break;
			if(temp_int<0||temp_int>20)
				check=false;
			else
				check=true;
		}
		if(check==false)
			invalid_input();											
	}while(check==false);
	if(temp_int!=999)
		pdt_tax=temp_int; 
}
void see_stock(){
	switch_count1++;
	fstream file1,file2;
	file1.open("purchase_register.txt",ios::in|ios::app);
	file2.open("stock_number.txt",ios::in);
	file2>>stk_no;
	file2.close();
	stock stk[stk_no+1],temp;
	ifstream stock_file("stock.txt",ios::in);
	stock_file.seekg(0);
	if(switch_count1==0){
		for(int j=0;j<stk_no;j++){	
			stock_file.read((char *)&stk[j],sizeof(stk[j]));
			stk[j].totalstk();
		}
	}
	system("cls");
	if(stk_no==0){
		line_end(10);
		color(4);
		cout<<setw(92)<<"::::::::::::::::::::::::"<<endl;
		cout<<setw(86)<<"NO PRODUCTS"<<endl;
		cout<<setw(92)<<"::::::::::::::::::::::::"<<endl;
		line_end(5);
	}
	else{
		stock_file.seekg(0);
		for(int i=0;i<stk_no;i++){	
			stock_file.read((char *)&stk[i],sizeof(stk[i]));
			stk[i].display();
		}	
		stk[stk_no+1].stock_value();
	}
	file1.close();
	stock_file.close();
	pause();
}
void stock::display()
{
	color(13);
	line_end(2);
	cout<<setw(110)<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::";
	
	cout<<endl<<endl<<setw(92);
	color(13);
	cout<<"The name of the product :: ";
	color(14);
	cout<<pdt_name;
	
	cout<<endl<<endl<<setw(92);
	color(13);
	cout<<"The code of the product :: ";
	color(14);
	cout<<pdt_code;
		
	cout<<endl<<endl<<setw(92);
	color(13);
	cout<<"The cost of the product :: ";
	color(14);
	cout<<pdt_cost<<" Rs/mt";
	
	cout<<endl<<endl<<setw(92);
	color(13);
	cout<<"The quantity of the product :: ";
	color(14);
	cout<<pdt_in<<" mtr.";
	cout<<endl;
	color(13);
	cout<<endl<<setw(110)<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::";
	
	cout<<endl;
}