extern int MainDialog (HWND hDlg, int Msg, int wParam, int lParam)
{
	for(;;)
	{
		if(Msg==WM_INITDIALOG)
		{
			MainDialog_hWnd=hDlg;
			SendMessage(MainDialog_hWnd, WM_SETICON, TRUE,(LPARAM)LoadIcon(GetWindowInstance(MainDialog_hWnd), MAKEINTRESOURCE(100)));
			SendMessage(MainDialog_hWnd,(UINT)WM_SETTEXT,(WPARAM)0,(LPARAM)"128Beta - NetWorkDLS");
			CenterWindow(MainDialog_hWnd);
			break;
		}
		if(Msg==WM_COMMAND)
		{
			if(wParam==102)
			{
				sprintf(F,"%s","*.*");
				OpenFileDialog(MainDialog_hWnd,"128Beta - Encrypt",F,"","*.*","",0);

				if(strcmp(F,"*.*")==0)
				{
					//    				MessageBox (NULL,"No Valad File Selected","128Gamma - ",0 + MB_ICONHAND + MB_SYSTEMMODAL);
				}
				else
				{
					encr = 1;
					decr = 0;
					DialogBox(hInstance,MAKEINTRESOURCE(200),0,PasswordDialog);
				}
			}

			if(wParam==103)
			{
				sprintf(F,"%s","*.*");
				OpenFileDialog(MainDialog_hWnd,"128Beta - Decrypt",F,"","*.*","",0);

				if(strcmp(F,"*.*")==0)
				{
					//    				MessageBox (NULL,"No Valad File Selected","128Gamma - ",0 + MB_ICONHAND + MB_SYSTEMMODAL);
				}
				else
				{
					decr = 1;
					encr = 0;
					DialogBox(hInstance,MAKEINTRESOURCE(200),0,PasswordDialog);
				}
			}

			if(wParam==104)
			{
        		EndDialog(PasswordDialog_hWnd,0);
				EndDialog(AboutDialog_hWnd,0);
				EndDialog(MainDialog_hWnd,0);
                PasswordDialog_hWnd = 0;
                AboutDialog_hWnd = 0;
                MainDialog_hWnd = 0;
                exit(0);
			}

			if(wParam==106)
			{
                EndDialog(AboutDialog_hWnd,0);
				DialogBox(hInstance,MAKEINTRESOURCE(300),0,AboutDialog);
			}

			break;
		}

		if(Msg==WM_CLOSE)
		{
        		EndDialog(PasswordDialog_hWnd,0);
				EndDialog(AboutDialog_hWnd,0);
				EndDialog(MainDialog_hWnd,0);
                PasswordDialog_hWnd = 0;
                AboutDialog_hWnd = 0;
                MainDialog_hWnd = 0;
                exit(0);
		}

		break;
	}
	return 0;
}

