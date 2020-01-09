function! RangeTest() range
  " 1
  echo a:firstline
  " 5
  echo a:lastline

  for linenum in range(a:firstline, a:lastline)
    echo getline(linenum)
  endfor
endfunction

1,10call RangeTest()
