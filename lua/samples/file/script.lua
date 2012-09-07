if not pge.require("pge.font") then
	error("Error loading module.")
end

if not pge.require("pge.gfx") then
	error("Error loading module.")
end

if not pge.require("pge.controls") then
	error("Error loading module.")
end

if not pge.require("pge.file") then
	error("Error loading module.")
end

if not pge.require("pge.utils") then
	error("Error loading module.")
end

-- Load a font 12 pixels in height
verdana12 = pge.font.load("verdana.ttf", 12)

-- Check the font loaded correctly
if not verdana12 then
	error("Failed to load font.")
end

-- Create some colors
black = pge.gfx.createcolor(0, 0, 0)
white = pge.gfx.createcolor(255, 255, 255)
green = pge.gfx.createcolor(0, 255, 0)
red = pge.gfx.createcolor(255, 0, 0)

run = true

-- Loop until exit
while pge.running() do
	
	-- Update controls
	pge.controls.update()
	
	-- If START pressed, end
	if pge.controls.pressed(PGE_CTRL_START) then
		run = false
		break
	end
	
	-- If CROSS pressed, continue
	if pge.controls.pressed(PGE_CTRL_CROSS) then
		run = true
		break
	end
	
	-- Start drawing
	pge.gfx.startdrawing()
	
	-- Clear screen (to black)
	pge.gfx.clearscreen()
	
	-- Activate the font for drawing
	verdana12:activate()
	
	verdana12:print(20, 20, white, "This sample creates a new EBOOT.PBP with custom data.")
	verdana12:print(20, 35, white, "Place your custom ICON0.PNG, PIC1.PNG etc. in this folder.")
	verdana12:print(20, 65, green, "Press CROSS to begin, or START to exit.")
	
	-- End drawing
	pge.gfx.enddrawing()
	
	-- Swap buffers
	pge.gfx.swapbuffers()
	
end

