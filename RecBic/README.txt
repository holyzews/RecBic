Provides an executable for RecBic algorithm with was published by Xiangyu.

Installation:
Before installation, please make sure that your computer already installed GCC version supporting c++ 11.
Extract the package
	% unzip RecBic.zip
Move to the RecBic folder
	% cd RecBic
Make an executable programe
	% make
Then you can use it with following options.

[Usage]\n\
$ ./RecBic -i filename [argument list]\n\
===================================================================\n\
[Input]\n\
-i : input file must be one of two tab-delimited formats\n\
  A) continuous data (default, use pre-set discretization (see -q and -r))\n\
     -------------------------------------\n\
     o        cond1    cond2    cond3\n\
     gene1      2.4      3.5     -2.4\n\
     gene2     -2.1      0.0      1.2\n\
     -------------------------------------\n\
  B) discrete data with arbitray classes (turn on -d)\n\
     use '0' for missing or insignificant data\n\
     -------------------------------------\n\
     o        cond1    cond2    cond3\n\
     gene1        1        2        2\n\
     gene2       -1        2        0\n\
     -------------------------------------\n\
-z : set the max number of columns of biclusters may have\n\
	 default: 40\n\
-x : set the min number of rows of biclusters may have\n\
	 default: 0.05*size of the input matrix\n\
-r : the number of ranks as which we treat the up(down)-regulated value\n\
     when discretization\n\
     default: 1\n\
-d : user should send their processed discrete data\n\
     to different value classes, see above\n\
===================================================================\n\
[Output]\n\
-o : number of blocks to report, default: 1\n\
-f : filtering overlapping blocks,\n\
     default: 1 (do not remove any blocks)\n\
-k : minimum column width of the block,\n\
     default: 5% of columns, minimum 2 columns\n\
-c : consistency level of the block (0.5-1.0], the minimum ratio between the\n\
     number of identical valid symbols in a column and the total number \n\
     of rows in the output\n\
     default: 0.9\n\
===================================================================\n";

