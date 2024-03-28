#! user/bin/perl -w

my $ARGC = @ARGV;
my $WINDOW_SIZE = 10;                                           #Default window size value goes from 7-11
my $hydro_threshold = 2.24;                                     #Default mean hydropathy for transmembrane domains is ~1.86 +- 0.38 min = 1.48 max = 2.24
my $fasta_flag = 0;
my $seq_length = 0;
my $cluster_count = 0;
my $cluster_num = 0;
my $hydro_sum=0;
my $hydro_mean = 0;
my $clustering = 0;
my @cluster_array;
my $temp = "";
my $prot_seq = "";
my $i;
my $j;

my %hydro = (                                                   #Aminoacids hydrophobicity hash
A => 1.800, 
C => 2.500, 
D => -3.500, 
E => -3.500,
F => 2.800, 
G => -0.400, 
H => -3.200, 
I => 4.500,
K => -3.900, 
L => 3.800, 
M => 1.900, 
N => -3.500,
P => -1.600, 
Q => -3.500, 
R => -4.500, 
S => -0.800,
T => -0.700, 
V => 4.200, 
W => -0.900, 
Y => -1.300
);

if($ARGC == 1)                                                  #Open file from command line, if given
    {
    open(INPUT, '<', $ARGV[0]) || die "Couldn't open $ARGV[1]\n";
    }
else                                                            #If no input file was given on program run, ask for input
    {
    print"Give the name of input file\n";
    $input_file = <STDIN>;
    chomp $input_file;
    open(INPUT, '<', $input_file) || die "Coundn't open $input_file\n";
    }

while($temp = <INPUT>)                                          #Load sequence to variable
    {
    if($fasta_flag == 1)
        {
        $prot_seq .= $temp;
        }
    elsif($temp =~ /^.*/)
        {
        $fasta_flag = 1;
        }
    }

$prot_seq =~ s/[^\w]//g;                                        #Remove white space from sequence
$seq_length = length($prot_seq);                                #Calculate length of sequence

if($seq_length < $WINDOW_SIZE) { die "The length of the protein is too short\n"; }

my @window_aa = split("",$prot_seq);

for($i = 0; $i <= $seq_length - $WINDOW_SIZE; $i++)             #i is used to keep track of which window we are calculating
    {
    $hydro_sum = 0;

    for($j = $i; $j < $i + $WINDOW_SIZE; $j++)                  #j is used to calculate the hydropathy of the residues in the current window
        {
        $hydro_sum += $hydro{$window_aa [$j]};
        }

    $hydro_mean = $hydro_sum/$WINDOW_SIZE;

    if($hydro_mean >= $hydro_threshold && $clustering == 0)     #Chech if a cluster starts from this window
        {
        $cluster_array[$cluster_count][0] = $i;
        $cluster_array[$cluster_count][1] = $i + $WINDOW_SIZE;
        $clustering = 1;
        }
    elsif($hydro_mean >= $hydro_threshold && $clustering == 1)  #Check if there is an unfinished cluster and if this window can be added to it
        {
        $cluster_array[$cluster_count][1] = $i + $WINDOW_SIZE;
        }
    elsif($hydro_mean < $hydro_threshold && $clustering == 1)   #Check if cluster ends here
        {
        $cluster_count++;
        $clustering = 0;
        }

    $hydro_mean = 0;
    }

open($output_file, '>', "transmembrane_domains_out.txt");                          #Open output file and print results

for($i = 0; $i < $cluster_count; $i++)
    {
    print $output_file "Transmembrane domain ", $i+1, " Starts:", $cluster_array[$i][0], "\t Ends: ",  $cluster_array[$i][1], "\n";
    }

close($output_file);

