

-- lua实现ip和整数 互相转化

-- ip to int
function ipToInt( str )
        local num = 0
        if str and type(str)=="string" then
                local o1,o2,o3,o4 = str:match("(%d+)%.(%d+)%.(%d+)%.(%d+)" )
                num = 2^24*o1 + 2^16*o2 + 2^8*o3 + o4
        end
    return num
end

print(ipToInt("127.0.0.1"))



-- int to ip
function  intToIp( n )
      if n then
              n = tonumber(n)
              local n1 = math.floor(n / (2^24))
              local n2 = math.floor((n - n1*(2^24)) / (2^16))
              local n3 = math.floor((n - n1*(2^24) - n2*(2^16)) / (2^8))
              local n4 = math.floor((n - n1*(2^24) - n2*(2^16) - n3*(2^8)))
              
              return n1.."."..n2.."."..n3.."."..n4
      end

      return "0.0.0.0"
end
    
print(intToIp(2130706433))
