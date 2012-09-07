if not pge.require("pge.texture") then
	error("Error loading module.")
end

if not pge.require("pge.controls") then
	error("Error loading module.")
end

if not pge.require("pge.gfx") then
	error("Error loading module.")
end

-- Load a texture to RAM
texture = pge.texture.load("pge.png", PGE_RAM)

-- Check the texture loaded correctly
if not texture then
	error("Failed to load texture.")
end

-- Set some initial values
xoffset = 0.0
yoffset = 0.0
step = 0.0
u0 = 0.0
v0 = 0.0
u1 = texture:width()
v1 = texture:height()
x = xoffset + 240 - (texture:width()/2)
y = yoffset + 136 - (texture:height()/2)
width = u1
height = v1

-- Loop until exit requested
while pge.running() do
	
	-- Update controls
	pge.controls.update()
	
	-- Start drawing
	pge.gfx.startdrawing()
	
	-- Clear screen (to black)
	pge.gfx.clearscreen()
	
	-- Activate the texture for drawing
	texture:activate()
	
	-- Draw the texture
	texture:draw(x, y, width, height, u0, v0, u1, v1)
	
	-- End drawing
	pge.gfx.enddrawing()
	
	-- Swap buffers
	pge.gfx.swapbuffers()
	
	-- Alter values based on button input

	if pge.controls.held(PGE_CTRL_LTRIGGER) then
		step = 10.0
	else
		step = 1.0
	end
	
	if pge.controls.held(PGE_CTRL_SQUARE) then
		if pge.controls.held(PGE_CTRL_RTRIGGER) then
			u1 = u1 + step
		else
			u0 = u0 + step
		end
	end
	
	if pge.controls.held(PGE_CTRL_TRIANGLE) then
		if pge.controls.held(PGE_CTRL_RTRIGGER) then
			v1 = v1 + step
		else
			v0 = v0 + step
		end
	end
	
	if pge.controls.held(PGE_CTRL_CROSS) then
		if pge.controls.held(PGE_CTRL_RTRIGGER) then
			v1 = v1 - step
		else
			v0 = v0 - step
		end
	end
	
	if pge.controls.held(PGE_CTRL_CIRCLE) then
		if pge.controls.held(PGE_CTRL_RTRIGGER) then
			u1 = u1 - step
		else
			u0 = u0 - step
		end
	end
	
	if pge.controls.analogx() > 64 then
		width = width + step
		if width > 0 then
			x = xoffset + 240 - (width/2)
		end
	end
	
	if pge.controls.analogx() < -64 then
		width = width - step
		if width > 0 then
			x = xoffset + 240 - (width/2)
		end
	end
	
	if pge.controls.analogy() > 64 then
		height = height + step
		if height > 0 then
			y = yoffset + 136 - (height/2)
		end
	end
	
	if pge.controls.analogy() < -64 then
		height = height - step
		if height > 0 then
			y  = yoffset + 136 - (height/2)
		end
	end
	
	if pge.controls.held(PGE_CTRL_LEFT) then
		xoffset = xoffset - step
		x = xoffset + 240 - (width/2)
	end
	
	if pge.controls.held(PGE_CTRL_RIGHT) then
		xoffset = xoffset + step
		x = xoffset + 240 - (width/2)
	end
	
	if pge.controls.held(PGE_CTRL_UP) then
		yoffset = yoffset - step
		y = yoffset + 136 - (height/2)
	end
	
	if pge.controls.held(PGE_CTRL_DOWN) then
		yoffset = yoffset + step
		y = yoffset + 136 - (height/2)
	end
	
	-- If START pressed, end
	if pge.controls.pressed(PGE_CTRL_START) then
		break
	end
	
end

texture = nil