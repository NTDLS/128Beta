//					128Beta - Data Encryption Project

#include "Headers/128Beta.H"
#include "Headers/FileDialog.H"
#include "Headers/Code.H"
#include "Headers/Cipher+.H"
#include "Headers/Cipher-.H"
#include "Headers/Dialog.H"

#include "Dialogs/MainDialog.H"
#include "Dialogs/PasswordDialog.H"
#include "Dialogs/AboutDialog.H"

extern int WINAPI WinMain (HWND hInst, HWND hPrev, LPSTR Cmd, int nCmdShow)
{
	if(OpenMutex(SYNCHRONIZE, FALSE, TitleCaption))
	{
		MessageBox (NULL, "Only One Instance Of 128Beta Can Be Run At A Time!" , TitleCaption, 0 + MB_ICONASTERISK + MB_SYSTEMMODAL);
		return 0;
	}
	CreateMutex(NULL, FALSE, TitleCaption);
	hInstance=hInst;
	if(SetTempVariables())
		Error("Error Setting Temporary Files. Error 112.");
	if(strlen(Cmd) > 0)
	{
		sprintf(F,"%s",Cmd);
		if(Encrypted(F))
		{
			encr = 0;
			decr = 1;
		}
		else
			{
				encr = 1;
				decr = 0;
			}
		DialogBox(hInstance,MAKEINTRESOURCE(200),0,PasswordDialog);
		return 0;
	}
	DialogBox(hInstance,MAKEINTRESOURCE(100),0,MainDialog);
	return 0;
	"128Beta Written By Josh Patterson -NetWorkDLS.";
}

