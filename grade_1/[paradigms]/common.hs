data List' t = Nil | Head t (List' t) deriving Show

fromList :: [t] -> List' t
fromList [] = Nil
fromList (x:y) = Head x (fromList y)

toList :: List' t -> [t]
toList Nil = []
toList (Head x y) = (x : toList y)

main = Nothing