-- test script for LuaWrapper

-- global variables can be use as settings

n = 42
pi = 3.14
text = "default"


function hello(msg)
    print("Lua prints message: '" .. msg .. "'.")
    return "Hi back from Lua!"
end


function add_one_week(date, format)
    print("Adding one week to this date string " .. date .. " (format " .. format .. ")")
    seconds = cb_datestr2seconds(date, format)
    seconds = seconds + 3600 * 24 * 7;
    later = cb_seconds2datestr(seconds, format)
    print("New date string " .. later)
    return later
end
