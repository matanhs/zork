local open = io.open

local function read_file(path)
    local file = open(path, "r") -- r read mode and b binary mode
    if file == nil then return nil end
    local content = file:read("*all") -- *a or *all reads the whole file
    file:close()
    return content
end

print ("start zork test in lua")
zork = require 'zork'
print ("zork module loaded")
local result_file_name = zork.zorkInit();
print ("zork Init returned")
local step_string = read_file(result_file_name);
print ("file read returned with the content:")
print (step_string)
print ("try game step command")
result_file_name = zork.zorkGameStep("w")
local step_string = read_file(result_file_name);
print (step_string)
