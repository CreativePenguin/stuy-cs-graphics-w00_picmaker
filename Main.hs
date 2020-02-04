import System.IO
import Control.Monad

main :: IO ()
main = do
  contents <- getContents
  putStrLn("P3")
  putStrLn("500 500")
  putStrLn("255")
  putStrLn(contents)

getColor :: String -> String
getColor randNum = ans --where--
  where ans = r ++ " " ++ g ++ " " ++ b
        r = toString (read randNum :: Int) `mod` 255
        g = (read randNum :: Int) / 1000 `mod` 255
        b = (read randNum :: Int) / 1000000 `mod` 255
