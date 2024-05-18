echo oi <                  
echo oi <<         
echo oi >
echo oi >>        
| echo oi
echo oi |
echo oi |         
echo oi > | ls
echo oi > file | ls |
echo oi > file | ls |       
echo oi |        | ls
echo "oi" 'mundo
echo 'o" 'i"
echo "c"'o'"m'"'o' "v"'ai 'm"u"n''''"d'"ão''"?

		// errado
		|
		| echo oi
		echo oi |
		| |
		echo oi "> file | ls" | ls |      
		           | echo oi
		echo oi |        | ls

		// correto
		ls | echo
		ls | > file
		ls|>file
		echo | echo | << file | echo