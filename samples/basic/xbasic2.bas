color15,1,1:screen2:screen1:width32:keyoff:defusr=&h7e:a=usr(0)
_turboon
fori=&h2000to&h37ff:vpokei,(imod8+5)*16+1:nexti:gosub *baboo
definta-z
*lop
fori=0to7:vpoke0+i,rnd(1)*256:vpoke&h800+i,rnd(1)*256:vpoke&h1000+i,rnd(1)*256
vpoke&h2000+i,rnd(1)*256:vpoke&h2800+i,rnd(1)*256:vpoke&h3000+i,rnd(1)*256
nexti
sx=rnd(1)*32:sy=rnd(1)*24
rem line(sx,0)-(sy,191),rnd(1)*15,bf
vpoke &h1800+sy*32+sx,0
locate 10,3:print "SCREEN1.5"
locate 10,10:print "SCREEN1.5"
locate 10,20:print "SCREEN1.5"
goto *lop

*baboo
fori=0to&h7ff:d=vpeek(i)
d=dord\2:d=d\VAL(MID$("84422211",IMOD8+1,1))
FORJ=0TO2:VPOKEI+&H0800*J,D:NEXTj
nexti
return
