color15,0,0:screen2:screen1:width32:keyoff:defusr=&h7e:a=usr(0)
fori=0to255:vpoke6144+i,i:next
fori=33*8to127*8-1:a=&hf0:v=vpeek(i)
vpoke&h800+i,v:vpoke&h1000+i,v
vpoke&h2000+i,a:vpoke&h2800+i,a:vpoke&h3000+i,a:next

ch=asc("a")
*chloop
sp=0:reada$:s$="":fori=0to7:a=val("&h"+mid$(a$,i*2+1,2)):vpokech*8+i,a:vpoke&h800+ch*8+i,a:vpoke&h1000+ch*8+i,a:next
sp=0:reada$:s$="":fori=0to7:a=val("&h"+mid$(a$,i*2+1,2)):vpoke&h2000+ch*8+i,a:vpoke&h2800+ch*8+i,a:vpoke&h3000+ch*8+i,a:next

cls

*loop
x=rand(32):y=rand(24):vpoke6144+x+y*32,ch+rand(5)
goto*loop

dataFFDFDFDFFFFBFBFB
data4494846444948464
