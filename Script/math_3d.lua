local vector3 = {}

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

---是否是零向量
function vector3:isZeroVector()

end

---归一化
---@return vector3
function vector3:normalize()
end

---vector3单元测试
local function vector3_test()
	local vec = vector3.new()
	vec.x = 10
	vec.y = 2
	vec.z = 5
	print(vec:length())
end

local quat = {}

---单位四元数
---@return 单位四元数
function quat_unit()
	local quat = {w=1,x=0,y=0,z=0}
	return quat
end

---根据旋转轴、旋转角度构造四元数
---@param n
---@param theta
function quat_from_n_theta(n, theta)
	local quat = {w=1,x=0,y=0,z=0}
	return quat
end

---四元数指数

---四元数求幂

---四元数叉乘
function quat_cross(q1, q2)
end

---四元数点乘
function quat_dot(q1, q2)
end

---四元数求逆
function quat_inverse(q)
end

---四元数插值
function quat_slerp(q1, q2, t)
end

---单元测试
local function math_3d_test()
	vector3_test()
end

math_3d_test()
