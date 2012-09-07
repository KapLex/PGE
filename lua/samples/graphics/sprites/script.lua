if not pge.require("pge.gfx") then
	error("Error loading module.")
end

if not pge.require("pge.texture") then
	error("Error loading module.")
end

if not pge.require("pge.controls") then
	error("Error loading module.")
end


-- Setup some variables we will use for the spritesheet 
UP = 0
DOWN = 1
LEFT = 2
RIGHT = 3

SPRITEDIM = 32

ANIMFRAMES = 3
ANIMWAIT = 5

SPRITESIT = 0
SPRITEWALKDOWN = 1
SPRITESTANDDOWN = 2
SPRITEWALKRIGHT = 4
SPRITESTANDRIGHT = 5
SPRITEWALKLEFT = 4
SPRITESTANDLEFT = 5
SPRITEWALKUP = 7
SPRITESTANDUP = 8

direction = RIGHT
animframe = 0
animwait = 10
spriteoffset = SPRITESTANDRIGHT
xpos = 50.0
ypos = 50.0
zoom = 1.0
walkspeed = 1.0

-- Load the spritesheet texture
spritesheet = pge.texture.load("russelchao.png", PGE_RAM)

-- Check it loaded correctly
if not spritesheet then
	error("Failed to load spritesheet.")
end

-- Loop until exit requested
while pge.running() do
	
	-- Update controls
	pge.controls.update()
	
	-- Start drawing
	pge.gfx.startdrawing()
	
	-- Clear screen (to black)
	pge.gfx.clearscreen()
	
	-- Activate the spritesheet texture for drawing
	spritesheet:activate()
	
	x = xpos
	width = SPRITEDIM * zoom
	y = ypos
	height = SPRITEDIM * zoom
	
	u0 = (spriteoffset + animframe) * SPRITEDIM
	u1 = SPRITEDIM
	v0 = 0
	v1 = SPRITEDIM
	
	if direction == LEFT then
		u0 = (spriteoffset + animframe + 1) * SPRITEDIM
		u1 = 0 - SPRITEDIM
	end
	
	-- Draw the sprite
	spritesheet:draw(x, y, width, height, u0, v0, u1, v1)
	
	-- End drawing
	pge.gfx.enddrawing()
	
	-- Swap buffers
	pge.gfx.swapbuffers()
	
	-- Update variables based on button input
	if pge.controls.held(PGE_CTRL_LEFT) or pge.controls.analogx() < -64 then
		direction = LEFT
		spriteoffset = SPRITEWALKLEFT
		xpos = xpos - walkspeed
	end
	
	if pge.controls.held(PGE_CTRL_RIGHT) or pge.controls.analogx() > 64 then
		direction = RIGHT
		spriteoffset = SPRITEWALKRIGHT
		xpos = xpos + walkspeed
	end
	
	if pge.controls.held(PGE_CTRL_UP) or pge.controls.analogy() < -64 then
		direction = UP
		spriteoffset = SPRITEWALKUP
		ypos = ypos - walkspeed
	end
	
	if pge.controls.held(PGE_CTRL_DOWN) or pge.controls.analogy() > 64 then
		direction = DOWN
		spriteoffset = SPRITEWALKDOWN
		ypos = ypos + walkspeed
	end
	
	if pge.controls.held(PGE_CTRL_UP) or pge.controls.held(PGE_CTRL_DOWN) or pge.controls.held(PGE_CTRL_LEFT) or pge.controls.held(PGE_CTRL_UP) or pge.controls.held(PGE_CTRL_RIGHT) or pge.controls.analogx() > 64 or pge.controls.analogx() < -64 or pge.controls.analogy() < -64 or pge.controls.analogy() > 64 then
		animwait = animwait - 1
		
		if animwait <= 0 then
			animwait = ANIMWAIT
			animframe = animframe + 1
			
			if animframe >= ANIMFRAMES then
				animframe = 0
			end
		end
		
	else
		
		animframe = 0
		
		if direction == UP then
			spriteoffset = SPRITESTANDUP
		elseif direction == DOWN then
			spriteoffset = SPRITESTANDDOWN
		elseif direction == LEFT then
			spriteoffset = SPRITESTANDLEFT
		elseif direction == RIGHT then
			spriteoffset = SPRITESTANDRIGHT
		else
			spriteoffset = SPRITESTANDUP
		end
	end
	
	if xpos < 0 then
		xpos = 0
	end
	
	if xpos > 480 - SPRITEDIM * 2 then
		xpos = 480 - SPRITEDIM * 2
	end
	
	if ypos < 0 then
		ypos = 0
	end
	
	if ypos > 272 - SPRITEDIM * 2 then
		ypos = 272 - SPRITEDIM * 2
	end
	
	if xpos < 240 then
		zoom = 1
	else
		if xpos >= 240 and xpos <= 280 then
			zoom = 1 + (xpos - 240)/40
		else
			zoom = 2
		end
	end
	
	-- If START pressedm end
	if pge.controls.pressed(PGE_CTRL_START) then
		break
	end
end

spritesheet = nil