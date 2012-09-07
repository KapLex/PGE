if not pge.require("pge.texture") then
	error("Error loading module.")
end

if not pge.require("pge.gfx") then
	error("Error loading module.")
end

if not pge.require("pge.controls") then
	error("Error loading module.")
end


-- Load the texture to RAM
texture = pge.texture.load("arrow.png")

-- Check the texture loaded correctly
if not texture then
	error("Failed to load texture.")
end

width = 0
height = 0

-- Loop until exit requested
while pge.running() do

	-- Update controls
	pge.controls.update()
	
	-- Start drawing
	pge.gfx.startdrawing()
	
	-- Clear screen
	pge.gfx.clearscreen()
	
	-- Activate the texture for drawing
	texture:activate()
	
	-- Set the drawing width based on the analog magnitude
	width = texture:width() * pge.controls.analogmag()
	
	-- Set the drawing height based on the analog magnitude
	height = texture:height() * pge.controls.analogmag()
	
	-- Draw texture, rotated by analog angle
	texture:draw(240 - (width/2), 136 - (height/2), width, height, 0, 0, texture:width(), texture:height(), pge.controls.analogangle())
		
	-- End drawing
	pge.gfx.enddrawing()
	
	-- Swap buffers
	pge.gfx.swapbuffers()
	
	-- If START pressed, end
	if pge.controls.pressed(PGE_CTRL_START) then
		break
	end
	
end

texture = nil