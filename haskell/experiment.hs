-- Too imperative
indexOf :: (Eq a) => [a] -> a -> Int
xs `indexOf` x = if null found then -1 else head found
    where found = [i | i <- [0 .. (length xs)-1], xs !! i == x]

-- Using recursion
indexOf' :: (Eq a) => [a] -> a -> Int
-- Edge case
indexOf' [] _ = -1
-- Pattern match
indexOf' (x:xs) a
  | x == a = 0
  | not (a `elem` xs) = -1
  | otherwise = 1 + indexOf' xs a

toUpperCase :: String -> String
toUpperCase xs = [if x `elem` lowercases
                     then uppercases !! (lowercases `indexOf` x)
                     else x | x <- xs]
                         where lowercases = ['a' .. 'z']
                               uppercases = ['A' .. 'Z']


-- zip' :: [a] -> [b] -> [(a, b)]
-- zip' xs ys = [ (xs !! i, ys !! i) | i <- [0 .. (min (length xs) (length ys))-1] ]

split :: String -> Char -> [String]
split "" _ = []
split (x:"") c
  | x == c = ["", ""]
split s c
  | last s == c = split (init s) c ++ [""]
  | otherwise   = t : split remain c
    where t      = takeWhile (/= c) s
          remain = drop (length t + 1) s

enumerate :: (Num b) => [a] -> [(b, a)]
enumerate =
    foldr (\x acc -> (if null acc then 0 else fst (head acc) + 1, x) : acc) []

primes :: (Integral a, Eq a) => a -> [a]
primes n = [x | x <- [2..n], foldr (\y acc -> x `mod` y /= 0 && acc) True [2..(x-1)]]


