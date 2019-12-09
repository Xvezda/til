if True:
  foo = 'bar'

# It will not cause the error
print foo

# ---

if False:
  hello = 'world'

# It will cause the error
try:
  print hello
except:
  print 'error'

# ---

try:
  x = 1
except:
  pass
print x
