//Find the common constitutive exons in two species
//We have the constitutive_exon.gff file previousely generated, we need to extract the FASTA file of the constitutive exons from the all-exon.FASTA file. The common identification or a given exon between these two files is FBgn+location

//Usage:
//	./get_constitutive_exons -constitutive_exons <> -all_exons <> -outf <>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int set_shared_size(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	else if (b < a)
	{
		return b;
	}
	else return a;
}

struct bundle 
{
	string header;
	string fasta;
	string id;
};

int main (int argc, char* argv[]) 
{	
	string inf1_tiltle, inf2_tiltle, outf_title;
	for (int i = 1; i < argc; ++i)
		{
			if (string(argv[i])=="-h")
			{
				cerr<<"Usage: "<<argv[0]<<" -constitutive_exons <input constitutive_exon.gff> -all_exons <input all_exon.FASTA> -out <output constitutive_exon.FASTA>";
			}
			if (string(argv[i])=="-constitutive_exons")
			{
				inf1_tiltle = string(argv[i+1]);
			}
			if (string(argv[i])=="-all_exons")
			{
				inf2_tiltle = string(argv[i+1]);
			}
			if (string(argv[i])=="-out")
			{
				outf_title = string(argv[i+1]);
			}
		}	


	string line;
	vector<string> L1;//store constitutive_gff identities
	ifstream in_file_1 (inf1_tiltle);
	if(in_file_1.is_open())
	{
		while(getline(in_file_1,line))
		{
			string cons_gff_id; int count = 0; size_t found = 0, found_loc1a, found_loc1b, found_loc2a, found_loc2b, found_fbgn;
    		while(found != string::npos)
    		{
    			found = line.find('\t',found+1);
    			count++;
    			//cout<<found<<' '<<count<<'\n';////////////////////////////////
    			if (count == 3)
    			{
    				found_loc1a = found+1;
    				//cout<<found<<' '<<count<<'\n';////////////////////////////////
    			}
    			else if (count == 4)
    			{
    				found_loc1b = found-1; found_loc2a = found+1;
    				//cout<<found<<' '<<count<<'\n';////////////////////////////////
    			}
    			else if (count ==5)
    			{
    				found_loc2b = found-1;
    				//cout<<found<<' '<<count<<'\n';////////////////////////////////
    			}
    			else if (count == 8)
    			{
    				found = line.find("FBgn"); found_fbgn = found;
    				//cout<<found<<' '<<count<<'\n';////////////////////////////////
    			}
    		}
    		cons_gff_id = line.substr(found_fbgn,11) + ' ' + line.substr(found_loc1a,found_loc1b - found_loc1a +1) + ' ' +line.substr(found_loc2a,found_loc2b - found_loc2a +1);
			L1.push_back(cons_gff_id);//format in L1: FBgn loc0 loc1
			line.clear();
		}
		cout<<"L1 completed...\n";///////////////////////////////////////
		sort(L1.begin(),L1.end());
		// for (int i = 0; i < 50; ++i)///////////////////////////////////////
		// {///////////////////////////////////////
		// 	cout<<L1[i]<<'\n';///////////////////////////////////////
		// }///////////////////////////////////////
	}
	else cout<<"Unable to open "<< inf1_tiltle<<'\n';
	

	line.clear(); 
	vector<string> L2;//store all_exon.FASTA ids
	ifstream in_file_2 (inf2_tiltle);
	if(in_file_2.is_open())
	{
		while(getline(in_file_2,line))
		{
			if (line.front()=='>')
			{
				size_t found, found_loc1a, found_loc1b, found_loc2a, found_loc2b, found_locequal; string all_exon_fasta_id;
				if (found != string::npos)
				{
					found = line.find("FBgn");
					all_exon_fasta_id = line.substr(found,11);
					found = line.find("loc="); found_locequal = found;
					found = line.find('(',found_locequal+1);
					if (found != string::npos)
					{
						found_loc1a = found + 1;
					}
					else
					{
						found = line.find(':', found_locequal+1); found_loc1a = found + 1;
					}
					found = line.find("..", found_loc1a+1); found_loc1b = found - 1; found_loc2a = found + 2;
					found = line.find(')',found_loc2a);
					if (found != string::npos)
					{
						found_loc2b = found - 1;
					}
					else
					{
						found = line.find(';',found_loc2a + 1); found_loc2b = found - 1;
					}
					all_exon_fasta_id = all_exon_fasta_id + ' ' + line.substr(found_loc1a,found_loc1b - found_loc1a +1) + ' ' +line.substr(found_loc2a,found_loc2b - found_loc2a +1);
				}
				L2.push_back(all_exon_fasta_id);//format in L1: FBgn loc0 loc1
			}
		}
		cout<<"L2 completed...\n";/////////////////////////////////
		sort(L2.begin(),L2.end());
		// for (int i = 0; i < 50; ++i)///////////////////////////////////////
		// {///////////////////////////////////////
		// 	cout<<L2[i]<<'\n';///////////////////////////////////////
		// }///////////////////////////////////////
	}
	else cout<<"Unable to open "<< inf2_tiltle<<'\n';
	

	//find the shared ids:
	int size_for_share = set_shared_size(L1.size(),L2.size());
	std::vector<string> shared (size_for_share);

	std::vector<string>::iterator it;
	it = set_intersection(L1.begin(),L1.end(),L2.begin(),L2.end(),shared.begin());
	shared.resize(it-shared.begin());
	shared.push_back("zzzzzz");//to account for the last id when later comparison with shared

	cout<<"number of shared read: "<<shared.size()<<'\n';//////////////////


	vector<bundle> BUN;//store all_exon.FASTA 
	ifstream in_file_2_again (inf2_tiltle);
	line.clear(); int count = -1;
	if (in_file_2_again.is_open())
	{
		while(getline(in_file_2_again,line))
		{
			if (line.front()=='>')
			{
				count++;
				BUN.resize(count+1);
				BUN[count].header = line;
				size_t found, found_loc1a, found_loc1b, found_loc2a, found_loc2b, found_locequal; string all_exon_fasta_id;
				if (found != string::npos)
				{
					found = line.find("FBgn");
					all_exon_fasta_id = line.substr(found,11);
					found = line.find("loc="); found_locequal = found;
					found = line.find('(',found_locequal+1);
					if (found != string::npos)
					{
						found_loc1a = found + 1;
					}
					else
					{
						found = line.find(':', found_locequal+1); found_loc1a = found + 1;
					}
					found = line.find("..", found_loc1a+1); found_loc1b = found - 1; found_loc2a = found + 2;
					found = line.find(')',found_loc2a);
					if (found != string::npos)
					{
						found_loc2b = found - 1;
					}
					else
					{
						found = line.find(';',found_loc2a + 1); found_loc2b = found - 1;
					}
					all_exon_fasta_id = all_exon_fasta_id + ' ' + line.substr(found_loc1a,found_loc1b - found_loc1a +1) + ' ' +line.substr(found_loc2a,found_loc2b - found_loc2a +1);
				}
				BUN[count].id = all_exon_fasta_id;
			}
			else
			{
				BUN[count].fasta += line;
			}
		}

	}
	else cout<<"Unable to open "<<inf2_tiltle<<" again!\n";

	ofstream out_file (outf_title);
	for (int i = 0; i < BUN.size(); ++i)
	{
		std::vector<string>::iterator found_it = find(shared.begin(),shared.end(),BUN[i].id);
		if (found_it != shared.end())
		{
			out_file << BUN[i].header << '\n' << BUN[i].fasta <<'\n';
		}
	}

	return 0;
}