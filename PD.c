#include <windows.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


#define FILE_MENU_NEXT 1
#define FILE_MENU_RESET 2
#define FILE_MENU_EXIT 3
#define CAL_CALC 4
#define BMR_CALC 5
#define RESET 6
#define FILE_HELP 7
#define HELP_EXER 8
#define FILE_EXER 9
#define EXER_NEXT 10
#define EXER_PREV 11
#define TERMINAL 12
#define SAVEFILE 13
#define SAVE_RESET 14


float BMR(float num1, float num2, float  genM, float genW, HWND hWnd);
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DestroyChildCallback(hWnd);
void AddMenus(HWND);
void AddControls(HWND);
void AddControls1(HWND);
void Filemenu(HWND hWnd, int counter);
void Filemenu1(HWND hWnd, int counter);
void Savemenu(HWND);

char buf[32], fub[32];
char nama[5][40];
float bmrs[5][2];
int counter, counter1;
int i = 0;
int j = 0;
int k = 0;
HMENU hMenu;
HWND hTinggi, hBerat, hBMR, hPW, hWP, hdrop, hExer, hNama, hUmur, hCal, hrdhm, hMakanCal, hLari, hBat;
HWND hNama1, hNama2, hNama3, hNama4, hNama5, hBMR1, hBMR2, hBMR3, hBMR4, hBMR5, hHasil1, hHasil2;
HWND hHasil3, hHasil4, hHasil5;


