ch=asc("a"):c=ch
*chloop
reada$:ifa$="end"then*chend
s$="":fori=0to7:a=val("&h"+mid$(a$,i*2+1,2)):vpokec*8+i,a:vpoke&h800+c*8+i,a:vpoke&h1000+c*8+i,a:nexti
reada$:s$="":fori=0to7:a=val("&h"+mid$(a$,i*2+1,2)):vpoke&h2000+c*8+i,a:vpoke&h2800+c*8+i,a:vpoke&h3000+c*8+i,a:nexti
c=c+1:goto*chloop
*chend
