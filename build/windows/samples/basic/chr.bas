color15,0,0:screen4:definta-z

ch=asc("a"):c=ch
*chloop
reada$:ifa$="end"then*chend
s$="":fori=0to7:a=val("&h"+mid$(a$,i*2+1,2)):vpokec*8+i,a:vpoke&h800+c*8+i,a:vpoke&h1000+c*8+i,a:nexti
reada$:s$="":fori=0to7:a=val("&h"+mid$(a$,i*2+1,2)):vpoke&h2000+c*8+i,a:vpoke&h2800+c*8+i,a:vpoke&h3000+c*8+i,a:nexti
c=c+1:goto*chloop
*chend

*loop
x=rand(32):y=rand(24):vpoke6144+x+y*32,ch+rand(5)
goto*loop

dataFFDFDFDFFFFBFBFB
data4494846444948464
dataE7C3FFC3C3C39199
data0A0AAA02020A0A0A
dataC3BD81818181BDC3
data04044070F0700404
dataend