int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	WNDCLASSW wc = {0};
	HWND hWnd;

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW ;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.style         = 0;
	wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = L"myWindowClass";
	wc.hIcon         = LoadIcon (NULL, IDI_APPLICATION);
	wc.lpfnWndProc = WindowProcedure;
	

	if(!RegisterClassW(&wc)){
		MessageBox(NULL, TEXT("Could not register window class"), 
                  NULL, MB_ICONERROR);
        return 0;
	}
	CreateWindowW(L"myWindowClass", L"Program Diet", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 200,200, 500 ,500,NULL,NULL,NULL,NULL);
	printf("Program Diet\ndibuat oleh Gilbert Lauren & Leandro Thiery");

	MSG msg = {0};
	ShowWindow(hWnd, ncmdshow);
    UpdateWindow(hWnd);
	while( GetMessage(&msg, NULL, NULL, NULL) )
	{
		TranslateMessage (&msg);
		DispatchMessage(&msg);
	}
	
	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch ( msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		AddMenus(hWnd);
		AddControls(hWnd);
	case WM_COMMAND:
		switch (wp)
		{

		case  FILE_MENU_NEXT:
			EnumChildWindows(hWnd, DestroyChildCallback, NULL);
			AddControls1(hWnd);
			if(bmrs[j-1][0] == 0){
				MessageBox(hWnd, "Missing Input bmr","Error", MB_ICONERROR);
				EnumChildWindows(hWnd, DestroyChildCallback, NULL);
				AddControls(hWnd);
				break;
			} 
			SetWindowText(hCal,buf);
			break;
		case FILE_MENU_EXIT:
			if(MessageBox(hWnd, "Are you sure you want to Exit?", "Wait!", MB_YESNO)==IDYES){
				DestroyWindow(hWnd);
				PostQuitMessage(0);
				return 0;
			}
			break;
		case FILE_MENU_RESET:
			EnumChildWindows(hWnd, DestroyChildCallback, NULL);
			AddControls(hWnd);
			break;
		case BMR_CALC:
			{
			char out[32], tempg[1];
			float genM = 0, genW = 0;
			float bmr, num1, num2, num3;

			GetWindowText(hNama, nama[i], 32);
			i+=1;
          	
			GetWindowText(hUmur, out, 32);
			num1 = strtof(out, NULL);
			if (num1==0){
				MessageBox(hWnd, "Missing Input","Error", MB_ICONERROR);
				break;
			}
			
			GetWindowText(hBerat, out, 32);
			num2 = strtof(out, NULL);

			GetWindowText(hPW, tempg, 32);
			if ((strcmp(tempg, "M") == 0) || (strcmp(tempg, "m") == 0)){
				genM = 1;
			} else if ((strcmp(tempg, "W") == 0) || (strcmp(tempg, "w") == 0)){
				genW = 1;
			} else {
				MessageBox(hWnd, "Masukkan L/l untuk Laki-Laki dan\n P/p untuk Perempuan","Error", MB_ICONERROR);
				break;
			}
			char num[32];
			GetWindowText(hExer, num, 32);
			num3 = strtof(num, NULL);

			if ((num3<0) || (num3>11)){
				MessageBox(hWnd, "Incorrect Value of Active\nInsert Number Between 0-11","Error", MB_ICONERROR);
				break;
			} else if (num3>=0 && num3<1){
				num3 = 1.2;
			} else if (num3>=1 && (num3<3)){
				num3 = 1.375;
			} else if (num3>=3 && (num3<6)){
				num3 = 1.55;
			} else if (num3>=6 && (num3<7)){
				num3 = 1.725;
			} else if (num3>7){
				num3 = 1.9;
			}

			bmr = BMR(num1, num2, genM, genW, hWnd)* num3;
			if (bmr==0){
				MessageBox(hWnd, "Missing Input","Error", MB_ICONERROR);
				break;
			}

  			sprintf(buf,"%0.2f",bmr);
			bmrs[j][0] = bmr;
			j+=1;


			SetWindowText(hBMR, buf);
			break;
			}

		case CAL_CALC:
			;
			char dum[32], dum1[40];
			float hasil, num1, num2, num3, bmr;
          	
			GetWindowText(hMakanCal, dum, 32);
			num1 = strtof(dum, NULL);
			
			GetWindowText(hLari, dum1, 32);
			num2 = strtof(dum1, NULL);


			

			//1KM = 75 Calorie//
			hasil = num1-(num2*75);
			printf("%f", bmrs[j-1][0]);
			printf("%f", bmrs[0][0]);
			
			
			bmrs[j-1][1] = hasil;
			
			if (hasil==0){
				MessageBox(hWnd, "Missing Input","Error", MB_ICONERROR);
				break;
			}

  			sprintf(fub,"%0.2f",hasil);

			SetWindowText(hBat, fub);

			bmr = strtof(buf, NULL);

			if(hasil>bmr){
				MessageBox(hWnd, ""
				"                                                       ./oyyo+/-	\n"
				"                                                     `+hmmmdhyyssy+:.`	\n"
				"                                                 ./sh+//:-.:syyddhhdo+-`                            \n"
				"                                                oysd:::ss+....-/ys:sdh-                             \n"
				"                                           `+//oNdy:..s/:....-/+::--+dy//.                          \n"
				"                                           /+/oos:.-+://+:....s/:s/:-/ys/-                          \n"
				"                                           `//:.....//+o//...../oo/---/y+:                          \n"
				"                                           `yo...........y/.....-s:----/s`                          \n"
				"                                          -ss-......-.:/+/+oooooo+------y-                          \n"
				"                                        .od:......../.-::---::::--------/ho-                        \n"
				"                                  .-:/+ydh-......-....-..---------------/dyh                        \n"
				"                              -+oyso+++hh/..:....-++/+oo+o/:---------/sshhyyho-`                    \n"
				"                            :soosso//::dh:..:+.....-///:--:-:::----+ymyhh++++shdo.                  \n"
				"                          `sysss+/:::::h+y--///::-::::://///::-:+oyhydyo+++++++ohmh:                \n"
				"                       ./+so//:::::::::oshy+////ossoo+/::::/+ohhhyyyo+++++++so++++ydd/              \n"
				"                    ./so+/:::::::::::::://+syyhdhyso++sooyshyyy+++++++++++++sy//++++smy.            \n"
				"                  -os/:::::::::::::::::::::::///+ossssysoso+////++++++++++++sh/:/+++++dm:           \n"
				"                .oo/::::::::::::::::::::::::::::::::::::::::///+++++++++s+o+sd:::/+++++yN+          \n"
				"               :s/:::::::::::/:::::::::::::::::::::::::::::::::///++++++oyshom:::/++++++yN+         \n"
				"              `h/:////++/:::///::+ooo+/::::::::::::::::::::::::::/++++++++sddm::::/++++++yN/        \n"
				"              +yoo+////::::::::::::/+syyso+/::::::::::::::::::::::++++++o++omN:::/oyyydyyymN.       \n"
				"            `/ys+/:::::::::::::::::::::/+osyyso+:::::::::::::::::/+++++yy++++d+/sdohyydyyyhdd`      \n"
				"          `+s+/:::::::::::::::::::::::::::::/+oyhys+/:::::::::///++++ohh+++++odhydyso+//+mhdN:      \n"
				"         -yo:::::::::::::::::::::::::::::::::://++oyyyysooo++++ooosyhyo+++++++hms/:+:/--:sh:-`      \n"
				"        :h/:::::::::::::::::::::::::::::::::::::///+++oossyyyyyyssoo+++++++++++yy:s++:---/h`        \n"
				"       -d/::::::::::::::::::::::::::::::::::::::::::////+++++++++++++++++++++++sd-...-----os        \n"
				"       d+::::::::::::::::::::::::::::::::::::::::::::::::/+++++++++++++++++++++oh...-------m`       \n"
				"      .m:::::::::::::::::::::::::::::::::::::::::::::::::/+++++++++++++++++++++ss..--------d-       \n"
				"      :h::::::::::::::::::::::::::::::::::::::::::::::::/++++++++++++++++++++++y/...-------m`       \n"
				"      /y::::::::://::::::::::::::::::::::::::::::::::::/+++++++++++++++++++++++d/....-----/h        \n"
				"      :h:::::::://o:::::::::::::::::::::::::::::::::://++++++++++++++++++++++o+d+....-----h:        \n"
				"      `m/:::::::::/:::::::::::::::::::::::::::::::::/+++++++++++++++++++oo+ohysmy.....---oN+        \n"
				"       oh:::::::::::::::::::::::::::::::::::::::::/+++++++++++++++++++syyshmmddhm.....--+mym`       \n"
				"       `yy::::::::::::::::::::::::::::::::::::://++++++++++++++++++ohmNdddhyyyssdo...--/mysd:       \n"
				"        `oh+::::::::::::::::::::::::::::::::///+++++++++++++++++oydNmddhhyssssssyd:..--/yshd+       \n"
				"          :yy/:::::::::::::::::::::::::::///+++++++++++++++ooyddmddhyyyssssssssyyo-.----:shd+       \n"
				"            /myo+/::::::::::::::::::////+++++++++++++oosyhdddhhyysssssssssssssyy//-...-/hhyd:       \n"
				"            :/:oyoso+++//////////++++++ooooooossyhhhhhhyysssssssssooooosssssssyysyy.-o--hyyh        \n"
				"           -+-:/:-/sy:://yhhhhhyyyyyhhhhhhhyyyyyyyssssssssooooooooooooossssssssssshsyyyshhy`        \n"
				"           `/o/y.-h+:    `/syssssssssyssssssssssssssooosyysooooooooooossssssssssssssssyhh/          \n"
				"             --:/:s`        oyoooooosyyysssssoooooossyyysoooooooooossssssssssssssssyhhy/`           \n"
				"                 `          `ysoooooooosyyyyyhdhhyyyssooooooooooooosssssssssssssyhhs+.              \n"
				"                             `ssoooooooosyyyhhddhdhhyssssoooooosssyyyyyyyyssssyhhd`                 \n"
				"                              ///+osdysoo+/:---.-::h/:/+ooooo++//:///+odsossssoo:`                  \n"
				"                                    /s:-.......----/ho-....---------:os:                            \n"
				"                                     `/os+:--/-::--oss+-:::-----::+o/.                              \n"
				"                                        `-/y::+o/--::yh::-.----:y-`                                 \n"
				"                                           `/+:-..--/y.y:..--::o-                                   \n"
				"                                              .:/..-o. :+.--:s-                                     \n"
				"                                               `y.-::o`s..--++                                      \n"
				"                                               :+/+ys/s///:+/                                       \n"
				"                                                  `` `--:-`                                        "
				"Berat badan akan naik", "Result", MB_ICONINFORMATION);
			} else if (hasil<bmr){
				MessageBox(hWnd, "Berat badan anda tidak akan naik", "Result", MB_ICONINFORMATION);
			}

			break;
		case FILE_HELP:
			;
			counter = 0;
			EnumChildWindows(hWnd, DestroyChildCallback, NULL);
			Filemenu(hWnd, counter);
			

			break;

		case HELP_EXER:
			;
			counter += 1;
			if (counter==2){
				counter = 0;
			}
			EnumChildWindows(hWnd, DestroyChildCallback, NULL);
			Filemenu(hWnd, counter);
			break;

		case FILE_EXER:
			;
			counter1 = 0;
			EnumChildWindows(hWnd, DestroyChildCallback, NULL);
			Filemenu1(hWnd, counter1);
			break;

		case EXER_NEXT:
			;
			counter1 +=1;
			EnumChildWindows(hWnd, DestroyChildCallback, NULL);
			Filemenu1(hWnd, counter1);
			break;
		
		case EXER_PREV:
			;
			counter1 -=1;
			EnumChildWindows(hWnd, DestroyChildCallback, NULL);
			Filemenu1(hWnd, counter1);
			break;

		case TERMINAL:
			; 
			int x=0, y=0;
			for(i=0; i<5; i++){
				printf("nama = %s \t bmr = %f \t hasil = %f\n", nama[i], bmrs[i][0], bmrs[i][1]);
			}
			break;

		case SAVEFILE:
			;
			char tempo[32];
			EnumChildWindows(hWnd, DestroyChildCallback, NULL);
			Savemenu(hWnd);

			SetWindowText(hNama1, nama[0]);
			sprintf(tempo,"%0.2f",bmrs[0][0]);
			SetWindowText(hBMR1, tempo);
			sprintf(tempo,"%0.2f",bmrs[0][1]);
			SetWindowText(hHasil1, tempo);

			SetWindowText(hNama2, nama[1]);
			sprintf(tempo,"%0.2f",bmrs[1][0]);
			SetWindowText(hBMR2, tempo);
			sprintf(tempo,"%0.2f",bmrs[1][1]);
			SetWindowText(hHasil2, tempo);

			SetWindowText(hNama3, nama[2]);
			sprintf(tempo,"%0.2f",bmrs[2][0]);
			SetWindowText(hBMR3, tempo);
			sprintf(tempo,"%0.2f",bmrs[2][1]);
			SetWindowText(hHasil3, tempo);

			SetWindowText(hNama4, nama[3]);
			sprintf(tempo,"%0.2f",bmrs[3][0]);
			SetWindowText(hBMR4, tempo);
			sprintf(tempo,"%0.2f",bmrs[3][1]);
			SetWindowText(hHasil4, tempo);

			SetWindowText(hNama5, nama[4]);
			sprintf(tempo,"%0.2f",bmrs[4][0]);
			SetWindowText(hBMR5, tempo);
			sprintf(tempo,"%0.2f",bmrs[4][1]);
			SetWindowText(hHasil5, tempo);


			break;

		case SAVE_RESET:
			;
			int c;
			for (c=0; c<5; c++){ 
				bmrs[c][1]= 0;
				bmrs[c][0]= 0;
			}
			memset(nama,0,strlen(nama));
			EnumChildWindows(hWnd, DestroyChildCallback, NULL);
			Savemenu(hWnd);

			SetWindowText(hNama1, nama[0]);
			sprintf(tempo,"%0.2f",bmrs[0][0]);
			SetWindowText(hBMR1, tempo);
			sprintf(tempo,"%0.2f",bmrs[0][1]);
			SetWindowText(hHasil1, tempo);

			SetWindowText(hNama2, nama[1]);
			sprintf(tempo,"%0.2f",bmrs[1][0]);
			SetWindowText(hBMR2, tempo);
			sprintf(tempo,"%0.2f",bmrs[1][1]);
			SetWindowText(hHasil2, tempo);

			SetWindowText(hNama3, nama[2]);
			sprintf(tempo,"%0.2f",bmrs[2][0]);
			SetWindowText(hBMR3, tempo);
			sprintf(tempo,"%0.2f",bmrs[2][1]);
			SetWindowText(hHasil3, tempo);

			SetWindowText(hNama4, nama[3]);
			sprintf(tempo,"%0.2f",bmrs[3][0]);
			SetWindowText(hBMR4, tempo);
			sprintf(tempo,"%0.2f",bmrs[3][1]);
			SetWindowText(hHasil4, tempo);

			SetWindowText(hNama5, nama[4]);
			sprintf(tempo,"%0.2f",bmrs[4][0]);
			SetWindowText(hBMR5, tempo);
			sprintf(tempo,"%0.2f",bmrs[4][1]);
			SetWindowText(hHasil5, tempo);
			break;
			

		case RESET:
			EnumChildWindows(hWnd, DestroyChildCallback, NULL);
			AddControls(hWnd);
		}
		break;

	default:
		return DefWindowProcW(hWnd,msg,wp,lp);
	}
}

