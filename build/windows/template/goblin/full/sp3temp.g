const scx=640,scy=480,wx=500,wy=400,wz=500,ot=1,om=1,TM=1000,MM=500,IMM=200;
const imgIm=1,ImMaxSel=20;

type global{rsi,rsx,rsy,rsz} gw as global;
dim t[TM],tx[TM],ty[TM],tz[TM],th[TM],tl[TM],th2[TM],tr[TM],txx[TM],tyy[TM],tww[TM],thh[TM],tsmo[TM],ts[TM],tc[TM],tn[TM],trs[TM],ta[TM],tsw[TM],tsh[TM],tsy[TM],tsx[TM],tbs[TM],tpri[TM],trgbmo[TM],t_r[TM],t_g[TM],t_b[TM];
dim m[MM],mx[MM],my[MM],mz[MM],mh[MM],mxx[MM],myy[MM],mzz[MM],mrx[MM],mry[MM],mrxx[MM],mryy[MM],mrzz[MM],md[MM],mrz[MM],ms[MM],msmo[MM],msx[MM],msy[MM],msz[MM],mtxmo[MM],mc[MM],mn[MM];
dim im[IMM],imn[IMM],imc[IMM],imw[IMM],imh[IMM];

const WVM=32;dim wv[WVM];setArray(wv,31,-1,-2,-3,-4,-5,-6,-7,-8,-8,-7,-6,-5,-4,-3,-2,-1,1,2,3,4,5,6,7,8,8,7,6,5,4,3,2,1);
const ANM=4;dim an[ANM];setArray(an,ANM,0,1,2,1);
const ANM1=7;dim an1[ANM1];setArray(an1,ANM1,0,1,2,3,2,1,0);

syncOn;syncRate 30;backdropOn;autocamOff;colorBackdrop 0;
setWindowPosition 0,64;setImageColorkey 0,0,0;
setWindowSize 512,384;
setCameraView 0,0,640,480;setCameraAspect 1.333

`----- load images
lo(1,"bmp\20.png");

`----- init
for(i=0 to 500){
 c=sett(rand(scx),rand(scy),1,1,1);th[c]=rand(4);ts[c]=600;
 c=setm(rand(wx*2)-wx,rand(wy*2)-wy,rand(wz*2)-wz,100,1);makeObjectSphere om+c,100;
}


`----- main
do{
`-- mov
 for(i=0 to TM-1){if(t[i]){sx=tx[i];sy=ty[i];c=tc[i];switch(t[i]){
case 1: sx=sx+rand(5)-2;sy=sy+rand(5)-2;
 tn[i]=an[th[i]/2];++th[i];if(th[i]==anm*2){th[i]=0;}
 break;
 }
 if(t[i]==0){deleteSprite ot+i;}else{tx[i]=sx;ty[i]=sy;}}}

`-- draw
for(i=0 to TM-1){
 if(t[i]){sx=tx[i];sy=ty[i];c=tc[i];sprite ot+i,sx,sy,imn[c]+tn[i];
  if(tsmo[i]){stretchSprite ot+i,tsw[i],tsh[i];}else{scaleSprite ot+i,ts[i];}
  if(trgbmo[i]){setSpriteDiffuse ot+i,t_r[i],t_g[i],t_b[i];}
  rotateSprite ot+i,tr[i];setSpritePriority ot+i,tpri[i];setSpriteAlpha ot+i,ta[i];}}

`----- m move
for(i=0 to MM){
 if(m[i]){sx=mx[i];sy=my[i];sz=mz[i];
  switch(m[i]){
case 1: sx=sx+rand(5)-2;sy=sy+rand(5)-2;sz=sz+rand(5)-2;
break;
}
  if(m[i]==0){deleteObject om+i;}else{
   positionObject om+i,sx,sy,sz;
   rotateObject om+i,mrx[i],mry[i],mrz[i];
   if(mtxmo[i]==1){textureObject om+i,imn[mc[i]]+mn[i];}
   if(msmo[i]==1){scaleObject om+i,msx[i],msy[i],msz[i];}
   else{scaleObject om+i,ms[i],ms[i],ms[i];}
   moveObject om+i,md[i];mx[i]=sx;my[i]=sy;mz[i]=sz;}}}

