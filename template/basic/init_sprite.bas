sp=0
*sploop
reada$:ifa$="end"then*spend
s$="":fori=0to31:s$=s$+chr$(val("&h"+mid$(a$,i*2+1,2))):nexti
sprite$(sp)=s$
reada$:s$="":fori=0to15:s$=s$+chr$(val("&h"+mid$(a$,i*2+1,2))):nexti
colorsprite$(sp)=s$:csp$(sp)=s$:sp=sp+1:goto*sploop
*spend
