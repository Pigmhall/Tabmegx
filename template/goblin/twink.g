case :sp=4;
 switch(th[i]){
  case 0:tn[i]=tl[i]/2;if(tl[i]<sp*2){++tl[i];}else{if(tl[i]==sp*2&&rand(3)==0){th[i]=1;tl[i]=sp*2-2;}}break;
  case 1:tn[i]=tl[i]/2;if(tl[i]>0){--tl[i];}else{if(tl[i]==0&&rand(3)==0){th[i]=0;tl[i]=2;}}break;
 }
 break;
