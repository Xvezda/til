let a = [1, 2, 3]
let b = a
let c = deepcopy(a)

echo '- Before remove'
echo printf('a: %s, b: %s, c: %s', string(a), string(b), string(c))

call remove(a, 1)
echo '- After remove'
echo printf('a: %s, b: %s, c: %s', string(a), string(b), string(c))
