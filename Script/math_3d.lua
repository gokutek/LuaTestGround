local vector3 = {}
local vector4 = {}
local matrix4x4 = {}
local euler = {}
local quat = {}

---构造vector3
function vector3.new()
	local vec3 = {x=0,y=0,z=0}
	setmetatable(vec3, {__index=vector3})
	return vec3
end

---返回零向量
---@return vector3
function vector3.zero()
	local vec = vector3.new()
	vec.x = 0
	vec.y = 0
	vec.z = 0
	return vec
end

---求模
---@return number
function vector3:length()
	return math.sqrt(self.x*self.x + self.y*self.y + self.z*self.z)
end

---归一化
---@return vector3
function vector3:normalize()
	local result = vector3.new()
	local len = self:length()
	if len ~= 0 then
		result.x = self.x/len
		result.y = self.y/len
		result.z = self.z/len
	end
	return result
end

---判断两个向量是否相等
---@param vec vector3
---@param epsilon number 允许的误差
---@return boolean
function vector3:equal(vec, epsilon)
	if not epsilon then
		epsilon = 0.00001
	end
	return (math.abs(self.x-vec.x) <= epsilon
			and math.abs(self.y-vec.y) <= epsilon
			and math.abs(self.z-vec.z) <= epsilon)
end

---点乘
---@param vec vector3
---@return number
function vector3:dot(vec)
	return self.x*vec.x + self.y*vec.y + self.z*vec.z
end

---叉乘
---@param vec vector3
---@return vector3
function vector3:cross(vec)
	local result = vector3.new()
	--TODO:
	return result
end

---向量+向量
---@param vec vector3
---@return vector3
function vector3:add(vec)
	local result = vector3.new()
	result.x = self.x + vec.x
	result.y = self.y + vec.y
	result.z = self.z + vec.z
	return result
end

---向量-向量
---@param vec vector3
---@return vector3
function vector3:sub(vec)
	local result = vector3.new()
	result.x = self.x - vec.x
	result.y = self.y - vec.y
	result.z = self.z - vec.z
	return result
end

---向量*标量
---@param scalar number
---@return vector3
function vector3:mul(scalar)
	local result = vector3.new()
	result.x = self.x * scalar
	result.y = self.y * scalar
	result.z = self.z * scalar
	return result
end

---vector3单元测试
local function vector3_test()
	local vec = vector3.new()
	vec.x = 10
	vec.y = 2
	vec.z = 5
	print(vec:length())
end

---构造单位四元数
---@return 单位四元数
function quat.new()
	local q = {w=1,x=0,y=0,z=0}
	setmetatable(q, {__index=quat})
	return q
end

---根据旋转轴、旋转角度构造四元数
---@param n vector3
---@param theta number
function quat.from_n_theta(n, theta)
	local q = quat.new()
	return q
end

---四元数插值
function quat.slerp(q1, q2, t)
end

---四元数指数

---四元数求幂

---四元数叉乘
function quat:cross(q)
end

---四元数点乘
function quat:dot(q)
end

---四元数求逆
function quat:inverse(q)
end

---单元测试
local function math_3d_test()
	vector3_test()
end

math_3d_test()
