if not pge.require("pge.font") then
	error("Error loading module.")
end

if not pge.require("pge.gfx") then
	error("Error loading module.")
end

if not pge.require("pge.controls") then
	error("Error loading module.")
end

if not pge.require("pge.zip") then
	error("Error loading module.")
end

-- Create a color
white = pge.gfx.createcolor(255, 255, 255)

-- Load a font, 16 pixels in height, to RAM
verdana16 = pge.font.load("verdana.ttf", 16, PGE_RAM)

-- Check the font loaded correctly
if not verdana16 then
	error("Failed to load font.")
end

text = "Opening ZIP file..."

gotimage = false

function drawtext()
	
	-- Start drawing
	pge.gfx.startdrawing()
	
	-- Clear screen (to black)
	pge.gfx.clearscreen()
	
	-- Activate font, ready for drawing
	verdana16:activate()
	
	-- Print the text
	verdana16:print(20, 20, white, text)
	
	-- If we've got the image, draw it
	if gotimage then
		image:activate()
		image:draw(20, 140)
	end
	
	-- End drawing
	pge.gfx.enddrawing()
	
	-- Swap buffers
	pge.gfx.swapbuffers()
	
end

-- Open the ZIP
zipfile = pge.zip.open("test.zip")

-- Check it was opened correctly
if zipfile then
	text = text .. "\nOpened ZIP successfully.\nOpening test.png in ZIP..."
	drawtext()
	
	-- Open the file 'test.png' that is in our ZIP file
	fileinzip = zipfile:read("test.png")
	
	-- Check it was opened correctly
	if fileinzip then		
		text = text .. "\nOpened test.png successfully.\nLoading texture..."
		drawtext()
		
		-- Load the texture from a memory (ZIP) stream
		image = pge.texture.loadmemory(fileinzip:data(), PGE_RAM)
		
		-- Check it was loaded correctly
		if image then			
			text = text .. "\nTexture loaded." 
			gotimage = true			
		else	
			text = text .. "\nTexture load failed."			
		end
		
		while pge.running() and not pge.controls.pressed(PGE_CTRL_START) do
			pge.controls.update()
			drawtext()
		end
		
	else -- Error opening file in zip	
		text = text .. "\nFailed to open test.png."
		
		while pge.running() and not pge.controls.pressed(PGE_CTRL_START) do
			pge.controls.update()
			drawtext()
		end		
	end
	
else -- Error opening ZIP	
	text = text .. "\Failed to open ZIP."
	
	while pge.running() and not pge.controls.pressed(PGE_CTRL_START) do
		pge.controls.update()
		drawtext()
	end	
end

-- Close the ZIP file
zipfile:close()

zipfile = nil
verdana16 = nil
fileinzip = nil