#! user/bin/perl -w

my $ARGC = @ARGV;
my $ASCII_Offset = 33;
my $i;
my $scoring;
my $sequence_length;
my $min_score;
my $header;
my $sequence;
my $quality;
my $temp = "";
my $plus_sign;
my @quality_array;

if($ARGC == 1)                                                                      #Open file from command line, if given
    {
    open(INPUT, '<', $ARGV[0]) || die "Couldn't open $ARGV[1]\n";
    }
else                                                                                #If no input file was given on program run, ask for input
    {
    print"Give the name of input file\n";
    $input_file = <STDIN>;
    chomp $input_file;
    open(INPUT, '<', $input_file) || die "Coundn't open $input_file\n";
    }

print"Give the minimum Q scoring for the sequences\n";

$min_score = <STDIN>;
$sequence_length = 0;

open($output_file, '>', "fastq_out.txt");                                          #Open output file and print results
open($output_file_garbage, '>', "garbage_disposal.txt"); 

while($temp = <INPUT>)
    {
    $header = $temp;
    chomp $header;
    $sequence = <INPUT>;
    chomp $sequence;
    $plus_sign = <INPUT>;
    $quality = <INPUT>;
    chomp $quality;

    @quality_array = split(//, $quality);

    $sequence_length = @quality_array;
    $scoring = 0;

    for($i = 0; $i < $sequence_length; $i++)
        {
        $scoring += ord($quality_array[$i])-$ASCII_Offset;
        }

    if($sequence_length != 0 && $scoring/$sequence_length >= $min_score)
        {
        print $output_file  $header, "\n", $sequence, "\n+\n", $quality;
        }
    else    
        {
        print $output_file_garbage  $header, "\n", $sequence, "\n+\n", $quality;
        }
    }

close($output_file);
close($output_file_garbage);



