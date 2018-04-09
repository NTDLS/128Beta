
int decode(char *Source, char *Input_Key)
{
	if((EncryptTemp_File = fopen(EncryptTemp,"rb")) == NULL)
		Error("Could Not Open Source File For Read. Error: 106");
	End_Of_File = 0;
	LoopCount = 0;
	while (End_Of_File != EOF)
	{
		End_Of_File = fscanf(EncryptTemp_File, "%c", &Char_Buffer);
		LoopCount++;

		if(LoopCount < 3)
			sprintf(Temp,"%s%s",Temp,&Char_Buffer);
		if(LoopCount == 3)
			KeyLeinght = Char_Int(Temp);

		if( LoopCount > 3 && LoopCount < KeyLeinght+4)
		{
			sprintf(Key,"%s%s",Key,&Char_Buffer);
		}
		if(LoopCount == KeyLeinght+4)
		{
			if(strcmp(Key,Input_Key) != 0)
			{
				MessageBox (GetActiveWindow(), "The Password You Entered Is Incorrect!" ,TitleCaption, 0 + MB_ICONEXCLAMATION + MB_SYSTEMMODAL);
				return 0;
				break;
			}
			else
				{
				if((Working_File = fopen(F,"wb")) == NULL)
					Error("Could Not Target File For Write. Error: 107");
			}
		}
		if(LoopCount > KeyLeinght+4)
		{
			if (End_Of_File != EOF)
			{
				Char_Buffer = Char_Buffer + 128;
				fprintf(Working_File, "%c", Char_Buffer);
			}
		}
	}
	return 128;
}
/////////////////////////////////////////////////////////////////////

