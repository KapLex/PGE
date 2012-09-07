if not pge.require("pge.controls") then
	error("Failed to load module.")
end

if not pge.require("pge.gfx") then
	error("Failed to load module.")
end

if not pge.require("pge.font") then
	error("Failed to load module.")
end

if not pge.require("pge.texture") then
	error("Failed to load module.")
end

if not pge.require("pge.dir") then
	error("Failed to load module.")
end

local green = pge.gfx.createcolor(255, 150, 0)
local white = pge.gfx.createcolor(255, 255, 255)
local whitesemi = pge.gfx.createcolor(255, 255, 255, 50)

local verdana9 = pge.font.load("verdana.ttf", 9, PGE_RAM)

if not verdana9 then
	error("Failed to load font.")
end

local verdana12 = pge.font.load("verdana.ttf", 12, PGE_RAM)

if not verdana12 then
	error("Failed to load font2.")
end

local logo = pge.texture.load("logo.png")

if not logo then
	error("Failed to load logo.")
end

local samplescripts =
{
	{name = "MP3 Playback", location = "/samples/audio/mp3", desc = "Shows the usage of the pge.mp3 module for MP3\nplayback, retrieving ID3 tag information and\npge.gfx.drawcustom() to create a simple visualizer."},
	{name = "WAV Playback", location = "/samples/audio/wav", desc = "Four WAV files of different formats are loaded\nready for playback. Sound quality can be\ncompared and pge.wav functionality is demonstrated."},
	{name = "Controls", location = "/samples/controls", desc = "Demonstrates how to handle button input, including\ngetting the pressed, held and released buttons.\nAnalog functionality is also shown."},
	{name = "Directory Access", location = "/samples/dir", desc = "A simple filebrowser to show how the pge.dir\nmodule works, including how to differentiate\nbetween a file and a folder."},
	{name = "File Access", location = "/samples/file", desc = "This sample allows you to edit the EBOOT.PBP\nto include your custom images and sounds. Full\npge.file functionality is shown."},
	{name = "Fonts", location = "/samples/font", desc = "Shows how to load a TTF font and display text.\nTwo fonts are loaded and the full character set\nis printed."},
	{name = "Advanced Textures", location = "/samples/graphics/advancedtextures", desc = "A sample to show the advanced features of textures.\nAll aspects of the loaded texture can be manipulated."},
	{name = "Fade", location = "/samples/graphics/fade", desc = "Illustrates how to use the alpha parameter when\ndrawing a texture. Two textures are loaded\nand fade in and out of each other."},
	{name = "Render Target", location = "/samples/graphics/rendertotexture", desc = "A sample that explains how to direct drawing to\na texture object instead of the screen."},
	{name = "Rotation", location = "/samples/graphics/rotation", desc = "A simple demonstration of how to draw a\nrotated texture object based on the analog angle."},
	{name = "Shapes", location = "/samples/graphics/shapes", desc = "Draws the primitive types of pge.gfx in a\nvariety of forms."},
	{name = "Sprites", location = "/samples/graphics/sprites", desc = "Loading and drawing a texture from a spritesheet.\nIncludes how to scale the loaded spritesheet."},
	{name = "Color", location = "/samples/graphics/color", desc = "This sample shows how to manipulate color\nvalues at will."},
	{name = "Math Benchmark", location = "/samples/mathbenchmark", desc = "A benchmark between the pge.math functions\nand Lua's built in math lib."},
	{name = "Net Download", location = "/samples/net/download", desc = "Demonstrates how to download a file from the net."},
	{name = "Net POST form", location = "/samples/net/postform", desc = "Shows how data is transmitted to a PHP page\non the net and receiving the response."},
	{name = "USB Access", location = "/samples/usb", desc = "Enabling and disabling USB access."},
	{name = "Netfront Browser", location = "/samples/utils/browser", desc = "A simple script to launch the PSP's\nNetfront browser."},
	{name = "Net Dialog", location = "/samples/utils/netdialog", desc = "Utilising the net dialog to create a\nconnection to the internet."},
	{name = "Message Dialog", location = "/samples/utils/msgdialog", desc = "Message dialog usage, including how to\ncapture what the user selected."},
	{name = "On Screen Keyboard", location = "/samples/utils/osk", desc = "Entering text using the built-in OSK\nand retrieving what the user input."},
	{name = "Save Data", location = "/samples/utils/savedata", desc = "How to use the savedata dialog to save,\nload, autosave and delete."},
	{name = "ZIP File Access", location = "/samples/zip", desc = "Demonstrates opening a ZIP file then loading\na resource from it."}
}

local index = 1

local basedir = pge.dir.getcwd()

while pge.running() do

	pge.controls.update()
	
	pge.gfx.startdrawing()
	
	pge.gfx.clearscreen()
	
	pge.gfx.drawrect(10, 10, 120, 252, whitesemi)
	pge.gfx.drawrectoutline(10, 10, 120, 252, white)
		
	logo:activate()
	logo:draweasy(0, 0)
	
	verdana9:activate()
	
	for k, n in pairs(samplescripts) do
		if index == k then
			--print("printing")
			verdana9:print(25, 10 + k*10, green, n.name)
		else
			--print("printing2")
			verdana9:print(25, 10 + k*10, white, n.name)
		end
	end
	
	verdana9:print(150, 255, white, "Press CROSS to start the sample and START to return from the sample.")
	
	verdana12:activate()
	
	verdana12:print(145, 160, white, samplescripts[index].name .. "\n\n" .. samplescripts[index].desc)
		
	if pge.controls.pressed(PGE_CTRL_UP) then
		if index > 1 then
			index = index - 1
		end
	end
	
	if pge.controls.pressed(PGE_CTRL_DOWN) then
		if index < #samplescripts then
			index = index + 1
		end
	end
	
	if pge.controls.pressed(PGE_CTRL_CROSS) then
		print(basedir)
		print(samplescripts[index].location)
		pge.dir.chdir(basedir .. samplescripts[index].location)
		--print(pge.dir.getcwd())
		local script = assert(loadfile(basedir .. samplescripts[index].location .. "/script.lua"))
		if script then
			script()
			script = nil
			collectgarbage("collect")
		else
			error("Failed to load script.")
		end
	end
	
	pge.gfx.enddrawing()
	
	pge.gfx.swapbuffers()

end