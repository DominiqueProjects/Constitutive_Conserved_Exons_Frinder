## usage:
##	./get_chickpea <conserved.gff> <constitutive.gff>
#!/bin/bash

conservedGFF=$1
constitutiveGFF=$2
conserved_sortedGFF=`echo ${conservedGFF} | sed s/.gff/_sorted.gff/`
constitutive_sortedGFF=`echo ${constitutiveGFF} | sed s/.gff/_sorted.gff/`
conserved_mergedBED=`echo ${conserved_sortedGFF} | sed s/_sorted.gff/_merged.bed/`
chickpeaGFF=`echo ${constitutiveGFF} | sed s/.gff/_chickpea.gff/`

bedtools sort -i ${conservedGFF} > ${conserved_sortedGFF} 
bedtools sort -i ${constitutiveGFF} > ${constitutive_sortedGFF}

# merge overlapping and/or book-ended features in ${conserved_sortedGFF};
# this is to prevent spliting a single feature in ${constitutive_sortedGFF} 
# into overlapping sub-features with same feature ID, which could lead to 
# counting a single alignment mapped to this region more than once 
bedtools merge -i ${conserved_sortedGFF} > ${conserved_mergedBED}

# get overlapping coordinates
bedtools intersect -a ${constitutive_sortedGFF} -b ${conserved_mergedBED} -sorted > ${chickpeaGFF}