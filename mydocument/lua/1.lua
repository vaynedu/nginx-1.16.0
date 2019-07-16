
origin_filename="00_t0635gds69v.320179.1.mp4"
local hy_filename = string.gsub(origin_filename, "(00_.*\.mp4)", "%1")
if(hy_filename ~= nil) then
   print(hy_filename)
   hy_filename =1
  print(hy_filename)
else
     hy_filename =0
  print(hy_filename)
end

print("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
hy_filename = string.find(origin_filename, "(00_.*\.mp4)")
if(hy_filename ~= nil) then
   print(hy_filename)
   hy_filename =1
  print(hy_filename)
else
     hy_filename =0
  print(hy_filename)
end





print("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb")


     local is_mp4_fisrt_flag = string.find(origin_filename, "(00_.*\.mp4)")
     if(is_mp4_fisrt_flag   ~= nil) then
        is_mp4_fisrt_flag = 1
     else
        is_mp4_fisrt_flag = 0
     end

print(is_mp4_fisrt_flag)

