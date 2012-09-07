if not pge.require("pge.gfx") then
	error("Error loading module.")
end

if not pge.require("pge.texture") then
	error("Error loading module.")
end

if not pge.require("pge.controls") then
	error("Error loading module.")
end


-- Create a texture, 128x128 in VRAM.
-- Render targets must reside in VRAM!
texture = pge.texture.create(128, 128, PGE_PIXEL_FORMAT_8888, PGE_VRAM)

-- Check the texture was created correctly
if not texture then
	error("Failed to create texture.")
end

-- Angle variables for rotation
angle = 0.0
anglestep = 0.01

-- Create some colors
white = pge.gfx.createcolor(255, 255, 255)

circlex = 13
circley = 39
xdirection = 1
ydirection = 1

-- Loop until exit requested
while pge.running() do

	-- Update controls
	pge.controls.update()
	
	-- Start drawing
	pge.gfx.startdrawing()
	
	-- Set the texture as the render target (instead of the screen)
	if not texture:settarget() then
		error("Failed to set texture as target.")
	end
	
	-- Clear screen (texture) to white
	pge.gfx.clearscreen(white)
	
	-- Draw a circle to the screen (texture) in a random color
	pge.gfx.drawcircle(circlex, circley, 10, 24, pge.gfx.createcolor(pge.math.randint(0, 255), pge.math.randint(0, 255), pge.math.randint(0, 255)))
	
	-- Revert to drawing directly to the screen
	pge.gfx.rendertoscreen()
	
	-- Clear screen (to black)
	pge.gfx.clearscreen()
	
	-- Activate the texture for drawing
	texture:activate()
	
	-- Draw texture, rotated by 'angle'
	texture:draweasy(240 - (texture:width()/2), 136 - (texture:height()/2), angle)
	
	-- End drawing
	pge.gfx.enddrawing()
	
	-- Swap buffers
	pge.gfx.swapbuffers()
	
	-- Increase angle
	angle = angle + anglestep
	
	circlex = circlex + 0.7 * xdirection
	circley = circley + 1.1 * ydirection
	
	if (circlex - 5) < 0 then
		circlex = 5
		xdirection = 1
	end
	
	if (circlex + 5) > 128 then
		circlex = 123
		xdirection = -1
	end
	
	if (circley - 5) < 0 then
		circley = 5
		ydirection = 1
	end
	
	if (circley + 5) > 128 then
		circley = 123
		ydirection = -1
	end
	
	-- If START pressed, end
	if pge.controls.pressed(PGE_CTRL_START) then
		break
	end
	
end

texture = nil