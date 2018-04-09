
extern int PasswordDialog (HWND hDlg, int Msg, int wParam, int lParam)
{
	for(;;)
	{
		if(Msg==WM_INITDIALOG)
		{
            EnableWindow(MainDialog_hWnd,FALSE);
			PasswordDialog_hWnd=hDlg;
			SendMessage(PasswordDialog_hWnd, WM_SETICON, TRUE,(LPARAM)LoadIcon(GetWindowInstance(PasswordDialog_hWnd), MAKEINTRESOURCE(100)));
			SendMessage(PasswordDialog_hWnd,(UINT)WM_SETTEXT,(WPARAM)0,(LPARAM)"128Beta - Password");
			CenterWindow(PasswordDialog_hWnd);
			infotext_static=GetDlgItem(PasswordDialog_hWnd,101);
			password_edit=GetDlgItem(PasswordDialog_hWnd,102);
			if(encr || !decr)
				SetText(infotext_static,"Enter A Password To Be Used To Encrypt This Data");
			if(decr || !encr)
				SetText(infotext_static,"Enter The Password That Was Used To Encrypt This Data.");
			break;
		}
		//----------------------------------------------------------------------

		if(Msg==WM_COMMAND)
		{
			if(wParam==103)
			{
				if(encr || !decr)
				{
					EndDialog(PasswordDialog_hWnd,0);
					CleanUp(0,1);
					if(Encrypted(F))
					{
						MessageBox (GetActiveWindow(), "The File You Are Trying To Encrypt Is Already Encrypted!" , "128Beta - NetWorkDLS", 0 + MB_ICONASTERISK + MB_TASKMODAL);
						CleanUp(0,1);
						break;
					}
					CleanUp(0,1);
					if(incode(F,GetText(password_edit)) == 0);
					{
						CleanUp(0,0);
						if(IncodeMain(EncryptTemp,F) == 0)
							MessageBox (GetActiveWindow(), "The File Was Successfully Encrypted." , "128Beta - Success", 0 + MB_ICONASTERISK);
						CleanUp(0,1);
					}
				}

				if(decr || !encr)
				{
					EndDialog(PasswordDialog_hWnd,0);
					CleanUp(0,1);
					if(!Encrypted(F))
					{
						MessageBox (GetActiveWindow(), "The File You Are Trying To Decrypt Is Not Encrypted!" , "128Beta - NetWorkDLS", 0 + MB_ICONASTERISK);
						CleanUp(0,1);
						break;
					}
					RemoveFlag(F);
					CleanUp(0,1);
					if(DecodeMain(FileToChangeTemp,EncryptTemp) == 0)
					{
						CleanUp(0,0);
						if(decode(F,GetText(password_edit)) == 128)
							MessageBox (GetActiveWindow(), "The File Was Successfully Decrypted." , "128Beta - Success", 0 + MB_ICONASTERISK);
						CleanUp(0,1);
					}
					unlink(FileToChangeTemp);
				}
                CleanUp(0,1);
				encr = 0;
				decr = 0;
				EndDialog(PasswordDialog_hWnd,0);
			}

			if(wParam==104)
			{
    			CleanUp(0,1);
				encr = 0;
				decr = 0;
				EndDialog(PasswordDialog_hWnd,0);
                PasswordDialog_hWnd = 0;
			}

			break;
		}
		if(Msg==WM_CLOSE)
		{
   			CleanUp(0,1);
			encr = 0;
    		decr = 0;
    		EndDialog(PasswordDialog_hWnd,0);
            PasswordDialog_hWnd = 0;
		}

		break;
	}
	return 0;
}