`----- cam
 positionCamera 0,0,0;
 moveCamera -500;

`--
 sync;
}
end;

`----- load image
sub lo(nm,fi$){
 i=0;flg=0;imgn=imgIm+nm*ImMaxSel;f$=left$(fi$,len(fi$)-4);fi$=f$;
 while(flg==0){
 if(fileExist(fi$+".png")){
  loadBitmap fi$+".png",1;setCurrentBitmap 1;w=bitmapWidth(1);h=bitmapHeight(1);
  loadImage fi$+".png",imgn+i,1;setCurrentBitmap 0;deleteBitmap 1;}
 else{flg=1;} ++i;fi$=f$+chr$(96+i);}
 im[nm]=1;imn[nm]=imgn;imw[nm]=w;imh[nm]=h;imc[nm]=i-1;}

`----- set t
sub sett(x,y,imgn,t1,pri){
 cf(t,TM,i);if(i!=-1){t[i]=t1;tx[i]=x;ty[i]=y;txx[i]=0;tyy[i]=0;tc[i]=imgn;tn[i]=0;th[i]=0;th2[i]=0;tl[i]=0;tsmo[i]=0;ts[i]=100;tsw[i]=100;tsh[i]=100;tr[i]=0;trs[i]=0;ta[i]=255;tbs[i]=-1;
  trgbmo[i]=0;t_r[i]=255;t_g[i]=255;t_b[i]=255;setSprite ot+i,0,1;tpri[i]=pri;offsetSprite ot+i,imw[imgn]/2,imh[imgn]/2;return i;}}

`----- set m
sub setM(x,y,z,sz,m1){
 cf(m,MM,i);if(i!=-1){m[i]=m1;mx[i]=x;my[i]=y;mz[i]=z;mrx[i]=0;mry[i]=0;mrz[i]=0;mxx[i]=0;myy[i]=0;mzz[i]=0;ms[i]=sz;msmo[i]=0;msx[i]=sz;msy[i]=sz;msz[i]=sz;md[i]=0;mh[i]=0;mtxmo[i]=0;mc[i]=0;mn[i]=0;}return i;}

sub chkT(x,y,a,ii,s){rs=-1;
 for(i=0 to TM){
  if(ii!=i&&t[i]==a&&abs(tx[i]-x)<s&&abs(ty[i]-y)<s){rs=t[i];@rsi=i;@rsx=tx[i];@rsy=ty[i];i=TM;}}return rs;}

sub chkM(x,y,z,a,ii,w){
 for(i=0 to MM-1){
  if(m[i]==a&&i!=ii&&abs(mx[i]-x)<w&&abs(my[i]-y)<w&&abs(mz[i]-z)<w){@rsi=i;@rsx=mx[i];@rsy=my[i];@rsz=mz[i];return 1;}}}  

`---- cntrBordr
sub brdRight(i){a=scx-getW(imw[tc[i]],ts[i])/2;return a;}
sub brdBottom(i){a=scy-getW(imh[tc[i]],ts[i])/2;return a;}
sub brdTop(i){a=getW(imh[tc[i]],ts[i])/2;return a;}
sub brdLeft(i){a=getW(imw[tc[i]],ts[i])/2;return a;}
sub hideRight(i){a=scx+getW(imw[tc[i]],ts[i])/2;return a;}
sub hideBottom(i){a=scy+getW(imh[tc[i]],ts[i])/2;return a;}
sub hideTop(i){a=-getW(imh[tc[i]],ts[i])/2;return a;}
sub hideLeft(i){a=-getW(imw[tc[i]],ts[i])/2;return a;}
sub getW(wid,scal){wid=wid*scal;wid=wid/100;return wid;}
