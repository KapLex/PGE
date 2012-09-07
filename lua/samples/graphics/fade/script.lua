if not pge.require("pge.texture") then
	error("Error loading module.")
end

if not pge.require("pge.controls") then
	error("Error loading module.")
end

if not pge.require("pge.gfx") then
	error("Error loading module.")
end


-- Load the first texture to RAM
texture1 = pge.texture.load("image1.png", PGE_RAM)

-- Load the second texture to RAM
texture2 = pge.texture.load("image2.png", PGE_RAM)

-- Check the textures loaded correctly.
if not texture1 or not texture2 then
	error("Failed to load textures.")
end

-- The transparency
alpha = 0

-- The 'direction' the transparency is moving (increasing or decreasing)
modifier = 1

-- Loop while exit requested
while pge.running() do

	-- Update controls
	pge.controls.update()
	
	-- Start drawing
	pge.gfx.startdrawing()
	
	-- Clear screen (to black)
	pge.gfx.clearscreen()
	
	-- Activate the first texture for drawing
	texture1:activate()
	
	-- Draw the first texture with transparency of 'alpha'
	texture1:draweasy(240 - (texture1:width()/2), 136 - (texture1:height()/2), 0, alpha)
	
	-- Activate the second texture for drawing
	texture2:activate()
	
	-- Draw the second texture with transparency of '255 - alpha'
	texture2:draweasy(240 - (texture2:width()/2), 136 - (texture2:height()/2), 0, 255 - alpha)
	
	-- End drawing
	pge.gfx.enddrawing()
	
	-- Dwap buffers
	pge.gfx.swapbuffers()
	
	-- Alter alpha value
	alpha = alpha + modifier
	
	-- Alter modifier
	if alpha > 255 then
		modifier = -1
		alpha = 255
	elseif alpha < 0 then
		modifier = 1
		alpha = 0
	end
	
	-- If STARTED pressed, end
	if pge.controls.pressed(PGE_CTRL_START) then
		break
	end

end

texture1 = nil
texture2 = nil