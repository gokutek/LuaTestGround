local MyExtension = require("MyExtension")
local n, s = MyExtension.encode()
print(n)
print(s)

local MyExtensionMath = require("MyExtension.Math")
print(MyExtensionMath.add(10, 20))
