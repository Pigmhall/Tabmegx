const scx=640,scy=480,ot=1,TM=1000,IMM=200;
const imgIm=1,ImMaxSel=20;

type global{rsi,rsx,rsy} gw as global;
dim t[TM],tx[TM],ty[TM],tz[TM],th[TM],tl[TM],th2[TM],tr[TM],txx[TM],tyy[TM],tww[TM],thh[TM],tsmo[TM],ts[TM],tc[TM],tn[TM],trs[TM],ta[TM],tsw[TM],tsh[TM],tsy[TM],tsx[TM],tbs[TM],tpri[TM],trgbmo[TM],t_r[TM],t_g[TM],t_b[TM];
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
for(i=0 to 5){
 c=sett(rand(scx),rand(scy),1,1,1);th[c]=rand(4);ts[c]=600;
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

sub chkT(x,y,a,ii,s){rs=-1;
 for(i=0 to TM){
  if(ii!=i&&t[i]==a&&abs(tx[i]-x)<s&&abs(ty[i]-y)<s){rs=t[i];@rsi=i;@rsx=tx[i];@rsy=ty[i];i=TM;}}return rs;}

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
