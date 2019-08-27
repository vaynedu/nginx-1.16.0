
--lua 的随机的数是封装C语言random,实现的是伪随机数,如果请求速度过快,产生的uuid是相同的
--这是一个比较垃圾的uuid

function get_uuid()
    local seed={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'}
    local tb={}
	math.randomseed(os.time())
    for i=1,32 do
        table.insert(tb,seed[math.random(1,16)])
    end
    local sid=table.concat(tb)
	print(sid)
    local u1 = string.sub(sid,1,8)
	local u2 = string.sub(sid,9,12)
	local u3 = string.sub(sid,13,16)
	local u4 = string.sub(sid,17,20)
	local u5 = string.sub(sid,21,32)

	return u1..'-'..u2..'-'..u3..'-'..u4..'-'..u5
end

--uuid:  b0a4d078-c5c4-451a-ad5f-9156ea08686c

print(get_uuid())


