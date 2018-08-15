//write each exon in all-exons file into seperate .fas files
//usage: ./parse_all_exons_file -all_exons <all-exons file> -out_dir <output directory for individual exon files>
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
	string inf_title, out_di;
	for (int i = 0; i < argc; ++i)
	{
		if (strcmp(argv[i],"-all_exons") == 0)
		{
			inf_title = argv[i+1];
		}
		if (strcmp(argv[i],"-out_dir") == 0)
		{
			out_di = argv[i+1];
		}
	}

	//set up out_put directory for individual exons
	string sys_cmd = "mkdir " + out_di;
	system(sys_cmd.c_str());

	//read in the whole of all-exon file into a vector
	std::vector<string> vec_of_exons;
	ifstream inf (inf_title);
	string line;
	if (inf.is_open())
	{
		while(getline(inf,line))
		{
			vec_of_exons.push_back(line);
		}
	}
	else
		cout<<"Unable to open file: "<<inf_title<<'\n';
	vec_of_exons.push_back(">end");//redundant at the end for later iteration use

	//collect pointers for '>' items in all-exon_vec
	int exon_count=0;
	std::vector< vector<string>::iterator > vec_of_it_of_exon_name;
	for (vector<string>::iterator it=vec_of_exons.begin(); it != vec_of_exons.end(); ++it)
	{
		string this_line = *it;
		if (this_line.front() == '>')
		{
			vec_of_it_of_exon_name.push_back(it);
			exon_count++;
		}
	}

	//output to individual files
	for (int i = 0; i < vec_of_it_of_exon_name.size()-1; ++i)
	{
		string exon_name = *vec_of_it_of_exon_name[i];
		size_t found = exon_name.find(' ');
		exon_name = exon_name.substr(1,found-1);
		found = exon_name.find(':'); exon_name[found] = '_';
		ofstream outf (out_di + '/' + exon_name + ".fas");
		while(vec_of_it_of_exon_name[i]!=vec_of_it_of_exon_name[i+1])
		{
			outf<< *vec_of_it_of_exon_name[i]<<'\n';
			vec_of_it_of_exon_name[i]++;
		}
	}
	cout<<"Wrote "<<exon_count-1<<" exons to individual files\n";
	return 0;
}