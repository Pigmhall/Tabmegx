syncOn;syncRate 30;backdropOn;autocamOff;colorBackdrop 0;
setWindowPosition 0,64;
setImageColorkey 0,0,0;
setWindowSize 512,384;

setCameraView 0,0,640,480;setCameraAspect 1.333

`makeObjectSphere 1,100;colorObject 1,0xff0000;

do{
` positionObject 1,rand(5)-2,rand(5)-2,rand(5)-2 
 positionCamera 0,0,0;
 moveCamera -500;
 setCursor 8,8
 setTextToBold
 setTextSize 50
` centerText 320,240,"Test?"
 sync;
}