void AddMenus(HWND hWnd)
{
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hHelpMenu = CreateMenu();

	AppendMenu(hMenu, MF_POPUP,(UINT_PTR)hFileMenu, "&File");
	AppendMenu(hFileMenu,MF_STRING, FILE_MENU_NEXT,"&Next");
	AppendMenu(hFileMenu,MF_STRING, FILE_MENU_RESET, "&Back");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL,NULL);
	AppendMenu(hFileMenu,MF_STRING, TERMINAL, "&Show Data (Terminal)");
	AppendMenu(hFileMenu,MF_STRING, SAVEFILE, "&Show Data");
	AppendMenu(hFileMenu,MF_STRING, FILE_MENU_EXIT, "&Exit");

	AppendMenu(hMenu, MF_POPUP,(UINT_PTR)hHelpMenu, "&Help");
	AppendMenu(hHelpMenu, MF_STRING,(HWND)FILE_HELP, "Exercise Calories");
	AppendMenu(hHelpMenu, MF_STRING,(HWND)FILE_EXER, "&Exercise Guide");

	SetMenu(hWnd, hMenu);
}

float BMR(float num1, float num2, float  genM, float genW, HWND hWnd)
{
	float hasil;
	float Aray[6][4]= {
		{60.9, -54, 61, -51},
		{22.7, 495, 22.5, 499},
		{17.5, 651, 12.2,746},
		{15.3, 679, 14.7, 496},
		{11.6, 879, 8.7, 829},
		{13.5, 487, 10.5, 596}
	};
	if((num1>0) && (num1<3)){
		if (genM==1){
			hasil = Aray[0][0]* num2 + Aray[0][1];
		} else if(genW==1){
			hasil = Aray[0][2]* num2 + Aray[0][3];
		}
	} else if((num1>=3) && (num1<10)){
		if (genM==1){
			hasil = Aray[1][0]*num2 + Aray[1][1];
		} else if(genW==1){
			hasil = Aray[1][2]*num2 + Aray[1][3];
		}
	} else if((num1>=10) && (num1<18)){
		if (genM==1){
			hasil = Aray[2][0]*num2 + Aray[2][1];
		} else if(genW==1){
			hasil = Aray[2][2]*num2 + Aray[2][3];
		}
	} else if((num1>=18) && (num1<30)){
		if (genM==1){
			hasil = Aray[3][0]*num2 + Aray[3][1];
		} else if(genW==1){
			hasil = Aray[3][2]*num2 + Aray[3][3];
		}
	} else if((num1>=30) && (num1<60)){
		if (genM==1){
			hasil = Aray[4][0]*num2 + Aray[4][1];
		} else if(genW==1){
			hasil = Aray[4][2]*num2 + Aray[4][3];
		}
	} else if((num1>=60) && (num1<300)){
		if (genM==1){
			hasil = Aray[1][0]*num2 + Aray[1][1];
		} else if(genW==1){
			hasil = Aray[1][2]*num2 + Aray[1][3];
		}
	} else {
		MessageBox(hWnd, "Incorrect Value of Umur\n(0-300)","Error", MB_ICONERROR);
	}
	return hasil;
}

