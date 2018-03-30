#include<bits/stdc++.h>
using namespace::std;

const int N = 2050;

int n, m;
int v[N];
bool primero;
int l[12][N];
int r[12][N];
int val[12][N];

void traverse(int depth, int pos){
	if(depth == 0){ // Si estamos en el valor mismo
		if(primero) printf("%d",val[depth][pos]); // Si es el primero 
		else printf(" %d",val[depth][pos]); // Si no es el primero
		primero = false;
		return;
	}
	traverse(depth-1,l[depth][pos]); // Hijo izquierdo
	traverse(depth-1,r[depth][pos]); // Hijo Derecho
}

int main(){
	int x;
	while(scanf("%d",&n)==1 and n){
		m = int(n<<1)-1;
		for(int i=0; i<m; i++) scanf("%d",v+i); // Leer datos

		// Asignacion del primer nivel del arbol (hojas)

		for(int i=0; i<m; i++){
			l[0][i] = i;
			r[0][i] = i;
			val[0][i] = v[i];
		}

		// Empezamos en nivel 1 de manera ascendente
		int depth = 1;
		
		// Iteramos hasta llegar al ultimo bit significativo de m
		// Definicion de cada nivel
		// Si un valor pertenece a al nivel i
		// Entonces ese valor es tiene puros 0 en su representacion binaria hasta el i-esimo bit

		while(m > 1){
			int impar = -1, par = -1, nodos = 0;
			for(int i=0; i<m; i++){
				if(val[depth-1][i]&1){
					// Es un valor impar en el bit depth
					if(impar == -1){ // Primer elemento del par
						impar = i;
					}
					else{ // Asignamos la pareja como su suma al siguiente nivel
						// Primer valor usado a la izquierda
						l[depth][nodos] = impar;
						// Segundo valor usado a la derecha
						r[depth][nodos] = i; 
						// Nuevo valor
						int x = (val[depth-1][impar]+val[depth-1][i])/2;
						// Asignamos el nuevo valor
						val[depth][nodos] = x; 
						// Aumentamos la cantidad de nodos en este nivel
						nodos+=1; 
						// Ahora buscaremos otra pareja
						impar = -1; 
					}
				}
				else{
					// Igual que para el caso par
					if(par == -1){ 
						par = i;
					}
					else{
						l[depth][nodos] = par;
						r[depth][nodos] = i;
						int x = (val[depth-1][par]+val[depth-1][i])/2;
						val[depth][nodos] = x;
						nodos += 1;
						par = -1;
					}
				}
			}
			m >>= 1; // Reducimos 1 bit
			depth += 1; // Aumentamos el nivel
		}
		primero = true; // Para imprimir bien, si es el primer valor impreso
		puts("Yes"); // Si hay solucion
		traverse(depth-1,0); // Imprimimos la solucion de manera recursiva
		puts("");
	}
	return 0;
}
