PATH=$PATH:"$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
export PATH
echo "Ready. Type 'minetestmapper --help' for usage information"
exec $SHELL
