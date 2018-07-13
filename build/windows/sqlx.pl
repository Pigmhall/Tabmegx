#
# sqlx.pl

use DBI;

if($#ARGV!=5){print "not enough arg";exit;}
($db,$host,$dbname,$user,$passwd,$commit)=@ARGV;

if($db eq "Mysql"){$dns="DBI:mysql:$dbname:$host";}
elsif($db eq "Pg"){$dns="DBI:Pg:host=$host dbname=$dbname";}
elsif($db eq "Oracle"){$dns="DBI:Oracle:$dbname";}

# 他のデータベースの場合はDBDごとに$dnsを合わせて追加してください。
# 例）elsif($db eq "？？"){$dns="DBI:？？:$dbname:$host";}

# デフォルト
else{$dns="DBI:$db:$dbname:$host";}

$db=DBI->connect($dns,$user,$passwd) or die "CONNECT ERROR $DBI::errstr";
$db->{AutoCommit}=0;$db->{RaiseError}=1;

if(!open(IN,"sql.dat")){print "sql.dat not found";exit;}
$q="";while($buf=<IN>){$q.=$buf;}
close(IN);
$q=~s/[\n\r\s;]*$//;

eval{$st=$db->prepare($q);$a=$st->execute;};
if($@){$err=$db->errstr;$err=~s/in '/in '\n/g;print "$err";}
else{
print "------------------------------------------------\n";
if($q!~/SELECT/i){
 if($a eq "0E0"){print "no rows";}
 else{ print "$a row(s)"; }}
else{
 $row=0;$fieldnum=$st->{NUM_OF_FIELDS};
 for($i=0;$i<$fieldnum;$i++){$relen[$i]=length($st->{NAME}->[$i]);$digit[$i]=1;}# length($st->{NAME}->[$i]);
 while($re=$st->fetchrow_arrayref){
  for($i=0;$i<$fieldnum;$i++){
   $re2[$row][$i]=$re->[$i];
   if(length($re->[$i])>$relen[$i]){$relen[$i]=length($re->[$i]);}
   if($re->[$i]=~/\D/){$digit[$i]=0;}}
  ++$row;}

 for($i=0;$i<$fieldnum;$i++){if($i>0){print " ";}
  if($digit[$i]){print right($st->{NAME}->[$i],$relen[$i]);}
  else{print left($st->{NAME}->[$i],$relen[$i]);}}
 print "\n";
 for($i=0;$i<$fieldnum;$i++){if($i>0){print " ";}print strs("-",$relen[$i]);}
 print "\n";
 for($i=0;$i<$row;$i++){
  for($j=0;$j<$fieldnum;$j++){if($j>0){print " ";}
   if($digit[$j]){print right($re2[$i][$j],$relen[$j]);}
   else{print left($re2[$i][$j],$relen[$j]);}}print "\n";}

print "$row row(s) selected";$a=0;
}

# if(($a ne "0e0")&&($a>1)){print "\nUpdate(Delete) of 2 or more lines is not accepted.\nrollback";&rollback;}
 if($commit==1){&commit;}else{&rollback;if(!$row){print "\nrollback";}}}

$db->disconnect;

exit;

#----------------
# right(文字列,右からの数)
sub right{
 my ($s,$i);$s="";for($i=0;$i<$_[1];$i++){$s="$s ";}
 return (substr("$s$_[0]",-$_[1]));}

#left(文字列,左からの数)
sub left{
 my ($s,$i);$s="";for($i=0;$i<$_[1];$i++){$s="$s ";}
 return(substr("$_[0]$s",0,$_[1]));}

#strs(文字列,数)
sub strs{
 my ($s,$i);$s="";for($i=0;$i<$_[1];$i++){$s="$s$_[0]";}
 return($s);}
 
sub commit{eval{$st->finish;$db->commit;};
 if($@){$err=$db->errstr;}}

sub rollback{eval{$st->finish;$db->rollback;};
 if($@){$err=$db->errstr;}}
