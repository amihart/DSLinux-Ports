function fibonacci(n)
  local a, b = 0, 1
  for i = 1, n do
    io.write(a)
    io.write(" ")
    a, b = b, a + b
  end
end

local n = tonumber(arg[1])
if n == nil or n < 0 or n > 93 then
  print("usage: fibonacci [count<=93]")
else
  fibonacci(n)
  print("")
end
