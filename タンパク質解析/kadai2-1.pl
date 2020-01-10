#!/usr/bin/perl
open(IN,"date/uniprot_sprot.dat");
open(OUT,">kadai2.txt");
@actn=();
$x=0;
$sequence="";
$countA=0;
$countB=0;
$countC=0;
$countD=0;
$countE=0;
$countF=0;
$countG=0;
$countH=0;
$countI=0;
$countJ=0;
$countK=0;
$countL=0;
$countM=0;
$countN=0;
$countO=0;
$countP=0;
$countQ=0;
$countR=0;
$countS=0;
$countT=0;
$countU=0;
$countV=0;
$countW=0;
$countX=0;
$countY=0;
$countZ=0;
while(<IN>){
  $line=$_;
  if($line=~/ACT_SITE/){
    @item=split(" ",$line);
push(@actn,$item[2]);
  }elsif($line=~/^SQ/ and @actn!=()){
    $x=1;
  }elsif($line=~/^ID/ and $x==1){
    for($i=0;$i<=$#seq;$i++){
      $sequence.=$seq[$i];
    }
for($i=0;$i<=$#actn;$i++){
      $sub=substr($sequence,$actn[$i]-1,1);
if($sub eq "A"){
      $countA++;
    }
    if($sub eq "B"){
      $countB++;
    }
    if($sub eq "C"){
      $countC++;
    }
    if($sub eq "D"){
      $countD++;
    }
    if($sub eq "E"){
      $countE++;
    }
    if($sub eq "F"){
      $countF++;
    }
    if($sub eq "G"){
      $countG++;
    }
    if($sub eq"H"){
      $countH++;
    }
    if($sub eq "I"){
      $countI++;
    }
    if($sub eq"J"){
      $countJ++;
    }
    if($sub eq"K"){
      $countK++;
    }
    if($sub eq"L"){
      $countL++;
    }
    if($sub eq"M"){
      $countM++;
    }
    if($sub eq"N"){
      $countN++;
    }
 if($sub eq"O"){
      $countO++;
    }
    if($sub eq"P"){
      $countP++;
    }
    if($sub eq"Q"){
      $countQ++;
    }
    if($sub eq"R"){
      $countR++;
    }
    if($sub eq"S"){
      $countS++;
    }
    if($sub eq"T"){
      $countT++;
    }
    if($sub eq"U"){
      $countU++;
    }
    if($sub eq"V"){
      $countV++;
    }
    if($sub eq"W"){
      $countW++;
    }
    if($sub eq"X"){
      $countX++;
    }
    if($sub eq"Y"){
      $countY++;
    }
    if($sub eq"Z"){
      $countZ++;
    }
    }
@actn=();
    $x=0;
    @seq=();
    $sequence="";
  }elsif($x==1){
    chop($line);
    @item2=split(" ",$line);
    push(@seq,@item2);
  }
}
print OUT"A $countA\n";
print OUT"R $countR\n";
print OUT"N $countN\n";
print OUT"D $countD\n";
print OUT"C $countC\n";
print OUT"Q $countQ\n";
print OUT"E $countE\n";
print OUT"G $countG\n";
print OUT"H $countH\n";
print OUT"I $countI\n";
print OUT"L $countL\n";
print OUT"K $countK\n";
print OUT"M $countM\n";
print OUT"F $countF\n";
print OUT"P $countP\n";
print OUT"S $countS\n";
print OUT"T $countT\n";
print OUT"W $countW\n";
print OUT"Y $countY\n";
print OUT"V $countV\n";
print OUT"B $countB\n";
print OUT"J $countJ\n";
print OUT"O $countO\n";
print OUT"X $countX\n";
print OUT"Z $countZ\n";
print OUT"U $countU\n";

close(OUT);
close(IN);
