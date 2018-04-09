#include <Stdio.H>
#include <Stdlib.H>
#include <Windows.H>
#include <WindowsX.H>

#if defined(__cplusplus)
#error This Program was designed to be compiled using C not C++.
#endif

#define TitleCaption "128Beta - NetWorkDLS"

extern void RemoveFlag(char *);
extern void Error(char *);

extern char *GetTempDirectory(void);
extern char *Int_Char (double );
extern char *StringScan (char *, int, int);

extern int Char_Int (char *);
extern int CleanUp(int, int);
extern int Encrypted(char *);
extern int SetTempVariables(void);
extern int incode(char *, char *);
extern int decode(char *, char *);


FILE *Working_File, *CypherTemp_File, *EncryptTemp_File;

static char CypherTemp[256];
static char EncryptTemp[256];
static char FileToChangeTemp[256];
static char F[256];
static int   StrCnt;
LPSTR StrFunc [16];
static char Header[11];
static int LoopCount;
static int KeyLeinght;
static char Temp[256];
static char Key[100];
static int End_Of_File = 0;
static char Char_Buffer;

static HWND hInstance = 0;
static HWND PasswordDialog_hWnd = 0;
static HWND MainDialog_hWnd = 0;
static HWND AboutDialog_hWnd = 0;

//////////////////////////////////////////////////////////////////////

extern char *GetTempDirectory()
{
	static char StrFunction [64][257];
	static int StrCnt;
	static char T [257];
	GetTempPath (256,T);
	if (++StrCnt==64) StrCnt = 0;
	sprintf(StrFunction[StrCnt],"%s",T);
	return StrFunction[StrCnt];
}

/////////////////////////////////////////////////////////////////////

extern char *Int_Char (double d)
{
	static int   StrCnt;
	LPSTR StrFunc [16];
	if (++StrCnt==16) StrCnt = 0;
	if (StrFunc[StrCnt]) free (StrFunc[StrCnt]);
	StrFunc[StrCnt] = (char*) malloc (2048);
	memset (StrFunc[StrCnt],0,2048);
	sprintf(StrFunc[StrCnt],"% .16g",d);
	return StrFunc[StrCnt];
}

/////////////////////////////////////////////////////////////////////

extern int Char_Int(char *string2convert)
{
	int i, lenght_string;
	int power;
	int tmp_number;
	char tmp_char;
	if (!string2convert)
	{
		string2convert = "0";
		 Error("Character To Interget Conversion Error. Error: 108.");
	}
	lenght_string = strlen(string2convert);
	for(i = 0; i < (lenght_string / 2); i++)
	{
		tmp_char = string2convert[i];
		string2convert[i] = string2convert[lenght_string - 1 - i];
		string2convert[lenght_string - 1 - i] = tmp_char;
	}
	power = 1;
	i = 0;
	tmp_number = 0;
	while (string2convert[i] != '\0')
	{
		tmp_number += (string2convert[i] - '0') * power;
		power *= 10;
		i++;
	}
	return tmp_number;
}

/////////////////////////////////////////////////////////////////////

extern char *StringScan (char *S, int length1, int length2)
{
	static  char StrFunction [64][257];
	static int StrCnt;
	if(++StrCnt==64) StrCnt = 0;
	strncpy (StrFunction[StrCnt], &S[length1], length2);
	return StrFunction[StrCnt];
}

/////////////////////////////////////////////////////////////////////

extern void Error(char *Message)
{
	MessageBox (GetActiveWindow(), Message ,TitleCaption,0 + MB_ICONHAND + MB_SYSTEMMODAL);
	CleanUp(1,1);
}

//////////////////////////////////////////////////////////////////////


extern int CleanUp(int Kill, int Delete)
{
	if(Working_File)fclose(Working_File);
	if(CypherTemp_File)fclose(CypherTemp_File);
	if(EncryptTemp_File)fclose(EncryptTemp_File);
    EnableWindow(MainDialog_hWnd,TRUE);
	Header[0] = '\0';
	Temp[0] = '\0';
	Key[0] = '\0';
	Char_Buffer = '\0';
	KeyLeinght = 0;
	LoopCount = 0;
	End_Of_File = 0;
	if(Delete)
	{
		unlink(EncryptTemp);
		unlink(CypherTemp);
	}
	if(Kill)
	{
     	unlink(EncryptTemp);
		unlink(CypherTemp);
        unlink(FileToChangeTemp);
        StrCnt = 0;
        LoopCount = 0;
        KeyLeinght = 0;
        End_Of_File = 0;
        StrFunc[0] = '\0';
        CypherTemp[0] = '\0';
        EncryptTemp[0] = '\0';
        FileToChangeTemp[0] = '\0';
        F[0] = '\0';
        Header[0] = '\0';
        Temp[0] = '\0';
        Key[0] = '\0';
        Char_Buffer = '\0';
		exit(0);
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////

extern int Encrypted(char *FileToCheck)
{
	FILE * FileToCheck_File;
	if((FileToCheck_File = fopen(FileToCheck,"rb")) == NULL)
		Error("Could Not Open Source For Read. Error: 109.");

	while (End_Of_File != EOF)
	{
		End_Of_File = fscanf(FileToCheck_File, "%c", &Char_Buffer);
		LoopCount++;
		if(LoopCount < 11)
			sprintf(Header,"%s%s",Header,&Char_Buffer);
		if(LoopCount == 11)
		{
			if(strcmp(Header,"Encrypted~") != 0)
			{
				if(FileToCheck_File)
					fclose(FileToCheck_File);
				End_Of_File = 0;
				return 0;
			}
			else
			    {
				if(FileToCheck_File)
					fclose(FileToCheck_File);
				End_Of_File = 0;
				return 1;
			}
		}
	}
	if(FileToCheck_File)
		fclose(FileToCheck_File);
	End_Of_File = 0;
	return 0;
}

//////////////////////////////////////////////////////////////////////

void RemoveFlag(char *FileToChange)
{
	LoopCount = 0;
	FILE *FileToChange_File , *FileToChangeTemp_File;
	if((FileToChange_File = fopen(FileToChange,"rb")) == NULL)
		Error("Could Not Open Source For Read.  Error: 110.");
	if((FileToChangeTemp_File = fopen(FileToChangeTemp,"wb")) == NULL)
		Error("Could Not Open Source For Read. Error: 111.");
	while (End_Of_File != EOF)
	{
		End_Of_File = fscanf(FileToChange_File, "%c", &Char_Buffer);
		LoopCount++;
		if(LoopCount > 10 && End_Of_File != EOF)
		{
			fprintf(FileToChangeTemp_File, "%c", Char_Buffer);
		}
	}
	if(FileToChangeTemp_File)
		fclose(FileToChangeTemp_File);
	if(FileToChange_File)
		fclose(FileToChange_File);
	End_Of_File = 0;
}

//////////////////////////////////////////////////////////////////////

extern int SetTempVariables()
{
    sprintf(EncryptTemp,"%s\\%s",GetTempDirectory(),"Et.128");
	sprintf(CypherTemp,"%s\\%s",GetTempDirectory(),"Ct.128");
	sprintf(FileToChangeTemp,"%s\\%s",GetTempDirectory(),"Ft.128");
	if(!EncryptTemp)
        return 1;
    if(!CypherTemp)
        return 1;
    if(!FileToChangeTemp)
        return 1;
    return 0;
}

//////////////////////////////////////////////////////////////////////

