int IncodeMain(char *, char *);
int DecodeMain(char *, char *);
//--------------------------------------------------------------------
void fin(void);
void assemble(void);
void code(void);
//--------------------------------------------------------------------
unsigned short ax,bx,cx,dx,si,tmp,x1a2,x1a0[5],res,i,inter,cfc,cfd,compte;
unsigned char cle[11];
short c;
FILE *in,*out;
//--------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////

int IncodeMain(char *Input_File,char *Output_File)
{
	si=0;
	x1a2=0;
	i=0;
	strcpy(cle,"128Gamma~Encrypted");
	if ((in=fopen(Input_File,"rb")) == NULL)
	{
		Error("Could Not Open Source File For Incode. Error: 100.");
		fin();
		return -1;
	}
	SetFileAttributesA(Output_File,128);
	if ((out=fopen(Output_File,"wb")) == NULL) {
		Error("Could Not Open Temp File For Incode. Error: 101.");
		fin();
		return -1;
	}

	fprintf(out,"Encrypted~");
	while ( (c=fgetc(in)) != EOF)
	{
		assemble();
		cfc=inter>>8;
		cfd=inter&255;
		for (compte=0;compte<=9;compte++)
		{
			cle[compte]=cle[compte]^c;
		}
		c = c ^ (cfc^cfd);
		fputc(c,out);
	}
	fclose (in);
	fclose (out);
	fin();
	return 0;
}

//////////////////////////////////////////////////////////////////////

int DecodeMain(char *Input_File, char *Output_File)
{
	si=0;
	x1a2=0;
	i=0;
	strcpy(cle,"128Gamma~Encrypted");
	if ((in=fopen(Input_File,"rb")) == NULL) {
		Error("Could Not Open Source File For Decode. Error: 102.");
		fin();
	}
	if ((out=fopen(Output_File,"wb")) == NULL) {
		Error("Could Not Open Temp File For Decode. Error: 103.");
		fin();
	}
	while ( (c=fgetc(in)) != EOF)
	{
		assemble();
		cfc=inter>>8;
		cfd=inter&255;
		c = c ^ (cfc^cfd);
		for (compte=0;compte<=9;compte++)
		{
			cle[compte]=cle[compte]^c;
		}
		fputc(c,out);
	}
	fclose (in);
	fclose (out);
	fin();
	return 0;
}

//////////////////////////////////////////////////////////////////////

void fin(void)
{
	for (compte=0;compte<=9;compte++)
	{
		cle[compte]=0;
	}
	ax=0;
	bx=0;
	cx=0;
	dx=0;
	si=0;
	tmp=0;
	x1a2=0;
	x1a0[0]=0;
	x1a0[1]=0;
	x1a0[2]=0;
	x1a0[3]=0;
	x1a0[4]=0;
	res=0;
	i=0;
	inter=0;
	cfc=0;
	cfd=0;
	compte=0;
	c=0;
}

//////////////////////////////////////////////////////////////////////

void assemble(void)
{
	x1a0[0]= ( cle[0]*256 )+ cle[1];
	code();
	inter=res;
	x1a0[1]= x1a0[0] ^ ( (cle[2]*256) + cle[3] );
	code();
	inter=inter^res;
	x1a0[2]= x1a0[1] ^ ( (cle[4]*256) + cle[5] );
	code();
	inter=inter^res;
	x1a0[3]= x1a0[2] ^ ( (cle[6]*256) + cle[7] );
	code();
	inter=inter^res;
	x1a0[4]= x1a0[3] ^ ( (cle[8]*256) + cle[9] );
	;
	code();
	inter=inter^res;
	i=0;
}

//////////////////////////////////////////////////////////////////////

void code(void)
{
	dx=x1a2+i;
	ax=x1a0[i];
	cx=0x015a;
	bx=0x4e35;
	tmp=ax;
	ax=si;
	si=tmp;
	tmp=ax;
	ax=dx;
	dx=tmp;
	if (ax!=0)
	{
		ax=ax*bx;
	}
	tmp=ax;
	ax=cx;
	cx=tmp;
	if (ax!=0)
	{
		ax=ax*si;
		cx=ax+cx;
	}
	tmp=ax;
	ax=si;
	si=tmp;
	ax=ax*bx;
	dx=cx+dx;
	ax=ax+1;
	x1a2=dx;
	x1a0[i]=ax;
	res=ax^dx;
	i=i+1;
}

//////////////////////////////////////////////////////////////////////

