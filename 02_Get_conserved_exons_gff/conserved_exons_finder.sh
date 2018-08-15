#usage:
#	./conserve_exons_finder <query constitutive-exon file> <query individual exon output dir> <target genome> <number of cores for parallel> <output target genome conserved region.gff>
#!/bin/bash
query_all_exons=$1
querydir=$2
targetgenome=$3
Cores=$4
exonerate_output=out_sugar.txt
target_con_GFF=$5

#write to individual 
./parse_all-exons_file -all_exons ${query_all_exons} -out_dir ${querydir}

#find conserved region by exonerate
ls ${querydir}/ | parallel -j ${Cores} exonerate --model est2genome --softmasktarget yes --bestn 1 --minintron 20 --maxintron 20000 --showvulgar no --showalignment no --showsugar yes --query ${querydir}/{} --target ${targetgenome} --showtargetgff yes >> ${exonerate_output}

echo exoneration completed...
#get target.gff
./get_target_conserved_gff -exo_out ${exonerate_output} -out_gff ${target_con_GFF}

#remove individual exon files
rm -r ${querydir}/