color15,0,0:screen2:screen1:width32:keyoff:defusr=&h7e:a=usr(0)
fori=33*8to127*8-1:a=&h70:v=vpeek(i)
vpoke&h800+i,v:vpoke&h1000+i,v
vpoke&h2000+i,a:vpoke&h2800+i,a:vpoke&h3000+i,a:nexti
