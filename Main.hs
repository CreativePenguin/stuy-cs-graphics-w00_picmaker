import System.IO
import Control.Monad

main :: IO ()
main = do
  contents <- getContents
  putStrLn("P3")
  putStrLn("500 500")
  putStrLn("255")
  putStrLn(contents)

getColor :: String a => a -> String
getColor randNum = ans --where--
  where ans = r ++ " " ++ g ++ " " ++ b
        r = read randNum % 255
        g = read randNum / 1000 % 255
        b = read randNum / 1000000 % 255
