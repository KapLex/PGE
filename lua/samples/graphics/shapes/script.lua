if not pge.require("pge.gfx") then
	error("Error loading module.")
end

if not pge.require("pge.controls") then
	error("Error loading module.")
end


-- Create some colors
white = pge.gfx.createcolor(255, 255, 255)
blue = pge.gfx.createcolor(0, 0, 255)
red = pge.gfx.createcolor(255, 0, 0)
green = pge.gfx.createcolor(0, 255, 0)

-- Loop until exit requested
while pge.running() do
	
	-- Update controls
	pge.controls.update()
	
	-- Start drawing
	pge.gfx.startdrawing()
	
	-- Clear screen
	pge.gfx.clearscreen()
	
	-- Draw a circle
	pge.gfx.drawcircle(50, 50, 50, 30, white)
	
	-- Draw a circle outline
	pge.gfx.drawcircleoutline(50, 50, 50, 30, blue)
	
	-- Draw a star
	pge.gfx.drawstar(300, 100, 19, 50, 5, red, 1)
	
	-- Draw a star outline
	pge.gfx.drawstaroutline(300, 100, 19, 50, 5, green, 1)
	
	-- Draw a rectangle
	pge.gfx.drawrect(20, 200, 30, 60, blue)
	
	-- Draw a rectangle outline
	pge.gfx.drawrectoutline(20, 200, 30, 60, white)
	
	-- Draw a rectangle (rotated by 1)
	pge.gfx.drawrect(120, 200, 30, 60, blue, 1)
	
	-- Draw a rectangle (rotated by PI/2)
	pge.gfx.drawrect(190, 200, 30, 60, blue, 1.5707963)
	
	-- Draw a rectangle (rotated by 3 * PI/2 + 1)
	pge.gfx.drawrect(260, 200, 30, 60, blue, 3 * 1.5707963 + 1)
	
	-- End drawing
	pge.gfx.enddrawing()
	
	-- Swap buffers
	pge.gfx.swapbuffers()
	
	-- If START pressed, end
	if pge.controls.pressed(PGE_CTRL_START) then
		break
	end
	
end
