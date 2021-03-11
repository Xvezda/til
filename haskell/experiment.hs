indexOf :: (Eq a) => [a] -> a -> Int
xs `indexOf` x = if null found then -1 else head found
    where found = [i | i <- [0 .. (length xs)-1], xs !! i == x]
