doubleMe x = x + x
doubleUs x y = doubleMe x + doubleMe y
doubleSmallNumber x = if x > 100
                         then x
                         else x*2
doubleSmallNumber' x = (if x > 100 then x else x*2) + 1

-- Function with no argument
conanO'Brien = "It's a-me, Conan O'Brien!"

removeNonUpperCase :: String -> String
removeNonUpperCase st = [ c | c <- st, c `elem` ['A'..'Z'] ]

addThree :: Int -> Int -> Int -> Int
addThree x y z = x + y + z

factorial :: Integer -> Integer
factorial n = product [1..n]

circumference :: Float -> Float
circumference r = 2 * pi * r

circumference' :: Double -> Double
circumference' r = 2 * pi * r

lucky :: (Integral a) => a -> String
lucky 7 = "LUCKY NUMBER SEVEN!"
lucky x = "Sorry, you're out of luck, pal!"

factorial' :: (Integral a) => a -> a
factorial' 0 = 1
factorial' n = n * factorial' (n - 1)

fibonacci :: Int -> Int
fibonacci 0 = 0
fibonacci 1 = 1
fibonacci 2 = 1
fibonacci x =
    if x < 0
       then error "x must be positive number"
       else fibonacci (x-1) + fibonacci (x-2)

fibonacci' :: Int -> [Int]
fibonacci' n = [fibonacci x | x <- [1..n]]

addVectors :: (Num a) => (a, a) -> (a, a) -> (a, a)
-- addVectors a b = (fst a + fst b, snd a + snd b)
addVectors (x1, y1) (x2, y2) = (x1 + x2, y1 + y2)

first :: (a, b, c) -> a
first (a, _, _) = a

second :: (a, b, c) -> b
second (_, b, _) = b

third :: (a, b, c) -> c
third (_, _, c) = c

head' :: [a] -> a
head' [] = error "Can't call head on an empty list, dummy!"
head' (x:_) = x

tell :: (Show a) => [a] -> String
tell [] = "The list is empty"
tell (x:[]) = "The list has one element: " ++ show x
tell (x:y:[]) = "The list has two elements: " ++ show x ++ " and " ++ show y
tell (x:y:_) = "The list is long. The first two elements are: " ++
    show x ++ " and " ++ show y

length' :: (Num b) => [a] -> b
length' [] = 0
length' (_:xs) = 1 + length' xs

-- sum' :: (Num a) => [a] -> a
-- sum' [] = 0
-- sum' (x:xs) = x + sum' xs

bmiTell :: (RealFloat a) => a -> String
bmiTell bmi
  | bmi <= 0.0  = "You're an ghost! Get off!"
  | bmi <= 18.5 = "You're under weight, you emo, you!"
  | bmi <= 25.0 = "You're supposedly normal. Pffft, I bet you're ugly!"
  | bmi <= 30.0 = "You're fat! Lose some weight, fatty!"
  | otherwise   = "You're a whale, congratulations!"

max' :: (Ord a) => a -> a -> a
-- max' a b | a > b = a | otherwise = b
max' a b
  | a > b     = a
  | otherwise = b

myCompare :: (Ord a) => a -> a -> Ordering
a `myCompare` b
  | a > b  = GT
  | a == b = EQ
  | a < b  = LT

bmiTell' :: (RealFloat a) => a -> a -> String
bmiTell' weight height
  | bmi <= 0.0    = "You're an ghost! Get off!"
  | bmi <= skinny = "You're under weight, you emo, you!"
  | bmi <= normal = "You're supposedly normal. Pffft, I bet you're ugly!"
  | bmi <= fat    = "You're fat! Lose some weight, fatty!"
  | otherwise     = "You're a whale, congratulations!"
  where bmi    = weight / height ^ 2
        (skinny, normal, fat) = (18.5, 25.0, 30.0)

initials :: String -> String -> String
-- initials (f:_) (l:_) = [f] ++ ". " ++ [l] ++ "."
initials firstname lastname = [f] ++ ". " ++ [l] ++ "."
    where (f:_) = firstname
          (l:_) = lastname

calcBmis :: (RealFloat a) => [(a, a)] -> [a]
calcBmis xs = [bmi w h | (w, h) <- xs]
    where bmi weight height = weight / height ^ 2

-- Following foo causes error
-- foo a b = bar a b
--     where bar a b = (baz a b) * 2
--           where baz a b = a + b

foo a b = bar a b
    where bar a b = (baz a b) * 2
            where baz a b = a + b

calcBmis' :: (RealFloat a) => [(a, a)] -> [a]
calcBmis' xs = [bmi | (w, h) <- xs, let bmi = w / h ^ 2, bmi >= 25.0]

describeList :: [a] -> String
describeList xs = "The list is " ++ case xs of []  -> "empty."
                                               [x] -> "a singleton list."
                                               xs  -> "a longer list."

-- describeList' :: [a] -> String
-- describeList' xs = "The list is " ++ what xs
--     where what [] = "empty."
--           what [x] = "a singleton list."
--           what xs = "a longer list."

describeList' :: [a] -> String
describeList' xs = "The list is " ++ what xs
    where what xs = case xs of []  -> "empty."
                               [x] -> "a singleton list."
                               xs  -> "a longer list."

-- maximum' :: (Ord a) => [a] -> a
-- maximum' [] = error "maximum of empty list"
-- maximum' [x] = x
-- maximum' (x:xs) = max x (maximum' xs)
-- maximum' (x:xs)
--   | x > maxTail = x
--   | otherwise = maxTail
--   where maxTail = maximum' xs

