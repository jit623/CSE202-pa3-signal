#!/usr/bin/perl

# Usage: checkOutput.pl <output file> <number of children> [<output file> <number of children> ...]
# Each run is scored out of 20; the total is out of 20 * (number of runs).
# Exits 0 only when every run gets a full score (used by the autograder).

use strict;
use warnings;

if ($#ARGV < 1 || @ARGV % 2 != 0) {
  print "\nUsage example: $0 output_4 4 output_16 16\n";
  print "\n  where 4 and 16 are the values of NUMCHILDREN and each output file is produced as follows:\n";
  print "\n  ./prog3 2>&1 | tee output_4\n\n";
  exit(1);
}

my $PER_RUN = 20;

# Scores one output file; prints the line counts and returns the score out of 20.
sub check_output {
  my ($file, $numChildren) = @_;
  my $score = 0;
  my $installing = 0;
  my $childSending = 0;
  my $parentSending = 0;
  my $childCaught = 0;
  my $parentCaught = 0;
  my $normally = 0;
  my $abnormally = 0;
  my $total = 0;

  open(my $in, "<", $file) || die("Can't open $file for reading - $!");
  while (<$in>) {
    if (/Parent process \d+ installing signal handlers/i) {
      $installing++;
    } elsif (/Child process \d+ sending \w+ to the parent process with the value \d+/i) {
      $childSending++;
    } elsif(/Parent process \d+ sending SIGUSR1 to the child process \d+ with the value \d+/i){
      $parentSending++;
    } elsif (/Parent process caught \w+ with the value \d+/i) {
      $parentCaught++;
    } elsif(/Child process caught \w+ with the value \d+/i){
      $childCaught++;
    } elsif (/Child process \d+ terminated normally with exit status \d+/i) {
      $normally++;
    } elsif (/Child process \d+ terminated abnormally/i) {
      $abnormally++;
    } elsif(/Parent process \d+ received a total of \d+/i){
      $total++;
    }
  }
  close($in);

  print "=== $file (NUMCHILDREN = $numChildren) ===\n";
  print "installing     = $installing\n";
  print "child sending  = $childSending\n";
  print "child caught   = $childCaught\n";
  print "parent sending = $parentSending\n";
  print "parent caught  = $parentCaught\n";
  print "normally       = $normally\n";
  print "abnormally     = $abnormally\n";
  print "total          = $total\n";

  if ($installing == 1) {
    $score += 2;
  } elsif($installing > 1) {
    $score += 1;
  }
  foreach my $count ($childSending, $childCaught, $parentSending, $parentCaught, $normally) {
    if ($count == $numChildren) {
      $score += 3;
    } elsif ($count > 0) {
      $score += 2;
    }
  }
  if ($abnormally == 0) {
    $score += 1;
  }
  if($total == 1){
    $score += 2;
  }
  print "score          = $score/$PER_RUN\n\n";
  return $score;
}

my $score = 0;
my $max = 0;
while (@ARGV) {
  my $file = shift @ARGV;
  my $numChildren = shift @ARGV;
  $score += check_output($file, $numChildren);
  $max += $PER_RUN;
}

print "-------------------\n";
print "Score  = $score/$max\n";

exit($score == $max ? 0 : 1);
