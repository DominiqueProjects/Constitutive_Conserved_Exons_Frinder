//write out target-genome conserved-gff file
//usage: ./get_target_conserved_gff -exo_out <exonerate output file> -out_gff <target-genome conserved-gff file>

#include <stdio.h>
#include <string.h>
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include <stdlib.h>
#include <cstdlib>
#include <cstdio>
// #include<>
// #include<>
// #include<>
// #include<>
// #include<>
// #include<>

using namespace std;

int main(int argc, char const *argv[])
{
	string inf_exo_out_title, out_conserve_gff_title;
	for (int i = 0; i < argc; ++i)
	{
		if (strcmp(argv[i],"-exo_out") == 0)
		{
			inf_exo_out_title = argv[i+1];
		}
		if (strcmp(argv[i],"-out_gff") == 0)
		{
			out_conserve_gff_title = argv[i+1];
		}
	}


	ofstream outf (out_conserve_gff_title);

	ifstream inf (inf_exo_out_title);
	string line;
	if (inf.is_open())
	{
		while(getline(inf,line))
		{
			size_t found = line.find("\texonerate:est2genome\tsimilarity\t");
			if (found != string::npos)
			{
				outf<<line<<'\n';
			}
		}
	}
	else
		cout<<"Unable to open file: "<<inf_exo_out_title<<'\n';

	return 0;
}