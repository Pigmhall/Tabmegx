case :sp=10;if(rand(32)==0){tsx[i]=rand(SCX);tsy[i]=rand(SCY);}
 if(sx>tsx[i]&&txx[i]>-sp){--txx[i];}if(sx<tsx[i]&&txx[i]<sp){++txx[i];}
 if(sy>tsy[i]&&tyy[i]>-sp){--tyy[i];}if(sy<tsy[i]&&tyy[i]<sp){++tyy[i];}
 tr[i]=wrapvalue(tr[i]+(txx[i]+tyy[i])/2);
 sx+=txx[i];sy+=tyy[i];
 break;
