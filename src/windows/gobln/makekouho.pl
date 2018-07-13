
$di="c:\\apps\\dbpro\\Help\\commands";

opendir(SESDIR,$di);
@items=grep(/.htm$/,readdir(SESDIR));
closedir(SESDIR);
open(OUT,"> kouho.ini");

foreach $item(@items){
 open(IN,"$di\\$item");
 while($buf=<IN>){
 if($buf=~/:/){
# <a href="display\PERFORM CHECKLIST FOR DISPLAY MODES.htm">
  $buf=~s/\xd|\xa//g;
  $buf=~m/href="([^"]*)"/;$url=$1;
  $buf=~s/<[^>]*>//g;
  ($cmd,$help)=split(/ : /,$buf);
  $help=~s/$cmd//;$help=~s/^ //;

  @cmds=split(/ /,$cmd);
  $cmd2="";$a=0;
  foreach $c(@cmds){
   $c1=substr($c,0,1);if($a==0){$c1=~tr/A-Z/a-z/;}
   $c2=substr($c,1);$c2=~tr/A-Z/a-z/;
   $cmd2.="$c1$c2";++$a;}

  if($help=~/Return/){$repCmd="$cmd2\\(,$cmd\\(";$cmd2.="(";}
  else{if($help ne ""){$cmd2.=" ";$cmd.=" ";}
   $repCmd="$cmd2,$cmd";
   }#  $repCmd="$cmd2\\(([^)]*)\\):,$cmd \$1:";$a=2;}
  print OUT "$cmd2,$help,$url\n";
  if($a>1){print "$repCmd\n";}}}
}
