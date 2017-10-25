import Prelude hiding (lookup)

data DT key val = Nil | Node key val Int (DT key val) (DT key val) deriving(Show)

lookup :: Ord key => key -> DT key val -> Maybe val
lookup k Nil = Nothing
lookup k (Node key val sz left right)
	| key == k = Just val
	| key < k = lookup k right
	| key > k = lookup k left

size :: DT key val -> Int
size Nil = 0
size (Node key val sz left right) = sz
lch :: DT key val -> DT key val
lch Nil = Nil
lch (Node key val sz left right) = left
rch :: DT key val -> DT key val
rch Nil = Nil
rch (Node key val sz left right) = right
gkey :: DT key val -> key
gkey Nil = undefined
gkey (Node key val sz left right) = key
gval :: DT key val -> val
gval Nil = undefined
gval (Node key val sz left right) = val

--abs :: Int -> Int
--abs x
--	| x < 0 = (-x)
--	| otherwise = x

rand :: DT key val -> DT key val -> Int
rand left right = abs(((size left) + 239) ^ 179 + ((size right) + 179) ^ 239)

check :: DT key val -> DT key val -> Bool
check left right
	| ((rand left right) `mod` ((size left) + (size right) - 1)) < (size left) = False
	| otherwise = True

split :: Ord key => DT key val -> key -> [DT key val]
split Nil k = (Nil:Nil:[])
split (Node key val sz left right) k
	| key == k = (left:right:[])
	| key < k = (Node key val (sz - (size sc1)) left fr1 : sc1 : [])
	| key > k = (fr2 : Node key val (sz - (size fr2)) sc2 right : [])
	where
		sp1 = split right k
		fr1 = head sp1
		sc1 = head (tail sp1)
		sp2 = split left k
		fr2 = head sp2
		sc2 = head (tail sp2)

merge :: Ord key => DT key val -> DT key val -> DT key val
merge Nil right = right
merge left Nil = left
merge left right
	| check left right = Node (gkey left) (gval left) ((size (lch left)) + (size mr1) + 1) (lch left) mr1
	| otherwise = Node (gkey right) (gval right) ((size mr2) + (size (rch right)) + 1) mr2 (rch right)
	where
		mr1 = merge (rch left) right
		mr2 = merge left (lch right)

insert :: Ord key => key -> val -> DT key val -> DT key val
insert key val tree = merge fr (merge (Node key val 1 Nil Nil) sc)
	where
		sp = split tree key
		fr = head sp
		sc = head (tail sp)

delete :: Ord key => key -> DT key val -> DT key val
delete key tree = merge fr sc
	where
		sp = split tree key
		fr = head sp
		sc = head (tail sp)