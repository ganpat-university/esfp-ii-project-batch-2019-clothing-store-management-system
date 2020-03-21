using namespace std;
void fontsize(int a, int b){  
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();  
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);  
	GetCurrentConsoleFontEx(console, 0, lpConsoleCurrentFontEx);  
	lpConsoleCurrentFontEx->dwFontSize.X = a;  
	lpConsoleCurrentFontEx->dwFontSize.Y = b;  
	SetCurrentConsoleFontEx(console, 0, lpConsoleCurrentFontEx);  
}
void line(int j){
	for(int i=0;i<5;i++){
		int z=15+i;
		if(j>=51){
			gotoxy(40,17);
			cout<<"LOADING "<<(j*100)/90<<" %";
		}
		gotoxy(j,z);
		cout<<" ";
	}
}
void start_page(){
	system("cls");
	gotoxy(73,38);
	fontsize(30,30);
	for(int j=5;j<91;j++){
		Sleep(80);
		if(j<51){
			gotoxy(40,17);
			color(15);
			cout<<"LOADING "<<(j*100)/90<<" %";
		}
		color(36);
		line(j);
	}
	gotoxy(25,10);
	color(48);
	cout<<"   Enter any key to start the Program ....   ";
	char i=getch();
	color(15);
}