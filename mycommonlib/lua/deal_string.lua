

-- 实现16进制和字符串之间互相转化
-- 作者
-- http://ju.outofmemory.cn/entry/201979


function str2hex(str)
	--判断输入类型
        if (type(str)~="string") then
	    return nil,"str2hex invalid input type"
        end

        --滤掉分隔符
        str=str:gsub("[%s%p]",""):upper()
        --检查内容是否合法
        if(str:find("[^0-9A-Fa-f]")~=nil) then
	    return nil,"str2hex invalid input content"
	end
        --检查字符串长度
        if(str:len()%2~=0) then
	    return nil,"str2hex invalid input lenth"
	end
        --拼接字符串
        local index=1
	local ret=""
	for index=1,str:len(),2 do
	    ret=ret..string.char(tonumber(str:sub(index,index+1),16))
	end
	
	return ret
end

function hex2str(hex)
	if (type(hex)~="string") then
        	return nil,"hex2str invalid input type"
	end
	
        local index=1
	local ret=""
	local tmp=""
	for index=1,hex:len(),2 do
		tmp = '0x'..string.sub(hex,index,index+1)
		ret = ret..string.char(tmp)
	end

	return ret
end


print(str2hex("1234ABCD"))
