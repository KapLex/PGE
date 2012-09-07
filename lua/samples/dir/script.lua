if not pge.require("pge.font") then
	error("Error loading module.")
end

if not pge.require("pge.gfx") then
	error("Error loading module.")
end

if not pge.require("pge.controls") then
	error("Error loading module.")
end

if not pge.require("pge.dir") then
	error("Error loading module.")
end

-- Create some colors
green = pge.gfx.createcolor(0, 255, 0)
white = pge.gfx.createcolor(255, 255, 255)

-- Load a font, 10 pixels in height, to VRAM
verdana10 = pge.font.load("verdana.ttf", 10, PGE_VRAM)

-- Check the font loaded correctly
if not verdana10 then
	error("Failed to load font: verdana.ttf")
end

-- The current directory
currentdir = ""

-- The file offset
fileoffset = 0

-- The limit of number of files to show on screen at once
filelimit = 15

function readdir(path)
	
	-- Change the directory to the path
	pge.dir.chdir(path)
	
	-- Open the directory
	dir = pge.dir.open()
	
	-- Check it opened correctly
	if dir then
	
		-- Read the contents of the directory
		dircontents = dir:read()
	
		-- Check we read the contents correctly
		if not dircontents then
			return nil
		end
	
		-- Close the directory
		dir:close()
	
		-- Reset the current selection to the first entry
		currentselection = 1
		
		-- Sort the contents so sub-directories appear first sorted alphabetically and files appear after, sorted alphabetically.
		table.sort(dircontents, function(a,b) if a.dir == b.dir then return a.name:lower() < b.name:lower() else return a.dir end end)
	
		-- Return the directory contents
		return dircontents
	else
		error("Error opening directory.")
	end

end

-- Reset the current selection to the first entry
currentselection = 1

-- Initially read the contents of the initial directory
dircontents = readdir(currentdir)

-- Loop with exit requested
while pge.running() do

	-- Update controls
	pge.controls.update()
	
	-- If UP pressed and the directory has contents, select the entry above
	if pge.controls.pressed(PGE_CTRL_UP) and dircontents then
		if currentselection > 1 then
			currentselection = currentselection - 1
			
			if currentselection > filelimit - 2 then
				fileoffset = fileoffset - 1
			end
		end
	end
	
	-- If DOWN pressed and the directory has contents, select the entry below
	if pge.controls.pressed(PGE_CTRL_DOWN) and dircontents then
		if currentselection < #dircontents then
			currentselection = currentselection + 1
			
			if currentselection >= filelimit then
				fileoffset = fileoffset + 1
			end
		end
	end
	
	-- If CROSS pressed, the directory has contents and the selected item is a directory, move into the directory selected
	if pge.controls.pressed(PGE_CTRL_CROSS) and dircontents then
		if dircontents[currentselection].dir then
			dircontents = readdir(dircontents[currentselection].name)
		end
	end
	
	-- If TRIANGLE pressed, move up a directory
	if pge.controls.pressed(PGE_CTRL_TRIANGLE) then
		dircontents = readdir("..")
		fileoffset = 0
	end
	
	-- If START pressed, end
	if pge.controls.pressed(PGE_CTRL_START) then
		break
	end
	
	-- Start drawing
	pge.gfx.startdrawing()
	
	-- End drawing
	pge.gfx.clearscreen()
	
	-- Activate the font for drawing
	verdana10:activate();
	
	-- Print the instructions
	verdana10:printcenter(5, green, "Press TRIANGLE to go up one level, press CROSS to enter a directory")
	
	-- Print the directory contents
	if dircontents then
		for index, entry in ipairs(dircontents) do	
			if index > fileoffset and index < (filelimit + fileoffset) then
				if currentselection == index then
					verdana10:print(30, ((index - fileoffset) * 12) + 12, green, entry.name)
					if entry.dir == true then
						pge.gfx.drawrect(15, ((index - fileoffset) * 12) + 12, 10, 10, green)
					end
				else
					verdana10:print(30, ((index - fileoffset) * 12) + 12, white, entry.name)
					if entry.dir == true then
						pge.gfx.drawrect(15, ((index - fileoffset) * 12) + 12, 10, 10, white)
					end
				end
			end
		end
	end
	
	-- End drawing
	pge.gfx.enddrawing()
	
	-- Swap buffers
	pge.gfx.swapbuffers()
	
end

verdana10 = nil