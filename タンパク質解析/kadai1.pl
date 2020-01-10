#!/usr/bin/perl
open(IN,"pdb1mbd.ent.txt");
open(OUT,">kadai1.txt");

while(<IN>){
  $line=$_;
  if($line=~/^ATOM/ && $line=~/CA/){
    @item=split(" ",$line);
    push(@name,$item[3]);
    push(@number,$item[4]);
    push(@x,$item[5]);
    push(@y,$item[6]);
    push(@z,$item[7]);
  }
}
for($i=0;$i<=$#name;$i++){
  for($j=$i+1;$j<=152;$j++){
    $dx=$x[$i]-$x[$j];
    $dy=$y[$i]-$y[$j];
    $dz=$z[$i]-$z[$j];
    $date=sqrt($dx**2 + $dy**2 + $dz**2);
    if($date<=7){
      push(@result1,[$name[$i],$number[$i],$name[$j],$number[$j],$date]);
    }
    if($date>7 and $date<10){
      push(@result2,[$name[$i],$number[$i],$name[$j],$number[$j],$date]);
    }
  }
}
foreach $R1(@result1){
  print OUT"@{$R1}\n";
}
foreach $R2(@result2){
  print OUT"@{$R2}\n";
}

close(OUT);
close(IN);
