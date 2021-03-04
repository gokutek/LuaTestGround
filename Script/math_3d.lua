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

---构造vector4
---@return vector4
function vector4.new()
	local vec = {x=0,y=0,z=0,w=0}
	setmetatable(vec, {__index=vector4})
	return vec
end

---向量x矩阵
---@param m matrix4x4
---@return vector4
function vector4:transform(m)
	--TODO:
end

---构造一个4x4矩阵
---@return matrix4x4单位矩阵
function matrix4x4.new()
	local m = {}
	m._11 = 1; m._12 = 0; m._13 = 0; m._14 = 0
	m._21 = 0; m._22 = 1; m._23 = 0; m._24 = 0
	m._31 = 0; m._32 = 0; m._33 = 1; m._34 = 0
	m._41 = 0; m._42 = 0; m._43 = 0; m._44 = 1
	setmetatable(m, {__index=matrix4x4})
	return m
end

---矩阵求逆
function matrix4x4:inverse()
	--TODO:
end

---矩阵的行列式
function matrix4x4:det()
	--TODO:
end

---矩阵x矩阵
function matrix4x4:mul()
	--TODO:
end

---平移变换矩阵
---@return matrix4x4
function matrix4x4:translate()
	--TODO:
end

---缩放变换矩阵
---@return matrix4x4
function matrix4x4:scale()
	--TODO:
end

---绕X轴的旋转变换矩阵
---@return matrix4x4
function matrix4x4:rotateX()
	--TODO:
end

---绕Y轴的旋转变换矩阵
---@return matrix4x4
function matrix4x4:rotateY()
	--TODO:
end

---绕Z轴的旋转变换矩阵
---@return matrix4x4
function matrix4x4:rotateZ()
	--TODO:
end

---绕任意轴的旋转变换矩阵
function matrix4x4:rotateAxis()
	--TODO:
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
---@return quat
function quat.slerp(q1, q2, t)
end

---四元数的`差`
---@return quat
function quat:difference(q)
	--TODO:
end

---四元数对数
---@return quat
function quat:log()
	--TODO:
end

---四元数指数
---@return quat
function quat:exp()
	--TODO:
end

---四元数求幂

---四元数x四元数
---@param q quat
---@return quat
function quat:cross(q)
end

---四元数·四元数
---@param q quat
---@return number
function quat:dot(q)
	return self.w*q.w + self.x*q.x + self.y*q.y + self.z*q.z
end

---四元数求逆
---@return quat
function quat:inverse(q)
end

---单元测试
local function math_3d_test()
	vector3_test()
end

math_3d_test()