if run == true then
	-- Init OSK with description, initial text and check success
	if not pge.utils.oskinit("EBOOT Name", "") then
		error("Error on osk init.")
	end

	ebootname = ""

	-- Loop until exit requested
	while pge.running() do

		-- Update controls
		pge.controls.update()

		-- Start drawing
		pge.gfx.startdrawing()
	
		-- Clear screen (to black)
		pge.gfx.clearscreen()
	
		-- End drawing
		pge.gfx.enddrawing()
	
		-- pge.utils.oskupdate() must be called after pge.gfx.enddrawing(), but before pge.gfx.swapbuffers()
		result, ebootname = pge.utils.oskupdate()
		
		if result then
			break
		end
	
		-- Swap buffers
		pge.gfx.swapbuffers()	
	end

	-- Open the EBOOT
	eboot_in = pge.file.open("../../EBOOT.PBP", PGE_FILE_RDONLY)

	-- Check EBOOT opened correctly
	if not eboot_in then
		error("Could not open EBOOT.PBP")
	end

	-- Get the size of the EBOOT
	eboot_size = eboot_in:seek(0, PGE_FILE_END)

	-- Rewind back to the start of the file
	eboot_in:rewind()

	-- Read 4 bytes from the file
	eboot_magic = eboot_in:read(4)

	-- Read an integer from the file
	eboot_version = eboot_in:readnum()

	eboot_valid = false

	-- Check the EBOOT header starts with "/0PBP"
	if eboot_magic:byte(1) == 0 and eboot_magic:byte(2) == 80 and eboot_magic:byte(3) == 66 and eboot_magic:byte(4) == 80 then
		-- If it does, it's a valid EBOOT file
		eboot_valid = true
	else
		error("Invalid EBOOT.PBP file.")
	end

	-- If the EBOOT is a valid file...
	if eboot_valid then
	
		-- Offset within the EBOOT for each file
		eboot_offsets = {0, 0, 0, 0, 0, 0, 0, 0}
	
		-- Names of each file
		eboot_data_names = {"PARAM.SFO", "ICON0.PNG", "ICON1.PMF", "PIC0.PNG", "PIC1.PNG", "SND0.AT3", "DATA.PSP", "DATA.PSAR"}
	
		-- Do we have new data to replace for each file?
		eboot_data_new = {false, false, false, false, false, false, false, false}
	
		-- Do we have old data for each file?
		eboot_data_old = {false, false, false, false, false, false, false, false}
	
		-- The size of each new file
		eboot_data_new_size = {0, 0, 0, 0, 0, 0, 0, 0}
	
		-- Get the initial offsets for each file
		for i = 1, 8 do
			eboot_offsets[i] = eboot_in:readnum()
		end
		
		-- Unpack the old data from the EBOOT
		for i = 1, 8 do
			if i == 8 then
				eboot_data_size = eboot_size - eboot_offsets[i]
			else
				eboot_data_size = eboot_offsets[i + 1] - eboot_offsets[i]
			end
			
			if eboot_data_size > 0 then
				eboot_data_old[i] = true
			
				-- Create a new file for the old data
				eboot_data_out = pge.file.open("_" .. eboot_data_names[i], PGE_FILE_CREATE + PGE_FILE_WRONLY);
		
				-- Check the new file was created correctly
				if not eboot_data_out then
					error("Could not open " .. eboot_data_names[i])
				end
				
				-- Seek to the correct position in the EBOOT
				eboot_in:seek(eboot_offsets[i], PGE_FILE_SET)
						
				-- Read the data in
				data = eboot_in:read(eboot_data_size)
			
				-- Write the data out to the file
				eboot_data_out:write(data)
			
				-- Close the file
				eboot_data_out:close()
		
			end	
		end
	
		-- Close the EBOOT
		eboot_in:close()
	
		-- Create a new EBOOT
		eboot_out = pge.file.open("EBOOT.PBP", PGE_FILE_CREATE + PGE_FILE_WRONLY)
	
		-- Check the new EBOOT was created correctly
		if not eboot_out then
			error("Could not open EBOOT.PBP for writing")
		end
	
		-- Write the "/0PBP" header
		eboot_out:write(string.char(0, 80, 66, 80))
		-- Write the version
		eboot_out:write(65536)
		-- Write the first offset
		offset = 40
		eboot_out:write(offset)
	
		-- Pack the new & old files into the EBOOT
		for i = 1, 8 do
			-- Try to open a new file
			eboot_data_in = pge.file.open(eboot_data_names[i], PGE_FILE_RDONLY)
		
			-- Check if new file exists
			if eboot_data_in then
		
				-- If it does we read it in and write it to the EBOOT
				eboot_data_new[i] = true
				eboot_data_new_size[i] = eboot_data_in:size()
			
				-- Read the file data
				eboot_data = eboot_data_in:read(eboot_data_new_size[i])
			
				-- Seek to the correct position in the new EBOOT
				eboot_out:seek(offset, PGE_FILE_SET)
			
				-- Write the file data to the new EBOOT
				eboot_out:write(eboot_data)
				offset = offset + eboot_data_new_size[i]
			
				-- Close the file
				eboot_data_in:close()
			else
				-- If it doesn't, we see if there was an existing file...
				if eboot_data_old[i] == true then
			
					-- ... open that file
					old_eboot_data_in = pge.file.open("_" .. eboot_data_names[i], PGE_FILE_RDONLY)	
					eboot_data_new_size[i] = old_eboot_data_in:size()
				
					-- Read the file data
					eboot_data = old_eboot_data_in:read(eboot_data_new_size[i])
				
					-- Seek to the correct position in the new EBOOT
					eboot_out:seek(offset, PGE_FILE_SET)
				
					-- Write the file data to the new EBOOT
					eboot_out:write(eboot_data)			
					offset = offset + eboot_data_new_size[i]
				
					-- Close the file
					old_eboot_data_in:close()
				else
					eboot_data_new_size[i] = 0
				end
			end
			-- Delete the old file
			pge.file.remove("_" .. eboot_data_names[i])
		end
	
		-- Seek to the position of the offsets
		eboot_out:seek(12, PGE_FILE_SET)
	
		-- Write the first new offset to the EBOOT
		eboot_data_new_size[1] = eboot_data_new_size[1] + 40
		eboot_out:write(eboot_data_new_size[1])
	
		-- Write the rest of the new offsets to the EBOOT
		for i = 2, 7 do
			eboot_data_new_size[i] = eboot_data_new_size[i] + eboot_data_new_size[i - 1]
			eboot_out:write(eboot_data_new_size[i])
		end
	
		-- Write the new name
		eboot_out:seek(320, PGE_FILE_SET)
	
		eboot_out:write(ebootname)
	
		ebootnamelength = 127 - ebootname:len()
		
		for _ = 1, ebootnamelength do
			eboot_out:write(string.char(0))
		end
	
		-- Close the EBOOT
		eboot_out:close()
	end

	-- Loop until exit
	while pge.running() do
	
		y = 5
		x = 20
	
		-- Update controls
		pge.controls.update()
	
		-- If START pressed, end
		if pge.controls.pressed(PGE_CTRL_START) then
			break
		end
	
		-- Start drawing
		pge.gfx.startdrawing()
	
		-- Clear screen (to black)
		pge.gfx.clearscreen()
	
		-- Activate the font for drawing
		verdana12:activate()
	
		-- Display what's been changed etc.
		for i = 1, 8 do
			verdana12:print(x, y + (i * 15), white, eboot_data_names[i] .. ": ")
		
			if eboot_data_new[i] == true then
				verdana12:print(x + verdana12:measure(eboot_data_names[i] .. ": "), y + (i * 15), green, "UPDATED")
			else
				if eboot_data_old[i] == true then
					verdana12:print(x + verdana12:measure(eboot_data_names[i] .. ": "), y + (i * 15), red, "UNCHANGED")
				else
					verdana12:print(x + verdana12:measure(eboot_data_names[i] .. ": "), y + (i * 15), white, "NOT PRESENT")
				end
			end
		end
	
		-- End drawing
		pge.gfx.enddrawing()
	
		-- Swap buffers
		pge.gfx.swapbuffers()
	
	end
	
	data = nil
	eboot_data = nil
	
end

verdana12 = nil