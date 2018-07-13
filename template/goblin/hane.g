case :
 sx+=txx[i];sy+=tyy[i];
 tr[i]=wrapvalue(tr[i]+trs[i]);
 ax=brdRight(i);if(sx>ax){sx=ax;txx[i]=-txx[i];}
 ax=brdLeft(i);if(sx<ax){sx=ax;txx[i]=-txx[i];}
 ay=brdBottom(i);if(sy>ay){sy=ay;tyy[i]=-tyy[i];}
 ay=brdTop(i);if(sy<ay){sy=ay;tyy[i]=-tyy[i];}
 break;
