--[[
    测试Lua语言本身的特性
--]]


-- 当做数组来使用
local function table_array()
    local list = {}
    table.insert(list, { name = "Tom", age = "12" })
    table.insert(list, { name = "Lee", age = "13" })
    table.insert(list, { name = "Jim", age = "14" })

    -- 将输出索引：1,2,3
    for k, v in pairs(list) do
        print(k .. ":" .. v.name)
    end
end

-- 当做map来使用
local function table_map()
    local map = {}
    map["Tom"] = { name = "Tom", age = "12" }
    map["Lee"] = { name = "Lee", age = "13" }
    map["Jim"] = { name = "Jim", age = "14" }

    -- 将输出map的Key："Tom"、"Lee"、"Jim"
    for k, v in pairs(map) do
        print(k .. ":" .. v.age)
    end

    -- 使用`#`取上面的map长度，返回0
    assert(#map == 0)

    -- 删除某个键值对
    print("delete key: Lee")
    map["Lee"] = nil
    for k, v in pairs(map) do
        print(k .. ":" .. v.age)
    end
end

-- 测试string
local function test_string()
    str="123 456"
    for k,v in str:gmatch("(%d+)") do
        print(tostring(k))
    end
end

-- 打印加载的模块
local function test_print_loaded_package()
    for k,v in pairs(package.loaded) do
        print(k)
    end
end

-- 测试table的一种初始化
local function test_table_init2()
    ROLE_TYPE = {
        HERO = 1,
        MONSTER = 2,
        PLAYER = 3,
    }
    
    -- 必须要在ROLE_TYPE.HERO两边加上[]，否则编译不过
    m = {
        [ROLE_TYPE.HERO] = 3,
        [ROLE_TYPE.MONSTER] = 4,
        [ROLE_TYPE.PLAYER] = 5,
    }

    for k, v in ipairs(m) do
        print(tostring(k) .. ":" .. tostring(v))
    end
end

-- 获取table长度
local function test_table_len()
	gdEquipEnchantPromote = {}
	
	gdEquipEnchantPromote[1] = {}
	gdEquipEnchantPromote[2] = {}
	gdEquipEnchantPromote[3] = {}
	gdEquipEnchantPromote[4] = {}
	gdEquipEnchantPromote[15] = {}
	
	--[[
	table.getn已经废弃了
	assert(4 == table.getn(gdEquipEnchantPromote))
	print("gdEquipEnchantPromote lengths is: " .. tostring(table.getn(gdEquipEnchantPromote)))
	--]]
	
	assert(4 == #gdEquipEnchantPromote)
	print("gdEquipEnchantPromote lengths is: " .. tostring(#gdEquipEnchantPromote))
end

-- 测试变量作用域
local function test_var_scope()
	local val = 100
	
	if true then
		local val = 90
		val = val + 1
		assert(val == 91)
		print("val=" .. val)
	end
	
	assert(val == 100)
	print("val=" .. val)
end

--测试正则匹配
local function test_gmatch()
    local desc = "被攻击时,有[g5%]的几率触发[r不破金刚]：物理、魔法免伤提高：[g10%], 每[g60]秒最多触发1次"
	
    for s in string.gmatch(desc, "%[.*%]") do
        print(s)
    end

    --懒惰匹配
    -- for s in string.gmatch(desc, "%[.*?%]") do
    --     print(s)
    -- end
	
	--匹配出中括号[]中的所有文本
	for _, _, s, _ in string.gmatch(desc, "()%[(%a)(.-)%]()") do
        print(s)
    end
end

--模拟“三目运算”
local function test_threeop()
	print(1 > 3 and 1 or 0)
	print(1 > 3 and 0 or 1)
	print(3 > 1 and 0 or 1)
	print(3 > 1 and nil or 1)
	--[[
	https://www.runoob.com/w3cnote/trinocular-operators-in-lua.html
	运算符优先级从高到低为：not、and、or
	x and y or z：
	x and y为true：则返回y
	x and y为false：则返回z
	综上所述：
	--]]
end

-- 测试nil作为key
local function test_nil_key()
	local tab = { 1, 2, 3 }
	print(tab[1] == 1)
	assert(tab[nil] == nil)
	
	--[[运行时将报错
	tab[nil] = 666
	--]]
end

--测试函参个数
local function test_func_param_count()
	local sum = function(x, y, z)
		local res = 0
		res = res + (x or 0)
		res = res + (y or 0)
		res = res + (z or 0)
		return res
	end
	--少传的参数为nil，多传的参数将被忽略
	assert(sum(1) == 1)
	assert(sum(1, 2) == 3)
	assert(sum(1, 2, 3) == 6)
	assert(sum(1, 2, 3, 4) == 6)
	
	print(sum(1))
	print(sum(1, 2))
	print(sum(1, 2, 3))
	print(sum(1, 2, 3, 4))
end

local function test_gfind1()
	--gfind也废弃了，使用gmatch
	local reward = "1,30021"
	for k, v in string.gmatch(reward, "(%d+)") do
		print(k)
	end
end

table_array()
table_map()
test_string()
test_print_loaded_package()
test_table_init2()
test_table_len()
test_var_scope()
test_gmatch()
test_threeop()
test_nil_key()
test_func_param_count()
test_gfind1()
