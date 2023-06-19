export ZSH="$HOME/.oh-my-zsh"
ZSH_THEME="robbyrussell"


plugins=(git)

source $ZSH/oh-my-zsh.sh

export TASK_NO="a"
function ac() {
	    case $1 in
				"chk")
					echo "TASK_NO: $TASK_NO"
					echo "down:" && cat ./down
					echo "s:" && cat ./s
					;;
				"set")
				    if [$# -lt 2 ]; then
				        echo need parameter: ROUND_NO
				        return 11
				    fi
					if [ "$(pwd)" != "/Users/user/CLionProjects/BOJ/scripts" ]; then
						cd /Users/user/CLionProjects/BOJ/scripts
					fi

					sh set "$2"
					export TASK_NO="a"
					sh down "$TASK_NO"
					;;
				"s")
					if [ $# -gt 1 ]; then
						sh s "$2"
					else
						contents=$(<./s)
						contents=${contents//\$1/$TASK_NO}
						echo -n "Run $contents (y/n): "
						read ans < /dev/tty
						echo
						case $ans in
							[Yy])
								sh s "$TASK_NO"
								;;
							*)
								return
								;;
						esac
					fi
					;;
				"t")
					shift
					sh t
					;;
				"nxt")
					prv=$TASK_NO
					case $TASK_NO in
    					[a-y])
							next_char=$(printf "\x$(printf '%x' $(($(printf '%d' "'$TASK_NO")+1)))")
					        ;;
					    z)
					        next_char="a"
					        ;;
					    *)
					        next_char="a"
					        ;;
					esac

					export TASK_NO="$next_char"
					echo "change TASK_NO: $prv -> $next_char"
					sh down "$TASK_NO"
					;;
				"down")
					if [ $# -gt 1 ]; then
						sh down "$2"
					else
						sh down "$TASK_NO"
					fi
					;;
				*)
				echo "Invalid command: $1"
				;;
		esac
}

