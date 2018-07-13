case NM:SP=5;if(rand(8)==0){th[i]=rand(4);}
 switch(th[i]){
  case 0:sy-=SP;break;
  case 1:sx+=SP;break;
  case 2:sy+=SP;break;
  case 3:sx-=SP;break;}
 ax=brdRight(i);if(sx>ax){sx=ax;th[i]=rand(4);}
 ax=brdLeft(i);if(sx<ax){sx=ax;th[i]=rand(4);}
 ay=brdBottom(i);if(sy>ay){sy=ay;th[i]=rand(4);}
 ay=brdTop(i);if(sy<ay){sy=ay;th[i]=rand(4);}
break;