BOOL CALLBACK DestroyChildCallback(hWnd){
	if(hWnd!=NULL){
		DestroyWindow(hWnd);
	}
	return TRUE;
}


void AddControls(HWND hWnd)
{
	CreateWindowW(L"static", L"BMR Calculator", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER , 5, 5, 100, 20, hWnd,NULL ,NULL,NULL);

	CreateWindowW(L"static", L"Name", WS_VISIBLE | WS_CHILD | SS_LEFT , 50,50,75,20, hWnd, NULL,NULL,NULL);
    CreateWindowW(L"static", L":", WS_VISIBLE | WS_CHILD | SS_LEFT , 175,50,10,20, hWnd, NULL,NULL,NULL);
	hNama = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | SS_LEFT , 200, 50, 150, 20, hWnd,NULL ,NULL,NULL);

	hBerat = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | SS_CENTER | ES_NUMBER, 200, 80, 50, 20, hWnd,NULL ,NULL,NULL);
	CreateWindowW(L"static", L"Mass(Kg)", WS_VISIBLE | WS_CHILD | SS_LEFT, 50,80,70,20, hWnd, NULL,NULL,NULL);
    CreateWindowW(L"static", L":", WS_VISIBLE | WS_CHILD | SS_LEFT , 175,80,10,20, hWnd, NULL,NULL,NULL);

	hPW = CreateWindowW(L"edit",L"",WS_BORDER | SS_CENTER | WS_CHILD | WS_VISIBLE,200,110,50,20,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"static",L"Sex(M/W)", SS_LEFT | WS_CHILD | WS_VISIBLE,50,110,125,20,hWnd,NULL,NULL,NULL);
	CreateWindowW(L"static", L":", WS_VISIBLE | WS_CHILD | SS_LEFT , 175,110,10,50, hWnd, NULL,NULL,NULL);

	CreateWindowW(L"static",L"Age", SS_LEFT | WS_CHILD | WS_VISIBLE | ES_NUMBER,50,140,50,20,hWnd,NULL,NULL,NULL);
	hUmur = CreateWindowW(L"edit",L"", WS_BORDER | SS_CENTER | WS_CHILD | WS_VISIBLE | ES_NUMBER,200,140,50,20,hWnd,NULL,NULL,NULL);
	CreateWindowW(L"static", L":", WS_VISIBLE | WS_CHILD | SS_LEFT , 175,140,10,50, hWnd, NULL,NULL,NULL);

	CreateWindowW(L"static",L"Run/week", SS_LEFT | WS_CHILD | WS_VISIBLE | ES_NUMBER,50,170,120,40,hWnd,NULL,NULL,NULL);
	hExer = CreateWindowW(L"edit",L"", WS_BORDER | SS_CENTER | WS_CHILD | WS_VISIBLE | ES_NUMBER,200,170,50,20,hWnd,NULL,NULL,NULL);
	CreateWindowW(L"static", L":", WS_VISIBLE | WS_CHILD | SS_LEFT , 175,170,10,50, hWnd, NULL,NULL,NULL);

	CreateWindowW(L"button", L"Calculate", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 280, 205, 75,20, hWnd, (HMENU)BMR_CALC, NULL, NULL);

    CreateWindowW(L"static", L"BMR", WS_VISIBLE | WS_CHILD | SS_LEFT, 50,205,75,20, hWnd, NULL,NULL,NULL);
	hBMR = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 200, 205, 70, 20, hWnd,NULL ,NULL,NULL);
    CreateWindowW(L"static", L":", WS_VISIBLE | WS_CHILD | SS_LEFT , 175,205,10,50, hWnd, NULL,NULL,NULL);

	CreateWindowW(L"button", L"Next", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 280, 235, 75,20, hWnd, (HMENU)FILE_MENU_NEXT, NULL, NULL);

}

