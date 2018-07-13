screen1:color 15,0,0
locate 10,1:print "-- test --"
*lop
x=rand(32):y=rand(32)
s=stick(0)
ifs=1then begin
 fori=0to8:locate 5+i,i+5:print "X";:next
 endif else begin
 fori=0to8:locate 5+i,i+5:print "J";:next
 locate 5,3:print "press up key"
endif

goto *lop
