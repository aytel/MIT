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

split :: Ord key => DT key val -> key -> (DT key val, DT key val)
split Nil k = (Nil, Nil)
split (Node key val sz left right) k
	| key == k = (left, right)
	| key < k = (Node key val (sz - (size fst_right)) left fst_right, snd_right)
	| key > k = (fst_left, Node key val (sz - (size snd_left)) snd_left right)
	where
		split_right = split right k
		fst_right = fst split_right
		snd_right = snd split_right
		split_left = split left k
		fst_left = fst split_left
		snd_left = snd split_left

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
insert key val tree = merge fs (merge (Node key val 1 Nil Nil) sn)
	where
		sp = split tree key
		fs = fst sp
		sn = snd sp

delete :: Ord key => key -> DT key val -> DT key val
delete key tree = merge fs sn
	where
		sp = split tree key
		fs = fst sp
		sn = snd sp