_turboon
screen1
*loop
sx=rand(32):sy=rand(24)
vpoke 6144+sx+sy*32,rand(256)
goto *loop