void AddControls1(HWND hWnd)
{
	CreateWindowW(L"static", L"Calorie Gain", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER , 5, 5, 100, 20, hWnd,NULL ,NULL,NULL);

	hMakanCal = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | SS_CENTER | ES_NUMBER , 200, 110, 50, 20, hWnd,NULL ,NULL,NULL);
	CreateWindowW(L"static", L"Food", WS_VISIBLE | WS_CHILD | SS_LEFT, 50,110,70,70, hWnd, NULL,NULL,NULL);
    CreateWindowW(L"static", L":", WS_VISIBLE | WS_CHILD | SS_LEFT , 175,110,10,20, hWnd, NULL,NULL,NULL);

	hLari = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | SS_CENTER | ES_NUMBER , 200, 80, 50, 20, hWnd,NULL ,NULL,NULL);
	CreateWindowW(L"static", L"Run Distance/day", WS_VISIBLE | WS_CHILD | SS_LEFT, 50,80,124,20, hWnd, NULL,NULL,NULL);
    CreateWindowW(L"static", L":", WS_VISIBLE | WS_CHILD | SS_LEFT , 175,80,10,20, hWnd, NULL,NULL,NULL);


	CreateWindowW(L"button", L"Calculate", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 280, 140, 75,20, hWnd, (HMENU)CAL_CALC, NULL, NULL);


    CreateWindowW(L"static", L"Last BMR", WS_VISIBLE | WS_CHILD | SS_LEFT, 50,50,75,20, hWnd, NULL,NULL,NULL);
	hCal = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 200, 50, 75, 20, hWnd,NULL ,NULL,NULL);
    CreateWindowW(L"static", L":", WS_VISIBLE | WS_CHILD | SS_LEFT , 175,50,10,20, hWnd, NULL,NULL,NULL);

	CreateWindowW(L"static", L"BMR", WS_VISIBLE | WS_CHILD | SS_LEFT, 50,140,75,20, hWnd, NULL,NULL,NULL);
	hBat = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 200, 140, 75, 20, hWnd,NULL ,NULL,NULL);
    CreateWindowW(L"static", L":", WS_VISIBLE | WS_CHILD | SS_LEFT , 175,140,10,50, hWnd, NULL,NULL,NULL);

	CreateWindowW(L"button", L"Reset", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 280, 225, 75,20, hWnd, (HMENU)RESET, NULL, NULL);

}

void Filemenu(HWND hWnd, int counter)
{
	switch (counter)
	{
	case 0:
		CreateWindowW(L"static", L""
		"1. Jumping Rope\n"
		"    The burn: 667-990 calories/hour \n"
		"    (if you’re jumping at 120 skips per minute)\n\n"
		"2. Running Up Hills/Stair Sprints\n"
		"    The burn: 639-946 calories/hour\n\n"
		"3. Kickboxing\n"
		"    The burn: 582-864 calories/hour\n\n"
		"4. Cycling Intervals\n"
		"    The burn: 568-841 calories/hour\n\n"
		"5. Running\n"
		"    The burn: 566-839 calories/hour (10 min/mile)\n\n"
		"6. Kettlebell Circuit\n"
		"    The burn: 554-822 calories/hour\n\n"
		"7. Stationary Bike\n"
		"    The burn: 498-738 calories/hour (at a vigorous pace)\n\n"
		"8. Rowing Machine\n"
		"    The burn: 481-713 calories/hour\n" 
		"    (at 150 watts, which you can check on the machine)\n\n", WS_VISIBLE | WS_CHILD | SS_LEFT, 5,5,450,400, hWnd, NULL,NULL,NULL);
		CreateWindowW(L"static", L"1/2", WS_VISIBLE | WS_CHILD | SS_LEFT, 100,410,40,20, hWnd, NULL,NULL,NULL);
		CreateWindowW(L"button", L"Next", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 380, 410, 75,20, hWnd, (HMENU)HELP_EXER, NULL, NULL);
		break;

	case 1:
		CreateWindowW(L"static", L""
		"9. Stairs\n"
		"    The burn: 452-670 calories/hour (when going 77 steps/minute)\n\n"
		"10. Strength Training\n"
		"    The burn: 341-504 calories/hour\n\n"
		"11. Metabolic Resistance Training Circuit\n"
		"    The burn: 340-505 calories/hour\n\n"
		"12. Elliptical\n"
		"    The burn: 322-478 calories/hour (at a resistance level of 8)\n\n"
		"13. Battle Ropes\n"
		"    The burn: 285-421 calories/hour\n\n"
		"14. Power Yoga\n"
		"    The burn: 226-335 calories/hour", WS_VISIBLE | WS_CHILD | SS_LEFT, 5,5,450,400, hWnd, NULL,NULL,NULL);

		CreateWindowW(L"button", L"Previous", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 280, 410, 75,20, hWnd,(HMENU)HELP_EXER, NULL, NULL);
		CreateWindowW(L"static", L"2/2", WS_VISIBLE | WS_CHILD | SS_LEFT, 100,410,40,20, hWnd, NULL,NULL,NULL);
		break;
	
	default:
		break;
	}
	
	
}

