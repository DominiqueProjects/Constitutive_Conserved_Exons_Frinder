//find in the original gff files all features of constitutive exons, return as new gff file 

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <set>
// #include <>
// #include <>
// #include <>
// #include <>
// #include <>

using namespace std;

struct bouquet
{
	string stem;
	set<string> buds;
};

int main(int argc, char const *argv[])
{
	if (argc == 2 && strcmp(argv[1],"-h"))
		{
			cerr<<"Usage: "<<argv[0]<<" -in_fbgn_fbtr_file <in_fbgn_fbtr_file> -in_gff_file <in_gff_file> -out_gff_file <out_gff_file>"<<endl;
			return 1;
		}

	string inf_1; string inf_2; string out_f;
 	for (int i = 0; i < argc; ++i)
	{
		if (strcmp(argv[i],"-in_fbgn_fbtr_file")==0)
		{
			inf_1 = argv[i+1];
		}
		if (strcmp(argv[i],"-in_gff_file")==0)
		{
			inf_2 = argv[i+1];
		}
		if (strcmp(argv[i],"-out_gff_file")==0)
		{
			out_f = argv[i+1];
		}
	}


	//build FBgn bouquet:
	std::vector<bouquet> fbgns_bouq;
	// bouquet bouq_0;
	// bouq_0.stem = "a0"; bouq_0.buds.insert("a0");
	// fbgns_bouq.push_back(bouq_0); exons_bouq.push_back(bouq_0);


	ifstream in_fbgn_fbtr_file (inf_1);
	string line;
	int count = 0;
	if (in_fbgn_fbtr_file.is_open())
	{
		while(getline(in_fbgn_fbtr_file,line))
		{
			if ((line.front() != '#') && !line.empty())
			{
				string this_fbgn = line.substr(0,11);
				int count_fbgn = 0;
				for (int i = 0; i < fbgns_bouq.size(); ++i)
				{
					if (fbgns_bouq[i].stem == this_fbgn)
					{
						fbgns_bouq[i].buds.insert(line.substr(12,11));
						// for (set<string>::iterator it = fbgns_bouq[i].buds.begin();it != fbgns_bouq[i].buds.end() ; ++it)////////////////////////
						// {////////////
						// 	cout << *it << ' ';
						// }////////////
						// cout<<'\n';/////////////////////////
						// //cout<< count_fbgn<<'\n';//////////////
						count_fbgn ++;
					}
				}
				if (count_fbgn == 0 )
				{
					count ++;
					fbgns_bouq.resize(count);
					fbgns_bouq[count-1].stem = this_fbgn;
					fbgns_bouq[count-1].buds.insert(line.substr(12,11));
					// cout<<"count "<<count<<'\n';////////////////
				}
			}
		}
	}
	else cout<< "Unable to open file "<< inf_1<<'\n';

	// cout<<fbgns_bouq[5].stem<<'\n'; ////////////////////
	// for (set<string>::iterator it = fbgns_bouq[5].buds.begin();it != fbgns_bouq[5].buds.end() ; ++it)
	// {////////////
	// 	cout << *it << '\n';
	// }////////////

	//set up outfile
	ofstream out_gff_file (out_f);
	//build exon bouquet:
	ifstream in_gff_file (inf_2);
	line.empty(); 
	if (in_gff_file.is_open())
	{
		while(getline(in_gff_file,line))
		{
			if ((line.front()!='#') && !line.empty())
			{
				size_t found = line.find('\t'); found = line.find('\t',found+1); 
				size_t found_1 = line.find('\t',found+1);
				string type = line.substr(found+1,found_1-found-1);
				if (type=="exon")
				{
					set<string> this_fbtr_set;
					size_t foundd = line.find("FBtr");
					while(foundd != string::npos)
					{
						this_fbtr_set.insert(line.substr(foundd,11));
						foundd = line.find("FBtr",foundd+1);
					}
					for (int i = 0; i < fbgns_bouq.size(); ++i)
					{
						if (fbgns_bouq[i].buds == this_fbtr_set)
						{
							out_gff_file<<line<<";ID="<<fbgns_bouq[i].stem<<'\n';
						}
					}
					

				}
			}
		}
	}
	else cout<<"Unable to open file "<<inf_2<<'\n';


	return 0;
}
