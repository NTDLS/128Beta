
extern int AboutDialog (HWND hDlg, int Msg, int wParam, int lParam)
{
	for(;;)
	{
		if(Msg==WM_INITDIALOG)
		{
			AboutDialog_hWnd=hDlg;
			SendMessage(AboutDialog_hWnd, WM_SETICON, TRUE,(LPARAM)LoadIcon(GetWindowInstance(AboutDialog_hWnd), MAKEINTRESOURCE(100)));
			SendMessage(AboutDialog_hWnd,(UINT)WM_SETTEXT,(WPARAM)0,(LPARAM)"128Beta - About");
			CenterWindow(AboutDialog_hWnd);
			break;
		}
		//----------------------------------------------------------------------

		if(Msg==WM_COMMAND)
		{

			if(wParam==101)
			{
				EndDialog(AboutDialog_hWnd,0);
                AboutDialog_hWnd = 0;
			}

			break;
		}

		if(Msg==WM_CLOSE)
		{
			EndDialog(AboutDialog_hWnd,0);
            AboutDialog_hWnd = 0;
		}

		break;
	}
	return 0;
}