void Filemenu1(HWND hWnd, int counter)
{	
	switch (counter)
	{
	case 0:
		CreateWindowW(L"static", L"1. Lunges\n    "
		"Challenging your balance is an essential part of a well-rounded exercise routine. "
		"Lunges do just that, promoting functional movement, while also increasing strength in your legs and glutes.\n\n"
		"a. Start by standing with your feet shoulder-width apart and arms down at         "
		"your sides.\n\n"
		"b. Take a step forward with your right leg and bend your right knee as you        "
		"do so, stopping when your thigh is parallel to the ground. Ensure that           "
		"your right knee doesn’t extend past your right foot.\n\n"
		"c. Push up off your right foot and return to the starting position. Repeat with      "
		"your left leg. This is one rep.\n\n"
		"d. Complete 10 reps for 3 sets.\n", WS_VISIBLE | WS_CHILD | SS_LEFT, 5,5,490,400, hWnd, NULL,NULL,NULL);
		
		CreateWindowW(L"button", L"Next", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 380, 410, 75,20, hWnd, (HMENU)EXER_NEXT, NULL, NULL);
		CreateWindowW(L"static", L"1/10", WS_VISIBLE | WS_CHILD | SS_LEFT, 100,410,40,20, hWnd, NULL,NULL,NULL);
		break;
	
	case 1:
		CreateWindowW(L"static", L"2. Pushups\n    "
		"Pushups are one of the most basic yet effective bodyweight moves you can perform "
		"because of the number of muscles that are recruited to perform them.\n\n"
		"1. Start in a plank position. Your core should be tight, shoulders              "
		"pulled down and back, and your neck neutral.\n\n"
		"2. Bend your elbows and begin to lower your body down to the floor.       "
		"When your chest grazes it, extend your elbows and return to               "
		"the start. Focus on keeping your elbows close to your body during      "
		"the movement.\n\n"
		"3. Complete 3 sets of as many reps as possible. If you can’t quite           " 
		"perform a standard pushup with good form, drop down to a                   "
		"modified stance on your knees — you’ll still reap many of the                "
		"benefits from this exercise while building strength.", WS_VISIBLE | WS_CHILD | SS_LEFT, 5,5,450,400, hWnd, NULL,NULL,NULL);

		CreateWindowW(L"static", L"2/10", WS_VISIBLE | WS_CHILD | SS_LEFT, 100,410,40,20, hWnd, NULL,NULL,NULL);
		CreateWindowW(L"button", L"Next", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 380, 410, 75,20, hWnd, (HMENU)EXER_NEXT, NULL, NULL);
		CreateWindowW(L"button", L"Previous", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 280, 410, 75,20, hWnd,(HMENU)EXER_PREV, NULL, NULL);
		break;
	case 2:
		CreateWindowW(L"static", L"3. Squats\n    "
		"Squats increase lower body and core strength, as well as flexibility in your "
		"lower back and hips. Because they engage some of the largest muscles in the body, "
		"they also pack a major punch in terms of calories burned.\n\n"
		"1. Start by standing straight, with your feet slightly wider than                  "
		"shoulder-width apart, and your arms at your sides.\n\n"
		"2. Brace your core and, keeping your chest and chin up, push your          "
		"hips back and bend your knees as if you’re going to sit in a chair.\n\n"
		"3. Ensuring your knees don’t bow inward or outward, drop down until       "
		"your thighs are parallel to the ground, bringing your arms out in          "
		"front of you in a comfortable position. Pause for one second, then        "
		"extend your legs and return to the starting position.\n\n"
		"4. Complete 3 sets of 20 reps.", WS_VISIBLE | WS_CHILD | SS_LEFT, 5,5,450,400, hWnd, NULL,NULL,NULL);

		CreateWindowW(L"static", L"3/10", WS_VISIBLE | WS_CHILD | SS_LEFT, 100,410,40,20, hWnd, NULL,NULL,NULL);
		CreateWindowW(L"button", L"Next", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 380, 410, 75,20, hWnd, (HMENU)EXER_NEXT, NULL, NULL);
		CreateWindowW(L"button", L"Previous", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 280, 410, 75,20, hWnd,(HMENU)EXER_PREV, NULL, NULL);
		break;

	case 3:
		CreateWindowW(L"static", L"4. Standing overhead dumbbell presses\n    "
		"Compound exercises, which utilize multiple joints and muscles, "
		"are perfect for busy bees as they work several parts of your body "
		"at once. A standing overhead press isn’t only one of the best "
		"exercises you can do for your shoulders, it also engages your upper back and core.\n\n"
		"Equipment: 10-pound dumbbells\n\n"
		"1. Pick a light set of dumbbells - we recommend 10 pounds to start -        "
		"and start by standing, either with your feet shoulder-width apart or       "
		"staggered. Move the weights overhead so your upper arms are           "
		"parallel to the floor.\n\n"
		"2. Bracing your core, begin to push up until your arms are fully                "
		"extended above your head. Keep your head and neck stationary.\n\n"
		"3. After a brief pause, bend your elbows and lower the weight back          "
		"down until your tricep is parallel to the floor again.\n\n"
		"4. Complete 3 sets of 12 reps.", WS_VISIBLE | WS_CHILD | SS_LEFT, 5,5,450,400, hWnd, NULL,NULL,NULL);

		CreateWindowW(L"static", L"4/10", WS_VISIBLE | WS_CHILD | SS_LEFT, 100,410,40,20, hWnd, NULL,NULL,NULL);
		CreateWindowW(L"button", L"Next", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 380, 410, 75,20, hWnd, (HMENU)EXER_NEXT, NULL, NULL);
		CreateWindowW(L"button", L"Previous", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 280, 410, 75,20, hWnd,(HMENU)EXER_PREV, NULL, NULL);
		break;

	case 4:
		CreateWindowW(L"static", L"5. Dumbbell rows\n	"
		"Not only will these make your back look killer in that dress,"
		"dumbbell rows are another compound exercise that strengthens multiple muscles in your upper body." 
		"Choose a moderate-weight dumbbell and ensure that you’re squeezing at the top of the movement.\n\n"
		"Equipment: 10-pound dumbbells\n\n"
		"1. Start with a dumbbell in each hand. We recommend no more than 10 pounds for beginners.\n\n"
		"2. Bend forward at the waist so your back is at a 45-degree angle to the ground. "
		"Be certain not to arch your back. Let your arms hang straight down."
		"Ensure your neck is in line with your back and your core is engaged.\n\n"
		"3. Starting with your right arm, bend your elbow and pull the weight straight up toward your chest,"
		"making sure to engage your lat, and stopping just below your chest.\n\n	"
		"4. Return to the starting position and repeat with the left arm. This is one rep. Repeat 10 times for 3 sets.", WS_VISIBLE | WS_CHILD | SS_LEFT, 5,5,450,400, hWnd, NULL,NULL,NULL);			//isiin ini

		CreateWindowW(L"static", L"5/10", WS_VISIBLE | WS_CHILD | SS_LEFT, 100,410,40,20, hWnd, NULL,NULL,NULL);
		CreateWindowW(L"button", L"Next", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 380, 410, 75,20, hWnd, (HMENU)EXER_NEXT, NULL, NULL);
		CreateWindowW(L"button", L"Previous", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 280, 410, 75,20, hWnd,(HMENU)EXER_PREV, NULL, NULL);
		break;

	case 5:
		CreateWindowW(L"static", L"6. Single-leg deadlifts\n"
		"This is another exercise that challenges your balance. Single-leg deadlifts require stability and leg strength. Grab a light to moderate dumbbell to complete this move.\n\n"
		"Equipment: dumbbell\n\n"
		"1. Begin standing with a dumbbell in your right hand and your knees slightly bent.\n\n"
		"2. Hinging at the hips, begin to kick your left leg straight back behind you, lowering the dumbbell down toward the ground.\n\n"
		"3. When you reach a comfortable height with your left leg, slowly return to the starting position in a controlled motion, squeezing your right glute. Ensure that your pelvis stays square to the ground during the movement.\n\n"
		"4. Repeat 10 to 12 reps before moving the weight to your left hand and repeating the same steps on the left leg.", WS_VISIBLE | WS_CHILD | SS_LEFT, 5,5,450,400, hWnd, NULL,NULL,NULL); 		//isiin ini

		CreateWindowW(L"static", L"6/10", WS_VISIBLE | WS_CHILD | SS_LEFT, 100,410,40,20, hWnd, NULL,NULL,NULL);
		CreateWindowW(L"button", L"Next", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 380, 410, 75,20, hWnd, (HMENU)EXER_NEXT, NULL, NULL);
		CreateWindowW(L"button", L"Previous", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 280, 410, 75,20, hWnd,(HMENU)EXER_PREV, NULL, NULL);
		break;

	case 6:
		CreateWindowW(L"static", L"7. Burpees\n\n"
		"An exercise we love to hate, burpees are a super effective whole-body move that provides great bang for your buck for cardiovascular endurance and muscle strength.\n\n"
		"1. Start by standing upright with your feet shoulder-width apart and your arms down at your sides.\n\n"
		"2. With your hands out in front of you, start to squat down. When your hands reach the ground, pop your legs straight back into a pushup position.\n\n"
		"3. Do a pushup.\n\n"
		"4. Come back up to the starting pushup position and jump your feet up to your palms by hinging at the waist. Get your feet as close to your hands as you can get, landing them outside your hands if necessary.\n\n"
		"5. Stand up straight, bringing your arms above your head and jump.\n\n"
		"6. This is one rep. Complete 3 sets of 10 reps as a beginner."
		, WS_VISIBLE | WS_CHILD | SS_LEFT, 5,5,450,400, hWnd, NULL,NULL,NULL);			//isiin ini

		CreateWindowW(L"static", L"7/10", WS_VISIBLE | WS_CHILD | SS_LEFT, 100,410,40,20, hWnd, NULL,NULL,NULL);
		CreateWindowW(L"button", L"Next", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 380, 410, 75,20, hWnd, (HMENU)EXER_NEXT, NULL, NULL);
		CreateWindowW(L"button", L"Previous", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 280, 410, 75,20, hWnd,(HMENU)EXER_PREV, NULL, NULL);
		break;

	case 7:
		CreateWindowW(L"static", L"8. Side planks\n\n"
		"A healthy body requires a strong core at its foundation, so don’t neglect core-specific moves like the side plank. Focus on the mind-muscle connection and controlled movements to ensure you’re completing this move effectively.\n\n"
		"1. Lie on your right side with your left leg and foot stacked on top of your right leg and foot. Prop your upper body up by placing your right forearm on the ground, elbow directly under your shoulder.\n\n"
		"2. Contract your core to stiffen your spine and lift your hips and knees off the ground, forming a straight line with your body.\n\n"
		"3. Return to start in a controlled manner. Repeat 3 sets of 10-15 reps on one side, then switch.", WS_VISIBLE | WS_CHILD | SS_LEFT, 5,5,450,400, hWnd, NULL,NULL,NULL);    //ini juga woi

		CreateWindowW(L"static", L"8/10", WS_VISIBLE | WS_CHILD | SS_LEFT, 100,410,40,20, hWnd, NULL,NULL,NULL);
		CreateWindowW(L"button", L"Next", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 380, 410, 75,20, hWnd, (HMENU)EXER_NEXT, NULL, NULL);
		CreateWindowW(L"button", L"Previous", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 280, 410, 75,20, hWnd,(HMENU)EXER_PREV, NULL, NULL);
		break;

	case 8:
		CreateWindowW(L"static", L"9. Situps\n\n"
		"Although they get a bad rap as being too basic, situps are an effective way to target your abdominal muscles. If you have lower back problems, stick with a crunch, which requires just your upper back and shoulders to lift off the ground.\n\n"
		"1. Start by lying on the ground on your back with your knees bent, feet flat, and your hands behind your head.\n\n"
		"2. Keeping your feet glued to the ground, begin to roll up from your head, engaging your core throughout. Don’t strain your neck during the upward motion.\n\n"
		"3. When your chest reaches your legs, begin the controlled phase back down to the starting position.\n\n"
		"4. Complete 3 sets of 15 reps as a beginner.", WS_VISIBLE | WS_CHILD | SS_LEFT, 5,5,450,400, hWnd, NULL,NULL,NULL);    // ini juga ya
	
		CreateWindowW(L"static", L"9/10", WS_VISIBLE | WS_CHILD | SS_LEFT, 100,410,40,20, hWnd, NULL,NULL,NULL);
		CreateWindowW(L"button", L"Next", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 380, 410, 75,20, hWnd, (HMENU)EXER_NEXT, NULL, NULL);
		CreateWindowW(L"button", L"Previous", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 280, 410, 75,20, hWnd,(HMENU)EXER_PREV, NULL, NULL);

		break;
	case 9:
		CreateWindowW(L"static", L"10. Glute bridge\n\n"
		"The glute bridge effectively works your entire posterior chain, which isn’t only good for you, but will make your booty look perkier as well.\n\n"
		"1. Start by lying on the floor with your knees bent, feet flat on the ground, and arms straight at your sides with your palms facing down.\n\n"
		"2. Pushing through your heels, raise your hips off the ground by squeezing your core, glutes, and hamstrings. Your upper back and shoulders should still be in contact with the ground, and your core down to your knees should form a straight line.\n\n"
		"3. Pause 1-2 seconds at the top and return to the starting position.\n\n"
		"4. Complete 10-12 reps for 3 sets.", WS_VISIBLE | WS_CHILD | SS_LEFT, 5,5,450,400, hWnd, NULL,NULL,NULL);    // ini juga ya
	
		CreateWindowW(L"static", L"10/10", WS_VISIBLE | WS_CHILD | SS_LEFT, 100,410,40,20, hWnd, NULL,NULL,NULL);
		CreateWindowW(L"button", L"Previous", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 280, 410, 75,20, hWnd,(HMENU)EXER_PREV, NULL, NULL);
	default:
		break;
	}
	
}