replicate' :: (Num i, Ord i) => i -> a -> [a]
replicate' n x
  | n <= 0 = []
  | otherwise = x:replicate' (n-1) x

-- take' :: Int -> [a] -> [a]
-- take' n xs
--   | null xs || n <= 0 = []
--   | otherwise = head xs:take' (n-1) (drop 1 xs)

-- take' :: Int -> [a] -> [a]
-- take' n xs
--   | null xs || n <= 0 = []
--   | otherwise = y:take' (n-1) ys
--   where (y:ys) = xs

take' :: (Num i, Ord i) => i -> [a] -> [a]
take' n _
  | n <= 0 = []
take' _ [] = []
take' n (x:xs) = x: take' (n-1) xs

-- reverse' :: [a] -> [a]
-- reverse' [] = []
-- reverse' [x] = [x]
-- reverse' (x:xs) = reverse' xs ++ [x]

repeat' :: a -> [a]
repeat' x = x:repeat' x

zip' :: [a] -> [b] -> [(a, b)]
zip' [] _ = []
zip' _ [] = []
zip' (x:xs) (y:ys) = (x, y):zip' xs ys

-- elem' :: (Eq a) => a -> [a] -> Bool
-- elem' _ [] = False
-- elem' a (x:xs)
--   | a == x    = True
--   | otherwise = elem' a xs

quicksort :: (Ord a) => [a] -> [a]
quicksort [] = []
quicksort (x:xs) =
    quicksort [a | a <- xs, a <= x] ++ [x] ++ quicksort [a | a <- xs, x < a]

applyTwice :: (a -> a) -> a -> a
applyTwice f x = f (f x)

zipWith' :: (a -> b -> c) -> [a] -> [b] -> [c]
zipWith' _ _ [] = []
zipWith' _ [] _ = []
zipWith' f (x:xs) (y:ys) = f x y : zipWith' f xs ys

-- flip' :: (a -> b -> c) -> (b -> a -> c)
-- flip' f = g
--     where g x y = f y x
flip' :: (a -> b -> c) -> b -> a -> c
flip' f y x = f x y

-- map' :: (a -> b) -> [a] -> [b]
-- map' _ [] = []
-- map' f (x:xs) = f x : map' f xs

-- filter' :: (a -> Bool) -> [a] -> [a]
-- filter' _ [] = []
-- filter' p (x:xs)
--   | p x       = x : filter' p xs
--   | otherwise = filter' p xs

quicksort' :: (Ord a) => [a] -> [a]
quicksort' [] = []
quicksort' (x:xs) =
    quicksort' (filter (<=x) xs) ++ [x] ++ quicksort' (filter (x<) xs)

largestDivisible :: (Integral a) => a
largestDivisible = head (filter p [100000,99999..])
    where p x = x `mod` 3829 == 0

takeWhile' :: (a -> Bool) -> [a] -> [a]
takeWhile' p (x:xs)
  | p x       = x : takeWhile' p xs
  | otherwise = []

chain :: (Integral a) => a -> [a]
chain 1 = [1]
chain n
  | even n = n : chain (n `div` 2)
  | odd n = n : chain (n*3 + 1)

numLongChains :: (Num a) => a
numLongChains = fromIntegral (howMany (filter isLong (map chain [1..100])))
    where howMany = length
          isLong xs = length xs > 15

numLongChains' :: Int
numLongChains' = length (filter (\xs -> length xs > 15) (map chain [1..100]))

addThree' :: (Num a) => a -> a -> a -> a
-- addThree' x y z = (x+y+z)
-- addThree' = \x -> \y -> \z -> x + y + z
addThree' = (\x -> (\y -> (\z -> (x + y + z))))

sum' :: (Num a) => [a] -> a
-- sum' xs = foldl (\acc x -> acc + x) 0 xs
-- sum' = foldl (+) 0
sum' = foldl1 (+)

elem' :: (Eq a) => a -> [a] -> Bool
elem' x xs = foldl (\acc y -> if y == x then True else acc) False xs

map' :: (a -> b) -> [a] -> [b]
-- Too expensive
-- map' f xs = foldl (\acc x -> acc ++ [f x]) [] xs
map' f xs = foldr (\x acc -> f x : acc) [] xs

maximum' :: (Ord a) => [a] -> a
maximum' = foldr1 (\x acc -> if x > acc then x else acc)

reverse' :: [a] -> [a]
-- reverse' = foldl (\acc x -> x : acc) []
reverse' = foldl (flip (:)) []

product' :: (Foldable t, Num a) => t a -> a
-- product' xs = foldr (\x acc -> x * acc) 1 xs
product' = foldr1 (*)

filter' :: (a -> Bool) -> [a] -> [a]
-- filter' _ [] = []
-- filter' p (x:xs)
--   | p x       = x : filter' p xs
--   | otherwise = filter' p xs
filter' p = foldr (\x acc -> if p x then x : acc else acc) []

last' :: [a] -> a
last' = foldl1 (\_ x -> x)

-- foldl' :: Foldable t => (b -> a -> b) -> b -> t a -> b
foldl' _ a [] = a
foldl' f a (x:xs) = foldl' f (f a x) xs

-- foldr' _ a [] = a
-- foldr' f a (x:xs) = foldr' f (f x a) xs

foldr' f a [] = a
foldr' f a (x:xs) = f x (foldr' f a xs)

scanl' _ a [] = [a]
scanl' f a (x:xs) = a : scanl' f (f a x) xs


-- TODO: How to implement scanr?
