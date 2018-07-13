color15,0,0:screen4,2,0:definta-z
gettimea$:a=val(mid$(a$,4,2)+right$(a$,2)):fori=0toa:a=rnd(1):next
sp=0
*sploop
reada$:ifa$="end"then*spend
s$="":fori=0to31:s$=s$+chr$(val("&h"+mid$(a$,i*2+1,2))):next
sprite$(sp)=s$
reada$:s$="":fori=0to15:s$=s$+chr$(val("&h"+mid$(a$,i*2+1,2))):next
colorsprite$(sp)=s$:csp$[sp]=s$:sp=sp+1:goto*sploop
*spend

fori=0to7:colorsprite$(i)=csp$[iand1]:tx[i]=128:ty[i]=96:next
*lop
fori=0to7
tx[i]=tx[i]+rand(3)-1:ty[i]=ty[i]+rand(3)-1
putspritei,(tx[i],ty[i]),,iand1
next
goto*lop

data073F2D0F0F070303010303070C1C180080F868E0E0C0C0808080C0C060301000
data040404040C0C0C0C0A0A0A0A0A0A0A00
data0C1E3E37FFFF3F3F3F3F3F1F1F070115000000071FBCFCFCF8F8F8FCFCFC0000
data09090A0A0A0A0A0A0A0A0A0A0A0A0909
dataend