void Savemenu(HWND hWnd)
{
	CreateWindowW(L"static", L"Name", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER , 100, 50, 100, 20, hWnd,NULL ,NULL,NULL);
	CreateWindowW(L"static", L"BMR", WS_VISIBLE | WS_CHILD | WS_BORDER  | SS_CENTER , 200, 50, 100, 20, hWnd,NULL ,NULL,NULL);
	CreateWindowW(L"static", L"Calorie Gain", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER , 300, 50, 100, 20, hWnd,NULL ,NULL,NULL);

	hNama1 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | SS_CENTER , 100, 100, 100, 20, hWnd,NULL ,NULL,NULL);
	hBMR1 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | SS_CENTER , 200, 100, 100, 20, hWnd,NULL ,NULL,NULL);
	hHasil1 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | SS_CENTER , 300, 100, 100, 20, hWnd,NULL ,NULL,NULL);

	hNama2 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | SS_CENTER , 100, 150, 100, 20, hWnd,NULL ,NULL,NULL);
	hBMR2 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | SS_CENTER , 200, 150, 100, 20, hWnd,NULL ,NULL,NULL);
	hHasil2 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | SS_CENTER , 300, 150, 100, 20, hWnd,NULL ,NULL,NULL);

	hNama3 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | SS_CENTER , 100, 200, 100, 20, hWnd,NULL ,NULL,NULL);
	hBMR3 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | SS_CENTER , 200, 200, 100, 20, hWnd,NULL ,NULL,NULL);
	hHasil3 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | SS_CENTER , 300, 200, 100, 20, hWnd,NULL ,NULL,NULL);

	hNama4 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | SS_CENTER , 100, 250, 100, 20, hWnd,NULL ,NULL,NULL);
	hBMR4 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | SS_CENTER , 200, 250, 100, 20, hWnd,NULL ,NULL,NULL);
	hHasil4 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | SS_CENTER , 300, 250, 100, 20, hWnd,NULL ,NULL,NULL);

	hNama5 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | SS_CENTER , 100, 300, 100, 20, hWnd,NULL ,NULL,NULL);
	hBMR5 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | SS_CENTER , 200, 300, 100, 20, hWnd,NULL ,NULL,NULL);
	hHasil5 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | SS_CENTER , 300, 300, 100, 20, hWnd,NULL ,NULL,NULL);

	CreateWindowW(L"button", L"RESET", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 280, 410, 75,20, hWnd,(HMENU)SAVE_RESET, NULL, NULL);

}
