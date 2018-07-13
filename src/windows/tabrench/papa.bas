cls:width 40,15:key off:color 15
scx=320:scy=240
screen 3,5:locate 0,0,0
gosub *genspbmp

*lop
line(0,0)-(scx,scy),0,bf
put sprite 0,(rand(10),rand(10)),0

screen
wait 35
if strig(0) then system
goto *lop



'----- bmp to sp
*genspbmp
 restore *genspbmp_files:i=0
*genspbmp_skip
 read a$:if a$="end" then return
 gload "bmp\"+a$+".bmp",(0,0)
 a$="":for j=0 to 15:for k=0 to 15:a$=a$+chr$(point(k,j)):next k,j
 sprite$(i)=a$:i=i+1:goto *genspbmp_skip
*genspbmp_files
data "4","end"
