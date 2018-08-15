# Constitutive_Conserved_Exons_Frinder
Find the constitutive, conserved exons between species and return as gff files


Usage as to get speciesA-constitutive-conserved-exons.gff 

>> Go to ./01_Get_constitutive_fasta/:

	required files:
		fbgn_fbtr_fbpp_fb_2018_02.tsv
		speciesA-all-cut_FASTA.gff
		speciesA-all-exons.fas
		speciesB-all-cut_FASTA.gff
		speciesB-all-exons.fas

	>> compile find_constitutive_exons_gff.cpp and get_constitutive_exons_fasta.cpp
	find_constitutive_exons_gff will take the fbgn_fbtr_fbpp_fb_2018_02.tsv file and the speciesA-all-cut_FASTA.gff file (gff file of speciesA genome, with FASTA data removed), find in which all constitutive exons in speciesA, and return as a new gff file (speciesA-all-cut_FASTA-constitutive_exons.gff).
	get_constitutive_exons_fasta will take the speciesA-all-cut_FASTA-constitutive_exons.gff generated in the previous step and the speciesA-all-exons.fas file, return the speciesA-constitutive-exons.fas file.
	
	>> run: ./find_constitutive_exons_gff --> speciesA-all-cut_FASTA-constitutive_exons.gff
										  --> speciesB-all-cut_FASTA-constitutive_exons.gff (for later to get speciesB-constitutive-conserved-exons.gff)
		    eg. ./find_constitutive_exons_gff -in_fbgn_fbtr_file fbgn_fbtr_fbpp_fb_2018_02.tsv -in_gff_file speciesA-all-cut_FASTA.gff -out_gff_file speciesA-all-cut_FASTA-constitutive_exons.gff

	>> run: ./get_constitutive_exons_fasta --> speciesA-constitutive-exons.fas (for later to get speciesB-constitutive-conserved-exons.gff)
		  								   --> speciesB-constitutive-exons.fas
		    eg. ./get_constitutive_exons_fasta -constitutive_exons speciesA-all-cut_FASTA-constitutive_exons.gff -all_exons speciesA-all-exons.fas -out speciesA-constitutive-exons.fas

	>> copy speciesA-constitutive-exons.fas to ./02_Get_conserved_exons_gff/
	>> copy speciesB-constitutive-exons.fas to ./02_Get_conserved_exons_gff/
	>> copy speciesA-all-cut_FASTA-constitutive_exons.gff to ./03_Get_constitutive_conserved_exons_gff/

	result files:
		speciesA-all-cut_FASTA-constitutive_exons.gff
		speciesA-constitutive-exons.fas
		speciesB-all-cut_FASTA-constitutive_exons.gff
		speciesB-constitutive-exons.fas
		

>> Go to ./02_Get_conserved_exons_gff/:

	required files:
		speciesB-constitutive-exons.fas
		speciesA-all-chromosome.fas
		speciesA-constitutive-exons.fas

	>> compile parse_all-exons_file.cpp and get_target_conserved_gff.cpp
	parse_all-exons_file will parse exons.fas file into individual exon.fas files.
	get_target_conserved_gff will take each speciesB-constitutive-exons FASTA, compare (exonerate) it to speciesA-all-chromosome.fas, and return speciesA-conserved-exons.gff.

	>> run: ./conserved_exons_finder.sh --> speciesA-conserved-exons.gff
	        eg. ./conserved_exons_finder.sh dsim-constitutive-exons.fas exons dmel-all-chromosome-r6.19.fas 10 dmel-conserved-exons.gff 

	>> copy speciesA-conserved-exons.gff to ./03_Get_constitutive_conserved_exons_gff/


>> Go to ./03_Get_constitutive_conserved_exons_gff/:
