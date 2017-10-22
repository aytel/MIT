head' :: [a] -> a
head' (x:_) = x

tail' :: [a] -> [a]
tail' (_:y) = y

take' :: Int -> [a] -> [a]
take' 0 x = []
take' n (x:y) = (x : take' (n - 1) y)

drop' :: Int -> [a] -> [a]
drop' 0 x = x
drop' n [] = []
drop' n (x:y) = drop' (n - 1) y

filter' :: (a -> Bool) -> [a] -> [a]
filter' f (x:y)
	| f x == True = (x : filter' f y)
	| otherwise = filter' f y
filter' f [] = []

foldl' :: (a -> b -> a) -> a -> [b] -> a
foldl' f z [] = z
foldl' f z (x:y) = foldl' f (f z x) y

concat' :: [a] -> [a] -> [a]
concat' (x:y) a = (x : concat' y a)
concat' [] a = a

quicksort' :: Ord a => [a] -> [a]
quicksort' [] = []
quicksort' (x:y) = concat' (concat' (quicksort'(filter' (< x) y)) (filter' (== x) y)) (concat' (x:[]) (quicksort'(filter' (> x) y)))