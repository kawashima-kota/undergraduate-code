#!/usr/bin/perl
open(IN,"date/uniprot_sprot.dat");
open(OUT,">kadai2.txt");
@actn=();
$x=0;
$sequence="";
%count=("A"=>0,"B"=>0,"C"=>0,"D"=>0,"E"=>0,"F"=>0,"G"=>0,"H"=>0,"I"=>0,"J"=>0,"K"=>0,"L"=>0,"M"=>0,"N"=>0,"O"=>0,"P"=>0,"Q"=>0,"R"=>0,"S"=>0,"T"=>0,"U"=>0,"V"=>0,"W"=>0,"X"=>0,"Y"=>0,"Z"=>0);
@keylist=keys(%count);
$keycount=keys(%count);
#print"$keycount\n";
#print"@keylist\n";
while(<IN>){
  $line=$_;
  if($line=~/ACT_SITE/){
    @item=split(" ",$line);
    #print OUT"$item[2]";
    push(@actn,$item[2]);
  }elsif($line=~/^SQ/ and @actn!=()){
    $x=1;
  }elsif($line=~/^ID/ and $x==1){
    for($i=0;$i<=$#seq;$i++){
      $sequence.=$seq[$i];
    }
    #print "@actn\n";
    #print OUT"$sequence\n";
    for($i=0;$i<=$#actn;$i++){
      $sub=substr($sequence,$actn[$i]-1,1);
     # print OUT"$sub\n";
      for($j=0;$j<$keycount;$j++){
        if($sub eq $keylist[$j]){
          $count{$keylist[$j]}++;
        }
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
for($i=0;$i<$keycount;$i++){
  print OUT"$keylist[$i] $count{$keylist[$i]}\n";
}
close(OUT);
close(IN);
