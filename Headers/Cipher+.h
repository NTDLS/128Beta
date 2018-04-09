
int incode(char *Source, char *Incode_Key)
{
	if((Working_File = fopen(Source,"rb")) == NULL)
		Error("Could Not Open Source For Read. Error: 104.");
	if((EncryptTemp_File = fopen(EncryptTemp,"wb")) == NULL)
		Error("Could Not Open Temp File For Write. Error: 105.");

	if(strlen(Incode_Key) < 10)
		fprintf(EncryptTemp_File,"0");
	fprintf(EncryptTemp_File,"%d",strlen(Incode_Key));
	fprintf(EncryptTemp_File,"~%s~",Incode_Key);
	End_Of_File = 0;
	while (End_Of_File != EOF)
	{
		End_Of_File = fscanf(Working_File, "%c", &Char_Buffer);
		if (End_Of_File != EOF)
		{
			Char_Buffer = Char_Buffer + 128;
			fprintf(EncryptTemp_File, "%c", Char_Buffer);
		}

	}
	return 0;
}

