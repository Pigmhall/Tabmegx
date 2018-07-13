*chkt
 ri=-1:forj=0toTM
  ifj<>iandabs(sx-tx(j))<12andabs(sy-ty(j))<12then ri=j:rx=tx(j):ry=ty(j) 
 nextj:return
*hajiku
 SP=5
 if sx<tx(ri) then sx=sx-rand(SP):tx(ri)=tx(ri)+rand(SP) else sx=sx+rand(SP):tx(ri)=tx(ri)-rand(SP)
 if sy<ty(ri) then sy=sy-rand(SP):ty(ri)=ty(ri)+rand(SP) else sy=sy+rand(SP):ty(ri)=ty(ri)-rand(SP)
return
