none:
	g++ edge_coupled_cpwg.cpp -o edge_coupled_cpwg

install:
	install -p -s edge_coupled_cpwg /usr/bin

uninstall:
	rm -f /usr/bin/edge_coupled_cpwg
